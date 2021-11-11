#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& profession)
    : Name(name),
      Profession(profession) {}

    virtual void Walk(const string& destination) const {
        PrintHuman() << " walks to: " << destination << endl;
    }
    
    const string Name;
    const string Profession;

protected: 
    ostream& PrintHuman() const {
        cout << Profession << ": " << Name;
        return cout;
    }
};

class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong) :
    Human(name, "Student"),
    FavouriteSong(favouriteSong) {}

    void Learn() {
        PrintHuman() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        PrintHuman() << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Human {
public:
    Teacher(string name, string subject)
    : Human(name, "Teacher"),
      Subject(subject) {}

    void Teach() {
        PrintHuman() << " teaches: " << Subject << endl;
    }

    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name)
    : Human(name, "Policeman") {}

    void Check(const Human& h) {
        PrintHuman() << " checks " << h.Profession << ". " << h.Profession << "'s name is: " << h.Name << endl;
    }
};


void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    vector<string> places = {"Moscow", "London"};

    VisitPlaces(t, places);
    p.Check(s);
    VisitPlaces(s, places);
    return 0;
}
