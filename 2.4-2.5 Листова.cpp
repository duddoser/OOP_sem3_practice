/*
Листова Анастасия, КМБО-01-21
Вариант 16.
«Пациент».
  фамилия, имя, дата рождения, телефон, адрес, номер карты, группа крови

Ключ:
    Номер карты, группа крови
*/

#include <iostream>
#include <vector>

using namespace std;

//узел
template <class T>
class Node
{
protected:
    //закрытые переменные Node N; N.data = 10 вызовет ошибку
    T data;

    //не можем хранить Node, но имеем право хранить указатель
    Node* left;
    Node* right;
    Node* parent;

    //переменная, необходимая для поддержания баланса дерева
    int height;

public:
    //доступные извне переменные и функции
    virtual void set_data(T d) { data = d; }
    virtual T get_data() { return data; }
    int get_height() { return height; }

    virtual Node* get_left() { return left; }
    virtual Node* get_right() { return right; }
    virtual Node* get_parent() { return parent; }

    virtual void set_left(Node* N) { left = N; }
    virtual void set_right(Node* N) { right = N; }
    virtual void set_parent(Node* N) { parent = N; }

    //Конструктор
    Node<T>(T n)
    {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }

    Node<T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
    }

    ~Node<T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 0;
    }

    virtual void print()
    {
        cout << data << '\n';
    }

    virtual void set_height(int h)
    {
        height = h;
    }

    template <class T1>
    friend ostream& operator<<(ostream& stream, Node<T1>& N);
};

template <class T>
ostream& operator<<(ostream& stream, Node<T>& N)
{
    stream << "Node data: " << N.data << ", height: " << N.height;
    return stream;
}

template <class T>
void print(Node<T>* N) { cout << N->get_data() << " H: " << N->get_height() << '\n'; }

template <class T>
class Tree
{
protected:
    //корень - его достаточно для хранения всего дерева
    Node<T>* root;

    virtual Node<T>* recursive_push(Node<T>* N, Node<T>* current)
    {
        //не передан добавляемый узел
        if (N == NULL)
            return NULL;

        //пустое дерево - добавляем в корень
        if (root == NULL)
            return root = N;

        if (current->get_data() > N->get_data())
        {
            //идем влево
            if (current->get_left() != NULL)
            {
                return recursive_push(N, current->get_left());
            }
            current->set_left(N);
            N->set_parent(current);
        }
        if (current->get_data() < N->get_data())
        {
            //идем вправо
            if (current->get_right() != NULL)
            {
                return recursive_push(N, current->get_right());
            }
            current->set_right(N);
            N->set_parent(current);
        }
        if (current->get_data() == N->get_data())
            //нашли совпадение
            return NULL;
        //вернуть добавленный узел
        return N;
    }

    //поиск узла в дереве
    virtual Node<T>* recursive_find(const T& data, Node<T>* current) const
    {
        if (current == NULL || current->get_data() == data)
            return current;
        if (current->get_data() > data)
        {
            return recursive_find(data, current->get_left());
        }
        else
        {
            return recursive_find(data, current->get_right());
        }
    }

    //функция добавления узла в дерево
    virtual Node<T>* push(Node<T>* N)
    {
        return recursive_push(N, root);
    }

public:
    //доступ к корневому элементу
    virtual Node<T>* get_root() { return root; }

    //конструктор дерева
    Tree<T>()
    {
        root = NULL;
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node<T>* push(T n)
    {
        Node<T>* N = new Node<T>(n);
        return push(N);
    }

    //удаление узла
    virtual void remove(Node<T>* ptr)
    {
        if (ptr == NULL)
            throw runtime_error("ptr is NULL");
        if (ptr->get_left() == NULL && ptr->get_right() == NULL)
        {
            if (ptr->get_parent())
            {
                if (ptr->get_parent()->get_left() == ptr)
                    ptr->get_parent()->set_left(NULL);
                else
                    ptr->get_parent()->set_right(NULL);
            }
        }
        else
        {
            Node<T>* replacement;
            if (ptr->get_left())
                replacement = max(ptr->get_left());
            else
                replacement = min(ptr->get_right());
            if (replacement->get_parent()->get_right() == replacement)
            {
                replacement->get_parent()->set_right(NULL);
            }
            else
            {
                replacement->get_parent()->set_left(NULL);
            }
            replacement->set_parent(ptr->get_parent());

            if (ptr->get_parent())
            {
                if (ptr->get_parent()->get_right() == ptr)
                    ptr->get_parent()->set_right(replacement);
                else
                    ptr->get_parent()->set_left(replacement);
            }

            if (ptr->get_left())
                ptr->get_left()->set_parent(replacement);
            if (ptr->get_right())
                ptr->get_right()->set_parent(replacement);

            replacement->set_left(ptr->get_left());
            replacement->set_right(ptr->get_right());
        }
        delete ptr;
    }

    //поиск минимума и максимума в дереве
    virtual Node<T>* min(Node<T>* current = NULL) const
    {
        if (current == NULL)
            current = root;
        if (current == NULL)
            return NULL;
        while (current->get_left() != NULL)
            current = current->get_left();
        return current;
    }

    virtual Node<T>* max(Node<T>* current = NULL)
    {
        if (current == NULL)
            current = root;
        if (current == NULL)
            return NULL;
        for (; current->get_right() != NULL; current = current->get_right())
            ;
        return current;
    }

    //поиск узла в дереве
    virtual Node<T>* find(T data) const
    {
        if (root == NULL)
            return NULL;
        return recursive_find(data, root);
    }

    //три обхода дерева
    virtual void pre_order(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->get_left() != NULL)
            pre_order(N->get_left(), f);
        if (N != NULL && N->get_right() != NULL)
            pre_order(N->get_right(), f);
    }

    // in_order-обход даст отсортированную последовательность
    virtual void in_order(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL && N->get_left() != NULL)
            in_order(N->get_left(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->get_right() != NULL)
            in_order(N->get_right(), f);
    }

    virtual void post_order(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL && N->get_left() != NULL)
            post_order(N->get_left(), f);
        if (N != NULL && N->get_right() != NULL)
            post_order(N->get_right(), f);
        if (N != NULL)
            f(N);
    }
};

//класс итератор по дереву
template <typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
    Node<ValueType>* ptr;

public:
    TreeIterator()
    {
        ptr = NULL;
    }

    TreeIterator(Node<ValueType>* p) { ptr = p; }

    TreeIterator(const TreeIterator& it)
    {
        ptr = it.ptr;
    }

    TreeIterator& operator=(const TreeIterator& it)
    {
        ptr = it.ptr;
        return *this;
    }

    TreeIterator& operator=(Node<ValueType>* p)
    {
        ptr = p;
    }

    bool operator!=(TreeIterator const& other) const
    {
        return ptr != other.ptr;
    }

    bool operator==(TreeIterator const& other) const
    {
        return ptr == other.ptr;
    }

    Node<ValueType>& operator*()
    {
        return *ptr;
    }

    TreeIterator& operator++()
    {
        if (ptr == NULL)
            throw length_error("Iterator is NULL");
        if (ptr->get_right())
        {
            ptr = ptr->get_right();
            while (ptr->get_left())
            {
                ptr = ptr->get_left();
            }
        }
        else
        {
            Node<ValueType>* prev;
            prev = ptr;
            ptr = ptr->get_parent();
            while (ptr != NULL && prev == ptr->get_right())
            {
                prev = ptr;
                ptr = ptr->get_parent();
            }
        }
        return *this;
    }

    TreeIterator& operator++(int v)
    {
        return operator++();
    }

    TreeIterator& operator--()
    {
        if (ptr == NULL)
            throw length_error("Iterator is NULL");
        if (ptr->get_left())
        {
            ptr = ptr->get_left();
            while (ptr->get_right())
            {
                ptr = ptr->get_right();
            }
        }
        else
        {
            Node<ValueType>* prev;
            prev = ptr;
            ptr = ptr->get_parent();
            while (ptr && prev == ptr->get_left())
            {
                prev = ptr;
                ptr = ptr->get_parent();
            }
        }
        return *this;
    }

    TreeIterator& operator--(int n)
    {
        return operator--();
    }

    Node<ValueType>* get_ptr()
    {
        return ptr;
    }
};

//класс итерируемое дерево поиска
template <class T>
class IteratedTree : public Tree<T>
{
public:
    typedef TreeIterator<T> iterator;
    IteratedTree<T>() : Tree<T>() {}

    iterator begin()
    {
        Node<T>* ptr = Tree<T>::root;
        while (ptr->get_left())
            ptr = ptr->get_left();
        return iterator(ptr);
    }

    iterator end()
    {
        return NULL;
    }
};

template <class T>
ostream& operator<<(ostream& out, IteratedTree<T>& t)
{
    for (auto i = t.begin(); i != t.end(); ++i)
    {
        out << *i << '\n';
    }
    return out;
}

// AVLTree 
template <class T>
class AVLTree : public IteratedTree<T>
{
protected:
    //определение разности высот двух поддеревьев
    int bfactor(Node<T>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->get_left() != NULL)
            hl = p->get_left()->get_height();
        if (p->get_right() != NULL)
            hr = p->get_right()->get_height();
        return (hr - hl);
    }

    //после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это значение могло поменяться
    virtual void fix_height(Node<T>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->get_left() != NULL)
            hl = p->get_left()->get_height();
        if (p->get_right() != NULL)
            hr = p->get_right()->get_height();
        p->set_height((hl > hr ? hl : hr) + 1);
    }

    //краеугольные камни АВЛ-деревьев - процедуры поворотов
    Node<T>* rotate_right(Node<T>* p) // правый поворот вокруг p
    {
        Node<T>* q = p->get_left();

        p->set_left(q->get_right());
        q->set_right(p);
        if (p != Tree<T>::root)
        {
            if (p->get_parent()->get_left() == p)
                p->get_parent()->set_left(q);
            else
                p->get_parent()->set_right(p);
        }
        else
            Tree<T>::root = q;

        q->set_parent(p->get_parent());
        p->set_parent(q);
        if (p->get_left() != NULL)
            p->get_left()->set_parent(p);

        fix_height(p);
        fix_height(q);
        return q;
    }

    Node<T>* rotate_left(Node<T>* q) // левый поворот вокруг q
    {
        Node<T>* p = q->get_right();

        q->set_right(p->get_left());
        p->set_left(q);
        if (q != Tree<T>::root)
        {
            if (q->get_parent()->get_right() == q)
                q->get_parent()->set_right(p);
            else
                q->get_parent()->set_left(q);
        }
        else
            Tree<T>::root = p;

        p->set_parent(q->get_parent());
        q->set_parent(p);
        if (q->get_right())
            q->get_right()->set_parent(q);

        fix_height(q);
        fix_height(p);
        return p;
    }

    //балансировка поддерева узла p 
    virtual Node<T>* balance(Node<T>* p) // балансировка узла p
    {
        fix_height(p);
        if (bfactor(p) >= 2)
        {
            rotate_left(p);
        }
        if (bfactor(p) <= -2)
        {
            rotate_right(p);
        }
        return p; // балансировка не нужна
    }

    virtual Node<T>* push(Node<T>* N)
    {
        Node<T>* result = recursive_push(N, Tree<T>::root);
        fix_height(result);
        return result;
    }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T>* recursive_push(Node<T>* N, Node<T>* current)
    {
        Node<T>* pushedNode = Tree<T>::recursive_push(N, current);
        //применяем к добавленному узлу балансировку
        if (current == NULL)
            return pushedNode;
        return balance(current);
    }

public:
    //конструктор AVLTree 
    AVLTree<T>() : IteratedTree<T>() {}

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерев
    virtual Node<T>* push(T n)
    {
        return push(new Node<T>(n));
    }

    //удаление узла
    virtual void remove(TreeIterator<T> it)
    {
        Node<T>* ptr = it.get_ptr();
        if (ptr == NULL)
            throw runtime_error("iterator is NULL");
        IteratedTree<T>::remove(ptr);
        balance(IteratedTree<T>::root);
    }

    virtual void remove(Node<T>* ptr)
    {
        IteratedTree<T>::remove(ptr);
        balance(IteratedTree<T>::root);
    }
};

template <class T>
class AVLTreeMultielem : public AVLTree<T>
{
protected:
    virtual Node<T>* balance(Node<T>* p) // балансировка узла p
    {
        AVLTree<T>::fix_height(p);

        if (AVLTree<T>::bfactor(p) >= 2 && p->get_left() != NULL && p->get_left()->get_data() != p->get_data())
        {
            AVLTree<T>::rotate_left(p);
        }
        if (AVLTree<T>::bfactor(p) <= -2)
        {
            AVLTree<T>::rotate_right(p);
        }
        return p; // балансировка не нужна
    }

    virtual void fix_height(Node<T>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->get_left() != NULL)
            hl = p->get_left()->get_height();
        if (p->get_right() != NULL)
            hr = p->get_right()->get_height();
        if (p->get_right() && p->get_right()->get_data() == p->get_data())
            --hr;
        p->set_height((hl > hr ? hl : hr) + 1);
    }

    virtual Node<T>* recursive_push_unbalanced(Node<T>* N, Node<T>* current)
    {
        //не передан добавляемый узел
        if (N == NULL)
            return NULL;

        //пустое дерево - добавляем в корень
        if (AVLTree<T>::root == NULL)
            return AVLTree<T>::root = N;

        if (current->get_data() > N->get_data())
        {
            //идем влево
            if (current->get_left() != NULL)
            {
                return recursive_push(N, current->get_left());
            }
            current->set_left(N);
            N->set_parent(current);
        }
        else
        {
            //идем вправо
            if (current->get_right() != NULL)
            {
                return recursive_push(N, current->get_right());
            }
            current->set_right(N);
            N->set_parent(current);
        }
        //вернуть добавленный узел
        return N;
    }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T>* recursive_push(Node<T>* N, Node<T>* current)
    {
        //вызываем функцию recursive_push из базового класса
        Node<T>* pushedNode = recursive_push_unbalanced(N, current);
        //применяем к добавленному узлу балансировку
        if (current == NULL)
            return pushedNode;
        return AVLTree<T>::balance(current);
    }

public:
    AVLTreeMultielem<T>() : AVLTree<T>() {}

    vector<Node<T>*> operator[](T i)
    {
        vector<Node<T>*> result;
        Node<T>* v = AVLTree<T>::root;
        while (v)
        {
            if (v->get_data() == i)
            {
                result.push_back(v);
                v = v->get_right();
                continue;
            }
            if (v->get_data() < i)
            {
                v = v->get_right();
                continue;
            }
            else
                v = v->get_left();
        }
        return result;
    }
};

const vector<string> adresses = { "Moscow", "Saint Petersburg", "Ryazan", "Lobnya", "Lyubertsy"};
const vector<string> names = { "Nastya", "Olya", "Yura", "Polina", "Alexey", "Alexander", "Oleg"};
const vector<string> secondnames = { "Smith ", "John­son ", "Williams", "Brown" , "Tay­lor", "Robin­son"};
const vector<string> dates = { "18.02.2003 ", "14.06.2005", "27.03.1977", "09.02.1981" , "16.01.2004", "19.02.1999" };

// Patient

class Patient
{
    // Пациент
private:
    string name; // имя пациента
    string secondname; // фамилия пациента
    string date_of_birth; // дата рождения пациента
    int telephone; // телефон пациента
    string address; // адрес пациента
    int number; // номер карты
    int blood_type; // группа крови

public:
    // конструкторы
    Patient() 
    { name = names[rand() % names.size()];
      secondname = secondnames[rand() % secondnames.size()];
      date_of_birth = dates[rand() % dates.size()];
      telephone = 6000 + rand() % 10000;
      address = adresses[rand() % adresses.size()];
      number = 1 + rand() % 100;
      blood_type = 1 + rand() % 4;
      cout << "\nPatient default constructor"; 
    }

    Patient(char* Name, char* Secondname, char* Date_of_birth, int Telephone, char* Address, int Number, int Blood_type) {
        name = Name; secondname = Secondname; date_of_birth = Date_of_birth; telephone = Telephone; address = Address; number = Number; blood_type = Blood_type;
    }

    string get_name() const { return name; }
    string get_secondname() const { return secondname; }
    string get_date_of_birth() const { return date_of_birth; }
    int get_telephone() const { return telephone; }
    string get_address() const { return address; }
    int get_number() const { return number; }
    int get_blood_type() const { return blood_type; }
};

// сравнение сначала по номеру карты, потом по группе крови
bool operator>(Patient f, Patient s)
{
    if (f.get_number() < s.get_number())
        return false;
    if (f.get_number() > s.get_number())
        return true;
    if (f.get_blood_type() > s.get_blood_type())
        return false;
    return true;
}

bool operator<(Patient f, Patient s)
{
    if (f.get_number() < s.get_number())
        return false;
    if (f.get_number() > s.get_number())
        return true;
    if (f.get_blood_type() > s.get_blood_type())
        return false;
    return true;
}

bool operator==(Patient f, Patient s)
{
    return f.get_blood_type() == s.get_blood_type() && f.get_number() == s.get_number();
}
bool operator!=(Patient f, Patient s)
{
    return !(f == s);
}

bool operator<=(Patient f, Patient s)
{
    return f < s || f == s;
}

bool operator>=(Patient f, Patient s)
{
    return f > s || f == s;
}

ostream& operator<<(ostream& out, Patient b)
{
    out << "Patient: ";
    out << "Name: " << b.get_name() << ", ";
    out << "Secondname: " << b.get_secondname() << ", ";
    out << "Date of birth: " << b.get_date_of_birth() << ", ";
    out << "Telephone: " << b.get_telephone() << ", ";
    out << "Adress: " << b.get_address() << ", ";
    out << "Number: " << b.get_number() << ", ";
    out << "Blood type: " << b.get_blood_type() << ", ";
    return out;
}

int main()
{
    AVLTree<int> tree;
    for (int i = 0; i < 12; ++i)
    {
        tree.push(i);
    }

    cout << tree << '\n';
    for (int i = 0; i < 5; ++i)
    {
        tree.remove(tree.find(i));
    }

    cout << "Tree with removed elements:\n";
    cout << tree << '\n';

    AVLTreeMultielem<int> mtree;
    for (int i = 0; i < 70; ++i)
    {
        mtree.push(i);
    }
    for (int i = 0; i < 2; ++i)
    {
        mtree.push(3);
    }
    cout << mtree << '\n';
    auto res = mtree[3];
    cout << '\n';
    for (auto i = res.begin(); i != res.end(); i++)
    {
        cout << **i << '\n';
    }


    cout << "\n\nTree with patients\n";
    AVLTreeMultielem<Patient> P_tree;
    for (int i = 0; i < 12; ++i)
    {
        P_tree.push(Patient());
    }
    cout << P_tree << '\n';
}
