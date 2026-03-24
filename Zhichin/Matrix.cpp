#include <iostream>
#include <string>
using namespace std;

class Matrix {
	int rows;
	int columns;
	int** matrix;

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
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new int[columns];
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
		matrix = new int* [rows] {};
		for (int i = 0; i < rows; i++)
			matrix[i] = new int[columns] {};
	}

	void MemoryDelete() {
		if (matrix != nullptr) {
			for (int i = 0; i < rows; i++)
				delete[] matrix[i];
			delete[] matrix;
			matrix = nullptr;
		}
	}


	int AddingElement(int row, int column, int elem) {
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

};


int main() {
	int rows, columns, value, rows1, columns1;
	int choice = -1;
	Matrix matr(0, 0);

	while (choice != 6) {
		cout << "1. Set the matrix size" << endl;
		cout << "2. Find out the matrix size" << endl;
		cout << "3. Specify a matrix element by its indices" << endl;
		cout << "4. Find a matrix element by its indices" << endl;
		cout << "5. Print Matrix" << endl;
		cout << "6. Exit" << endl;
		cout << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << endl;
			int flag1 = -1;
			while (flag1 != 1) {
				cout << "Enter size (rows columns): ";
				cin >> rows >> columns;
				if (rows > 0 && columns > 0) {
					Matrix test(rows, columns);
					matr = test;
					flag1 = 1;
				}
				else
					cout << "Incorrect size" << endl;
			}
			cout << endl;
			break;
		}
		case 2: {
			cout << endl;
			matr.ShowSize();
			cout << endl;
			break;
		}
		case 3: {
			cout << endl;
			int flag2 = -1;
			while (flag2 != 1) {
				cout << "Enter index element (row columns) and value: ";
				cin >> rows1 >> columns1 >> value;
				flag2 = matr.AddingElement(rows1, columns1, value);
			}
			cout << endl;
			break;
		}
		case 4: {
			cout << endl;
			int flag3 = -1;
			while (flag3 != 1) {
				cout << "Enter index element (row columns): ";
				cin >> rows1 >> columns1;
				flag3 = matr.PrintElement(rows1, columns1);
			}
			cout << endl;
			break;
		}
		case 5: {
			cout << endl;
			matr.PrintMatrix();
			cout << endl;
			break;
		}
		}
	}
	return 0;
}