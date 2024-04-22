#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

class Coordinates {                                                         // Coordinates class
    private:                                                                // Attributes
    int x;
    int y;

    public:
    Coordinates (int x1, int y1) {                                          // Constructor for Coordinates
        x = x1;
        y = y1;
    }

    int getX() {                                                            // To get the x value of the coordinte
        return x;
    }

    int getY() {                                                            // To get the y value of the coordinate
        return y;
    }

    double distance(Coordinates& p) {                                       // Distance between two coordinates
        int distX = x - p.getX();
        int distY = y - p.getY();
        return sqrt(distX*distX + distY*distY);
    }

    void translate(int dx, int dy) {                                        // To translate the coordinate
        x += dx;
        y += dy;
    }

    void scale(int factor, bool sign){                                      // To scale the coordinate
        if (factor == 0 || !sign) {
            cout << "Error!Cannot divide by zero or there is no sign!!!";
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

    string display() {                                                      // To display the current coordinate position
        return "X = " + to_string(x) + ", Y = " + to_string(y); 
    }
};  

// ==================================================================================== //
// ==================================================================================== //

class Shape {                                                               // Shape Class
    protected:                                                              // attributes
    Coordinates position;
    int sides;

    public:
    Shape(int noOfSides, Coordinates& coord) : position(coord), sides(noOfSides) {}     // Constructor for shape class

    Coordinates getCoordinates() {                                          // get coordinates of the object; 
        return position;
    }

    int getSides() {                                                        // To get the side of the shape
        return sides;
    }

    void setCoordinates(Coordinates& newcoord) {                            // To set the new coordinates
        position = newcoord;
    }

    virtual void translate(int dx, int dy) {                                // To translate the shape
        position.translate(dx, dy);
    }

    virtual void scale(int factor, bool sign) {}                            // pure virtual function to scale

    virtual double getArea() = 0;                                           // pure virtual function to get area

    virtual double getPerimeter() = 0;                                      // pure virtual function to get perimeter

    virtual string display() = 0;                                           // pure virtual function to display
};

// ==================================================================================== //
// ==================================================================================== //

class Rectangle : public Shape {                                            // Rectangle class inherients from Shape class
    private:
    double width, length;                                                      // attributes

    public:
    Rectangle(Coordinates &coord, double w, double l) : Shape(4, coord), width(w), length(l) {}      // Constructor for Rectangle class

    double getArea() override {                                             // To get the area of the rectangle (override the function from shape class)
        return width * length;
    }

    double getPerimeter() override {                                        // To get the perimeter of the rectangle (override the function from shape class)
        return 2 * (width + length);
    }

    void scale(int factor, bool sign) override {                            // To scale the rectangle (override the function from shape class)
        if (sign) {
            width *= factor;
            length *= factor;
        } else {
            width /= factor;
            length /= factor;
        }
    }

    string display() override {                                            // To display the informations of the rectangle (override the function from shape class)
        string disPlay =  "The name of the shape : Rectangle\n";
        disPlay += "The attributes(position, width, length) >> Position : " + position.display() + ", Width : " +  to_string(width) + ", Length : " + to_string(length) +"\n";
        disPlay += "The area : " + to_string(round(getArea()*100)/100.0) +"\n";
        disPlay += "The perimeter : " + to_string(round(getPerimeter()*100)/100.0)+ "\n";
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Square : public Shape {                                               // Square class inherients from Shape class
    private:                                                                // attributes
    double side;

    public:                                                                 
    Square(Coordinates &coord, double s) : Shape(4, coord), side(s) {}         // Constructor for the Square class

    double getArea() override {                                             // To get the area of the Square (override the function from shape class)
        return side * side;
    }

    double getPerimeter() override {                                        // To get the perimeter of the Square (override the function from shape class)
        return 4 * side;
    }

    void scale(int factor, bool sign) override {                            // To scale the Square (override the function from shape class)
        if (sign) {
            side *= factor;
        } else {
            side /= factor;
        }
    }

    string display() override {                                             // To display the functions of the Square (override the function from shape class)
        string disPlay =  "The name of the shape : Square\n";
        disPlay += "The attributes(position and side) >> Position : " + position.display() + ", Side : " +  to_string(side) + "\n";
        disPlay += "The area : " + to_string(round(getArea()*100)/100.0) +"\n";
        disPlay += "The perimeter : " + to_string(round(getPerimeter()*100)/100.0) + "\n";
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Circle : public Shape {                                               // Circle class inherients from Shape class
    private:                                                                // attributes    
    double radius;
    const double pi = 3.14159265358979323846;                               // declare constant for pi value

    public:
    Circle(Coordinates &coord, double r) : Shape(0, coord), radius(r) {}    // Constructor for Circle class

    double getArea() override {                                             // To get the area of the circle
        return pi * radius * radius;
    }
    
    double getPerimeter() override {                                        // To get the perimeter of the circle
        return 2 * pi * radius;
    }

    void scale(int factor, bool sign) override {                            // To scale the circle
        if (sign) {
            radius *= factor;
        } else {
            radius /= factor;
        }
    }

    string display() override {                                            // To display the informations of the circle
        string disPlay =  "The name of the shape : Circle\n";
        disPlay += "The attributes(position and radius) >> Position : " + position.display() + ", Radius : " +  to_string(radius) + "\n";
        disPlay += "The area : " + to_string(round(getArea()*100)/100.0) +"\n";
        disPlay += "The perimeter : " + to_string(round(getPerimeter()*100)/100.0)+ "\n";
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Triangle : public Shape {                                             // Triangle class inherients from Shape class
    private:                                                                // attributes
    Coordinates vertex1, vertex2, vertex3;                                  // initialize three objects(vertices) from Coordinates class

    public:
    Triangle(Coordinates &v1, Coordinates &v2, Coordinates &v3) : Shape(3, v1), vertex1(v1), vertex2(v2), vertex3(v3) {}   // Constructor for the Triangle class

    double getPerimeter() override {                                        // To get the perimeter of the triangle
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        return (a + b + c);
    }

    void translate(int dx, int dy) override {                               // To translate the triangle
        vertex1.translate(dx, dy);
        vertex2.translate(dx, dy);
        vertex3.translate(dx, dy);
    }

    double getArea() override {                                             // To get the area of the triangle
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        double s = (a + b+ c)/2;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }

    void scale(int factor, bool sign) override {                            // To scale the triangle
        vertex1.scale(factor, sign);
        vertex2.scale(factor, sign);
        vertex3.scale(factor, sign);
    }

    string display() override {                                             // To display the informations of the triangle
        string disPlay =  "The name of the shape : Triangle\n";
        disPlay += "The attributes(three vertices) : " + vertex1.display() + ", " + vertex2.display() + ", " + vertex3.display() +"\n";
        disPlay += "The area : " + to_string(round(getArea()*100)/100.0) +"\n";
        disPlay += "The perimeter : " + to_string(round(getPerimeter()*100)/100.0) + "\n";
        return disPlay;
    }
};

// ==================================================================================== //
// ==================================================================================== //

class ShapeList {                                                           // ShapeList Class to handle the storage of all Shapes
    private:
    vector<Shape*>listofShapes;                                             // Initialize a vector variable "listofShapes" which will store objects of Shape class

    public:
    void addShape(Shape* s) {                                               // To add  new shape to the vector
        listofShapes.push_back(s);
    }

    void translateShapes(int dx, int dy) {                                  // To translate all shapes of the vector
        for (auto& each : listofShapes) {
            (*each).translate(dx, dy);
        }
    }
    
    Shape* getShape(int pos) {                                              // To get the shape by position
        return listofShapes[pos-1];
    }

    Shape* removeShape(int pos) {                                           // To remove the shape by position
        Shape* removed_shape = listofShapes[pos-1];
        listofShapes.erase(listofShapes.begin() + (pos - 1));
        return removed_shape;
    }

    double area(int pos) {                                                  // To get the area of the shape by position
        return (*listofShapes[pos-1]).getArea();
    }

    void scale(int factor, bool sign) {                                     // To scale all shapes of the vector
        for (auto& each : listofShapes) {
            (*each).scale(factor, sign);
        }
    }

    double perimeter(int pos) {                                             // To get the perimeter of the shape by position
        return (*listofShapes[pos-1]).getPerimeter();
    }

    string display() {                                                      // To display informations of all shapes of the vector
        string dis_play;
        int counter  = 1;
        for (auto& each : listofShapes) {
            dis_play += "\nThe positon of the shape : " + to_string(counter) + "\n";
            dis_play += (*each).display() +"\n";
            counter++;
        }
        return dis_play;
    }

    int size() {                                                            // To get the size of the vector
        return listofShapes.size();
    }
};

// ==================================================================================== //
// ==================================================================================== //

class ShapeManagment {                                                      // ShapeManagement class to handle ShapeList class
    private:
    ShapeList shape_list;                                                   // initialize an object as "shape_list" from ShapeList class

    public:
    bool wanna_continue(){                                                  // To ask the user whether he/she wants to contiue the program or not
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

    // ==================================================================================== //

    void optionMenu() {                                                     // The option menu method to ask the user 
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
            cout << "Please provide your option(0 to 7) >> ";
            cin >> option;
            cout << "\n";

            if (option == 1) {                                              // Add the shape according to the user input    
                string shape;
                int x, y;
                cout << "Please choose shape(Rectangle, Square, Circle, Triangle) : ";
                cin >> shape;
                while (true) {
                    if (shape == "Rectangle" || shape == "rectangle") {                             // Adding a rectangle shape
                        int width, length;
                        
                        cout << "Please input rectangle position!\n";       // Asking for user inputs
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
                    else if (shape == "Square" || shape == "square") {                          // Adding a square shape
                        int side;   

                        cout << "Please input square position!\n";         // Asking user inputs
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
                    else if (shape == "Circle" || shape == "circle") {                           // Adding a circle shape
                        double radius;  

                        cout << "Please provide the circle position!\n";    // Asking the user inputs
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
                    else if (shape == "Triangle" || shape == "triangle") {                         // Adding a triangle shape
                        int x1, y1, x2, y2, x3, y3;

                        cout << "Please provide first vertex!!\n";           // Asking user inputs
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
                cout << "The shape is added successfully!\n";               // Tell the user that the shape is added 

                if (!wanna_continue()){                                     //Ask the user whether want to continue the progarm or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 2) {                                         // Remove the shape according to the position that the user input
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if (position < 1 || position > shape_list.size()) {         // Check whether it is out of index or not
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    Shape* removed_shape = shape_list.removeShape(position);// Remove the shape
                    cout << "The shape is removed successfully!!"; 
                }

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 3) {                                         // To get the information of the shape by position
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if (position < 1 || position > shape_list.size()) {         // Check whether it is out of index or not     
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    Shape* shape_position = shape_list.getShape(position);  // Display the informations of the shape
                    cout << (*shape_position).display();
                }

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 4) {                                         // To display the area and the perimeter of the shape by position
                int position;
                cout << "Please provide the position of the shape : ";
                cin >> position;
                if ( position < 1 || position > shape_list.size()) {        // Check whether it is out of index or not
                    cout << "Error!! There is no shape in that position!!";
                } else {
                    double area = round(shape_list.area(position) *100)/100.0;                // get area
                    double perimeter = round(shape_list.perimeter(position)) * 100/100.0;      // get perimeter
                    cout << "The area of the shape : " + to_string(area) + "\n";            // show the result to the user
                    cout << "The perimeter of the shape : " + to_string(perimeter) + "\n";  // show the result to the user 
                }

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 5) {                                         // Display all shapes' informations
                cout << shape_list.display();                               

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 6) {                                         // To translate all shapes
                int dx, dy;

                cout << "Please provide the translate values for X and Y!!\n";  // ask the user for translate values
                cout << "Translate value for X : ";
                cin  >> dx;
                cout << "Translate value for Y : ";
                cin  >> dy;

                shape_list.translateShapes(dx, dy);                         // translate all shapes
                cout << "All shapes are translated successfully!!";

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 7) {                                         // To scale all shapes
                int factor;
                string input_bool;
                bool sign;

                cout << "Please provide the factor for the scale : ";       // ask the factor value
                cin  >> factor;
                while (true) {
                    cout << "Please provide the sign for the scale(True or Falase) : "; // To get the sign (true or false)
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

                shape_list.scale(factor, sign);                             // Scale all shapes
                cout << "All shapes are scaled successfully!!";

                if (!wanna_continue()){                                     //Ask the user whether want to continue the program or not?
                    break;
                }
            }
            // ==================================================================================== 
            else if (option == 0) {                                         // Exit the program
                cout << "Thank you for using our program!\nProgram exit successfully!!";
                break;
            }
            // ==================================================================================== 
            else {                                                          // To handle the invalid input
                cout << "Invalid option!!\nPlease provide a valid option!!\n"<< endl;
            }  
        }
    }
};

// ==================================================================================== //
// ==================================================================================== //

int main() {
    ShapeManagment program;                                                 // create an object "program" for ShapeManagment class
    program.optionMenu();                                                   // Run the program
}

// ==================================================================================== //
// ==================================================================================== //