#include "phone_number.h"
#include <algorithm>
#include <exception>
#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream is(international_number);

    char sign;
    is.get(sign);

    if (sign != '+'
        || !getline(is, country_code_, '-')
        || !getline(is, city_code_, '-')
        || !getline(is, local_number_))
        throw invalid_argument("invalid number format");
        
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    ostringstream os;
    os << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
    return os.str();
}
