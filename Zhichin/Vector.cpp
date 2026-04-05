#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Vector {
	int n;
	double* vector;

public:
	Vector(int n1) {
		n = n1;
		vector = nullptr;
		MemoryAllocation();
	}

	~Vector() {
		MemoryDelete();
	}

	Vector(const Vector& vec) {
		n = vec.n;
		vector = new double[n];
		for (int i{ 0 }; i < n; i++)
			vector[i] = vec.vector[i];
	}

	Vector& operator=(const Vector& vec) {
		if (this != &vec) {
			MemoryDelete();

			n = vec.n;
			MemoryAllocation();
			for (int i{ 0 }; i < n; i++) {
				vector[i] = vec.vector[i];
			}
		}
		return *this;
	}

	void MemoryAllocation() {
		if (vector != nullptr)
			MemoryDelete();
		vector = new double[n] {};
	}

	void MemoryDelete() {
		delete[] vector;
		vector = nullptr;
	}

	void AddingComponent(int ind, double comp) {
		vector[ind] = comp;
	}

	void LenghtVector() {
		double sum = 0.0;
		for (int i{ 0 }; i < n; i++) {
			sum += vector[i] * vector[i];
		}
		cout << sqrt(sum) << endl;
	}

	double operator*(const Vector& vec) {
		double sklr = 0.0;
		for (int i{ 0 }; i < n; i++) {
			sklr += vector[i] * vec.vector[i];
		}
		return sklr;
	}

	Vector operator+(const Vector& vec) {
		if (n != vec.n)
			return Vector(0);

		Vector res(n);
		for (int i{ 0 }; i < n; i++) {
			res.vector[i] = vector[i] + vec.vector[i];
		}
		return res;
	}

	void PrintVector() {
		cout << "(";
		for (int i{ 0 }; i < n; i++) {
			cout << vector[i];
			if (i < n - 1) cout << ", ";
		}
		cout << ")" << endl;
	}

};

int main() {

	Vector vec3(3);
	Vector vec1(3);
	vec1.AddingComponent(0, 5);
	vec1.AddingComponent(1, 1);
	vec1.AddingComponent(2, 2);

	Vector vec2(3);
	vec2.AddingComponent(0, 3);
	vec2.AddingComponent(1, 2);
	vec2.AddingComponent(2, 1);

	double sklr = vec1 * vec2;
	vec3 = vec1 + vec2;

	vec3.PrintVector();
	cout << sklr << endl;
	vec1.LenghtVector();
	vec1.PrintVector();
	return 0;

}