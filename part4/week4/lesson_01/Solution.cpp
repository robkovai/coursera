#include "Common.h"

#include <functional>
#include <stdexcept>

using namespace std;

namespace Shapes {

class Shape : public IShape {
public:
    void SetPosition(Point position) override {
        this->position = position;
    }

    Point GetPosition() const override {
        return this->position;
    }

    void SetSize(Size size) override {
        this->size = size;
    }

    Size GetSize() const override {
        return this->size;
    }

    void SetTexture(std::shared_ptr<ITexture> texture) override {
        this->texture = texture;
    }

    ITexture* GetTexture() const override {
        return this->texture.get();
    }

protected:
    char GetTexturePixel(Point position) const {
        char pixel = '.';
        if (this->GetTexture())
            if (position.y < this->GetTexture()->GetSize().height && position.x < this->GetTexture()->GetSize().width)
                pixel = this->GetTexture()->GetImage()[position.y][position.x];
        return pixel;
    }

    void DrawPixel(Image &image, Point position) const {
        size_t x = this->GetPosition().x + position.x;
        size_t y = this->GetPosition().y + position.y;
        if (y < image.size() && x < image[y].size())
            image[y][x] = this->GetTexturePixel(position);
    }

    void DrawShape(Image &image, std::function<bool(Point)> condition = nullptr) const {
        for (int x = 0; x < this->GetSize().width; ++x) {
            for (int y = 0; y < this->GetSize().height; ++y) {
                Point position = {x, y};
                if (condition && !condition(position))
                    continue;
                this->DrawPixel(image, position);
            }
        }
    }

private:
    Point position;
    Size size;
    std::shared_ptr<ITexture> texture;
};

class Rectangle : public Shape {
public:
    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(*this);
    }

    void Draw(Image& image) const override {
        this->DrawShape(image);
    }
};

class Ellipse : public Shape {
    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(*this);
    }

    void Draw(Image& image) const override {
        this->DrawShape(image, [this](Point position) {
            return IsPointInEllipse(position, this->GetSize());
        });
    }
};

} // Shapes

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle: return make_unique<Shapes::Rectangle>();
        case ShapeType::Ellipse: return make_unique<Shapes::Ellipse>();
        default: throw invalid_argument("unknown shape_type");
    }
}
