#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x;
    int n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;

    double res = 1.0;
    double elem = 1.0;
    for (int i = 1; i <= n; i++) {
        elem *= (x / i);
        res += elem;
    }
    cout << res << endl;

    return 0;
}

//-------------------------------------//

int main()
{
    double x;
    int n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;

    double res = 0.0;
    double elem = x;

    for (int i = 1; i <= n; i += 2) {
        if (i % 2 != 0) {
            if ((i / 2) % 2 == 0)
                res += elem;
            else
                res -= elem;
        }
        elem *= (x * x) / ((i + 1) * (i + 2));
    }
    cout << "sin(" << x << ") = " << res << endl;
    cout << "Exact meaning: " << sin(x) << endl;

    return 0;
}

//-------------------------------------------------//


int main()
{
    double x;
    int n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;

    double res = 0.0;
    double elem = 1;

    for (int i = 0; i <= n; i += 2) {
        if (i % 2 == 0) {
            if ((i / 2) % 2 == 0)
                res += elem;
            else
                res -= elem;
        }
        elem *= (x * x) / ((i + 1) * (i + 2));
    }
    cout << "cos(" << x << ") = " << res << endl;
    cout << "Exact meaning: " << cos(x) << endl;

    return 0;
}
////
////