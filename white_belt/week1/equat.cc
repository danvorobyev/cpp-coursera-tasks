#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double get_linear_root(double a, double b) {
    return -b / a;
}

double squared_discr(double a, double b, double c) {
    return pow(b, 2) - 4 * a * c;
}

vector<double> get_true_quad_roots(double a, double b, double c) {
    double squared_d = squared_discr(a, b, c);
    if (squared_d < 0)
        return {};

    if (squared_d == 0)
        return {-b / (2 * a)};

    double discr = sqrt(squared_d);
    return {(-b - discr) / (2 * a), (-b + discr) / (2 * a)};
};

vector<double> get_quad_roots(double a, double b, double c) {
    if (a == 0 && b == 0) 
        return {};

    if (a == 0) 
        return {get_linear_root(b, c)};

    return get_true_quad_roots(a, b, c);
}

int main() {
    double a, b, c;
    
    cin >> a >> b >> c;

    vector<double> roots = get_quad_roots(a, b, c);    
             
    for (auto root: roots)
        cout << root << " ";

    cout << endl; 

    return 0;
}
