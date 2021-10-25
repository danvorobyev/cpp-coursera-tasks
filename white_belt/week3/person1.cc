#include <map>

string FindNameByYear(int year, map<int, string>& names) {
    string name;
    for (const auto& item : names) {
        if (item.first <= year)
            name = item.second;
        else 
            break;
    }
    return name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        const string first_name = FindNameByYear(year, first_names);
        const string last_name = FindNameByYear(year, last_names);
        if (first_name.empty() && last_name.empty())
            return "Incognito";
        if (first_name.empty())
            return last_name + " with unknown first name";
        if (last_name.empty())
            return first_name + " with unknown last name";
        return first_name + " " + last_name;
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
};
