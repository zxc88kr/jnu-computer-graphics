// 컴퓨터그래픽스 HW#4
// 학번 : 195443
// 이름 : 박찬

#define EPSILON 0.0000001
#define _USE_MATH_DEFINES

#include <cstdio>
#include <algorithm>
#include <cmath>

struct Interval
{
	double begin; // begin point
	double end; // end point

	// constructor
	Interval() : begin(0), end(0) {}
	Interval(double _begin, double _end) : begin(_begin), end(_end) {}

	// print interval points
	friend void printInterval(const Interval& I)
	{
		printf("[%lf, %lf]\n", I.begin, I.end);
	}

	// operator overloading
	friend Interval operator+(const Interval& I1, const Interval& I2)
	{
		double _begin = I1.begin + I2.begin;
		double _end = I1.end + I2.end;
		return Interval(_begin, _end);
	}
	friend Interval operator-(const Interval& I1, const Interval& I2)
	{
		double _begin = I1.begin - I2.end;
		double _end = I1.end - I2.begin;
		return Interval(_begin, _end);
	}
	friend Interval operator*(const Interval& I1, const Interval& I2)
	{
		double _begin = std::min(std::min(I1.begin * I2.begin, I1.begin * I2.end),
								 std::min(I1.end   * I2.begin, I1.end   * I2.end));
		double _end = std::max(std::max(I1.begin * I2.begin, I1.begin * I2.end),
							   std::max(I1.end   * I2.begin, I1.end   * I2.end));
		return Interval(_begin, _end);
	}
	friend Interval operator/(const Interval& I1, const Interval& I2)
	{
		if (I2.begin * I2.end > 0)
		{
			double _begin = std::min(std::min(I1.begin / I2.begin, I1.begin / I2.end),
									 std::min(I1.end   / I2.begin, I1.end   / I2.end));
			double _end = std::max(std::max(I1.begin / I2.begin, I1.begin / I2.end),
								   std::max(I1.end   / I2.begin, I1.end   / I2.end));
			return Interval(_begin, _end);
		}
	}
	friend Interval operator^(const Interval& I, int n)
	{
		double _begin, _end;
		if (n % 2 == 0)
		{
			_begin = (I.begin * I.end < 0) ? (0) : (std::min(std::pow(I.begin, n), std::pow(I.end, n)));
			_end = std::max(std::pow(I.begin, n), std::pow(I.end, n));
		}
		else
		{
			_begin = std::pow(I.begin, n);
			_end = std::pow(I.end, n);
		}
		return Interval(_begin, _end);
	}
	friend Interval operator^(double n, const Interval& I)
	{
		if (n == M_E)
		{
			double _begin = std::exp(I.begin);
			double _end = std::exp(I.end);
			return Interval(_begin, _end);
		}
	}
	friend Interval operator+(double k, const Interval& I)
	{
		double _begin = k + I.begin;
		double _end = k + I.end;
		return Interval(_begin, _end);
	}
	friend Interval operator+(const Interval& I, double k)
	{
		double _begin = I.begin + k;
		double _end = I.end + k;
		return Interval(_begin, _end);
	}
	friend Interval operator-(double k, const Interval& I)
	{
		double _begin = k - I.end;
		double _end = k - I.begin;
		return Interval(_begin, _end);
	}
	friend Interval operator-(const Interval& I, double k)
	{
		double _begin = I.begin - k;
		double _end = I.end - k;
		return Interval(_begin, _end);
	}
	friend Interval operator*(double k, const Interval& I)
	{
		double _begin = (k > 0) ? (k * I.begin) : (k * I.end);
		double _end = (k > 0) ? (k * I.end) : (k * I.begin);
		return Interval(_begin, _end);
	}
	friend Interval operator*(const Interval& I, double k)
	{
		double _begin = (k > 0) ? (I.begin * k) : (I.end * k);
		double _end = (k > 0) ? (I.end * k) : (I.begin * k);
		return Interval(_begin, _end);
	}
	friend Interval operator/(double k, const Interval& I)
	{
		if (I.begin * I.end > 0)
		{
			double _begin = std::min(k / I.begin, k / I.end);
			double _end = std::max(k / I.begin, k / I.end);
			return Interval(_begin, _end);
		}
	}
	friend Interval operator/(const Interval& I, double k)
	{
		double _begin = (k > 0) ? (I.begin / k) : (I.end / k);
		double _end = (k > 0) ? (I.end / k) : (I.begin / k);
		return Interval(_begin, _end);
	}
};

double f(double x)
{
	return (x + 1) * (x - 1) * (x - 4);
}
Interval f(const Interval& I)
{
	return (I + 1) * (I - 1) * (I - 4);
}
double g(double x)
{
	return (x + 1) * (x - 1) * (x - 1) * (x - 4);
}
Interval g(const Interval& I)
{
	return (I + 1) * ((I - 1) ^ 2) * (I - 4);
}

double (*funcOriginal)(double);
Interval (*funcInterval)(const Interval&);

double intervalMethod(const Interval& I)
{
	if (I.end - I.begin < EPSILON)
	{
		double root = (I.begin + I.end) / 2;
		if (funcOriginal(root - EPSILON) * funcOriginal(root + EPSILON) < 0) return root;
		else return NULL;
	}

	Interval J = funcInterval(I);

	if (J.begin * J.end > 0)
		return NULL;

	Interval I1(I.begin, (I.begin + I.end) / 2);
	Interval I2((I.begin + I.end) / 2, I.end);

	double temp = intervalMethod(I1);

	return (temp != NULL) ? temp : intervalMethod(I2);
}

int main()
{
	Interval I(0, 5);

	funcOriginal = f;
	funcInterval = f;
	double root = intervalMethod(I);
	printf("%llf\n", root);

	return 0;
}