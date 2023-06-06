#include<iostream>

using namespace std;

#define tab "\t"
#define delimetr  "\n---------------------------------------\n"


class List
{
	class Element 
	{		// это включение или композиция в класс
		int Data; // значение элемента 
		Element* pNext; // указатель на сдедующий элемент 
		Element* pPrev;  //указатель на предыдущий элемент 
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) 
			: Data(Data), pNext(pNext), pPrev(pPrev) // инициализация в заголовке
		{
			cout << "EConstructor:\t" << this << endl; 
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl; 
		}
		friend class List;
	}*Head,*Tail; // объекты и указатели на объекты можно объявлять сражу после описания класса
	size_t size;			// это псевдоним для типа данных 
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
		size++;  // отработает как в if так и в else
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
		Head = Head->pNext; // смещаем голову 
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
		cout << "Количество элементов списка: " << size << endl; 
	}
	void revers_print()const
	{
		for (Element * Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl; 
	}
};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.revers_print();
}