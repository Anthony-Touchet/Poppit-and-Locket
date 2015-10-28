#include "VecMath.h"

int main()
{
	Vector<double> a(1, 1);
	Vector<double> b(2, 2);

	Vector<double> c = a + b;

	cout << c.x << ", " << c.y << endl;

	system("pause");
}