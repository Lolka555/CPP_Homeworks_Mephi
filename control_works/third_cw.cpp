#include <cmath>
#include <sstream>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

/*
 * В данном задании необходимо реализовать несколько классов, моделирующих некоторые свойства определенных геометрических
 * фигур.
 * - IShape2D -- базовый интерфейс, который должны реализовать все классы фигур. Содержит объявления методов
 *  GetPerimeter() и GetArea()
 * - Rectangle -- прямоугольник. Принимает в конструкторе длину и ширину. Кроме методов, объявленных в IShape2D, также
 *  имеет метод для вычисления радиуса описанной окружности GetCircumscribedCircleRadius()
 * - Square -- квадрат. Принимает в конструкторе длину стороны. Кроме методов, объявленных в IShape2D, также
 *  имеет метод для вычисления радиуса описанной окружности GetCircumscribedCircleRadius()
 * - Circle -- окружность. Принимает в конструкторе радиус.
 * Также нужно реализовать функцию PrintProperties(std::stringstream& ss, const IShape2D* shape), которая для данной
 * фигуры формирует запись в лог, пишущийся в поток ss. В лог для данной фигуры должны записаться периметр и площадь, а также
 * радиус описанной окружности, если он определен для неё.
 */

class IShape2D {
public:
  virtual ~IShape2D() = default;
  virtual float GetPerimeter() const = 0;
  virtual float GetArea() const = 0;
  virtual float GetCircumscribedCircleRadius() const = 0;
};

class Rectangle : public IShape2D {
private:
  float dlina;
  float visota;

public:
  Rectangle(float dlina_, float visota_) : dlina(dlina_), visota(visota_) {}

  float GetArea() const override {
    return dlina * visota;
  }

  float GetPerimeter() const override {
    return 2 * (dlina + visota);
  }

  float GetCircumscribedCircleRadius() const override {
    return std::sqrt(dlina * dlina + visota * visota) / 2;
  }
};

class Square : public IShape2D {
private:
  float dlina;

public:
  Square(float dlina_) : dlina(dlina_) {}

  float GetArea() const override {
    return dlina * dlina;
  }

  float GetPerimeter() const override {
    return 4 * dlina;
  }

  float GetCircumscribedCircleRadius() const override{
    return dlina * std::sqrt(2) / 2;
  }
};

class Circle : public IShape2D {
private:
  float radius;

public:
  Circle(float radius_) : radius(radius_) {}

  float GetArea() const override {
    return M_PI * radius * radius;
  }

  float GetPerimeter() const override {
    return 2 * M_PI * radius;
  }

  float GetCircumscribedCircleRadius() const override{
    return radius;
  }
};

void PrintProperties(std::stringstream& ss, const IShape2D* shape) {
  ss << "A shape with P = " << shape->GetPerimeter() << "; S = " <<
      shape->GetArea() << "; R = " << shape->GetCircumscribedCircleRadius() <<
      "\n";

}


int main() {
    // Код, помогающий в отладке
    std::vector<std::unique_ptr<IShape2D>> shapes;

    shapes.push_back(std::make_unique<Circle>(10));
    shapes.push_back(std::make_unique<Circle>(20));
    shapes.push_back(std::make_unique<Rectangle>(5, 10));
    shapes.push_back(std::make_unique<Rectangle>(1, 10));
    shapes.push_back(std::make_unique<Square>(5));

    std::stringstream ss;
    for (auto& shape : shapes) {
        PrintProperties(ss, shape.get());
    }

    std::cout << ss.str();
    std::string expectedOutput = R"(A shape with P = 62.8319; S = 314.159
A shape with P = 125.664; S = 1256.64
A shape with P = 30; S = 50; R = 5.59017
A shape with P = 22; S = 10; R = 5.02494
A shape with P = 20; S = 25; R = 3.53553
)";
    // Если проверка не проходит из-за точности чисел с точкой, то нестрашно
    assert(ss.str() == expectedOutput);
}
