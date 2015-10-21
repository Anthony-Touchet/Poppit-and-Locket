//Guy Goudeau
//gg1126
//Oct 19, 2015
#include <iostream>
#include "Header.h"
using namespace std;


int main()
{

	Vectors <int> TwoD1(6, 9);
	Vectors <int> TwoD2(9, 6);
	Vectors <int> TwoDAdd = TwoD1 + TwoD2;
	Vectors <int> TwoDSub = TwoD1 - TwoD2;

	Vectors <int> ThreeD1(-6, 50, 6);
	Vectors <int> ThreeD2(4, 2, 14);
	Vectors <int> ThreeDAdd = ThreeD1 + ThreeD2;
	Vectors <int> ThreeDSub = ThreeD1 - ThreeD2;

	cout << "Adding 2D vectors: (" << TwoDAdd.x << "," << TwoDAdd.y << ")" << endl;
	cout << "Subtracting 2D vectors: (" << TwoDSub.x << "," << TwoDSub.y << ")" << endl << endl;

	cout << "Adding 3D vectors: (" << ThreeDAdd.x << "," << ThreeDAdd.y << "," << ThreeDAdd.z << ")" << endl;
	cout << "Subtracting 3D vectors: (" << ThreeDSub.x << "," << ThreeDSub.y << "," << ThreeDSub.z << ")" << endl << endl;

	ThreeD1.SqRoot();
	ThreeD2.SqRoot();
	cout << endl;

	ThreeD1.Normalize();
	ThreeD2.Normalize();
	cout << endl;

	system("pause");
	return 0;
}