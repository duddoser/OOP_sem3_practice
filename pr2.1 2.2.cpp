#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

// написать функцию push() с исключением, в функциях поиска исполльзовать find() из библиотеки stl

#include <iostream>
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

    Sportsman& operator= (const Sportsman& sp) {
        medals = sp.medals;
        age = sp.age;
        name = sp.name;
        secondName = sp.secondName;
        country = sp.country;
        sport = sp.sport;
        return *this;
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

    string getName() { return name; }
    string getSecondName() { return secondName; }
    string getCountry() { return country; }
    string getSport() { return sport; }

    int getAge() { return age; }
    int getMedals() { return medals; }

    friend ostream& operator<<(ostream&, const Sportsman&);
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

template<typename VALUE>
void print_set(set<VALUE> st) {
    auto it = st.begin();
    cout << "\n\n";
    while (it != st.end()) {
        cout << *it << ", ";
        it++;
    } cout << "\n";
}

template<class KEY, typename VALUE>
void print(map<KEY, VALUE> map) {
    auto it_m = map.begin();
    cout << "\n\n";
    while (it_m != map.end()) {
        cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
        it_m++;
    }
}

template<class KEY, typename VALUE, class K>
pair<KEY, VALUE> find_key(map<KEY, VALUE> &map, K key) {
    auto r = map.find(key);
    return *r;
}

template<class KEY, typename VALUE>
map<KEY, VALUE> find_values(map<KEY, VALUE> mp, VALUE value) {
    map<KEY, VALUE> res_map;
    auto it_m = mp.begin();
    while (it_m != mp.end()) {
        if (it_m->second == value)
            res_map.insert(*it_m);
        it_m++;
    }
    return res_map;
}

bool Condition(int mark) {
    if (mark > 3)
        return true;
    return false;
}

template<class K, class V>
pair<set<K>, set<V>> vect(map<K, V> source) {
    set<K> set_K; set<V> set_V;

    auto it = source.begin();

    for(; it != source.end(); it++) {
        set_K.insert(it->first);
        set_V.insert(it->second);
    }
    return pair<set<K>, set<V>>(set_K, set_V);
}

template<class KEY, typename VALUE, class C>
map<KEY, VALUE> filter(map<KEY, VALUE> source, bool (*ptr_f)(C)) {
    map<KEY, VALUE> result;
    for (auto it = source.begin(); it != source.end(); *it++)
        if (ptr_f(it->second))
            result.insert(*it);
    return result;
}

bool medals_condition(Sportsman s) {
    if (s.getMedals() > 5)
        return true;
    return false;
}

template<class KEY, typename VALUE>
void push(map<KEY ,VALUE> &mp, KEY key, VALUE val) {
    auto el = mp.find(key);
    if (key == el->first)
        throw invalid_argument("this key already exist");

    mp.insert({key, val});
}

// -------2.2-------

template<class KEY, typename VALUE, class C>
multimap<KEY, VALUE> filter_multimap(multimap<KEY, VALUE> source, bool (*ptr_f)(C)) {
    multimap<KEY, VALUE> result;
    for (auto it = source.begin(); it != source.end(); *it++)
        if (ptr_f(it->second))
            result.insert(*it);
    return result;
}

template<class KEY, typename VALUE>
void print_multimap(multimap<KEY, VALUE> map) {
    auto it_m = map.begin();
    cout << "\n\n";
    while (it_m != map.end()) {
        cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
        it_m++;
    }
}

bool multimap_int_cond(int v) {
    if (v > 4)
        return true;
    return false;
}

template<class K, class V>
pair<set<K>, set<V>> vect_multimap(multimap<K, V> source) {
    set<K> set_K; set<V> set_V;

    auto it = source.begin();

    for(; it != source.end(); it++) {
        set_K.insert(it->first);
        set_V.insert(it->second);
    }
    return pair<set<K>, set<V>>(set_K, set_V);
}

template<class KEY, typename VALUE, class K>
multimap<KEY, VALUE> multimap_find_keys(multimap<KEY, VALUE> map, K key) {
    multimap<KEY, VALUE> result;
    auto key_it = map.equal_range(key);

    for (auto it = key_it.first; it != key_it.second; it++) {
        result.insert(*it);
    }
    return result;
}

template<class KEY, typename VALUE>
multimap<KEY, VALUE> multimap_find_values(multimap<KEY, VALUE> mp, VALUE value) {
    multimap<KEY, VALUE> res_map;
    auto it_m = mp.begin();
    while (it_m != mp.end()) {
        if (it_m->second == value)
            res_map.insert(*it_m);
        it_m++;
    }
    return res_map;
}

template<class KEY, typename VALUE>
pair<KEY, VALUE> push_multimap(multimap<KEY ,VALUE> &mp, KEY key, VALUE val) {
    mp.insert({key, val});
    pair<KEY, VALUE> el;
    el.first = key; el.second = val;
    return el;
}


int main() {

    // 2.1
    map<string, int> marks;

    marks["Petrov"] = 5;
    marks["Ivanov"] = 4;
    marks["Sidorov"] = 5;
    marks["Nikolaev"] = 3;
    marks["Abramov"] = 4;

    cout << "\nMap:";

    print(marks);

    pair<string, int> a = find_key(marks, "Nikolaev");
    cout << "\n" << a.first << ": " << a.second;

    map<string, int> res_map = find_values<string, int>(marks, 4);
    print(res_map);

    bool (*ptr_f)(int);
    ptr_f = Condition;

    map<string, int> res = filter<string, int>(marks, ptr_f);
    print(res);

    set<string> s1 = vect(marks).first;
    set<int> s2 = vect(marks).second;

    cout << "\nset_Key: ";
    print_set(s1);

    cout << "\nset_Value: ";
    print_set(s2);

    map<string, Sportsman> Sp_map;

    Sportsman
            sp1("Gregory", "Demchenko", "Russia", "Voleyball", 19, 2),
            sp2("Alexey", "Avgust", "Belarus", "Tennis", 21, 4),
            sp3("Xiao", "Lin", "China", "Skiing", 27, 9),
            sp4("John", "Lenon", "Britain", "Football", 32, 4),
            sp5("Ayanami", "Rei", "Japan", "Archery", 14, 10);

    string Sportsman_1 = "Sportsman_1";
    push(Sp_map, Sportsman_1, sp1);

    string Sportsman_2 = "Sportsman_2";
    push(Sp_map, Sportsman_2, sp2);

    string Sportsman_3 = "Sportsman_3";
    push(Sp_map, Sportsman_3, sp3);

    string Sportsman_4 = "Sportsman_4";
    push(Sp_map, Sportsman_4, sp4);

    string Sportsman_5 = "Sportsman_5";
    push(Sp_map, Sportsman_5, sp5);

    cout << "\nSportsman Map: ";
    print(Sp_map);


    map<string, Sportsman> filtered_Sp_map;

    bool (*ptr_f2)(Sportsman);
    ptr_f2 = medals_condition;

    filtered_Sp_map = filter(Sp_map, ptr_f2);

    cout << "\nFiltered sp_map:";
    print(filtered_Sp_map);

    // 2.2
    multimap<string, int> marks2;

    for (auto &mark : marks)
        push_multimap(marks2, mark.first, mark.second);

    string k = "Sidorov";
    push_multimap(marks2, k, 4);

    bool (*ptr_f_multimap)(int);
    ptr_f_multimap = multimap_int_cond;

    multimap<string, int> result = filter_multimap(marks2, ptr_f_multimap);

    print_multimap(result);

    set<string> set_key = vect_multimap(marks2).first;
    set<int> set_val = vect_multimap(marks2).second;

    print_multimap(marks2);

    cout << "\nmultimap keys set:";
    print_set(set_key);

    cout << "\nmultimap values set:";
    print_set(set_val);

    multimap<string, int> keys_found = multimap_find_keys(marks2, "Sidorov");

    print_multimap(keys_found);
}
