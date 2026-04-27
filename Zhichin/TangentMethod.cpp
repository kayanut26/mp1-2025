#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

class TangentMethod {
private:
    double accuracy;
    int MaxIter;

public:
    TangentMethod(double eps = 1e-7, int MaxIter1 = 1000)
        : accuracy(eps), MaxIter(MaxIter1) {
    }

    double method(function<double(double)> f, function<double(double)> df, double x0) {
        double x = x0;

        for (int i = 0; i < MaxIter; i++) {
            double fx = f(x);
            double dfx = df(x);

            double xNew = x - fx / dfx;

            if (abs(xNew - x) < accuracy) {
                cout << "Converged after " << i + 1 << " iterations" << endl;
                return xNew;
            }

            x = xNew;
        }

        cout << "Maximum iterations reached!" << endl;
        return x;
    }
};

double func(double x) {
    return x * x - 4;
}

double derfunc(double x) {
    return 2 * x;
}


int main() {
    TangentMethod method1;

    cout << "x^2 - 4 = 0:" << endl;
    double root1 = method1.method(func, derfunc, 3.0);
    cout << "Root: " << root1 << endl;
    cout << "Check: f(" << root1 << ") = " << func(root1) << endl;
    cout << endl;
}