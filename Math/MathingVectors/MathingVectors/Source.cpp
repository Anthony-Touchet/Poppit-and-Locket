/*
Anthony Touchet

Math...
1. Create a templated class that supports 2D Vector addition and subtraction. ////COMPLETE
2. Add support for 3D vectors. ////COMPLETE
3. Add support for magnitude of a vector. ////COMPLETE
4. Add support for normalizing a vector./////COMPLETE
5. Add support for dot and cross product.////COMPLETE
*/

#include "Header.h"

int main(){

	Vector<double> a (7, 5);//Vector a
	Vector<double> b (0, 2);//Vector b

	Vector<double> c = a + b;//Verctor c is equal to a + b

	c.Print();

	cout << "\n";

	cout << "The magnitude is: " << c.Magnitude() << endl;

	cout << "\n";

	c.Nomalizing();

	cout << "\n";
	
	cout << "The Dot Product of a and b is: " << a * b << endl;

	system("pause");
}