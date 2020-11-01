#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*struct Image {
    double quality;
    double freshness;
    double rating;
};

struct Params {
    double a;
    double b;
    double c;
};*/

class FunctionPart {
public:    
    FunctionPart(char operation, double value): operation(operation), value(value) {}

    double Apply(double value) const {
        switch (operation) {
            case '+': return value + this->value;
            case '-': return value - this->value;
            case '*': return value * this->value;
            case '/': return value / this->value;
        }
        return value;
    }

    void Invert() {
        switch (operation) {
            case '+': operation = '-'; break;
            case '-': operation = '+'; break;
            case '*': operation = '/'; break;
            case '/': operation = '*'; break;
        }
    }

private:
    char operation;
    double value;    
};

class Function {
public:    
    void AddPart(char operation, double value) {
        parts.push_back({operation, value});
    }
    double Apply(double value) const {
        for (const auto &part : parts)
            value = part.Apply(value);
        return value;
    }
    void Invert() {
        for (auto &part : parts)
            part.Invert();
        reverse(parts.begin(), parts.end());
    }

private:
    vector<FunctionPart> parts;
};

/*Function MakeWeightFunction(const Params& params, const Image& image) {
    Function function;
    function.AddPart('*', params.a);
    function.AddPart('-', image.freshness * params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params, const Image& image, double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}

int main() {
    Image image = {10, 2, 6};
    Params params = {4, 2, 6};
    cout << ComputeImageWeight(params, image) << endl;
    cout << ComputeQualityByWeight(params, image, 52) << endl;
    return 0;
}*/