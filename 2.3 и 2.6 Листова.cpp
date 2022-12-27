// Листова Анастасия
// КМБО-01-21, Вариант 16.

#include <iostream>
#include <queue>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Exception : public exception
{
protected:
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}
	virtual void print()
	{
		cout << "\nException: " << str << "; " << "\n\n";
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int index;
public:
	IndexOutOfBoundsException(char* s, int Index) : Exception(s)
	{
		index = Index;
	}
	IndexOutOfBoundsException(const char* s, int Index) : Exception(s)
	{
		index = Index;
	}
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
		index = e.index;
	}
	virtual void print()
	{
		cout << "\nIndexOutOfBoundsException: " << str << "; " << "\n\n";
	}
};


class Patient {
private:
	char* name;
	char* surname;
	int day_of_birth;
	int month_of_birth;
	int year_of_birth;
	int telephone;
	char* address;
	int number;
	int blood_type;

public:
	Patient(const char* Name, const char* Surname, int Day_of_birth, int Month_of_birth, int Year_of_birth, int Telephone, const char* Address, int Number, int Blood_type)
	{
		name = new char[strlen(Name) + 1];
		for (int i = 0; i < strlen(Name); i++)
			name[i] = Name[i];
		name[strlen(Name)] = '\0';
		surname = new char[strlen(Surname) + 1];
		for (int i = 0; i < strlen(Surname); i++)
			surname[i] = Surname[i];
		surname[strlen(Surname)] = '\0';
		day_of_birth = Day_of_birth;
		month_of_birth = Month_of_birth;
		year_of_birth = Year_of_birth;
		telephone = Telephone;
		address = new char[strlen(Address) + 1];
		for (int i = 0; i < strlen(Address); i++)
			address[i] = Address[i];
		address[strlen(Address)] = '\0';
		number = Number;
		blood_type = Blood_type;
	}

	Patient(char* Name, char* Surname, int Day_of_birth, int Month_of_birth, int Year_of_birth, int Telephone, char* Address, int Number, int Blood_type)
	{
		name = new char[strlen(Name) + 1];
		for (int i = 0; i < strlen(Name); i++)
			name[i] = Name[i];
		name[strlen(Name)] = '\0';
		surname = new char[strlen(Surname) + 1];
		for (int i = 0; i < strlen(Surname); i++)
			surname[i] = Surname[i];
		surname[strlen(Surname)] = '\0';
		day_of_birth = Day_of_birth;
		month_of_birth = Month_of_birth;
		year_of_birth = Year_of_birth;
		telephone = Telephone;
		address = new char[strlen(Address) + 1];
		for (int i = 0; i < strlen(Address); i++)
			address[i] = Address[i];
		address[strlen(Address)] = '\0';
		number = Number;
		blood_type = Blood_type;
	}

	Patient(const Patient& P)
	{
		name = new char[strlen(P.name) + 1];
		for (int i = 0; i < strlen(P.name); i++)
			name[i] = P.name[i];
		name[strlen(P.name)] = '\0';
		surname = new char[strlen(P.surname) + 1];
		for (int i = 0; i < strlen(P.surname); i++)
			surname[i] = P.surname[i];
		surname[strlen(P.surname)] = '\0';
		day_of_birth = P.day_of_birth;
		month_of_birth = P.month_of_birth;
		year_of_birth = P.year_of_birth;
		telephone = P.telephone;
		address = new char[strlen(P.address) + 1];
		for (int i = 0; i < strlen(P.address); i++)
			address[i] = P.address[i];
		address[strlen(P.address)] = '\0';
		number = P.number;
		blood_type = P.blood_type;
	}

	~Patient()
	{
		if (name != NULL)
			delete[] name;
		name = NULL;
		if (surname != NULL)
			delete[] surname;
		surname = NULL;
		if (address != NULL)
			delete[] address;
		address = NULL;
	}

	Patient& operator=(Patient& P)
	{
		name = new char[strlen(P.name) + 1];
		for (int i = 0; i < strlen(P.name); i++)
			name[i] = P.name[i];
		name[strlen(P.name)] = '\0';
		surname = new char[strlen(P.surname) + 1];
		for (int i = 0; i < strlen(P.surname); i++)
			surname[i] = P.surname[i];
		surname[strlen(P.surname)] = '\0';
		day_of_birth = P.day_of_birth;
		month_of_birth = P.month_of_birth;
		year_of_birth = P.year_of_birth;
		telephone = P.telephone;
		address = new char[strlen(P.address) + 1];
		for (int i = 0; i < strlen(P.address); i++)
			address[i] = P.address[i];
		address[strlen(P.address)] = '\0';
		number = P.number;
		blood_type = P.blood_type;
		return *this;
	}

	Patient& operator=(const Patient& P)
	{
		name = new char[strlen(P.name) + 1];
		for (int i = 0; i < strlen(P.name); i++)
			name[i] = P.name[i];
		name[strlen(P.name)] = '\0';
		surname = new char[strlen(P.surname) + 1];
		for (int i = 0; i < strlen(P.surname); i++)
			surname[i] = P.surname[i];
		surname[strlen(P.surname)] = '\0';
		day_of_birth = P.day_of_birth;
		month_of_birth = P.month_of_birth;
		year_of_birth = P.year_of_birth;
		telephone = P.telephone;
		address = new char[strlen(P.address) + 1];
		for (int i = 0; i < strlen(P.address); i++)
			address[i] = P.address[i];
		address[strlen(P.address)] = '\0';
		number = P.number;
		blood_type = P.blood_type;
		return *this;
	}

	bool operator<(const Patient& P)
	{
		if (number > P.number) return false;
		if (number < P.number) return true;
		if (blood_type < P.blood_type) return false;
		if (blood_type > P.blood_type) return true;
		if (surname > P.surname) return false;
		if (surname < P.surname) return true;
		if (name > P.name) return false;
		if (name < P.name) return true;
		return false;
	}

	bool operator<(const Patient& P) const
	{
		if (number > P.number) return false;
		if (number < P.number) return true;
		if (blood_type < P.blood_type) return false;
		if (blood_type > P.blood_type) return true;
		if (surname > P.surname) return false;
		if (surname < P.surname) return true;
		if (name > P.name) return false;
		if (name < P.name) return true;
		return false;
	}

	friend ostream& operator<<(ostream& s, Patient& P);
	friend ostream& operator<<(ostream& s, const Patient& P);
};

ostream& operator<<(ostream& s, Patient& P)
{
	s << '(' << P.name << ", " << P.surname << ", " << P.day_of_birth << ", " << P.month_of_birth << ", " << P.year_of_birth << '.' << P.telephone <<
		'.' << P.address << ", \"" << P.number << ", \"" << P.blood_type << "\")" << '\n';
	return s;
}

ostream& operator<<(ostream& s, const Patient& P)
{
	s << '(' << P.name << ", " << P.surname << ", " << P.day_of_birth << ", " << P.month_of_birth << ", " << P.year_of_birth << '.' << P.telephone <<
		'.' << P.address << ", \"" << P.number << ", \"" << P.blood_type << "\")" << '\n';
	return s;
}

template<typename T>
void print_queue(T& q)
{
	cout << "Priority Queue: \n";
	while (!q.empty()) {
		cout << q.top();
		q.pop();
	}
	cout << '\n';
}

class K
{
private:
	int number;
public:
	K()
	{
		number = 0;
	}

	K(int Number)
	{
		number = Number;
	}

	K(const K& obj)
	{
		number = obj.number;
	}

	~K() { }

	int getNumber() { return number; }
	void setNumber(int Number) { number = Number; }

	K& operator=(const K& other)
	{
		number = other.number;
		return *this;
	}

	bool operator==(const K& other) const
	{
		if (number == other.number) return true;
		return false;
	}

	bool operator!=(K& other) const
	{
		if (number != other.number) return true;
		return false;
	}

	bool operator<(const K& other) const
	{
		if (number < other.number) return true;
		else if (number > other.number) return false;
		return false;
	}

	friend ostream& operator<<(ostream& ustream, K& key);
	friend ostream& operator<<(ostream& ustream, const K& key);
};

ostream& operator<<(ostream& ustream, const K& key)
{
	ustream << '(' << key.number << ')';
	return ustream;
}

ostream& operator<<(ostream& ustream, K& key)
{
	ustream << '(' << key.number << ')';
	return ustream;
}

class V
{
private:
	int blood_type;
public:
	V()
	{
		blood_type = 0;
	}
	V(int Blood_type)
	{
		blood_type = Blood_type;
	}
	V(const V& obj)
	{
		blood_type = obj.blood_type;
	}

	V& operator=(const V& other)
	{
		blood_type = other.blood_type;
		return *this;
	}

	~V() { }

	int getBloodType() { return blood_type; }
	void setBloodType(int Blood_type) { blood_type = Blood_type; }

	bool operator==(const V& other) const
	{
		if (blood_type == other.blood_type) return true;
		return false;
	}

	bool operator!=(V& other) const
	{
		if (blood_type != other.blood_type) return true;
		return false;
	}

	bool operator<(const V& other) const
	{
		if (blood_type < other.blood_type) return true;
		else if (blood_type > other.blood_type) return false;
		return false;
	}

	friend ostream& operator<<(ostream& ustream, V& value);
	friend ostream& operator<<(ostream& ustream, const V& value);
};

ostream& operator<<(ostream& ustream, const V& value)
{
	ustream << '(' << value.blood_type << ')';
	return ustream;
}

ostream& operator<<(ostream& ustream, V& value)
{
	ustream << '(' << value.blood_type << ')';
	return ustream;
}

class Element
{
private:
	K* key;
	V* value;
public:
	Element()
	{
		key = new K;
		value = new V;
	}
	Element(K& Key, V& Value)
	{
		key = new K(Key);
		value = new V(Value);
	}
	Element(const Element& other)
	{
		key = new K(*other.key);
		value = new V(*other.value);
	}
	~Element()
	{
		if (value != nullptr)
			delete value;
		value = nullptr;
		if (key != nullptr)
			delete key;
		key = nullptr;
	}

	K* getKeyPtr() { return key; }
	V* getValuePtr() { return value; }
	K getKey() { return *key; }
	V getValue() { return *value; }

	Element& operator=(Element& el)
	{
		key = new K(*el.key);
		value = new V(*el.value);
		return *this;
	}

	Element& operator=(const Element& el)
	{
		key = new K(*el.key);
		value = new V(*el.value);
		return *this;
	}

	bool operator<(const Element& other)
	{
		if (key->getNumber() < other.key->getNumber()) return true;
		if (key->getNumber() > other.key->getNumber()) return false;
		return false;
	}

	bool operator>(const Element& other)
	{
		if (key->getNumber() < other.key->getNumber()) return false;
		if (key->getNumber() > other.key->getNumber()) return true;
		return false;
	}

	bool operator==(const Element& other)
	{
		if (key->getNumber() == other.key->getNumber()) return true;
		return false;
	}

	bool operator<(Element& other)
	{
		if (key->getNumber() < other.key->getNumber()) return true;
		if (key->getNumber() > other.key->getNumber()) return false;
		return false;
	}

	bool operator>(Element& other)
	{
		if (key->getNumber() < other.key->getNumber()) return false;
		if (key->getNumber() > other.key->getNumber()) return true;
		return false;
	}

	bool operator==(Element& other)
	{
		if (key->getNumber() == other.key->getNumber()) return true;
		return false;
	}

	friend ostream& operator<<(ostream& s, const Element& el);
	friend ostream& operator<<(ostream& s, Element& el);
};

ostream& operator<<(ostream& s, const Element& el)
{
	s << "Key: " << *el.key << "\", Value: " << *el.value;
	return s;
}

ostream& operator<<(ostream& s, Element& el)
{
	s << "Key: " << *el.key << "\", Value: " << *el.value;
	return s;
}

template <class T>
class Node
{
private:
	T value;
public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//сравнение узлов
	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};

template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap
{
protected:
	//массив
	Node<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;

	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (len == 0) return;
		if (index == -1) index = len - 1;
		int parent_index = GetParentIndex(index);
		if (parent_index < 0) return;
		//нужно сравнить элементы и при необходимости произвести просеивание вверх
		if (arr[parent_index] < arr[index])
		{
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
	}
	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int index = 0)
	{
		//то же, что и SiftDown
		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (len == 0) return;
		if (index < 0 || index >= len) return;

		if (!hasLeftChild(index)) return; //детей нет
		int child_index = -1;
		if (!hasRightChild(index)) //есть один ребенок
			child_index = GetLeftChildIndex(index);
		else
			child_index = arr[GetLeftChildIndex(index)] < arr[GetRightChildIndex(index)] ? GetRightChildIndex(index) : GetLeftChildIndex(index);

		//нужно сравнить элементы и при необходимости произвести просеивание вверх
		if (arr[child_index] > arr[index])
		{
			Swap(child_index, index);
			Heapify(child_index);
		}
	}
public:
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);

		return arr[index];
	}

	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}

	~Heap()
	{
		while (getCount() != 0)
		{
			Node<T>* N = ExtractMax();
			delete N;
		}
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 < 0 || index1 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index1);
		if (index2 < 0 || index2 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index2);

		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source)
	{
		dest->setValue(source->getValue());
	}

	bool hasLeftChild(int index) {
		return len > index * 2 + 1;
	}

	bool hasRightChild(int index) {
		return len > index * 2 + 2;
	}

	bool hasParent(int index) {
		if (index == 0) return false;
		return len > index;
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}

	Node<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака

		return &arr[index * 2 + 2];
	}

	Node<T>* GetParent(int index)
	{
		if (index < 0 || index >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака

		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index < 0 || index >= len) throw IndexOutOfBoundsException("Index is out of bounds.\n", index);
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	//удобный интерфейс для пользователя 
	void push(T v)
	{
		Node<T>* N = new Node<T>;
		N->setValue(v);
		push(N);
	}

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	void push(Node<T>* N)
	{
		//добавить элемент и включить просеивание
		if (len < size)
		{
			arr[len] = *N;
			len++;
			SiftUp();
		}
		else
		{
			size = len + 1;
			arr = new Node<T>[len + 1];
			arr[len] = *N;
			len++;
			SiftUp();
		}
	}
	//удаление элемента по индексу
	Node<T>* pop(int index)
	{
		if (len == 0) return nullptr;
		if (index < 0 || index >= len) return nullptr;
		Node<T>* res = new Node<T>;
		Copy(res, &arr[index]);

		Swap(index, len - 1);
		len--;
		Heapify(index);

		return res;
	}
	//удаление максимума (корня)
	Node<T>* ExtractMax()
	{
		//исключить максимум и запустить просеивание кучи
		if (len == 0) return nullptr;
		Node<T>* res = new Node<T>;
		Copy(res, &arr[0]);

		Swap(0, len - 1);
		len--;
		Heapify();

		return res;
	}

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(Node<T>*))
	{
		for (int i = 0; i < len; i++) f(&arr[i]);
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
	}
	//вывод кучи
	void print_heap()
	{
		cout << "Heap: \n";
		while (getCount() != 0)
		{
			Node<T>* N = ExtractMax();
			N->print();
			delete N;
			cout << "\n";
		}
	}
};

int main()
{
	// Задание 2.3 
	setlocale(LC_ALL, "Rus");

	priority_queue<Patient, vector<Patient>, less<Patient>> pq;

	Patient patient_1("Nastia", "Listova", 18, 2, 2003, 12345, "Moscow", 123, 1);
	Patient patient_2("Polina", "Listova", 14, 6, 2005, 73951, "Kletino", 123, 3);
	Patient patient_3("Egor", "Seregin", 23, 5, 2003, 96036, "Bali", 567, 2);
	Patient patient_4("Svetlana", "Listova", 27, 3, 1977, 52016, "Tambov", 123, 3);
	Patient patient_5("Nastia", "Matveeva", 14, 7, 2003, 13627, "France", 340, 4);
	Patient patient_6("Kirill", "Kovalev", 1, 12, 2015, 19876, "Kasimov", 340, 1);
	Patient patient_7("Nikita", "Artamonov", 19, 2, 1999, 50092, "Turkey", 192, 2);

	pq.push(patient_1); pq.push(patient_2); pq.push(patient_3); pq.push(patient_4); pq.push(patient_5); pq.push(patient_6); pq.push(patient_7);

	print_queue(pq);

	//Задание 2.6 
	K key_1(123); V value_1(1);
	K key_2(123); V value_2(3);
	K key_3(567); V value_3(2);
	K key_4(123); V value_4(3);
	K key_5(340); V value_5(4);
	K key_6(340); V value_6(1);
	K key_7(192); V value_7(2);

	Element el1(key_1, value_1);
	Element el2(key_2, value_2);
	Element el3(key_3, value_3);
	Element el4(key_4, value_4);
	Element el5(key_5, value_5);
	Element el6(key_6, value_6);
	Element el7(key_7, value_7);

	Heap<Element> H;
	H.push(el1); H.push(el2); H.push(el3); H.push(el4); H.push(el5); H.push(el6); H.push(el7);

	cout << "куча после удаления элемента по индексу 4:\n";
	print(H.pop(4));
	cout << '\n';

	H.print_heap();

	return 0;
}