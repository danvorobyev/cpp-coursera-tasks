#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

#define pi 3.14

class Figure {
public:
  Figure(const string& type_) : type(type_) {}

  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;

  virtual ~Figure() = default;

protected:
  const string type;
};

class Triangle : public Figure {
public:
  Triangle(double a, double b, double c)
  : Figure("TRIANGLE"),
    P(a + b + c),
    S(sqrtl((P/2)*(P/2 - a)*(P/2 - b)*(P/2 - c))) {}

  string Name() const override {
    return type;
  }

  double Perimeter() const override {
    return P;
  }

  double Area() const override {
    return S;
  }
private:
  double P;
  double S;
};

class Rect : public Figure {
public:
  Rect(double w, double h)
  : Figure("RECT"),
    P(2 * w + 2 * h),
    S(w * h) {}

  string Name() const override {
    return type;
  }

  double Perimeter() const override {
    return P;
  }

  double Area() const override {
    return S;
  }
private:
  double P;
  double S;
};

class Circle : public Figure {
public:
  Circle(double r)
  : Figure("CIRCLE"),
    P(2 * pi * r),
    S(pi * pow(r, 2)) {}

  string Name() const override {
    return type;
  }
  
  double Perimeter() const override {
    return P;
  }

  double Area() const override {
    return S;
  }
private:
  double P;
  double S;
};

shared_ptr<Figure> CreateFigure(istream& is) {
  string figure;
  is >> figure;
  if (figure == "TRIANGLE") {
    double first_side, second_side, third_side;
    is >> first_side >> second_side >> third_side;
    return make_shared<Triangle>(first_side, second_side, third_side);
  } else if (figure == "RECT" ) {
    double width, height;
    is >> width >> height;
    return make_shared<Rect>(width, height);
  } else {
    double radius;
    is >> radius;
    return make_shared<Circle>(radius);
  }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
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