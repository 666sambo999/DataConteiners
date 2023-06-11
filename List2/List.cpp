#include"List.h"

//////////////////////////////////////////////////////////////////////////
///////////		Element member functions					///////////
template <typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev) // инициализация в заголовке
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T> List<T>::Element::~Element()
{
#ifdef DEBUG			
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
///////////		Element member functions					//////////
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///////////		ConstBaseIterator member functions					///////////
template <typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	// return !(*this == other);
	return this->Temp != other.Temp; // будет быстрее, так как проц сравгивает адреса
}
template <typename T> const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
///////////		ConstBaseIterator member functions		//////////
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///////////		ConstIterator member functions					///////////
template <typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor\t" << this << endl;
#endif // DEBUG

}
template <typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor\t" << this << endl;
#endif // DEBUG
}
template <typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator ++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template <typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator ++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template <typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template <typename T> typename List<T>::ConstIterator List<T>::ConstIterator:: operator --(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
///////////		ConstIterator member functions		//////////
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///////////		ConstReverseIterator member functions					///////////
template <typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
///////////		ConstReverseIterator member functions	//////////
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///////////		Iterator member functions					///////////
template <typename T> T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
///////////		Iterator member functions					//////////
//////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////	ReverseIterator member functions			///////////
template <typename T> T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
///////////		ReverseIterator member functions			///////////
//////////////////////////////////////////////////////////////////


template <typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T> typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template <typename T> typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template <typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template <typename T> typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template <typename T> typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

//			Constructors 
template <typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template <typename T>List<T>::List(int size)
{
	while (size--)push_back(int());
}
template <typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template <typename T>List<T>::List(const List<T>& other) :List() // Конструктор копирования 
{
	*this = other; // повторное использование кода 
	cout << "LCopyConstructor:\t" << this << endl;
}
template <typename T>List<T>::~List()
{
	while (Tail)pop_back();
	//while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//			Operators
template <typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	//1)удаляем старое значение объекта 
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "LCopyAssigment:\t" << this << endl;
	return*this;
}

//			Adding element 
template <typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	/*Element* New = new Element(Data, Head);
	New ->pNext = Head;
	Head->pPrev = New;
	Head = New;*/
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template <typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;  // отработает как в if так и в else
}
template <typename T> void List<T>::insert(T Data, int index)
{
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	if (index > size)return;
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
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev ->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template <typename T> void List<T>::erase(int index)
{
	if (index == 0)return pop_front();
	if (index == size - 1)return pop_back();
	if (index >= size)return;
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head; // заходим через голову 
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail; // заходим через хвост 
		for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	//1) Исключаем элемент из списка
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	//2) удаляем элeмент из памяти 
	delete Temp;
	size--;
}

//			Removing Methods
template <typename T> void List<T>::pop_front()
{
	if (Head == Tail)
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
template <typename T>void List<T>::pop_back()
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
template <typename T> void List<T>::print()
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template <typename T>void List<T>::revers_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	//			type			name=initialisation;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it) // должен быть написан typename
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}
