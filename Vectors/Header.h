#pragma once

template <typename V>
class Vectors
{
public:
	V x;
	V y;
	V z;
	Vectors(V a, V b)
	{
		x = a;
		y = b;
	}
	Vectors(V a, V b, V c)
	{
		x = a;
		y = b;
		z = c;
	}
	Vectors operator+(Vectors &other)
	{
		Vectors temp(0, 0);
		temp.x = x + other.x;
		temp.y = y + other.y;
		temp.z = z + other.z;
		return temp;
	}
	Vectors operator-(Vectors &other)
	{
		Vectors temp(0, 0);
		temp.x = x - other.x;
		temp.y = y - other.y;
		temp.z = z - other.z;
		return temp;
	}
	void SqRoot()
	{
		int mag = sqrt((x ^ 2) + (y ^ 2) + (z ^ 2));
		cout << "Magnitude of vector is: " << mag << endl;
	}
	void Normalize()
	{
		int mag = sqrt((x ^ 2) + (y ^ 2) + (z ^ 2));
		x = x / mag;
		y = y / mag;
		z = z / mag;
		cout << "Normalized vector now has components (" << x << "," << y << "," << z << ")" << endl;
	}
};