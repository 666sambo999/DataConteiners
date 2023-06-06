#include<iostream>

using namespace std;

#define tab "\t"
#define delimetr  "\n---------------------------------------\n"


class List
{
	class Element 
	{		// ��� ��������� ��� ���������� � �����
		int Data; // �������� �������� 
		Element* pNext; // ��������� �� ��������� ������� 
		Element* pPrev;  //��������� �� ���������� ������� 
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) 
			: Data(Data), pNext(pNext), pPrev(pPrev) // ������������� � ���������
		{
			cout << "EConstructor:\t" << this << endl; 
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl; 
		}
		friend class List;
	}*Head,*Tail; // ������� � ��������� �� ������� ����� ��������� ����� ����� �������� ������
	size_t size;			// ��� ��������� ��� ���� ������ 
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl; 
	}
	~List()
	{
		while (Tail)pop_back();
		//while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl; 
	}
	//			Adding element 
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data, Head);
		New ->pNext = Head; 
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;  // ���������� ��� � if ��� � � else
	}
	void insert(int Data, int index)
	{
		if (index==0)return push_front(Data);
		if (index > size)return;
		Element* New = new Element(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else 
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev ->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//			Removing Methods
	void pop_front()
	{
		if(Head==Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			//size--;
			size = 0;
			return;
		}
		Head = Head->pNext; // ������� ������ 
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		/*{
			delete Head;
			Head = Tail = nullptr;
			size = 0;
			return;
		}*/
		Tail = Tail->pPrev;
		delete Tail->pNext; 
		Tail->pNext = nullptr;
		size--;
	}


	//			Methods
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<  Temp->pNext << endl; 
		cout << "���������� ��������� ������: " << size << endl; 
	}
	void revers_print()const
	{
		for (Element * Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl; 
	}
};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.revers_print();
	//list.pop_front();
	/*list.~List();
	list.pop_front();
	list.pop_back();
	list.print();
	list.revers_print();*/

	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.revers_print();
}