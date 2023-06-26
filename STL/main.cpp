#include <iostream>
#include <array>
#include<stack>
#include<vector>
#include<deque>

using namespace std;
using std::cout;
#define tab "\t"
#define delimiter "\n-------------------------------------------------\n"

//#define STL_ARRAY
//#define STL_STACK
//#define STL_VECTOR
#define STL_DEQUE

//template <typename T> void vector_properties(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl; 

#ifdef STL_ARRAY
	const int N = 5;
	std::array <int, N> arr = { 3,5,8 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef DEBUG
	std::stack<int> stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(12);
	stack.push(18);
	while (!stack.empty())
	{
		cout << stack.top() << endl;
		stack.pop();
	}

#endif // DEBUG

#ifdef STL_VECTOR
	std::vector<int> vec = { 3,4,5,6,12,17,18,20,35,10 };
	try
	{
		for (int i = 0; i < vec.size() * 2; i++)
		{
			//cout << vec[i] << tab;
			cout << vec.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)// e - добавили имя аргумента 
	{
		std::cerr << e.what() << endl; 
	}
	vector_properties(vec);
	vec.push_back(66);
	vector_properties(vec);
	vec.reserve(20); // метод резервирует доп вместительность 
	//vec.shrink_to_fit();// урезает вместительность до фактичесткого размера 
	vec.resize(15);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)// посфиксный для того чтобы не создавал лишних элеметов 
	{
		cout << *it << tab; 
	}
	cout << endl; 
	vector_properties(vec);
	cout << "Size: " << vec.size() << endl; 
	cout << "Max size: " << vec.max_size() << endl;// влияет на количество тэлеменотов: память ПК, тип данных, количество 
	//cout << "Capacity: " << vec.capacity() << endl; // вместительность 

	cout << delimiter << endl; 

	/*int index;
	int value;
	do
	{
		cout << "Введете индекс добавляемого значения: "; cin >> index;
		cout << "Введете значение добавляемого значения: "; cin >> value;
		if (index > vec.size())cout << "Очень большой индекс" << endl; 
	} while (index > vec.size());*/
	//vec.insert(vec.begin()+index, value);
	//for (int i : vec)cout << i << tab; cout << endl; 

	vec.insert(vec.begin()+3, {1202,2000,1985});
	for (int i : vec)cout << i << tab; cout << endl; 
	vec.erase(vec.begin() + 5);
	for (int i : vec)cout << i << tab; cout << endl; 
	vec.erase(vec.begin() + 2, vec.begin()+7);
	for (int i : vec)cout << i << tab; cout << endl; 
	cout << "Begin: " << vec.front() << endl;
	cout << "End: " << vec.back() << endl;
#endif // STL_VECTOR

#ifdef STL_DEQUE

	std::deque<int> deque = { 3,5,6,8,9,10 };
	for (int i = 0; i < deque.size(); i++)
	{
		cout << deque[i] << tab;
	}
	cout << endl; 
	deque.push_back(34);
	deque.push_back(45);
	deque.push_back(56);
	deque.push_front(1);
	deque.push_front(2);
	deque.push_front(0);
	for (int i : deque)cout << i << tab; cout << endl; 
#endif // STL_DEQUE

}

template <typename T> void vector_properties(const std::vector<T>& vec)
{
	cout << "Size: " << vec.size() << endl;
	cout << "Max size: " << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
}