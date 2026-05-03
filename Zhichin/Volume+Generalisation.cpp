#include <iostream>


using namespace std;

const double PI = 3.14159;

class GeometricObject {
private:
    string name;
public:
    GeometricObject(const string& n) : name(n) {}

    string getName() const {
        return name;
    }

    void printInfo() {
        cout << "Geometric object: " << name << endl;
    }
};

class Sphere : public GeometricObject {
private:
    double radius;
public:
    Sphere(double r, const string& n) : GeometricObject(n), radius(r) {}

    double getSurfaceArea() {
        return 4 * PI * radius * radius;
    }

    double getVolume() {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }

    void printInfo() {
        cout << "Sphere: " << getName() << endl;
        cout << "Radius: " << radius << endl;
        cout << "Surface area: " << getSurfaceArea() << endl;
        cout << "Volume: " << getVolume() << endl;
    }
};

class Parallelepiped : public GeometricObject {
private:
    double length, width, height;
public:
    Parallelepiped(double l, double w, double h, const string& n) : GeometricObject(n), length(l), width(w), height(h) {}

    double getSurfaceArea() {
        return 2 * (length * width + length * height + width * height);
    }

    double getVolume() {
        return length * width * height;
    }

    void printInfo() {
        cout << "Parallelepiped: " << getName() << endl;
        cout << "Dimensions: " << length << " x " << width << " x " << height << endl;
        cout << "Surface area: " << getSurfaceArea() << endl;
        cout << "Volume: " << getVolume() << endl;
    }
};

int main() {
    Sphere ball(5.0, "Ball");
    ball.printInfo();
    cout << endl;

    Parallelepiped box(2.0, 3.0, 4.0, "Box");
    box.printInfo();

    return 0;
}
