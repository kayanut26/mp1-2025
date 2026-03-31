#include <iostream>
#include <string>
using namespace std;

class Matrix {
	int rows;
	int columns;
	double** matrix;

public:
	// Constructor
	Matrix(int rows1, int columns1) {
		rows = rows1;
		columns = columns1;
		matrix = nullptr;
		MemoryAllocation();
	}

	// Destructor
	~Matrix() {
		MemoryDelete();
	}

	// Copy constructor
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

	// Assignment operator
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
};



int main() {
	Matrix matr(3, 3);
	Matrix matr2(3, 3);
	Matrix matr3(3, 3);
	Matrix matr4(3, 3);
	matr.AddingElement(0, 0, 1);
	matr.AddingElement(0, 1, 2);
	matr.AddingElement(0, 2, 3);
	matr.AddingElement(1, 0, 4);
	matr.AddingElement(1, 1, 5);
	matr.AddingElement(1, 2, 6);
	matr.AddingElement(2, 0, 7);
	matr.AddingElement(2, 1, 8);
	matr.AddingElement(2, 2, 9);

	matr2.AddingElement(0, 0, 9);
	matr2.AddingElement(0, 1, 8);
	matr2.AddingElement(0, 2, 7);
	matr2.AddingElement(1, 0, 6);
	matr2.AddingElement(1, 1, 5);
	matr2.AddingElement(1, 2, 4);
	matr2.AddingElement(2, 0, 3);
	matr2.AddingElement(2, 1, 2);
	matr2.AddingElement(2, 2, 1);

	/*matr3 = matr * matr2;
	cout << endl;*/
	matr4 = matr2 + matr;

	matr.PrintMatrix();
	cout << endl;
	matr2.PrintMatrix();
	cout << endl << "------------------" << endl << endl;
	/*matr3.PrintMatrix();
	cout << endl;*/
	matr4.PrintMatrix();
	cout << endl;

}

// класс вектор, оператор==, гаусс

//int main() {
//	int rows, columns, value, rows1, columns1;
//	int choice = -1;
//	Matrix matr(0, 0);
//
//	while (choice != 6) {
//		cout << "1. Set the matrix size" << endl;
//		cout << "2. Find out the matrix size" << endl;
//		cout << "3. Specify a matrix element by its indices" << endl;
//		cout << "4. Find a matrix element by its indices" << endl;
//		cout << "5. Print Matrix" << endl;
//		cout << "6. Exit" << endl;
//		cout << endl;
//		cout << "Your choice: ";
//		cin >> choice;
//
//		switch (choice) {
//		case 1: {
//			cout << endl;
//			int flag1 = -1;
//			while (flag1 != 1) {
//				cout << "Enter size (rows columns): ";
//				cin >> rows >> columns;
//				if (rows > 0 && columns > 0) {
//					Matrix test(rows, columns);
//					matr = test;
//					flag1 = 1;
//				}
//				else
//					cout << "Incorrect size" << endl;
//			}
//			cout << endl;
//			break;
//		}
//		case 2: {
//			cout << endl;
//			matr.ShowSize();
//			cout << endl;
//			break;
//		}
//		case 3: {
//			cout << endl;
//			int flag2 = -1;
//			while (flag2 != 1) {
//				cout << "Enter index element (row columns) and value: ";
//				cin >> rows1 >> columns1 >> value;
//				flag2 = matr.AddingElement(rows1, columns1, value);
//			}
//			cout << endl;
//			break;
//		}
//		case 4: {
//			cout << endl;
//			int flag3 = -1;
//			while (flag3 != 1) {
//				cout << "Enter index element (row columns): ";
//				cin >> rows1 >> columns1;
//				flag3 = matr.PrintElement(rows1, columns1);
//			}
//			cout << endl;
//			break;
//		}
//		case 5: {
//			cout << endl;
//			matr.PrintMatrix();
//			cout << endl;
//			break;
//		}
//		}
//	}
//	return 0;
//}
