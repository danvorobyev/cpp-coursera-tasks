#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Student {
    string name;
    string surname;
    struct Date {
        int day;
        int month;
        int year;
    } birth;
};

int main() {
    int N;
    cin >> N;

    vector<Student> students(N);

    for (Student& student : students) {
        cin >> student.name >> student.surname
            >> student.birth.day >> student.birth.month 
            >> student.birth.year;
    }

    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
        string request;
        int student_id;
        cin >> request >> student_id;
        student_id--;

        if (request == "name" && student_id >= 0 && student_id < students.size())
            cout << students[student_id].name    << " " 
                 << students[student_id].surname << endl;
        else if (request == "date" && student_id >= 0 && student_id < students.size())
            cout << students[student_id].birth.day   << "."
                 << students[student_id].birth.month << "."
                 << students[student_id].birth.year  << endl;
        else 
            cout << "bad request" << endl;
    }
    return 0;
}
