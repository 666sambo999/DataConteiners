#include <iostream>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
class Element
{
	int Data;			// значение элемента  
	Element* pNext;		//адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl; 
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl; 
	}
	friend class ForwardList; // подружить классы 
};

class ForwardList
{
	Element* Head;   // Голова- это указатель на начальный элемент в списке
	//  также как в массиве, имя массива содержит адрем нулевого массива,
	//  Голова списка содержит адрес начального элемента. 
public:
	ForwardList()
	{
		Head = nullptr;		// Когда список пуст, его голова указывает на 0(ноль) 
		cout << "LConstructor:\t" << this << endl; 
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl; 
	}

	// Adding element:
	void push_front(int Data)
	{
		Element* New = new Element(Data); //1) создаем новый элемент 
		New->pNext = Head; //2) включам новый элемент в список 
		Head = New; // переносим голову на новый элемент 
	} 

	//		Methods
	void print()const
	{
		Element* Temp = Head;	// Temp -  это итератор,
		// итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных   
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl; 
			Temp = Temp->pNext; // переход на новый элемент 
		}
	}


};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}