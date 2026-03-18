#include <iostream>
#include <string>
using namespace std;

class Time {
	int hours;
	int minuts;
	int seconds;

	void Normalize() {
		if (seconds >= 60) {
			minuts += seconds / 60;
			seconds %= 60;
		}
		else if (seconds < 0) {
			int n = (abs(seconds) + 59) / 60;
			minuts -= n;
			seconds += n * 60;
		}

		if (minuts >= 60) {
			hours += minuts / 60;
			minuts %= 60;
		}
		else if (minuts < 0) {
			int n = (abs(minuts) + 59) / 60;
			hours -= n;
			minuts += n * 60;
		}

		if (hours >= 24) {
			hours %= 24;
		}

	}
public:
	Time() {
		hours = 0;
		minuts = 0;
		seconds = 0;
	}

	void SetTime(int n1, int n2, int n3) {
		hours = n1;
		minuts = n2;
		seconds = n3;
		Normalize();

	}

	void Difference(int n1, int n2, int n3) {
		int diffsec = abs((hours * 3600 + minuts * 60 + seconds) - (n1 * 3600 + n2 * 60 + n3)),
			diffhou = diffsec / 3600;
		diffsec %= 3600;
		int diffmin = diffsec / 60;
		diffsec %= 60;

		cout << "Difference: " << diffhou << ":"
			<< diffmin << ":" << diffsec << endl << endl;

	}

	void ShiftLeft(int n1, int n2, int n3) {

		int diffsec = hours * 3600 + minuts * 60 + seconds - (n1 * 3600 + n2 * 60 + n3);

		diffsec %= 24 * 3600;
		if (diffsec < 0)
			diffsec += 24 * 3600;

		int NewHours = diffsec / 3600;
		diffsec %= 3600;
		int NewMinuts = diffsec / 60;
		int NewSeconds = diffsec % 60;

		hours = NewHours;
		minuts = NewMinuts;
		seconds = NewSeconds;

		cout << "New time: " << hours << ":" << minuts << ":" << seconds << endl;

	}

	void ShiftRight(int n1, int n2, int n3) {

		int diffsec = hours * 3600 + minuts * 60 + seconds + (n1 * 3600 + n2 * 60 + n3);

		diffsec %= 24 * 3600;
		if (diffsec < 0)
			diffsec += 24 * 3600;

		int NewHours = diffsec / 3600;
		diffsec %= 3600;
		int NewMinuts = diffsec / 60;
		int NewSeconds = diffsec % 60;

		hours = NewHours;
		minuts = NewMinuts;
		seconds = NewSeconds;

		cout << "New time: " << hours << ":" << minuts << ":" << seconds << endl;

	}

	void PrintTime() {

		if (hours < 10) cout << "0";
		cout << hours << ":";

		if (minuts < 10) cout << "0";
		cout << minuts << ":";

		if (seconds < 10) cout << "0";
		cout << seconds << endl;

	}
};

int main() {
	int hours, minuts, seconds, hours1, minuts1, seconds1;
	Time time;
	int choice = -1;

	while (choice != 6) {
		cout << "Select an action" << endl;
		cout << "1. Set time" << endl;
		cout << "2. Find out the time" << endl;
		cout << "3. Calculate the difference between the given time and the set time" << endl;
		cout << "4. Shift time by a given offset downwards" << endl;
		cout << "5. Shift time by a given offset upwards" << endl;
		cout << "6. Exit" << endl;
		cout << endl;
		cout << "Your choice: ";
		cin >> choice;


		switch (choice) {
		case 1: {
			cout << endl;
			int flag1 = -1;
			while (flag1 != 1) {
				cout << "hours minuts seconds: ";
				cin >> hours >> minuts >> seconds;
				if (hours >= 0 && minuts >= 0 && seconds >= 0) {
					time.SetTime(hours, minuts, seconds);
					flag1 = 1;
				}
				else
					cout << "Incorrect time" << endl;
			}
			break;
		}
		case 2: {
			time.PrintTime();
			break;
		}
		case 3: {
			int flag2 = -1;
			while (flag2 != 1) {
				cout << "hours minuts seconds: ";
				cin >> hours1 >> minuts1 >> seconds1;
				if (hours1 >= 0 && minuts1 >= 0 && seconds1 >= 0) {
					time.Difference(hours1, minuts1, seconds1);
					flag2 = 1;
				}
				else
					cout << "Incorrect time" << endl;
			}
			break;
		}
		case 4: {
			int flag3 = -1;
			while (flag3 != 1) {
				cout << "hours minuts seconds: ";
				cin >> hours1 >> minuts1 >> seconds1;
				if (hours1 >= 0 && minuts1 >= 0 && seconds1 >= 0) {
					time.ShiftLeft(hours1, minuts1, seconds1);
					flag3 = 1;
				}
				else
					cout << "Incorrect time" << endl;
			}
			break;
		}
		case 5: {
			int flag4 = -1;
			while (flag4 != 1) {
				cout << "hours minuts seconds: ";
				cin >> hours1 >> minuts1 >> seconds1;
				if (hours1 >= 0 && minuts1 >= 0 && seconds1 >= 0) {
					time.ShiftRight(hours1, minuts1, seconds1);
					flag4 = 1;
				}
				else
					cout << "Incorrect time" << endl;
			}
			break;
		}
		}
	}
	return 0;
}