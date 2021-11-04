#include "phone_number.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    PhoneNumber p("7-aaa-bbbccc");
    cout << p.GetInternationalNumber() << endl;
    cout << p.GetCityCode() << endl;
    cout << p.GetLocalNumber() << endl;

    return 0;
}