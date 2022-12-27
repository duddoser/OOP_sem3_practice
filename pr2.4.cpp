#include <iostream>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// тут exception для итератора который к элементу не привязан
class Iterator_Exception : public exception {
public:
    Iterator_Exception(string *msg) : exception() { }
};

// класс элемента нового с ключом и значением
template<class K, class T>
class Element {
protected:
    // значение и ключ
    T data;
    K key;

    // указатели 
    Element *left;
    Element *right;
    Element *parent;

    // переменная для поддержания баланса дерева
    int height;
public:
    // сеттеры и геттеры
    virtual void setData(T d) { data = d; }
    virtual void setKey(K k) { key = k; }

    virtual T getData() { return data; }
    virtual K getKey() { return key; };

    int getHeight() { return height; }

    virtual Element *getLeft() { return left; }
    virtual Element *getRight() { return right; }
    virtual Element *getParent() { return parent; }

    virtual void setLeft(Element *N) { left = N; }
    virtual void setRight(Element *N) { right = N; }
    virtual void setParent(Element *N) { parent = N; }

    // Конструктор. Устанавливаем стартовые значения для указателей
    Element<K, T>(K k, T n) {
        data = n;
        key = k;
        left = right = parent = NULL;
        height = 1;
    }

    Element<K, T>(K k) {
        key = k;
        left = right = parent = NULL;
        height = 1;
    }

    Element<K, T>() {
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
    }

    // вывод элемента
    virtual void print() {
        cout << "\n" << data << " " << key;
    }

    virtual void setHeight(int h) {
        height = h;
    }

    template<class K1, class T1>
    friend ostream &operator<<(ostream &stream, Element<K1, T1> &N);
};

template<class K1, class T1>
ostream &operator<<(ostream &stream, Element<K1, T1> &N) {
    stream << "\n{Key: " << N.key << ", data: " << N.data << "}, height: " << N.height;
    return stream;
}

// само бинарное дерево поиска
template<class K, class T>
class Map {
protected:
    // корень, начало и конец
    Element<K, T> *root;
    Element<K, T> *begin_, *end_;

    // разность высот поддеревьев левого и правого
    int bfactor(Element<K, T> *p) {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        return (hr - hl);
    }

    // тут мы фиксируем высоту дерева минимальную
    void fixHeight(Element<K, T> *p) {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    // правый поворот для балансировки
    Element<K, T> *RotateRight(Element<K, T> *p) // правый поворот вокруг p
    {
        Element<K, T>* q = p->getLeft();
        p->setLeft(q->getRight());
        q->setRight(p);

        if (p != root) {
            if (p->getParent()->getKey() > p->getKey()) // p->getParent
                p->getParent()->setLeft(q);
            else p->getParent()->setRight(q);
        }
        else root = q;

        q->setParent(p->getParent());
        p->setParent(q);
        if (p->getLeft() != NULL) p->getLeft()->setParent(p);

        fixHeight(p);
        fixHeight(q);
        return q;
    }

    // левый поворот
    Element<K, T> *RotateLeft(Element<K, T> *q) // левый поворот вокруг p
    {
        Element<K, T>* p = q->getRight();
        q->setRight(p->getLeft());
        p->setLeft(q);

        if (q != root) {
            if (q->getParent()->getKey() > q->getKey()) // p->getParent
                q->getParent()->setLeft(p);
            else q->getParent()->setRight(p);
        }
        else root = p;

        p->setParent(q->getParent());
        q->setParent(p);
        if (q->getRight() != NULL) q->getRight()->setParent(q);

        fixHeight(q);
        fixHeight(p);
        return p;
    }

    // сама логика балансировки через повороты
    Element<K, T> *Balance(Element<K, T> *p) // балансировка узла p
    {
        fixHeight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->getRight()) < 0) RotateRight(p->getRight());
            return RotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->getLeft()) > 0) RotateLeft(p->getLeft());
            return RotateRight(p);
        }
        return p;  
    }

    // рекурсивный push потому что push жлемента должен быть быстрыйвроед как O(log n)
    Element<K, T> *push_R(Element<K, T> *n, Element<K, T> *Current) {
        if (n == NULL) return NULL;
        if (root == NULL) {
            root = n;
            return n;
        }

        if (Current->getKey() > n->getKey()) {
            //идем влево
            if (Current->getLeft() != NULL)
                Current->setLeft(push_R(n, Current->getLeft()));
            else
                Current->setLeft(n);
            Current->getLeft()->setParent(Current);
        }
        if (Current->getKey() < n->getKey()) {
            //идем вправо
            if (Current->getRight() != NULL)
                Current->setRight(push_R(n, Current->getRight()));
            else
                Current->setRight(n);
            Current->getRight()->setParent(Current);
        }
        if (Current->getKey() == n->getKey())
            ;

        if (Current != NULL)
            return Balance(Current);

        return n;
    }

    // Поиск по ключу
    virtual Element<K, T> *Find_R_Key(K key, Element<K, T> *Current) {
        // база рекурсии
        if (Current == NULL) return NULL;

        if (Current->getKey() == key) return Current;

        // рекурсивный вызов
        if (Current->getKey() > key) return Find_R_Key(key, Current->getLeft());

        if (Current->getKey() < key) return Find_R_Key(key, Current->getRight());
    }

public:
    // обьявляем итератор пока что абстрактно
    class tree_iterator;

    virtual Element<K, T> *getRoot() { return root; }

    // конструкторы
    Map() {
        root = NULL;
    }

    // этот конструктор нужен для нормальной работы итератора, 
    // надо ввести максимально маленький и максимально большой ключи - это будут end_ и begin_
    Map(K k1, K k2) {
        root = NULL;
        begin_ = new Element<K, T>(k1);
        end_ = new Element<K, T>(k2);
        push_R(begin_, root);
        push_R(end_, root);
    }

    Element<K, T> *push(Element<K, T> *N) {
        return push_R(N, root);
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    Element<K, T> *push(K k, T n) {
        auto *N = new Element<K, T>;
        N->setData(n);
        N->setKey(k);
        return push(N);
    }

    // удаление элемента
    Element<K, T> *Remove(K key, Element<K, T> *Current) {
        if (Current == NULL)
            return Current;

        if (key < Current->getKey())
            Current->setLeft(Remove(key, Current->getLeft()));

        else if (key > Current->getKey())
            Current->setRight(Remove(key, Current->getRight()));

        else if (Current->getLeft() != NULL && Current->getRight() != NULL) {
            Current->setKey(Min(Current->getRight())->getKey());
            Current->setRight(Remove(Current->getKey(), Current->getRight()));
        }

        else {
            if (Current->getLeft() != NULL)
                Current = Current->getLeft();
            else if (Current->getRight() != NULL)
                Current = Current->getRight();
            else
                Current = NULL;
        }

        return Current;
    }

    // поиск по ключу такой же как в привате уже забыл зачем мне их 2...
    virtual Element<K, T> *FindKey(K key, Element<K, T> *Current) {
        //база рекурсии
        if (Current == NULL) return NULL;
        if (Current->getKey() == key) return Current;
        //рекурсивный вызов
        if (Current->getKey() > key)
            return FindKey(key,Current->getLeft());
        if (Current->getKey() < key)
            return FindKey(key,Current->getRight());
    }

    virtual Element<K, T> *Min(Element<K, T> *Current = NULL) {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getLeft() != NULL)
            Current = Current->getLeft();
        return Current;
    }

    virtual Element<K, T> *Max(Element<K, T> *Current = NULL) {
        //максимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getRight() != NULL)
            Current = Current->getRight();
        return Current;
    }

    // а теперь самое веселое - подкласс итератора
    tree_iterator begin() {
        // получаем такой begin потому что при перечислении элементов должен быть обработан последний
        // лучше никогда не делать вывод элементов с конца, потому что не выводится самый левый)
        // но петрусевич не заметил хихиихих
        tree_iterator it = begin_->getParent();
        return it;
    }

    tree_iterator end() {
        tree_iterator it = end_;
        return it;
    }

    class tree_iterator {
    protected:
        Element<K, T> *ptr; // указатель на текущий эелмент
    public:
        tree_iterator() { ptr = NULL; }

        tree_iterator(Element<K, T> *p) { ptr = p; }

        tree_iterator(const tree_iterator &it) { ptr = it.ptr; }
        // нужны min и max такие же как в дереве для всяких перегруженных операторов
        Element<K, T> *Min(Element<K, T> *Current = NULL) {
            if (ptr == NULL) return NULL;
            if (Current == NULL)
                Current = ptr;
            while (Current->getLeft() != NULL)
                Current = Current->getLeft();
            return Current;
        }

        Element<K, T> *Max(Element<K, T> *Current = NULL) {
            if (ptr == NULL) return NULL;
            if (Current == NULL)
                Current = ptr;
            while (Current->getRight() != NULL)
                Current = Current->getRight();
            return Current;
        }

        const Element<K, T> operator++(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            if (ptr->getRight() != NULL)
                ptr = Min(ptr->getRight());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Element<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() < ptr->getKey())
                    current = current->getParent();
                if (current->getKey() > ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Element<K, T> operator++() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            if (ptr->getRight() != NULL)
                ptr = Min(ptr->getRight());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Element<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() < ptr->getKey())
                    current = current->getParent();
                if (current->getKey() > ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        const Element<K, T> &operator--(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            if (ptr->getLeft() != NULL)
                ptr = Max(ptr->getLeft());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Element<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() > ptr->getKey())
                    current = current->getParent();
                if (current->getKey() < ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Element<K, T> &operator--() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");

            if (ptr->getLeft() != NULL)
                ptr = Max(ptr->getLeft());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Element<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() > ptr->getKey())
                    current = current->getParent();
                if (current->getKey() < ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Element<K, T> &operator*() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the element");
            return *ptr;
        }

        bool operator!=(const tree_iterator &it) { return ptr != it.ptr; }

        bool operator==(const tree_iterator &it) { return ptr == it.ptr; }
    };
};
// функция вывода, никто не знает но на самом деле она с костылём
template<class K, class T>
void print(Map<K, T> Tree) {
    auto it = Tree.begin();
    while (it != Tree.end()) {
        cout << *it << " ";
        it++;
    }
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
    // Спортсмены
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

    // Имена спортсменов
    string
        name1 = "Gregory Demchenko",
        name2 = "Alexey Avgust",
        name3 = "Xiao Lin",
        name4 = "John Lenon",
        name5 = "Ayanami Rei",
        name6 = "Polnaref Jian Piere",
        name7 = "Peter Lindemann",
        name8 = "Glen Quagmire",
        name9 = "Mathew Bellamy",
        name10 = "Anatoly Annin";

    // Создаем наше дерево передавая элемент begin_ и end_
    Map<string , Sportsman> T("AAAAAAAAAAAAAAAA", "ZZZZZZZZZZZZZZZZ");

    T.push(name1, sp1);
    T.push(name2, sp2);
    T.push(name3, sp3);
    T.push(name4, sp4);
    T.push(name5, sp5);
    T.push(name6, sp6);
    T.push(name7, sp7);
    T.push(name8, sp8);
    T.push(name9, sp9);
    T.push(name10, sp10);

    // Вывод дерева
    print(T);

    // Удаляем элемент по ключу name7 = "Peter Lindemann"
    T.Remove(name7, T.getRoot());
    cout << "Дерево после удаления name7 = \"Peter Lindemann\"\n";
    print(T);

    // Находим элемент c ключом name3 = "Xiao Lin"
    Element<string , Sportsman> *el = T.FindKey(name3, T.getRoot());
    cout << "\nЭлемент name3 = \"Xiao Lin\"\n\n" << *el << endl;
    return 0;
}
