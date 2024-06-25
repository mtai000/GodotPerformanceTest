#include "pch.hpp"

template<int n>
struct Vec {
    float data[n];

    float& operator[] (const int i)       {assert(i<n && i>= 0); return data[i];}
    float  operator[] (const int i) const {assert(i<n && i>= 0); return data[i];}
    float norm2() { return this * this; }
    float norm() {return std::sqrt(norm2());}
};

template<> struct Vec<3> {
    union{
        struct {float x,y,z;};
        float data[3];
    };

    Vec<3>():x(0),y(0),z(0){};
    Vec<3>(float xx) : x(xx),y(xx),z(xx){};
    Vec<3>(float xx, float yy, float zz): x(xx),y(yy),z(zz){};

    float& operator[] (const int i)       {assert(i<3 && i>=0); return data[i];}
    float  operator[] (const int i) const {assert(i<3 && i>=0); return data[i];}
    float norm2() {return x*x + y*y + z*z;}
    float norm() {return std::sqrt(norm2());}
};

template<> struct Vec<2> {
	union
	{
		struct {
			float x, y;
		};
		float data[2];
	};
	Vec<2>() :x(0), y(0) {};
	Vec<2>(float xx) : x(xx), y(xx) {};
	Vec<2>(float xx, float yy) : x(xx), y(xx) {};
	float& operator[] (const int i) { assert(i < 2 && i >= 0);  return data[i]; }
	float  operator[] (const int i) const { assert(i < 2 && i >= 0); return data[i]; }
	float norm2() { return x * x + y * y; }
	float norm() { return std::sqrt(norm2()); }
};


template<int n> float operator* (const Vec<n> v1, const Vec<n> v2) {
	float ret = 0;
	for (int i = n; i--; ret += v1[i] * v2[i]);
	return ret;
}

template<int n> Vec<n> operator* (const Vec<n> v1, const float& f) {
	Vec<n> ret = v1;
	for (int i = n; i--; ret *= f);
	return ret;
}

template<int n> Vec<n> operator* (const float& f, const Vec<n> v1) {
	Vec<n> ret = v1;
	for (int i = n; i--; ret *= f);
	return ret;
}

template<int n> Vec<n> operator- (const Vec<n> v1, const Vec<n> v2)
{
	Vec<n> ret = v1;
	for (int i = n; i--; ret -= v2[i]);
	return ret;
}

template<int n> Vec<n> operator+ (const Vec<n> v1, const Vec<n> v2)
{
	Vec<n> ret = v1;
	for (int i = n; i--; ret += v2[i]);
	return ret;
}

template<int R, int C> struct Matrix
{
	Vec<C> row[R] = { {} };

	      Vec<C>& operator[] (const int i)		 { assert(i >= 0 && i < R); return row[i]; }
	const Vec<C>& operator[] (const int i) const { assert(i >= 0 && i < R); return row[i]; }

	Vec<R> col(const int index) const {
		assert(index >= 0 && index < C);
		Vec<R> ret;
		for (int i = R; i--; ret[i] = row[i][index]);
		return ret;
	};

	void Print()
	{
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
				std::cout << row[i][j] << "\t";
			std::cout << std::endl;
		}
	}
};

typedef Matrix<4, 4> Mat4x4;
typedef Matrix<3, 3> Mat3x3;
typedef Mat4x4 Mat4;



template<int R, int C> Vec<R> operator*(const Matrix<R, C>& lhs, const Vec<C>& rhs) {
	Vec<R> ret;
	for (int i = R; i--; ret[i] = lhs[i] * rhs);
	return ret;
}

template<int R1, int C1, int C2> Matrix<R1, C2> operator*(const Matrix<R1, C1>& lhs, const Matrix<C1, C2>& rhs) {
	Matrix<R1, C2> ret;
	for (int i = R1; i--;)
		for (int j = C2; j--; ret[i][j] = lhs[i] * rhs.col(j));
	return ret;
}


template<> struct Vec<4> {
	union
	{
		struct {
			float x, y, z, w;
		};
		float data[4];
	};
	Vec<4>() :x(0), y(0), z(0), w(0) {};
	Vec<4>(float xx) : x(xx), y(xx), z(xx), w(xx) {};
	Vec<4>(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {};
	float& operator[] (const int i) { assert(i < 4 && i >= 0);  return data[i]; }
	float  operator[] (const int i) const { assert(i < 4 && i >= 0); return data[i]; }

	Vec<4> RotateX(float rad) const{
		Mat4 m = { {{1,		  0,        0,	0},
					{0,cos(rad),-sin(rad),	0},
					{0,sin(rad), cos(rad),	0},
					{0,       0,        0,  1}} };
		return m * (*this);
	}

	Vec<4> RotateY(float rad) const {
		Mat4 m = { {{	 cos(rad),		 0, sin(rad),	0},
					{			0,       1,        0,	0},
					{	-sin(rad),       0, cos(rad),	0},
					{			0,       0,        0,	1}}};
		return m * (*this);
	}

	Vec<4> RotateZ(float rad) const {
		Mat4 m = { {{	 cos(rad),-sin(rad),        0,	0},
					{	 sin(rad), cos(rad),        0,	0},
					{			0,        0,	    1,	0},
					{			0,        0,        0,	1}} };
		return m * (*this);
	}
};


typedef Vec<4> Vec4;
typedef Vec<3> Vec3;
typedef Vec<2> Vec2;