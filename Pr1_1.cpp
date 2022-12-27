// Григорий Деиченко КМБО 06-21 Практическая работа 1.1

#include <iostream>
#include <list>
#include <cmath>
#include <experimental/random>

using namespace std;

class Complex {
private:
    double re, im;

public:
    Complex() { re = im = 0; }

    Complex(double r) {
        re = r;
        im = 0;
    }

    Complex(double r, double i) {
        re = r;
        im = i;
    }

    Complex(const Complex& c) {
        re = c.re;
        im = c.im;
    }

    ~Complex() { }

    Complex operator+ (Complex& c) {
        Complex n;

        n.re = re + c.re;
        n.im = im + c.re;

        return n;
    }

    Complex operator- (Complex& c) {
        Complex n;

        n.re = re - c.re;
        n.im = im - c.im;

        return n;
    }

    Complex operator* (Complex& c) {
        Complex n;

        n.re = re * c.re;
        n.im = im * c.im;

        return n;
    }

    Complex operator/ (Complex& c) {
        Complex n;

        double r = c.re * c.re + c.im * c.im;
        n.re = (re * c.re + im * c.im) / r;
        n.re = (im * c.re - re * c.im) / r;

        return n;
    }

    // Модуль комплексного числа
    double Module() {
        return sqrt(re*re + im*im);
    }

    bool operator> (Complex& c) { return Module() > c.Module(); }
    bool operator< (Complex& c) { return Module() < c.Module(); }
    bool operator== (Complex& c) const {
        if (re == c.re && im == c.im)
            return true;
        return false;
    }
    bool operator!= (Complex& c) const {
        if (re != c.re && im != c.im)
            return true;
        return false;
    }

    Complex& operator= (const Complex& c) { re = c.re; im = c.im; }

    friend ostream& operator<<(ostream&, const Complex&);
    friend istream& operator>>(istream&, const Complex&);

    double getRe() const { return re; }
    double getIm() const { return im; }

    void setRe(double Re) { re = Re; }
    void setIm(double Im) { im = Im; }
};

ostream& operator<< (ostream& out, const Complex& c) {
    out << c.re;
    if (c.im > 0)
        out << "+";
    out << c.im << "i";
    return out;
}

istream& operator>> (istream& in, const Complex& c) {
    in >> c.re >> c.im;
    return in;
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
    auto it = lst.begin();

    while (it != lst.end()) {
        if (*it > el)
            break;
        it++;
    }

    lst.insert(it, el);
}

// Функция фильтрации
template<class T>
void filter(list<T> source, list<T>& result, bool (*ptr_f)(T)) {
    for (auto it = source.begin(); it != source.end(); *it++)
        if (ptr_f(*it))
            push(result,*it);
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
bool Condition(Complex c) {
    if (c.getRe() != 0)
        return c.getRe() < 0;
    else
        return false;
}

int main() {

    list<Complex> lst;

    for (int i = 0; i < 10; i++) {
        Complex c(experimental::randint(-10, 10), experimental::randint(-10, 10));
        push(lst, c);
    }

    auto it = lst.begin();

    Complex com(10, 2);

    push(lst, com);

    // Выводим список из рандомных значений с добавленным значением "com"
    cout << "Random Complex list:" << endl;
    print(lst);
    cout << "\n";

    // Работа функции удаления элемента из списка
    Complex popedEl = pop(lst);

    cout << "pop: " << endl;
    cout << popedEl << endl;

    print(lst);

    // Работа функции filter
    list<Complex> res;

    bool (*ptr_f)(Complex); ptr_f = Condition;
    filter(lst, res, ptr_f);

    cout << "filter function: " << endl;
    print(res);

    return 0;
}