#pragma once

#include <iostream>
#include <ctime>

using namespace std;

using std::cout;

#define tab "\t"
#define delimetr  "\n---------------------------------------\n"


template <typename T>class List
{
	class Element
	{		// это включение или композици€ в класс
		T Data; // значение элемента 
		Element* pNext; // указатель на сдедующий элемент 
		Element* pPrev;  //указатель на предыдущий элемент 
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail; // объекты и указатели на объекты можно объ€вл€ть сражу после описани€ класса
	size_t size;			// это псевдоним дл€ типа данных 

	class ConstBaseIterator
	{
		// Generalisation - обобщает 
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) : Temp(Temp) {}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();
		ConstIterator& operator ++();
		ConstIterator operator ++(int);
		ConstIterator& operator--();
		ConstIterator operator --(int);
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator& operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin()const;
	ConstIterator end()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;

	//			Constructors 
	List();
	List(int size);
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//			Operators
	List<T>& operator=(const List<T>& other);
	//			Adding element 
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);
	void erase(int index);

	//			Removing Methods
	void pop_front();
	void pop_back();

	//			Methods
	void print();
	void revers_print()const;
};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right);
