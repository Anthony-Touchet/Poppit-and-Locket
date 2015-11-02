/*
Anthony Touchet

Math...
1. Create a templated class that supports 2D Vector addition and subtraction. ////COMPLETE
2. Add support for 3D vectors. ////COMPLETE
3. Add support for magnitude of a vector. ////COMPLETE
4. Add support for normalizing a vector./////COMPLETE
5. Add support for dot and cross product.////COMPLETE
*/

#include "VecMath.h"

int main() {

	Vector<int> a(14, 5, -5);//Vector a
	Vector<int> b(-2, 1, 43);//Vector b

	Vector<int> result = a / b;

	cout << result.x << ", " << result.y << ", " << result.z << endl;

	system("pause");
}