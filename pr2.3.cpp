#include <iostream>
#include <queue>

using namespace std;

class Sportsman {
private:
    string name, secondName, country, sport;
    int age, medals;

public:

    Sportsman() {
        name = secondName = country = sport = "";
        age = medals = 0;
    }

    Sportsman(string Name, string secName, string Country, string Sport, int Age, int Medals) {
        name = Name; secondName = secName; country = Country; sport = Sport;
        age = Age; medals = Medals;
    }

    Sportsman(const Sportsman& c) {
        name = c.name; secondName = c.secondName; country = c.country; sport = c.sport;
        age = c.age; medals = c.medals;
    }

    ~Sportsman() { }

    friend ostream& operator<<(ostream&, const Sportsman&);

    Sportsman& operator= (const Sportsman& sp) {
        medals = sp.medals;
        age = sp.age;
        name = sp.name;
        secondName = sp.secondName;
        country = sp.country;
        sport = sp.sport;
    }

    bool operator< (const Sportsman& sp) {
        if (medals < sp.medals)
            return true;
        if (age > sp.age)
            return true;
        if (secondName > sp.secondName)
            return true;
        if (name > sp.name)
            return true;
        return false;
    }

    bool operator> (const Sportsman& sp) {
        if (medals > sp.medals)
            return true;
        if (age < sp.age)
            return true;
        if (secondName < sp.secondName)
            return true;
        if (name < sp.name)
            return true;
        return false;
    }
};

ostream& operator<< (ostream& out, const Sportsman& c) {
    out << "--Sportsman-- " << endl
        << "Name: " << c.name << endl
        << "Second Name: " << c.secondName << endl
        << "Country: " << c.country << endl
        << "Number of medals: " << c.medals << endl
        << "Age: " << c.age << endl << endl;
    return out;
}

template<typename T>
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {

    Sportsman
            sp1("Gregory", "Demchenko", "Russia", "Voleyball", 19, 2),
            sp2("Alexey", "Avgust", "Belarus", "Tennis", 21, 4),
            sp3("Xiao", "Lin", "China", "Skiing", 27, 9),
            sp4("John", "Lenon", "Britain", "Football", 32, 4),
            sp5("Ayanami", "Rei", "Japan", "Archery", 14, 10),
            sp6("Polnaref", "Jian Piere", "France", "Athletics", 18, 8),
            sp7("Peter", "Lindemann", "Germany", "Tennis", 38, 16),
            sp8("Glen", "Quagmire", "USA", "Athletics", 30, 6),
            sp9("Mathew", "Bellamy", "Britain", "Voleyball", 27, 6),
            sp10("Anatoly", "Annin", "Russia", "Chess", 41, 22);

    priority_queue<Sportsman, vector<Sportsman>, less<> > sport_pqueue;

    for (const Sportsman& s : {sp1, sp2, sp3, sp4, sp5, sp6, sp7, sp8, sp9, sp10}) {
        sport_pqueue.push(s);
    }

    print_queue(sport_pqueue);
}