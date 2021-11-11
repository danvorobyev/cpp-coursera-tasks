#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& name_)
    : Name(name_) {}

    const string Name;
};


class Dog : public Animal {
public:
    Dog(const string& name_)
    : Animal(name_) {}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
    Dog d("Barboskin");
    d.Bark();
    return 0;
}
