#include <iostream>
#include <cmath>

class Field 
{
protected:
    double* value;
    
public:
    Field() : value(new double[3]{0.0, 0.0, 0.0}) {}
    Field(double x, double y, double z) : value(new double[3]{x, y, z}) {}
    virtual ~Field() { delete[] value; }
    
    Field(const Field& other) : value(new double[3]{other.value[0], other.value[1], other.value[2]}) {}
    
    Field& operator=(const Field& other) 
    {
        if (this != &other) 
        {
            delete[] value;
            value = new double[3]{other.value[0], other.value[1], other.value[2]};
        }
        return *this;
    }
    
    void printMagnitude() const {
        std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
    }
    
    double* getValue() const { return value; }
};

class Electric_Field : public Field 
{
private:
    double calculated_field;
    
public:
    Electric_Field() : Field(), calculated_field(0.0) {}
    Electric_Field(double x, double y, double z) : Field(x, y, z), calculated_field(0.0) {}
    
    Electric_Field operator+(const Electric_Field& other) 
    {
        return Electric_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Electric_Field& ef);
    
    void calculateElectricField(double Q, double r) 
    {
        const double epsilon_0 = 8.854e-12;
        calculated_field = Q / (4 * M_PI * r * r * epsilon_0);
    }
    
    double getCalculatedField() const { return calculated_field; }
};

class Magnetic_Field : public Field 
{
private:
    double calculated_field;
    
public:
    Magnetic_Field() : Field(), calculated_field(0.0) {}
    Magnetic_Field(double x, double y, double z) : Field(x, y, z), calculated_field(0.0) {}
    
    Magnetic_Field operator+(const Magnetic_Field& other) 
    {
        return Magnetic_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Magnetic_Field& mf);
    
    void calculateMagneticField(double I, double r) 
    {
        const double mu_0 = 4 * M_PI * 1e-7;
        calculated_field = (I * mu_0) / (2 * M_PI * r);
    }
    
    double getCalculatedField() const { return calculated_field; }
};

std::ostream& operator<<(std::ostream& os, const Electric_Field& ef)
{
    os << "Electric Field Components: (" << ef.value[0] << ", " << ef.value[1] << ", " << ef.value[2] << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Magnetic_Field& mf)
{
    os << "Magnetic Field Components: (" << mf.value[0] << ", " << mf.value[1] << ", " << mf.value[2] << ")";
    return os;
}

int main()
{
    Electric_Field e1(1e5, 10.9, 1.7e2);
    Magnetic_Field b1(2.5, 1.2, 0.8);
    
    std::cout << "Initial fields:\n";
    e1.printMagnitude();
    b1.printMagnitude();
    
    
    e1.calculateElectricField(1e-6, 0.1);
    b1.calculateMagneticField(10, 0.1);
    
    std::cout << "\nCalculated values:\n";
    std::cout << "Electric Field: " << e1.getCalculatedField() << " N/C\n";
    std::cout << "Magnetic Field: " << b1.getCalculatedField() << " T\n";
    
    Electric_Field e2(2e5, 5.5, 3e2);
    Electric_Field e3 = e1 + e2;
    
    Magnetic_Field b2(1.5, 0.8, 0.4);
    Magnetic_Field b3 = b1 + b2;
    
    std::cout << "\nAfter operator overloading:\n";
    std::cout << "Electric Field Sum: " << e3 << "\n";
    std::cout << "Magnetic Field Sum: " << b3 << "\n";
    
    return 0;
}
