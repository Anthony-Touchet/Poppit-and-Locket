using namespace std;
#include <iostream>
#include <string>

template<typename V>
class Vector {
public:
	V x;
	V y;
	V z = 0;
	V alpha = 0;

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

	Vector(V a, V b, V c, V d)
	{
		x = a;
		y = b;
		z = c;
		alpha = d;
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

	double LinearInterpolation(float a, float b, float perc)//LinearInterpolation
	{
		return (a + (b - a)) * perc;
	}

	float DtoR(int d)//Degrees to Radians
	{
		return (d / 180)*3.14;
	}

	float RtoD(int r)//Radians to degrees
	{
		return (r / 3.14) * 180;
	}

	Vector<int> HexColor(/*string color[8]*/ char f[1])
	{
		//Vector<int> color;	//End Result

		//string red[2];		//Color holders and assigning values
		//string blue[2];
		//string green[2];
		//string alpha[2];

		//red[0] = color[0];
		//red[1] = color[1];

		//green[0] = color[2];
		//green[1] = color[3];
		//
		//blue[0] = color[4];
		//blue[1] = color[5];
		//
		//alpha[0] = color[6];
		//alpha[1] = color[7];

		int sorter;
		switch (f)
		{
		case (char)97:
			sorter = 10;
			break;

		case (char)98:
			sorter = 11;
			break;

		case (char)99:
			sorter = 12;
			break;

		case (char)100:
			sorter = 13;
			break;

		case (char)101:
			sorter = 14;
			break;

		case (char)102:
			sorter = 15;
			break;

		default:
			break;
		}

		cout << sorter << endl;
	}
};

