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
	//			Methods
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<  Temp->pNext << endl; 
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
		list.push_front(rand() % 100);
	}
	list.print();

}