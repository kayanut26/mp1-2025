#include <iostream>
#include <string>
using namespace std;

class Matrix {
	int rows;
	int columns;
	double** matrix;

public:
	Matrix(int rows1, int columns1) {
		rows = rows1;
		columns = columns1;
		matrix = nullptr;
		MemoryAllocation();
	}

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

		double GetComponent(int ind) {
			if (ind >= 0 && ind < n) {
				return vector[ind];
			}
			return 0;
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

	~Matrix() {
		MemoryDelete();
	}

	Matrix(const Matrix& matr) {
		rows = matr.rows;
		columns = matr.columns;
		matrix = new double* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new double[columns];
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = matr.matrix[i][j];
			}
		}
	}

	Matrix& operator=(const Matrix& test) {
		if (this != &test) {
			MemoryDelete();

			rows = test.rows;
			columns = test.columns;
			MemoryAllocation();

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					matrix[i][j] = test.matrix[i][j];
				}
			}
		}
		return *this;
	}

	void ShowSize() {
		cout << "Matrix size: " << rows << "x" << columns << endl;
	}

	void MemoryAllocation() {
		if (matrix != nullptr) {
			MemoryDelete();
		}
		matrix = new double* [rows] {};
		for (int i = 0; i < rows; i++)
			matrix[i] = new double[columns] {};
	}

	void MemoryDelete() {
		if (matrix != nullptr) {
			for (int i = 0; i < rows; i++)
				delete[] matrix[i];
			delete[] matrix;
			matrix = nullptr;
		}
	}

	int AddingElement(int row, int column, double elem) {
		if (row >= 0 && row < rows && column >= 0 && column < columns) {
			matrix[row][column] = elem;
			return 1;
		}
		else {
			cout << "Error: out of range" << endl;
			return -1;
		}
	}

	int PrintElement(int row, int column) {
		if (row >= 0 && row < rows && column >= 0 && column < columns) {
			cout << "Element matrix[" << row << "][" << column << "]: " << matrix[row][column] << endl;
			return 1;
		}
		else {
			cout << "Error: out of range" << endl;
			return -1;
		}
	}

	void PrintMatrix() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				cout << matrix[i][j] << "\t";
			cout << endl;
		}
	}

	Matrix& operator+=(const Matrix& matr) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] += matr.matrix[i][j];
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& matr) {
		if (rows != matr.rows || columns != matr.columns) {
			return Matrix(0, 0);
		}
		Matrix res(rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				res.matrix[i][j] = matrix[i][j] + matr.matrix[i][j];
			}
		}
		return res;

	}

	Matrix operator-(const Matrix& matr) {
		if (rows != matr.rows || columns != matr.columns) {
			return Matrix(0, 0);
		}
		Matrix res(rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				res.matrix[i][j] = matrix[i][j] - matr.matrix[i][j];
			}
		}
		return res;

	}

	Matrix operator*(const Matrix& matr) {
		if (columns != matr.rows) {
			return Matrix(0, 0);
		}
		Matrix res(rows, matr.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < matr.columns; j++) {
				double sum = 0;
				for (int k = 0; k < columns; k++) {
					sum += matrix[i][k] * matr.matrix[k][j];
				}
				res.matrix[i][j] = sum;
			}
		}
		return res;
	}


	bool Gauss(Vector& b, Vector& x) {
		if (rows != columns)
			return false;

		for (int i = 0; i < rows; i++) {
			int indMaxElem = i;
			for (int j = i + 1; j < rows; j++) {
				if (abs(matrix[j][i]) > abs(matrix[indMaxElem][i])) {
					indMaxElem = j;
				}
			}
			if (matrix[indMaxElem][i] == 0) {
				cout << "Zero matrix" << endl;
				return false;
			}

			swap(matrix[i], matrix[indMaxElem]);
			if (i != indMaxElem) {
				double temp = b.GetComponent(i);
				b.AddingComponent(i, b.GetComponent(indMaxElem));
				b.AddingComponent(indMaxElem, temp);
			}

			double leadingElem = matrix[i][i];
			for (int j = i; j < columns; j++) {
				matrix[i][j] = matrix[i][j] / leadingElem;
			}
			b.AddingComponent(i, b.GetComponent(i) / leadingElem);

			for (int k = i + 1; k < rows; k++) {
				double a = matrix[k][i];
				for (int j = i; j < columns; j++) {
					matrix[k][j] -= a * matrix[i][j];
				}
				b.AddingComponent(k, b.GetComponent(k) - a * b.GetComponent(i));
			}
		}

		x.AddingComponent(rows - 1, b.GetComponent(rows - 1));
		for (int i = rows - 2; i >= 0; i--) {
			double sum = 0.0;
			for (int j = i + 1; j < columns; j++) {
				sum += matrix[i][j] * x.GetComponent(j);
			}
			x.AddingComponent(i, b.GetComponent(i) - sum);
		}
		return true;
	}

};



int main() {

	Matrix A(3, 3);
	A.AddingElement(0, 0, 1); A.AddingElement(0, 1, 1); A.AddingElement(0, 2, 1);
	A.AddingElement(1, 0, 2); A.AddingElement(1, 1, 3); A.AddingElement(1, 2, 1);
	A.AddingElement(2, 0, 1); A.AddingElement(2, 1, 2); A.AddingElement(2, 2, 3);

	Matrix::Vector b(3);
	b.AddingComponent(0, 6);
	b.AddingComponent(1, 14);
	b.AddingComponent(2, 14);

	Matrix::Vector x(3);

	if (A.Gauss(b, x)) {
		cout << "Solution: ";
		x.PrintVector();
	}

	return 0;
}