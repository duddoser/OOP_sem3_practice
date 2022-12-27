// Группа КМБО-01-21
// Листова Анастасия
// Вариант 16

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;

public:
	Element(T value)
	{
		field = value;
		next = NULL;
		prev = NULL;
	}

	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template <class T1>
	friend ostream& operator<<(ostream& ustream, Element<T1>& obj);
};

template <class T>
ostream& operator<<(ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

// LinkedList Parent 
template <class T>
class Stack;

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;

public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = tail = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		cout << "\nLinkedList class destructor";
		if (head != NULL)
		{
			Element<T>* current = head;
			Element<T>* temp = head->getNext();
			for (; current != tail; current = temp, temp = temp->getNext())
				delete current;
		}
		head = NULL;
		tail = NULL;
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i < 0 || i > num)
			return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	virtual Stack<T> filter(bool (*condition)(T))
	{
		Stack<T> result;
		Element<T>* p = head;
		while (true)
		{
			if (condition(p->getValue()))
				result.push(p->getValue());

			if (p == tail)
				break;

			p = p->getNext();
		}
		return result;
	}

	template <class T1>
	friend ostream& operator<<(ostream& ustream, LinkedListParent<T1>& obj);
	template <class T1>
	friend istream& operator>>(istream& ustream, LinkedListParent<T1>& obj);
};

template <class T>
ostream& operator<<(ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template <class T>
istream& operator>>(istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

///////////////////////////////////////// Iterated LinkedList ///////////////////////////////////////////

//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	///////////////////////////////////////// iterator ///////////////////////////////////////////

	//дописать класс итератора по списку
	class iterator : public std::iterator<std::input_iterator_tag, T>
	{
	private:
		//текущий элемент
		Element<T>* ptr;

	protected:
		Element<T>* getPtr()
		{
			return ptr;
		}

	public:
		//конструкторы
		iterator() { ptr = NULL; }
		iterator(Element<T>* p) { ptr = p; }
		iterator(const iterator& it) { ptr = it.ptr; }

		//методы работы с итераторами
		//присваивание
		iterator& operator=(const iterator& it)
		{
			ptr = it.ptr;
			return *this;
		}
		iterator& operator=(Element<T>* p)
		{
			ptr = p;
			return *this;
		}

		//проверка итераторов на равенство
		bool operator!=(iterator const& other) { return ptr != other.ptr; }
		bool operator==(iterator const& other) { return ptr == other.ptr; }
		//получить значение
		Element<T>& operator*()
		{
			if (ptr == NULL)
				throw invalid_argument("NULL pointer!");
			return *ptr;
		}
		//перемещение с помощью итераторов
		iterator& operator++()
		{
			if (ptr != NULL && ptr->getNext() != NULL)
				ptr = ptr->getNext();
			return *this;
		}
		iterator& operator++(int v)
		{
			if (ptr != NULL && ptr->getNext() != NULL)
				ptr = ptr->getNext();
			return *this;
		}
		iterator& operator--()
		{
			if (ptr != NULL && ptr->getPrevious() != NULL)
				ptr = ptr->getPrevious();
			return *this;
		}
		iterator& operator--(int v)
		{
			if (ptr != NULL && ptr->getPrevious() != NULL)
				ptr = ptr->getPrevious();
			return *this;
		}
	};

	iterator begin()
	{
		iterator it = LinkedListParent<T>::head;
		return it;
	}
	iterator end()
	{
		iterator it = LinkedListParent<T>::tail;
		return it;
	}

	template <class T1>
	friend ostream& operator<<(ostream& ustream, IteratedLinkedList<T1>& obj);
};

template <class T>
ostream& operator<<(ostream& ustream, IteratedLinkedList<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		auto p = obj.begin();
		while (true)
		{
			ustream << *p << " ";
			if (p == obj.end())
				break;
			++p;
		}
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (auto p = obj.begin();; i++)
	{
		ustream << "arr[" << i << "] = " << *p << "\n";
		if (p == obj.end())
			break;
		++p;
	}

	return ustream;
}

// Stack

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~Stack()
	{

		cout << "\nIteratedLinkedList destructor";
	}

	virtual Element<T>* push(T value)
	{
		Element<T>* res = new Element<T>(value);

		if (LinkedListParent<T>::num == 0)
		{
			LinkedListParent<T>::head = res;
		}
		else
		{
			LinkedListParent<T>::tail->setNext(res);
			res->setPrevious(LinkedListParent<T>::tail);
		}

		LinkedListParent<T>::tail = res;
		LinkedListParent<T>::num++;
		return res;
	}

	virtual Element<T>* pop()
	{
		if (LinkedListParent<T>::num == 0)
			return NULL;
		Element<T>* res = LinkedListParent<T>::tail;
		if (LinkedListParent<T>::num == 1)
		{
			LinkedListParent<T>::head = LinkedListParent<T>::tail = NULL;
		}
		res->getPrevious()->setNext(NULL);
		LinkedListParent<T>::tail = res->getPrevious();
		res->setPrevious(NULL);
		LinkedListParent<T>::num--;
		return res;
	}
};

//Sorted Stack

template <typename T>
class SortedStack : public Stack<T>
{
public:
	virtual Element<T>* push(T value)
	{
		auto p = IteratedLinkedList<T>::begin();
		auto pEnd = IteratedLinkedList<T>::end();
		Element<T>* elem = new Element<T>(value);

		if (p == NULL)
		{
			LinkedListParent<T>::head = elem;
			LinkedListParent<T>::tail = elem;
		}
		else if (p == pEnd)
		{
			if ((*pEnd).getValue() > value)
			{
				LinkedListParent<T>::head = elem;
				elem->setNext(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail->setPrevious(elem);
			}
			else
			{
				LinkedListParent<T>::tail = elem;
				elem->setPrevious(LinkedListParent<T>::head);
				LinkedListParent<T>::head->setNext(elem);
			}
		}
		else
		{
			while (p != pEnd)
			{
				if ((*p).getValue() > value)
					break;
				++p;
			}

			if (p == IteratedLinkedList<T>::begin())
			{
				elem->setNext(LinkedListParent<T>::head);
				LinkedListParent<T>::head->setPrevious(elem);
				LinkedListParent<T>::head = elem;
			}
			else if (p == pEnd && (*pEnd).getValue() < value)
			{
				elem->setPrevious(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail->setNext(elem);
				LinkedListParent<T>::tail = elem;
			}
			else
			{
				elem->setNext((*p).getPrevious()->getNext());
				elem->setPrevious((*p).getPrevious());
				elem->getPrevious()->setNext(elem);
				elem->getNext()->setPrevious(elem);
			}
		}

		LinkedListParent<T>::num++;

		return elem;
	}
};

// посимвольное сравнение для char*
bool opa(char a[], char b[])
{
	int i = 0;
	while (a[i] == b[i]) i++;
	return (a[i] > b[i]);
}

// Patient

class Patient
{
	// Пациент
public:
	char* name; // имя пациента
	char* secondname; // фамилия пациента
	char* date_of_birth; // дата рождения пациента
	int telephone; // телефон пациента
	char* address; // адрес пациента
	int number; // номер карты
	int blood_type; // группа крови

	// конструкторы
	Patient() { char u[] = ("n/a"); name = u; secondname = u; date_of_birth = u; telephone = 0; address = u; number = 0; blood_type = 0;  cout << "\nPatient default constructor"; }

	Patient(char* Name, char* Secondname, char* Date_of_birth, int Telephone, char* Address, int Number, int Blood_type) {
		name = Name; secondname = Secondname; date_of_birth = Date_of_birth; telephone = Telephone; address = Address; number = Number; blood_type = Blood_type;
	}

	~Patient() { }

	// Сравнение: сначала по номеру карты, потом по группе крови, потом по фамилии, потом по имени.

	int operator > (Patient P)
	{
		if (number == P.number)
		{
			if (blood_type == P.blood_type)
			{
				if (secondname == P.secondname)
					return opa(P.name, name);
				else
					return opa(P.secondname, secondname);
			}
			else
				return  (blood_type < P.blood_type);
		}
		return (number < P.number);
	}

	int operator < (Patient P)
	{
		if (number == P.number)
		{
			if (blood_type == P.blood_type)
			{
				if (secondname == P.secondname)
					return opa(name, P.name);
				else
					return opa(secondname, P.secondname);
			}
			else
				return  (blood_type > P.blood_type);
		}
		return (number > P.number);
	}

	friend ostream& operator<<(ostream& s, Patient& value);
};

ostream& operator<<(ostream& s, Patient& value)
{
	s << "[ " << value.name << ", " << value.secondname << ", " << value.date_of_birth << ", " << value.telephone << ", " << value.address << ", " << value.number << ", " << value.blood_type << " ]\n";
	return s;
}

bool sogl(char ch)
{
	if (ch == 'a' || ch == 'A' ||
		ch == 'e' || ch == 'E' ||
		ch == 'y' || ch == 'Y' ||
		ch == 'o' || ch == 'O' ||
		ch == 'u' || ch == 'U' ||
		ch == 'i' || ch == 'I')
		return 0;
	else
		return 1;
};

int main()
{
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.push(3);
	S.push(4);
	S.push(5);
	S.push(6);
	cout << S;
	cout << "\n";
	Element<int>* e1 = S.pop();
	cout << "\nElement = " << e1->getValue();
	cout << S;
	cout << "\nIndex in the Stack class: " << S[4]->getValue();

	cout << S;
	cout << "\nIterators:\n";

	Stack<int>::iterator p = S.begin();
	while (true)
	{
		cout << *p << " ";
		if (p == S.end())
			break;
		p++;
	}
	cout << *p << " ";
	

	SortedStack<char> A;
	A.push('U');
	A.push('T');
	A.push('W');
	A.push('F');
	A.push('A');
	A.push('B');
	A.push('H');
	A.pop();
	A.push('L');
	A.push('C');
	Stack<char> filtered(A.filter(sogl));
	cout << filtered;
	

	char name1[] = "Egor";
	char secondname1[] = "Seregin";
	char date_of_birth1[] = "23.05.2003";
	int telephone1 = 2508;
	char address1[] = "Navla";
	int number1 = 237;
	int blood_type1 = 1;

	char name2[] = "Polina";
	char secondname2[] = "Listova";
	char date_of_birth2[] = "14.06.2005";
	int telephone2 = 7724;
	char address2[] = "Moscow";
	int number2 = 144;
	int blood_type2 = 3;

	char name3[] = "Nastia";
	char secondname3[] = "Listova";
	char date_of_birth3[] = "18.02.2003";
	int telephone3 = 1581;
	char address3[] = "Moscow";
	int number3 = 237;
	int blood_type3 = 1;

	char name4[] = "Fedor";
	char secondname4[] = "Dydikin";
	char date_of_birth4[] = "16.01.2004";
	int telephone4 = 5360;
	char address4[] = "Lobnia";
	int number4 = 150;
	int blood_type4 = 3;

	Patient p1(name1, secondname1, date_of_birth1, telephone1, address1, number1, blood_type1);
	Patient p2(name2, secondname2, date_of_birth2, telephone2, address2, number2, blood_type2);
	Patient p3(name3, secondname3, date_of_birth3, telephone3, address3, number3, blood_type3);
	Patient p4(name4, secondname4, date_of_birth4, telephone4, address4, number4, blood_type4);

	SortedStack<Patient> hospital;
	hospital.push(p1);
	hospital.push(p2);
	hospital.push(p3);
	hospital.push(p4);
	hospital.pop();
	cout << hospital;
	return 0;
}



