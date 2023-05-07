// 컴퓨터그래픽스 HW#3
// 학번 : 195443
// 이름 : 박찬

#include <cstdio>

struct Vector3d // 3D Vector
{
	double x; // x-coordinate
	double y; // y-coordinate
	double z; // z-coordinate

	// constructor
	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	
	friend void printVector3d(const Vector3d& a)
	{
		printf("(%lf, %lf, %lf)\n", a.x, a.y, a.z);
	}

	friend Vector3d operator+(const Vector3d& a, const Vector3d& b)
	{
		double _x = a.x + b.x;
		double _y = a.y + b.y;
		double _z = a.z + b.z;
		return Vector3d(_x, _y, _z);
	}
	friend Vector3d operator-(const Vector3d& a, const Vector3d& b)
	{
		double _x = a.x - b.x;
		double _y = a.y - b.y;
		double _z = a.z - b.z;
		return Vector3d(_x, _y, _z);
	}
	friend Vector3d operator*(const Vector3d& a, double d)
	{
		double _x = a.x * d;
		double _y = a.y * d;
		double _z = a.z * d;
		return Vector3d(_x, _y, _z);
	}
	friend Vector3d operator*(double d, const Vector3d& a)
	{
		double _x = d * a.x;
		double _y = d * a.y;
		double _z = d * a.z;
		return Vector3d(_x, _y, _z);
	}
	friend Vector3d operator/(const Vector3d& a, double d)
	{
		double _x = a.x / d;
		double _y = a.y / d;
		double _z = a.z / d;
		return Vector3d(_x, _y, _z);
	}
	friend Vector3d cross(const Vector3d& a, const Vector3d& b)
	{
		double _x = a.y * b.z - a.z * b.y;
		double _y = a.z * b.x - a.x * b.z;
		double _z = a.x * b.y - a.y * b.x;
		return Vector3d(_x, _y, _z);
	}
	friend double dot(const Vector3d& a, const Vector3d& b)
	{
		double scalar = a.x * b.x + a.y * b.y + a.z * b.z;
		return scalar;
	}
};

int main()
{
	Vector3d P0(0, 0, 0);
	Vector3d P1(-1, 5, 0);
	Vector3d P2(1, 0, 5);

	Vector3d O(5, 1, 1);
	Vector3d V1(-1, 0, 0);
	Vector3d V2(-1, 1, 1);

	printf("----------------------------------------\n");

	double k;
	Vector3d N, U, V;

	N = cross(P1 - P0, P2 - P0);
	printf("N = ");
	printVector3d(N);

	k = dot(cross(P1 - P0, P2 - P0), N);

	U = cross(P2 - P0, N) / k;
	printf("U = ");
	printVector3d(U);

	V = cross(N, P1 - P0) / k;
	printf("V = ");
	printVector3d(V);

	printf("----------------------------------------\n");

	double t, _u, _v;
	bool isHit;
	Vector3d v, P;

	v = V1 - O;

	t = dot(P0 - O, N) / dot(v, N);

	P = O + t * v;
	printf("P = ");
	printVector3d(P);

	_u = dot(P - P0, U);
	_v = dot(P - P0, V);
	printf("u, v = (%lf, %lf)\n", _u, _v);

	isHit = (_u > 0 && _v > 0 && _u + _v < 1) ? true : false;
	if (isHit) printf("ray hits triangle\n");
	else	   printf("ray doesn't hit triangle\n");

	printf("----------------------------------------\n");

	v = V2 - O;

	t = dot(P0 - O, N) / dot(v, N);

	P = O + t * v;
	printf("P = ");
	printVector3d(P);

	_u = dot(P - P0, U);
	_v = dot(P - P0, V);
	printf("u, v = (%lf, %lf)\n", _u, _v);

	isHit = (_u > 0 && _v > 0 && _u + _v < 1) ? true : false;
	if (isHit) printf("ray hits triangle\n");
	else	   printf("ray doesn't hit triangle\n");

	printf("----------------------------------------\n");

	return 0;
}