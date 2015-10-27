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

	Vector<double> a (8, 4);//Vector a
	Vector<double> b (2, 2);//Vector b

	Vector<double> result = a.Nomalize();

	cout << result.x << " " << result.y << " " << result.z << endl;

	system("pause");
}