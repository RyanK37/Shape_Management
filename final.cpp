#include <iostream>
#include <string>
#include <cmath>
#include <vector>
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
        return round(width * length * 100)/100.0;
    }

    double getPerimeter() override {
        return round( 2 * (width + length) * 100)/100.0;
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
        disPlay += "The perimeter : " + to_string(getPerimeter()) + "\n";
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
        return round(side * side * 100)/100.0;
    }

    double getPerimeter() override {
        return round(4 * side * 100)/100.0;
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
        disPlay += "The perimeter : " + to_string(getPerimeter()) + "\n";
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
        return round(pi * radius * radius * 100)/100.0 ;
    }
    
    double getPerimeter() override {
        return round(2 * pi * radius * 100)/100.0;
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
        disPlay += "The perimeter : " + to_string(getPerimeter())+ "\n";
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
        return (round((a + b + c) * 100))/100.0;
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
        return (round(sqrt(s * (s-a) * (s-b) * (s-c)) * 100))/100.0;
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
        disPlay += "The perimeter : " + to_string(getPerimeter()) + "\n";
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class ShapeList {
    private:
    vector<Shape*>listofShapes;

    public:
    void addShape(Shape* s) {
        listofShapes.push_back(s);
    }

    void translateShapes(int dx, int dy) {
        for (auto& each : listofShapes) {
            (*each).translate(dx, dy);
        }
    }
    
    Shape* getShape(int pos) {
        return listofShapes[pos-1];
    }

    Shape* removeShape(int pos) {
        Shape* removed_shape = listofShapes[pos-1];
        listofShapes.erase(listofShapes.begin() + (pos - 1));
        return removed_shape;
    }

    double area(int pos) {
        return (*listofShapes[pos-1]).getArea();
    }

    void scale(int factor, bool sign) {
        for (auto& each : listofShapes) {
            (*each).scale(factor, sign);
        }
    }

    double perimeter(int pos) {
        return (*listofShapes[pos-1]).getPerimeter();
    }

    string display() {
        string dis_play;
        int counter  = 1;
        for (auto& each : listofShapes) {
            dis_play += "\nThe positon of the shape : " + to_string(counter) + "\n";
            dis_play += (*each).display() +"\n";
            counter++;
        }
        return dis_play;
    }

    // string displayByPosition(int pos) {
    //     return (*listofShapes[pos-1]).display();
    // }
    
    int size() {
        return listofShapes.size();
    }
};

// ==================================================================================== //
// ==================================================================================== //

class ShapeManagment {
    private:
    ShapeList shape_list;

    public:
    bool wanna_continue(){                                     //to ask the user whether he/she wants to contiue the program or not
        while (true){
            string option1;
            cout << "\nDo you want to continue program?(Type Yes or No)  >> ";
            cin  >> option1;
            if (option1 == "No" || option1 == "no") {
                cout << "\nThank you for using our program!\nProgram exit successfully!!";
                return false;
            }
            else if (option1 == "Yes" || option1 == "yes" || option1 == "YEs" || option1 == "YeS" || option1 == "yeS" || option1 == "yEs") {
                return true;
            }
            else {
                cout << "\nInvalid input!!\nPlease type Yes or No!!\n";
            }
        }
    }

    void optionMenu() {
        int option;
        while (true) {
            cout << "\nOption menu!\n";
            cout << "1. Add a shape\n";
            cout << "2. Remove a shape by position\n";
            cout << "3. Get information about a shape by position\n";
            cout << "4. Area and perimeter of a shape by position\n";
            cout << "5. Display information of all the shapes\n";
            cout << "6. Translate all the shapes\n";
            cout << "7. Scale all the shapes\n";
            cout << "0. Quit program\n";
            cout << "Please provide your option >> ";
            cin >> option;
            cout << "\n";

            if (option == 1) {
                string shape;
                int x, y;
                cout << "Please choose shape(Rectangle, Square, Circle, Triangle) : ";
                cin >> shape;
                while (true) {
                    if (shape == "Rectangle") {
                        int width, length;
                        
                        cout << "Please input rectangle position!\n";
                        cout << "X - coordinate : ";
                        cin >> x ;
                        cout << "Y - coordinate : ";
                        cin >> y;
                        cout << "Please input the width(w) : ";
                        cin >>  width;
                        cout << "Please input the length(l) : ";
                        cin >> length;

                        Coordinates coord(x, y);
                        Shape* rect = new Rectangle(coord, width, length);
                        shape_list.addShape(rect);
                        break;
                    } 
                    // --------------------------------------------------------------------------------
                    else if (shape == "Square") {
                        int side;   
                        cout << "Please input square position!\n";
                        cout << "X - coordinate : ";
                        cin >> x ;
                        cout << "Y - coordinate : ";
                        cin >> y;
                        cout << "Please input the side(s) : ";
                        cin >>  side;   
                        Coordinates coord(x, y);
                        Shape* sqr = new Square(coord, side);
                        shape_list.addShape(sqr);
                        break;
                    }
                    // --------------------------------------------------------------------------------
                    else if (shape == "Circle") {
                        double radius;

                        cout << "Please provide the circle position!\n";
                        cout << "X - coordinate : ";
                        cin >> x;
                        cout << "Y - coordinate : ";
                        cin >> y;
                        cout << "Please provide the radius : ";
                        cin >> radius;

                        Coordinates coord(x, y);
                        Shape* crl = new Circle(coord, radius);
                        shape_list.addShape(crl);
                        break;
                    }
                    // --------------------------------------------------------------------------------
                    else if (shape == "Triangle") {
                        int x1, y1, x2, y2, x3, y3;

                        cout << "Please provide first vertex : ";
                        cout << "First vertex X : ";
                        cin  >> x1;
                        cout << "First vertex Y : ";
                        cin  >> y1;
                        cout << "Second vertex X : ";
                        cin  >> x2;
                        cout << "Second vertex Y : ";
                        cin  >> y2;
                        cout << "Third vertex X : ";
                        cin  >> x3;
                        cout << "Third vertex Y : ";
                        cin  >> y3; 

                        Coordinates vertex1(x1, y1);
                        Coordinates vertex2(x2, y2);
                        Coordinates vertex3(x3, y3);

                        Shape* trg = new Triangle(vertex1, vertex2, vertex3);
                        shape_list.addShape(trg); 
                        break;
                    }
                    // --------------------------------------------------------------------------------
                    else {
                        cout << "Error!! Please input valid shape!!";
                    }
                }
                cout << "The shape is added successfully!\n";

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 2) {
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if (position < 1 || position > shape_list.size()) {
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    Shape* removed_shape = shape_list.removeShape(position);
                    cout << "The shape is removed successfully!!"; 
                }

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 3) {
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if (position < 1 || position > shape_list.size()) {
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    Shape* shape_position = shape_list.getShape(position);
                    cout << (*shape_position).display();
                }

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 4) {
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if ( position < 1 || position > shape_list.size()) {
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    double area = shape_list.area(position);
                    double perimeter = shape_list.perimeter(position);
                    cout << "The area of the shape : " + to_string(area) + "\n";
                    cout << "The perimeter of the shape : " + to_string(perimeter) + "\n";
                }

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 5) {
                cout << shape_list.display();

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 6) {
                int dx, dy;

                cout << "Please provide the translate values for X and Y!!\n";
                cout << "Translate value for X : ";
                cin  >> dx;
                cout << "Translate value for Y : ";
                cin  >> dy;

                shape_list.translateShapes(dx, dy);

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 7) {
                int factor;
                string input_bool;
                bool sign;
                cout << "Please provide the factor for the scale : ";
                cin  >> factor;
                while (true) {
                    cout << "Please provide the sign for the scale(True or Falase) : ";
                    cin  >> input_bool;
                    if (input_bool == "True") {
                        sign = true;
                        break;
                    } else if (input_bool == "False") {
                        sign = false;
                        break;
                    } else {
                        cout << "Invalid Input!! Please provide valid input(True or False)!!\n";
                    }
                }

                if (!wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 0) {
                cout << "Thank you for using our program!\nProgram exit successfully!!";
                break;
            }
            // ==================================================================================== 
            else {
                cout << "Invalid option!!\nPlease provide a valid option!!\n"<< endl;
            }  
        }
    }
};

// ==================================================================================== //
// ==================================================================================== //

int main() {
    ShapeManagment program;
    program.optionMenu();
}

// ==================================================================================== //
// ==================================================================================== //