#include <iostream>
#include<time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

class Element
{
	int Data;			//�������� ��������
	Element* pNext;		//����� ���������� ��������
	static int count;	//������� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
	friend class Stack;

};

int Element::count = 0;	//����������� ���������� ����� ������������������� ������ �� ��������� ������.

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int) // ����������� ++
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
protected:
	Element* Head;	//������ - ��� ��������� �� ��������� ������� ������,
	//��� �� ��� � �������, ��� ������� �������� ����� �������� �������,
	//������ ����� �������� ����� ���������� ��������.
	unsigned int size;	//���������� ��������� ������
public:
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;	//����� ������ ����, ��� ������ ��������� �� 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//begin() - ���������� �������� �� ������ ����������
		//end()   - ���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;	//�������� ���������� ��� ��������� =
		cout << "CopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);	//���������� ������� std::move() ������������� �������� MoveAssignment ��� ������ ���������
		cout << "MoveConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		//Deep copy:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_front(Temp->Data);
		reverse();
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//				Adding elements:
	void push_front(int Data)
	{
		/*
		Element* New = new Element(Data);	//1) ������� ����� �������
		New->pNext = Head;	//2) �������� ����� ������� � ������
		Head = New;		//3) ��������� ������ �� ����� �������
		*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;
		//1) ������� ����� �������:
		//Element* New = new Element(Data);
		//2) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//3) �������� ��������� �������� ������:
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		Element* Erased = Head;	//1) ���������� ����� ���������� ��������
		Head = Head->pNext;		//2) ��������� ��������� ������� �� ������
		delete Erased;			//3) ������� ������� �� ������
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
			size++;
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print()const
	{
		/*
		-----------------------
		��� ���� ����� ������������ �� ������ ����� ��� ����:
			1. ��������;
			2. ����;
		-----------------------
		*/
		cout << "\n-----------------" << this << "-----------------\n";
		cout << "Head: " << Head << endl;
		/*Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}*/

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ���������:  " << Head->count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Iterator it = right.begin(); it != right.end(); ++it)
		cat.push_back(*it);
	return cat;
}

class Stack : private ForwardList // ����������� �� �������� ������ ��� ������ �� �� public
{
public:
	void push(int Data)// ����������� 
	{
		ForwardList::push_front(Data);
	}
	void pop()
	{
		ForwardList::pop_front();
	}
	int top()const
	{
		return Head->Data; 
	}
	int depht()const
	{
		return ForwardList::size; 
	}
};

//#define BASE_CHECK
//#define COPY_CHECK
//#define PREFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define ITERATORS_CHECK
//#define PLUS

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		//cout << number << tab;
		//list.push_front(number);
		list.push_back(number);
	}
	//list.push_back(123);
	list = list;
	list.print();
	//list.pop_back();
	int value;
	int index;

	cout << "������� �������� ������������ ��������: "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	list.insert(value, index);
	list.print();


	/*ForwardList list2;
	list2.push_back(1024);
	list2.push_back(2048);
	list2.push_back(3072);
	list2.push_back(4096);

	list.print();
	list2.print();*/
#endif // BASE_CHECK

#ifdef COPY_CHECK
	ForwardList list2 = list;	//Copy constructor
	//ForwardList list2;
	//list2.push_back(1024);
	//list2.push_back(2048);
	//list2.push_back(3072);
	//list2.push_back(4096);
	//list2 = list;	//Copy assignment
	list.print();
	list2.print();
#endif // COPY_CHECK

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	cout << "������ ������, ���� �������� ������" << endl;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "������ ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	//list.print();
	cout << delimiter << endl;
	cout << "�������� ������: " << endl;
	t_start = clock();
	ForwardList list2 = list;
	t_end = clock();
	cout << "������ ���������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������." << endl;
	//list2.print();  
#endif // PREFORMANCE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	long long arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for: https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	//� ������ ������ range (��������) - ��� ��������� ������, ��� ������� ������ ����������� 'for'
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef ITERATORS_CHECK
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef PLUS
	ForwardList list1 = { 3,5,8,13,21 };
	for (int i : list1)cout << i << tab; cout << endl;

	ForwardList list2 = { 34,55,89 };
	for (int i : list2)cout << i << tab; cout << endl;

	//ForwardList list3 = list1 + list2;	//MoveConstructor
	ForwardList list3;
	list3 = list1 + list2;	//MoveAssignment
	for (int i : list3)cout << i << tab; cout << endl;
#endif // PLUS

	Stack stack; 
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(14);

	while (stack.depht())
	{
		cout << stack.top() << endl; 
		stack.pop();
	}

}