#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Coordinates {
    private:
    int x;
    int y;

    public:
    Coordinates (int x1, int y1) {
        x = x1;
        y = y1;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    double distance(Coordinates &p) {
        int distX = x - p.getX();
        int distY = y - p.getY();
        return sqrt(distX*distX + distY*distY);
    }

    void translate(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void scale(int factor, bool sign){
        if (factor == 0 && !sign) {
            cout << "Cannot divide by zero.!!!";
        } else {
            if (sign) {
                x *= factor;
                y *= factor;
            } else {
                x /= factor;
                y /= factor;
            }
        }
    }

    string display() {
        return "X = " + to_string(x) + ", Y = " + to_string(y); 
    }
};  

// ==================================================================================== //
// ==================================================================================== //

class Shape {
    protected:
    Coordinates position;
    int sides;

    public:
    Shape(int noOfSides, Coordinates &coord) : position(coord), sides(noOfSides) {}

    Coordinates getCoordinates() {
        return position;
    }

    int getSides() {
        return sides;
    }

    void setCoordinates(Coordinates &newcoord) {
        position = newcoord;
    }

    virtual void translate(int dx, int dy) {
        position.translate(dx, dy);
    }

    virtual void scale(int factor, bool sign) {} 

    virtual double getArea() = 0;

    virtual double getPerimeter() = 0;

    virtual string display() = 0;
};

// ==================================================================================== //
// ==================================================================================== //

class Rectangle : public Shape {
    private:
    int width, length;

    public:
    Rectangle(Coordinates &coord, int w, int l) : Shape(4, coord), width(w), length(l) {}

    double getArea() override {
        return width * length;
    }

    double getPerimeter() override {
        return 2 * (width + length);
    }

    void scale(int factor, bool sign) override {
        if (sign) {
            width *= factor;
            length *= factor;
        } else {
            width /= factor;
            length /= factor;
        }
    }

    string display() override {
        string disPlay =  "The name of the shape : Circle\n";
        disPlay += "The attributes(position, width, length) >> Position : " + position.display() + ", Width : " +  to_string(width) + ", Length : " + to_string(length) +"\n";
        disPlay += "The area : " + to_string(getArea()) +"\n";
        disPlay += "The perimeter : " + to_string(getPerimeter()); 
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Square : public Shape {
    private:
    int side;

    public:
    Square(Coordinates &coord, int s) : Shape(4, coord), side(s) {}

    double getArea() override {
        return side * side;
    }

    double getPerimeter() override {
        return 4 * side;
    }

    void scale(int factor, bool sign) override {
        if (sign) {
            side *= factor;
        } else {
            side /= factor;
        }
    }

    string display() override {
        string disPlay =  "The name of the shape : Square\n";
        disPlay += "The attributes(position and side) >> Position : " + position.display() + ", Side : " +  to_string(side) + "\n";
        disPlay += "The area : " + to_string(getArea()) +"\n";
        disPlay += "The perimeter : " + to_string(getPerimeter()); 
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Circle : public Shape {
    private:
    double radius;
    const double pi = 3.14159265358979323846; 

    public:
    Circle(Coordinates &coord, double r) : Shape(0, coord), radius(r) {}

    double getArea() override {
        return pi * radius * radius;
    }
    
    double getPerimeter() override {
        return 2 * pi * radius;
    }

    void scale(int factor, bool sign) override {
        if (sign) {
            radius *= factor;
        } else {
            radius /= factor;
        }
    }

    string display() override {
        string disPlay =  "The name of the shape : Circle\n";
        disPlay += "The attributes(position and radius) >> Position : " + position.display() + ", Radius : " +  to_string(radius) + "\n";
        disPlay += "The area : " + to_string(getArea()) +"\n";
        disPlay += "The perimeter : " + to_string(getPerimeter()); 
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Triangle : public Shape {
    private:
    Coordinates vertex1, vertex2, vertex3;

    public:
    Triangle(Coordinates &v1, Coordinates &v2, Coordinates &v3) : Shape(3, v1), vertex1(v1), vertex2(v2), vertex3(v3) {}

    double getPerimeter() override {
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        return a + b + c;
    }

    void translate(int dx, int dy) override {
        vertex1.translate(dx, dy);
        vertex2.translate(dx, dy);
        vertex3.translate(dx, dy);
    }

    double getArea() override {
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        double s = (a + b+ c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    void scale(int factor, bool sign) override {
        vertex1.scale(factor, sign);
        vertex2.scale(factor, sign);
        vertex3.scale(factor, sign);
    }

    string display() override {
        string disPlay =  "The name of the shape : Triangle\n";
        disPlay += "The attributes(three vertices) : " + vertex1.display() + ", " + vertex2.display() + ", " + vertex3.display() +"\n";
        disPlay += "The area : " + to_string(getArea()) +"\n";
        disPlay += "The perimeter : " + to_string(getPerimeter()); 
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

int main(){
    Coordinates point(5, 10);
    std::cout << "Original: " << point.display() << std::endl;

    point.translate(3, 4);
    std::cout << "After translation: " << point.display() << std::endl;

    point.scale(2, true);
    std::cout << "After scaling up: " << point.display() << std::endl;

    point.scale(2, false);
    std::cout << "After scaling down: " << point.display() << std::endl;

    Coordinates point2(10, 15);
    std::cout << "Distance to (10, 15): " << point.distance(point2) << std::endl;

    return 0;

}


