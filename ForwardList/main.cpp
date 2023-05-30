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
		//while (Head)pop_front();
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl; 
	}

	// Adding element:
	void push_front(int Data)
	{
		Element* New = new Element(Data); //1) создаем новый элемент 
		New->pNext = Head; //2) включам новый элемент в список 
		Head = New; // переносим голову на новый элемент 
	} 
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}

	void insert(int Data, int index)
	{
		//1) Сoздаем новый элемент 
		Element* New = new Element(Data);
		//2)  доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//3) включаем созданный элемент в список
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		Element* Temp = Head;
		for (int i=0; i<index-1;i++)
		{
			Head = Temp->pNext;
		}
			
		delete Temp;
		//Head->pNext = nullptr;
	}

	//			Removing element 
	void pop_front()
	{
		Element* Erased = Head; // 1) запоминаем адрес удаляемого эдемента 
		Head=Head->pNext; //2) Исключаем удаляемый элемент из списка
		delete Erased;	  // 3) удаляем элемент из памяти 
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
	}

	//		Methods
	void print()const
	{
		/*для того чтобы перемнщатся по списку нужно две вещи
		* 1. итератор 
		* 2. цикл */
		
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
		//list.push_front(rand() % 100);
		list.push_back(rand()%100);
	}
	//list.push_back(321);
	list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	
	/*int value;
	int index;
	cout << "Введите значение добавляемого значения: "; cin >> value;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	list.insert(value,index);*/
	
	int index;
	cout << "Введите индекс удаляемого значения: "; cin >> index;
	list.erase(index);
	list.print();

}