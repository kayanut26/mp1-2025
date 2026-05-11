#include <iostream>
#include <cmath>
#include <functional>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

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
		cout << sqrt(sum) << endl;;
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
	cout << ")" << endl;;
	return os;
}

class Matrix {
	int rows;
	int columns;
	int** matrix;

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
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new int[columns];
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
		cout << "Matrix size: " << rows << "x" << columns << endl;;
	}

	int getSize() {
		return rows;
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

	int& operator()(int i, int j) {
		if (i < 0 || i >= rows || j < 0 || j >= columns)
			throw MatrixException("index out of range");
		return matrix[i][j];
	}

	const int& operator()(int i, int j) const {
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
				cout << "Zero matrix" << endl;;
				return false;
			}

			if (i != indMaxElem) {
				swap(matrix[i], matrix[indMaxElem]);
				swap(b[i], b[indMaxElem]);
			}

			int leadingElem = matrix[i][i];
			for (int j = i; j < columns; j++) {
				matrix[i][j] /= leadingElem;
			}
			b[i] /= leadingElem;

			for (int k = i + 1; k < rows; k++) {
				int a = matrix[k][i];
				for (int j = i; j < columns; j++) {
					matrix[k][j] -= a * matrix[i][j];
				}
				b[k] -= a * b[i];
			}
		}

		x[rows - 1] = b[rows - 1];
		for (int i = rows - 2; i >= 0; i--) {
			int sum = 0.0;
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
		cout << endl;;
	}
	return os;
}

enum Status { EMPTY, INJURED, KILLED };

class Gamer {
protected:
	string name;
	int shipsleft;
	Matrix myPole;
	Matrix enemyPole;
	Status s;
	Status ls;
	int lx, ly;
public:
	Gamer(string n) : name(n), shipsleft(4), myPole(5, 5), enemyPole(5, 5), s(EMPTY), ls(EMPTY), lx(-1), ly(-1) {}
	int getLx() const { return lx; }
	int getLy() const { return ly; }


	virtual void Do() = 0;
	virtual void Answer() = 0;
	virtual void placeShips() = 0;
	virtual Status getls() const = 0;
};

class User : public Gamer {
	int x, y;
public:
	User(string n) : Gamer(n), x(0), y(0) {}

	void showMyPole() {
		cout << "  1 2 3 4 5" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " ";
			for (int j = 0; j < 5; j++) {
				if (myPole(i, j) == 1)
					cout << "H ";
				else
					cout << "0 ";
			}
			cout << endl;;
		}
	}

	void showEnemyPole() {
		cout << "  1 2 3 4 5" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " ";
			for (int j = 0; j < 5; j++) {
				if (enemyPole(i, j) == 1)
					cout << "X ";
				else
					cout << "? ";
			}
			cout << endl;;
		}
	}

	bool tryPlaceShips(int row, int col, int ship, int space) {
		if (space == 0) {
			if (col + ship > 5) return false;
			else {
				for (int j = col; j < col + ship; j++) {
					if (myPole(row, j) != 0) return false;
				}
				for (int j = col; j < col + ship; j++)
					myPole(row, j) = 1;
			}
		}
		else {
			if (row + ship > 5) return false;
			else {
				for (int i = row; i < row + ship; i++) {
					if (myPole(i, col) != 0) return false;
				}
				for (int i = row; i < row + ship; i++)
					myPole(i, col) = 1;
			}
		}
		return true;
	}

	void placeShips() override {
		vector<int> ships = { 4, 3, 2, 1 };

		for (int ship : ships) {
			bool success = false;
			while (!success) {
				int row, col;
				cout << "\n" << "Place ship size(" << ship << ")" << endl;;
				cout << "Enter your point: ";
				cin >> row >> col;
				row--;
				col--;

				int space;
				cout << "Enter: horizontal - 0, vertical - 1: ";
				cin >> space;

				success = tryPlaceShips(row, col, ship, space);
				if (!success)
					cout << "You can't place a ship here." << endl;;
			}
		}
		showMyPole();
	}

	void Do() override {
		cout << "\n" << name << " Your turn" << endl;
		showEnemyPole();
		cout << "Enter your point: ";
		cin >> x >> y;

		x--;
		y--;

		if (x < 0 || x >= 5 || y < 0 || y >= 5) {
			cout << "Invalid point" << endl;
			return Do();
		}

		lx = x;
		ly = y;

		enemyPole(x, y) = 1;
	}
	void Answer() override {
		string status;
		s = EMPTY;

		cout << "Your answer at point(" << lx << ", " << ly << ")" << endl;;
		cout << "Options: empty, injured, killed: ";
		cin >> status;
		if (status == "empty")
			s = EMPTY;
		else if (status == "injured")
			s = INJURED;
		else if (status == "killed")
			s = KILLED;
		ls = s;
	}

	Status getls() const override { return ls; }
};

class Computer : public Gamer {
	int x, y;
public:
	Computer(string n) : Gamer(n), x(0), y(0) {}

	bool check(int row, int col) {
		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {
				if (i >= 0 && i < 5 && j >= 0 && j < 5) {
					if (myPole(i, j) == 1) return false;
				}
			}
		}
		return true;
	}

	bool tryPlaceShips(int row, int col, int ship, int space) {
		if (space == 0) {
			if (col + ship > 5) return false;
			else {
				for (int j = col; j < col + ship; j++) {
					if (myPole(row, j) != 0) return false;
					if (!check(row, j)) return false;
				}
				for (int j = col; j < col + ship; j++)
					myPole(row, j) = 1;
			}
		}
		else {
			if (row + ship > 5) return false;
			else {
				for (int i = row; i < row + ship; i++) {
					if (myPole(i, col) != 0) return false;
					if (!check(i, col)) return false;
				}
				for (int i = row; i < row + ship; i++)
					myPole(i, col) = 1;
			}
		}
		return true;
	}

	void placeShips() override {
		vector<int> ships = { 4, 3, 2, 1 };

		for (int ship : ships) {
			bool success = false;
			int attempts = 0;
			while (!success) {
				attempts++;
				int row = rand() % 5;
				int col = rand() % 5;
				int space = rand() % 2;
				success = tryPlaceShips(row, col, ship, space);

			}
			if (!success) {
				return;
			}
		}
	}

	void Do() override {
		cout << "\n" << name << " attacks!" << endl;

		while (enemyPole(x, y) == 1) {
			x = rand() % 5;
			y = rand() % 5;
		}
		enemyPole(x, y) = 1;

		cout << "Attack at (" << x << ", " << y << ")" << endl;
		lx = x;
		ly = y;

	}


	void Answer() override {

		/*if (lx < 0 || lx >= 5 || ly < 0 || ly >= 5) {
			return;
		}*/

		if (myPole(lx, ly) == 1) {
			myPole(lx, ly) = 0;
			shipsleft--;

			if (shipsleft == 0) {
				s = KILLED;
				cout << "I lost" << endl;
			}
			else {
				s = INJURED;
				cout << "I injured" << endl;
			}
		}
		else {
			s = EMPTY;
			cout << "Miss" << endl;
		}
		ls = s;
	}

	Status getls() const override { return ls; }
};

class Game {
	User user;
	Computer computer;
	bool GAMEOVER;
	bool turn;
public:
	Game() : user(User("TeaMan ")), computer(Computer("CoffeeMan ")), GAMEOVER(false), turn(true) {}

	void Start() {
		user.placeShips();
		computer.placeShips();

		while (!GAMEOVER) {
			if (turn) {
				user.Do();
				computer.Answer();
				Status res = computer.getls();

				if (res == KILLED) {
					cout << "I lost. You win" << endl;
					GAMEOVER = true;
				}
				else if (res == EMPTY) {
					cout << "Miss" << endl;
					turn = false;

				}
				else {
					cout << "Injured" << endl;
					cout << "Your turn" << endl;
				}
			}
			else {

				computer.Do();
				user.Answer();
				Status res = user.getls();

				if (res == KILLED) {
					cout << "I lost. You win" << endl;
					GAMEOVER = true;
				}
				else if (res == EMPTY) {
					cout << "Miss" << endl;
					turn = true;

				}
				else {
					cout << "Injured" << endl;

				}
			}
		}
		cout << "Game over" << endl;
	}
};

int main() {
	srand(static_cast<unsigned int>(time(0)));

	Game game;
	game.Start();

	return 0;
}