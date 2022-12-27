// Григорий Деиченко КМБО 06-21 Практическая работа 1.2

#include <iostream>
#include <list>
#include <cmath>
#include <string>

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



// Функция вывода списка
template<class T>
void print(list<T> lst) {
    auto it = lst.begin();

    while (it != lst.end()) {
        cout << *it << " ";
        it++;
    }
}

// Функция добавления в список с сохранением упорядоченности
template <class T>
void push(list<T>& lst, T el) {
    if (lst.empty()) {
        lst.insert(lst.begin(), el);
        return;
    }

    auto p = lst.begin();
    while (p != lst.end() && *p < el) {
        p++;
    }

    lst.insert(p, el);
}

// Функция фильтрации
template<class T>
void filter(list<T> source, list<T>& result, bool (*ptr_f)(char)) {
    for (auto it = source.begin(); it != source.end(); *it++)
        if (ptr_f(*it))
            result.push(*it);
}

// Функция удаления
template <class T>
T pop(list<T>& lst) {
    if (lst.empty())
        throw invalid_argument("list is empty!");

    auto p = lst.begin();
    lst.erase(p);
    return *p;
}

// Условие для filter()
bool Condition() {
    return true;
}

int main() {

    list<Sportsman> lst;

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

    push(lst, sp1);
    push(lst, sp2);
    push(lst, sp3);
    push(lst, sp4);
    push(lst, sp5);
    push(lst, sp6);
    push(lst, sp7);
    push(lst, sp8);
    push(lst, sp9);
    push(lst, sp10);

    // Вывод списка
    print(lst);
    cout << "\n";

    // Работа функции удаления элемента из списка
    Sportsman popedEl = pop(lst);

    cout << "pop: " << endl;
    cout << popedEl << endl;

    print(lst);

    cout << "pop sp5" << endl;
    print(lst);
    cout << "\n";

    return 0;
}