#include"List.h"
#include"List.cpp"

//#define Base_Check
#define Home_Work1
//#define Iterator_Perfomance
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef Base_Check
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
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


	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.revers_print();
#endif // Base_Check
#ifdef Iterator_Perfomance

	clock_t t_start, t_end;
	int sum = 0;
	t_start = clock();
	List list(2000000);
	t_end = clock();
	cout << "Список создан за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";

	//List list = { 3,5,8,13,21 };
	//list.print();

#ifdef Home_Work1
	t_start = clock();
	for (int i : list)
	{
		//cout << i << tab;
		sum += i;
	}
	cout << endl;
	t_end = clock();
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
	cout << delimetr << endl;
	/*List::Iterator begin = list.begin();
	List::Iterator end = list.end();
	for (List::Iterator it = begin; it != end; ++it)*/
	int sum2 = 0;
	t_start = clock();
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		//cout << *it << tab;
		sum2 += *it;
	}
	cout << endl;
	t_end = clock();
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
#endif // Home_Work1

#endif // Iterator_Perfomance

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2; //CopyConstructor, потому что мы создаем объект, а не создаваемый  

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	for (List<int>::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list3)cout << i << tab; cout << endl;


	List<double> d_list = { 2.2, 3.4, 4.5, 5.6, 7.8 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list_1 = { "куда","идем","мы", "с","Пятачком" };
	List<std::string> s_list_2 = { "большой","большой","секрет","+","Винни" };
	List<std::string> s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;

	for (List<std::string>::ConstReverseIterator it = s_list_3.rbegin(); it != s_list_3.rend(); ++it)
	{
		cout << *it<< tab; 
	}
	cout << endl; 
}