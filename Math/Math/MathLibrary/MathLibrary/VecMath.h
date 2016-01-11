using namespace std;
#include <iostream>
#include <string>

template<typename V>
class Vector {
public:
	V x = 0;
	V y = 0;
	V z = 0;
	V alpha = 0;

	void Print()
	{
		cout << x << " " << y << " " << z << endl;
	}

	Vector()
	{
		x = 0;
		y = 0;
		z = 0;
		alpha = 0;
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
		double div;
		if (x >= y && x >= z)
		{
			div = x;
		}

		else if (y >= x && y >= z)
		{
			div = y;
		}

		else
		{
			div = z;
		}
		double newx = x / div;
		double newy = y / div;
		double newz = z / div;

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

	Vector<int> HexColor(unsigned int HexColor)
	{
		unsigned int Hexred = HexColor >> 24;
		unsigned int Hexgreen = (HexColor >> 16) & 0x00FF;
		unsigned int Hexblue = (HexColor >> 8) & 0x0000FF;
		unsigned int Hexalpha = HexColor & 0x000000FF;
		Vector<int> hex(Hexred, Hexgreen, Hexblue, Hexalpha);

		return hex;
	}

	bool SquareCollision(Vector first, Vector other)
	{
		Vector<float> max1 = first;
		Vector<float> max2 = other;

		Vector<float> min1 = { max1.x + 50, max1.y + 50 };
		Vector<float> min2 = { max2.x + 50, max2.y + 50 };

		if (max1.x <= min2.x && max2.x <= min1.x && max1.y <= min2.y && max2.y <= min1.y)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool CircleCollision(Vector c1, Vector c2)
	{
		if (sqrt((c1 - c2) * (c1 - c2)) <= c1.z + c2.z)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
};

class Rect {
public:
	float height;
	float width;
	Vector<float> min;
	Vector<float> max;
	Vector<float> Pos;
	char name;
	
	Rect(int h, int w, Vector<float> pos, char na)
	{
		height = h;
		width = w;
		Pos = pos;
		min = pos;
		max = { Pos.x + w, Pos.y + h };
		name = na;
	}
};

class Node {
public:

	Vector<float> value;
	bool minMax;
	int belong;
	Node *next;
	Node *pre;

	Node (Vector<float> val, bool mm, int be)
	{
		value = val;
		minMax = mm;
		belong = be;
		Node *next;
		Node *pre;
	}

	void read(Node &start)
	{
		Node *current = &start;
		for (int i = 0; i < 50; i++)
		{
			if (current->next == NULL)
			{
				cout << belong << " " << minMax << endl;
				break;
			}

			else
			{
				cout << belong << " " << minMax << endl;
				*current = *current->next;
			}
		}
	}

	void SetNext(Node &ne)
	{
		next = &ne;
		ne.pre = this;
	}

	void SetPre(Node &ne)
	{
		pre = &ne;
	}

	void Insert(Node *a, Node *b)
	{
		this->next = b;
		this->pre = a;

		a->next = this;
		b->pre = this;
	}

	void Remove()
	{
		if (this->next == NULL)//Pre
		{
			this->pre->next = NULL;
		}

		else
		{	
			this->pre->next = this->next;
		}
		
		if (this->pre->next != NULL)
		{
			if (this->pre == NULL)//Next
			{
				this->next->pre = NULL;
			}

			else
			{
				this->next->pre = this->pre;
			}
		}

		this->next = NULL;
		this->pre = NULL;
	}

	bool Compare(Node &node)
	{
		if (node.value.x > this->value.x)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool SortCompare(Node &start)
	{
		Node *current = &start;
		for (int i = 0; i < 50; i++)
		{
			if (current->next != NULL)
			{
				Node *compare = current->next;
				if (current->Compare(*compare) == false)
				{
					return false;
				}

				Node *change = current->next;
				current = change;
			}
		}

		return true;
	}

	Vector<int> CompareName(int &num)
	{	
		Vector<int> result = {num, this->belong};
		return result;
	}
};