using namespace std;
#include <iostream>
#include <string>

template<typename V>
class Vector {
public:
	V x;
	V y;
	V z = 0;

	void Print()
	{
		cout << x << " " << y << " " << z << endl;
	}

	Vector(V a, V b)
	{
		x = a;
		y = b;
	}

	Vector(V a, V b, V c)
	{
		x = a;
		y = b;
		z = c;
	}

	Vector operator+(Vector other)
	{
		Vector temp(0, 0);
		temp.x = x + other.x;
		temp.y = y + other.y;
		temp.z = z + other.z;
		return temp;
	}

	Vector operator-(Vector other)
	{
		Vector temp(0, 0);
		temp.x = x - other.x;
		temp.y = y - other.y;
		temp.z = z - other.z;
		return temp;
	}

	double Magnitude()
	{
		int tempx = x * x;
		int tempy = y * y;
		int tempz = z * z;
		double sr = sqrt(tempx + tempy + tempz);

		return sr;
	}

	Vector Nomalize()
	{
		double newx = x / z;
		double newy = y / z;
		double newz = z / z;

		Vector temp(newx, newy, newz);
		return temp;
	}

	double operator*(Vector other) //Dot Product
	{
		Vector temp(0, 0);
		temp.x = x * other.x;
		temp.y = y * other.y;
		temp.z = z * other.z;
		double dot = temp.x + temp.y + temp.z;

		return dot;
	}

	Vector operator/(Vector other)//Cross Product
	{
		double crossx, crossy, crossz;
		crossx = (y * other.z) - (other.y * z);
		crossy = (z * other.x) - (other.z * x);
		crossz = (x * other.y) - (other.x * y);

		Vector cross(crossx, crossy, crossz);
		return cross;
	}

	double Angle(Vector b)//Angle between two vectors.
	{
		double base, opp, hyp;
		opp = this->Magnitude();
		base = b.Magnitude();
		hyp = sqrt((base * base) + (opp * opp));

		Vector tri(base, opp, hyp);
		tri = tri.Nomalize();

		double angle = acos(base / hyp);

		angle = (angle / 3.14) * 180;

		return angle;
	}
};