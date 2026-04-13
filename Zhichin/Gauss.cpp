#include <iostream>
#include <string>
using namespace std;


class MatrixException {
	string message;
public:
	MatrixException(string message1) {
		message = message1;
	}
	string getMessage() {
		return message;
	}
};

class VectorException {
	string message;
public:
	VectorException(string message1) {
		message = message1;
	}
	string getMessage() {
		return message;
	}
};

class Vector {
	int n;
	double* vector;

public:
	Vector(int n1) {
		if (n1 < 0)
			throw VectorException("the number of elements is negative");
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

	double& operator[](int i) {
		if (i < 0 || i >= n)
			throw VectorException("index out of range");
		return vector[i];
	}

	const double& operator[](int i) const {
		if (i < 0 || i >= n)
			throw VectorException("index out of range");
		return vector[i];
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

	friend ostream& operator<<(ostream& os, Vector& vec);
};

ostream& operator<<(ostream& os, Vector& vec) {
	cout << "(";
	for (int i{ 0 }; i < vec.n; i++) {
		cout << vec[i];
		if (i < vec.n - 1) cout << ", ";
	}
	cout << ")" << endl;
	return os;
}

class Matrix {
	int rows;
	int columns;
	double** matrix;

public:
	Matrix(int rows1, int columns1) {
		if (rows1 < 0 || columns1 < 0)
			throw MatrixException("rows or columns are negative");
		rows = rows1;
		columns = columns1;
		matrix = nullptr;
		MemoryAllocation();
	}

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

	double& operator()(int i, int j) {
		if (i < 0 || i >= rows || j < 0 || j >= columns)
			throw MatrixException("index out of range");
		return matrix[i][j];
	}

	const double& operator()(int i, int j) const {
		if (i < 0 || i >= rows || j < 0 || j >= columns)
			throw MatrixException("index out of range");
		return matrix[i][j];
	}

	friend ostream& operator<<(ostream& stream, Matrix& matr);

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
			if (abs(matrix[indMaxElem][i]) < 1e-14) {
				cout << "Zero matrix" << endl;
				return false;
			}

			if (i != indMaxElem) {
				swap(matrix[i], matrix[indMaxElem]);
				swap(b[i], b[indMaxElem]);
			}

			double leadingElem = matrix[i][i];
			for (int j = i; j < columns; j++) {
				matrix[i][j] /= leadingElem;
			}
			b[i] /= leadingElem;

			for (int k = i + 1; k < rows; k++) {
				double a = matrix[k][i];
				for (int j = i; j < columns; j++) {
					matrix[k][j] -= a * matrix[i][j];
				}
				b[k] -= a * b[i];
			}
		}

		x[rows - 1] = b[rows - 1];
		for (int i = rows - 2; i >= 0; i--) {
			double sum = 0.0;
			for (int j = i + 1; j < columns; j++) {
				sum += matrix[i][j] * x[j];
			}
			x[i] = b[i] - sum;
		}
		return true;
	}

};

ostream& operator<<(ostream& os, Matrix& matr) {
	for (int i = 0; i < matr.rows; i++) {
		for (int j = 0; j < matr.columns; j++)
			os << matr(i, j) << "\t";
		cout << endl;
	}
	return os;
}


int main() {

	try {
		Matrix A(3, 3);
		Vector b(3);
		Vector x(3);

		try {
			Matrix A(3, 3);
			Vector b(3);
			Vector x(3);

			A(0, 0) = 1;  A(0, 1) = 1;  A(0, 2) = 1;
			A(1, 0) = 2;  A(1, 1) = 3;  A(1, 2) = 1;
			A(2, 0) = 1;  A(2, 1) = 2;  A(2, 2) = 3;

			cout << A << endl;

			b[0] = 6;
			b[1] = 14;
			b[2] = 14;

			if (A.Gauss(b, x)) {
				cout << "Solution: ";
				cout << x << endl;
			}
		}
		catch (MatrixException& ex) {
			cerr << "Matrix error: " << ex.getMessage() << endl;
		}
		catch (VectorException& ex) {
			cerr << "Vector error: " << ex.getMessage() << endl;
		}
	}
	catch (MatrixException& ex) {
		cerr << "Matrix error: " << ex.getMessage() << endl;
	}
	catch (VectorException& ex) {
		cerr << "Vector error: " << ex.getMessage() << endl;
	}

	return 0;
}