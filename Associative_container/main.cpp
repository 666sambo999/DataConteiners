#include<iostream>
#include<set>
#include<map>
#include<vector>

using namespace std;
using std::cout;
using std::endl;
using std::cin;

#define tab "\t"
#define delimeter "\n----------------------------------\n"

//#define STL_SET
#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_SET
	//std::set<int> set = { 50,25,89,43,32,65,76,14,14,23,14 };// set- в виде бинарного дерева,и уникальным 
	std::multiset<int> set = { 50,25,89,43,32,65,76,14,14,23,14 };
	for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it)
		cout << *it << tab;
	cout << endl;
#endif // STL_SET

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int,std::string>(0,"Sunday"),
		std::pair<int,std::string>(1,"Monday"),
		std::pair<int,std::string>(2,"Tuesday"),
		std::pair<int,std::string>(3,"Wednesday"),
		std::pair<int,std::string>(4,"Thursday"),
		std::pair<int,std::string>(5,"Friday"),
		std::pair<int,std::string>(6,"Saturday"), //{4,"Saturday}, - 2 вариант 
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << endl;
	// multimap - не уникальный, выводит все значения, элементы 
	cout << delimeter << endl;
	for (std::pair<int, std::string> i : week)cout << i.first << tab << i.second << endl;
#endif // STL_MAP

	cout << delimeter << endl; 
	std::map<std::string, std::vector<std::string>> dictionary =
	{
		std::pair<std::string,std::vector<std::string>>("declaration",{"декларация","объявление","заявление"}),
		std::pair<std::string,std::vector<std::string>>("definition",{"определение","формулировка","формулирование"}),
		std::pair<std::string,std::vector<std::string>>("space",{"пробел","космос","пространство"}),
		{"solely",{"единственно","исключительно","только","самостоятельно"}},
		{"fire",{"огонь","костер","сжигать","обжигать"}},
	};


	for (std::map<std::string, std::vector<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout.width(13);
		cout << left;
		//cout << it->first << ":";
		cout << it->first + ":";
		for (std::vector<std::string>::iterator v_it = it->second.begin(); v_it != it->second.end(); ++v_it)
		{
			cout << *v_it << ", "; 
		}
		cout << "\b\b;\n";// "\b - вывод символа backspace в консоль 
	}
	cout << endl; 
}