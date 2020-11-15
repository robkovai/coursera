#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

const double Pi = 3.14;

class Figure {
public:    
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Rect : public Figure {
public:
    Rect(double width, double height): width(width), height(height) {}

    string Name() const override {
        return "RECT";
    }

    double Perimeter() const override {
        return width * 2 + height * 2;
    }

    double Area() const override {
        return width * height;
    }

private:
    const double width;
    const double height;
};

class Triangle : public Figure {
public:
    Triangle(double a, double b, double c): a(a), b(b), c(c) {}

    string Name() const override {
        return "TRIANGLE";
    }

    double Perimeter() const override {
        return a + b + c;
    }

    double Area() const override {
        const double p = Perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    const double a;
    const double b;
    const double c;
};

class Circle : public Figure {
public:
    Circle(double radius): radius(radius) {}

    string Name() const override {
        return "CIRCLE";
    }

    double Perimeter() const override {
        return Pi * radius * 2;
    }

    double Area() const override {
        return Pi * pow(radius, 2);
    }

private:
    const double radius;        
};

shared_ptr<Figure> CreateFigure(istream &stream) {
    string figure;
    stream >> figure;
    if (figure == "RECT") {
        double width, height;
        stream >> width >> height;
        return make_shared<Rect>(width, height);
    } else if (figure == "TRIANGLE") {
        double a, b, c;
        stream >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (figure == "CIRCLE") {
        double radius;
        stream >> radius;
        return make_shared<Circle>(radius);
    }
    return nullptr;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                << current_figure->Name() << " "
                << current_figure->Perimeter() << " "
                << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
