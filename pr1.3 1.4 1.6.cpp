#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class Element {//элемент связного списка
private:
//указатель на предыдущий и следующий элемент
    Element *next;
    Element *prev;
//информация, хранимая в поле
    T field;
public:
    Element(T value = 0, Element<T> *next_ptr = NULL, Element<T> *prev_ptr = NULL) {
        field = value;
        next = next_ptr;
        prev = prev_ptr;
    }

    //доступ к полю *next
    virtual Element *getNext() { return next; }

    virtual void setNext(Element *value) { next = value; }

    //доступ к полю *prev
    virtual Element *getPrevious() { return prev; }

    virtual void setPrevious(Element *value) { prev = value; }

    //доступ к полю с хранимой информацией field
    virtual T getValue() { return field; }

    virtual void setValue(T value) { field = value; }

    template<class T1>
    friend ostream &operator<<(ostream &
    ustream, Element<T1> &obj);
};

template<class T>
ostream &operator<<(ostream &ustream, Element<T> &obj) {
    ustream << obj.field;
    return ustream;
}

template<class T>
class LinkedListParent {
protected:
//достаточно хранить начало и конец
    Element<T> *head;
    Element<T> *tail;
//для удобства храним количество элементов
    int num;
public:
    virtual int Number() { return num; }

    virtual Element<T> *getBegin() { return head; }

    virtual Element<T> *getEnd() { return tail; }

    LinkedListParent() {
        //конструктор без параметров
        cout << "\nParent constructor";
        head = NULL;
        num = 0;
    }

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление

    virtual Element<T> *push(T value) = 0;

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление

    virtual Element<T> *pop() = 0;

    virtual ~LinkedListParent() {
        //деструктор - освобождение памяти
        cout << "\nParent destructor";
    }

    //получение элемента по индексу - какова асимптотическая оценка этого действия?

    virtual Element<T> *operator[](int i) {
        //индексация
        if (i < 0 || i > num) return NULL;
        int k = 0;
        //ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
        Element<T> *cur = head;
        for (k = 0; k < i; k++)
            cur = cur->getNext();
        return cur;
    }

    template<class T1>
    friend ostream &operator<<(ostream &ustream, LinkedListParent<T1> &obj);

    template<class T1>
    friend istream &operator>>(istream &ustream, LinkedListParent<T1> &obj);
};

template<class T>
ostream &operator<<(ostream &ustream, LinkedListParent<T> &obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.num << "\n";
        for (Element<T> *current = obj.getBegin(); current !=
                                                   NULL; current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }
    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (Element<T> *current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";
    return ustream;
}

template<class T>
istream &operator>>(istream &ustream, LinkedListParent<T> &obj) {
    //чтение из файла и консоли совпадают
    int len;
    ustream >> len;
    //здесь надо очистить память под obj, установить obj.num = 0
    double v = 0;
    for (int i = 0; i < len; i++) {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

class Iterator_Exception : public exception {
public:
    Iterator_Exception(string *msg) : exception() {

    }
};

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType> {
private:
public:
    ListIterator() { ptr = NULL; }

    //ListIterator(ValueType* p) { ptr = p; }
    ListIterator(Element<ValueType> *p) { ptr = p; }

    ListIterator(const ListIterator &it) { ptr = it.ptr; }

    bool operator!=(ListIterator const &other) const {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");
        else {
            return ptr != other.ptr;
        }
    }

    bool operator==(ListIterator const &other) const {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");
        else {
            return ptr == other.ptr;
        }
    }//need for BOOST_FOREACH
    Element<ValueType> &operator*() const {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");
        return *ptr;
    }

    ListIterator &operator++() {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");

        ptr = ptr->getNext();
        return *this;

    }

    ListIterator &operator++(int v) {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");
        else {
            ptr = ptr->getNext();
            return *this;
        }
    }

    ListIterator &operator--() {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");

        ptr = ptr->getPrevious();
        return *this;
    }

    ListIterator &operator--(int v) {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");

        ptr = ptr->getPrevious();
        return *this;
    }

    ListIterator &operator=(const ListIterator &it) {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");

        ptr = it.ptr;
        return *this;
    }

    ListIterator &operator=(Element<ValueType> *p) {
        if (ptr == NULL)
            throw Iterator_Exception((string *) "iterator is not bound to the element");

        ptr = p;
        return *this;
    }

private:
    Element<ValueType> *ptr;
};

template<class T>
class IteratedLinkedList : public LinkedListParent<T> {
public:
    IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }

    virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

    // Сделать подкласс итератора

    ListIterator<T> begin() {
        ListIterator<T> it = LinkedListParent<T>::head;
        return it;
    }

    ListIterator<T> end() {
        ListIterator<T> it = LinkedListParent<T>::tail;
        return it;
    }
};

template<class T>
class Stack : public IteratedLinkedList<T> {

public:
    class iterator;

    Stack() : IteratedLinkedList<T>() {  };

    ~Stack() {
        Element<T> *p = IteratedLinkedList<T>::head;
        Element<T> *temp = p;
        for (; p != NULL; p = temp) {
            temp = p->getNext();
            delete p;
        }
    }

    Element<T> *push(T value) {
        auto element = new Element<T>(value, NULL, LinkedListParent<T>::tail);
        if (LinkedListParent<T>::num != 0) {
            LinkedListParent<T>::tail->setNext(element);
        }
        LinkedListParent<T>::tail = element;
        LinkedListParent<T>::num++;
        if (LinkedListParent<T>::num == 1) {
            LinkedListParent<T>::head = element;
        }

        LinkedListParent<T>::tail->setNext(new Element<T>(value));

        return element;
    }

    Element<T> *pop() {
        if (IteratedLinkedList<T>::tail == NULL)
            return NULL;
        Element<T> *res = IteratedLinkedList<T>::tail;

        if (IteratedLinkedList<T>::head == IteratedLinkedList<T>::tail)
            IteratedLinkedList<T>::head = IteratedLinkedList<T>::tail = NULL;
        else {
            Element<T> *current;
            for (current = IteratedLinkedList<T>::head; current->getNext() != IteratedLinkedList<T>::tail; current = current->getNext());

            IteratedLinkedList<T>::tail = current;
            IteratedLinkedList<T>::tail->setNext(NULL);
        }

        IteratedLinkedList<T>::tail->setNext(new Element<T>(res->getValue()));

        IteratedLinkedList<T>::num--;
        return res;
    }

    iterator begin() {
        auto it = LinkedListParent<T>::head;
        return it;
    }

    iterator end() {
        iterator it = LinkedListParent<T>::tail->getNext();
        return it;
    }

    class iterator {
    private:
        Element<T> *ptr;
    public:
        iterator() { ptr = NULL; }

        iterator(Element<T> *p) { ptr = p; }

        iterator(const iterator &it) { ptr = it.ptr; }

        const Element<T> operator++(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            ptr = ptr->getNext();
            return *ptr;
        }

        const Element<T> operator--(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            ptr = ptr->getPrevious();
            return *ptr;
        }

        Element<T> &operator++() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            ptr = ptr->getNext();
            return *ptr;
        }
        Element<T> &operator--() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            ptr = ptr->getPrevious();
            return *ptr;
        }

        Element<T> &operator* () {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");
            return *ptr;
        }

        bool operator!= (const iterator &it) { return ptr != it.ptr; }
        bool operator== (const iterator &it) { return ptr == it.ptr; }
    };

    template<class T1>
    friend ostream &operator<<(ostream &ustream, Stack<T1> &s);
};

// Вывод списка через итераторы
template<class T1>
ostream &operator<<(ostream &ustream, Stack<T1> &s) {
    auto it = s.begin();

    ustream << "\n";
    while (it != s.end()) {
        ustream << *it << " ";
        it++;
    }

    return ustream;
}

template<class T>
class D_Stack : public Stack<T> {
protected:
    void insert(int pos, T value) {
        Element<T> *current = D_Stack<T>::head;

        for (int i = 0; i < pos; i++) {
            current = current->getNext();
            if (current == D_Stack<T>::tail) {
                break;
            }
        }

        Element<T> *new_el = new Element<T>(value);
        new_el->setNext(current->getNext());
        current->setNext(new_el);
    }

public:
    D_Stack() : Stack<T>() {};

    ~D_Stack() {

    };

    Element<T> *push(T value) override {
        if (Stack<T>::head == NULL) {
            return Stack<T>::push(value);
        }
        if (!(Stack<T>::head->getValue() < value)) {
            auto elem = new Element<T>(value, Stack<T>::head);
            Stack<T>::head->setPrevious(elem);
            Stack<T>::head = elem;
            Stack<T>::num++;
            return elem;
        }
        if (Stack<T>::head == Stack<T>::tail) {
            auto elem = new Element<T>(value, NULL, Stack<T>::tail);
            Stack<T>::tail->setNext(elem);
            Stack<T>::tail = elem;
            Stack<T>::num++;
            return elem;
        }
        auto current = Stack<T>::head;
        while (current != Stack<T>::tail) {
            if (!(current->getNext()->getValue() < value)) {
                auto elem = new Element<T>(value, current->getNext(), current);
                current->setNext(elem);
                elem->getNext()->setPrevious(elem);
                Stack<T>::num++;
                return elem;
            }
            current = current->getNext();
        }
        auto elem = new Element<T>(value, NULL, Stack<T>::tail);
        Stack<T>::num++;
        Stack<T>::tail->setNext(elem);
        Stack<T>::tail = elem;

        Stack<T>::tail->setNext(new Element<T>(value));
        return elem;
    }

};

template<class T, class Predicate>
void filter(LinkedListParent<T>& list, LinkedListParent<T>& dest_list, const Predicate& pred) {
    auto it = list.getBegin();
    for (; it != list.getEnd(); it = it->getNext()) {
        if (pred(it->getValue()))
            dest_list.push(it->getValue());
    }
}

bool Condition(int c) {
    if (c % 2 == 0)
        return true;
    else
        return false;
}

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

int main() {
    // Создаем стек s
    Stack<int> s;

    s.push(2);
    s.push(3);
    s.push(8);
    s.push(1);

    cout << "\n\nStack:" << s << endl;

    cout << "---------------------\n" << endl;

    // Удаление элемента из списка
    Element<int> *el = s.pop();
    cout << "s.pop(): " << *el << "\nStack after pop: " << s;

    // Создаем отсортированный стек
    D_Stack<int> D;
    D.push(2);
    D.push(1);
    D.push(5);
    D.push(4);
    D.push(6);
    D.push(7);

    cout << D << endl;

    // Функция filter
    bool (*ptr_f)(int);
    ptr_f = Condition;

    D_Stack<int> D_filter;
    filter(D, D_filter, ptr_f);

    cout << "\n\n---------------------" << endl;

    cout << D_filter << endl;

    cout << "\n---------------------" << endl;

    // 1.5

    // Создаем отсортированный список с элементами класса спортсмен
    D_Stack<Sportsman> sp;
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

    sp.push(sp1);
    sp.push(sp2);
    sp.push(sp3);
    sp.push(sp4);
    sp.push(sp5);
    sp.push(sp6);
    sp.push(sp7);
    sp.push(sp8);
    sp.push(sp9);
    sp.push(sp10);

    cout << sp;
}
