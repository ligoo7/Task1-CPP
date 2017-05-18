/*6. Вычесть из каждого числа сумму всех чисел
B) двусторонняя очередь (std::deque)
Горлищева Лидия*/

#include "stdafx.h"
#include <iostream> 
#include <sstream>
#include <fstream>
#include <deque>
#include <vector>
#include <iterator> 
#include <algorithm>

//циклическое заполение файла
std::fstream& FillingFileCycle(std::string fileName, int N, int M) 
{
	std::fstream fout(fileName, std::ios::out);
	for (int i = 0; i < N; i++) {
		fout << (rand() % (2 * M + 1) - M) << "\n";
	}
	fout.close();
	return fout;
}

//заполнение файла с использованием алгоритма std::generate
std::fstream FillingFileGenerate(std::string fileName, int N, int M) 
{
	std::vector<int> v(N);
	std::fstream fout(fileName, std::ios::out);
	std::generate(v.begin(), v.end(), rand);
	for (int i = 0; i < N; i++) {
		fout << (v[i] % (2 * M +1)) - M  << "\n";
	}
	fout.close();
	return fout;
}

//заполение контейнера из файла
bool FillingFromFile(std::string fileName, std::deque<int> &dec) 
{
	dec.clear();
	std::fstream fin(fileName, std::ios_base::in);
	int num;
	if (fin.is_open())
	{
		while (fin >> num) 
			dec.push_back(num);
		fin.close();
		return true;
	}
	else 
	{
		return false;
	}
}

//печать контейнера
void PrintContainer(std::deque<int> dec) 
{
	for (std::deque<int>::iterator it = dec.begin(); it != dec.end(); ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << "\n\n";
}

//заполнение файла элементами контейнера 
std::fstream& SaveToFile(std::string fileName, std::deque<int> dec)
{
	std::fstream fout(fileName, std::ios::out);
	for (int el : dec)
	{
		fout << el << "\n";
	}
	fout.close();
	return fout;
}

//поиск суммы элементов
int SumContainer(std::deque<int>::iterator first, std::deque<int>::iterator last) 
{
	if (first == last)
	{
		throw "Контейнер пуст";
	}
	int sum = *first;
	for (std::deque<int>::iterator it = ++first; it != last; ++it)
		sum += *it;
	return sum;
}

//преобразование контейнера 
void Modify(std::deque<int> &dec) 
{
	try
	{
		int sum = SumContainer(dec.begin(), dec.end());
		for (std::deque<int>::iterator it = dec.begin(); it != dec.end(); ++it)
			(*it) -= sum;
	}
	catch (const char* e) 
	{
		std::cout << e << std::endl;
	}
}

//преобразование части контейнера
void ModifyPart(std::deque<int>::iterator first, std::deque<int>::iterator last) 
{
	try
	{
		int sum = SumContainer(first, last);
		std::cout << "Сумма чисел диапазона: ";
		std::cout << sum; std::cout << "\n\n";
		for (std::deque<int>::iterator it = first; it != last; ++it)
			*it -= sum;
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
	}
}

class Transform
{
private:
	int a;
public:
	explicit Transform(int sum)
	{
		a = sum;
	}
	int operator()(int el) const 
	{
		return el - a;
	}
};

class Foreach 
{
private:
	int a;
public:
	explicit Foreach(int sum)
	{
		a = sum;
	}
	void operator()(int &el) const 
	{
		el -= a;
	}
};

//преобразование с transform
void ModifyTransform(std::deque<int> &dec)
{
	try
	{
		int sum = SumContainer(dec.begin(), dec.end());
		std::transform(dec.begin(), dec.end(), dec.begin(), Transform(sum));
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
	}
}

//преобразование с foreach
void ModifyForEach(std::deque<int> &dec) 
{
	try
	{
		int sum = SumContainer(dec.begin(), dec.end());
		std::for_each(dec.begin(), dec.end(), Foreach(sum));
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
	}
}

//среднее арифметическое всех чисел         
double Average(std::deque<int> dec)
{
	return (double)SumContainer(dec.begin(), dec.end()) / dec.size();
}

//ввод параметров
void InputParametrs(int &N, int &M)
{
	N = -1;
	while (N <= 0)
	{
		std::cout << "\nВведите количество чисел: ";
		std::cin >> N;
	}
	std::cout << "\nВведите границу диапазона M: ";
	std::cin >> M;
	M = abs(M);
	std::cout << std::endl;
}

//получение имени файла
std::string GetFileName() 
{
	std::string fileName;
	std::cout << "Введите имя файла: ";
	std::cin >> fileName;
	std::cout << std::endl;
	return fileName + ".txt";
}

//вывод контейнера на экран
bool ContainerToConsole(std::deque<int> dec)
{
	if (!dec.empty())
	{
		std::cout << "Контенер: ";
		PrintContainer(dec);
		return true;
	}
	else
		std::cout << "Контейнер пуст\n\n";
	return false;
}

//печать менюшки
void printMenu()
{
	std::cout << "1. Заполнение файла случайными числами в диапазоне от -M до M\n";
	std::cout << "2. Заполнение контейнера числами из файла\n";
	std::cout << "3. Преобразование контейнера\n";
	std::cout << "4. Преобразование части контейнера\n";
	std::cout << "5. Преобразование с использованием алгоритма std::transform\n";
	std::cout << "6. Преобразование с использованием алгоритма std::for_each\n";
	std::cout << "7. Сумма и среднее арифметическое чисел, содержащихся в контейнере\n";
	std::cout << "8. Сохранить результат в файл\n";
	std::cout << "9. Вывести результат на экран\n";
	std::cout << "0. Выйти\n\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::deque<int> dec, NewDec;
	std::string fileName;
	int N, M, c;

	while (true)
	{
		printMenu();
		int choice = -1;
		std::cin >> choice;
		while ((choice > 9) || (choice < 0))
		{
			std::cout << "Неверный индекс\n\n";
			printMenu();
			std::cin >> choice;
		}
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			fileName = GetFileName();
			InputParametrs(N, M);
			c = 0;
			while ((c < 1) || (c > 2))
			{
				std::cout << "1. Генерация в цикле\n";
				std::cout << "2. Генерация с использованием алгоритма std::generate\n\n";
				std::cin >> c;
				std::cout << std::endl;
			}
			switch (c)
			{
			case 1:
				FillingFileCycle(fileName, N, M);
				break;
			case 2:
				FillingFileGenerate(fileName, N, M);
			case 3:
				break;
			}
			break;
		case 2:
			fileName = GetFileName();
			if (FillingFromFile(fileName, dec)) 
			{
				ContainerToConsole(dec);
			}
			else {
				std::cout << "Невозможно открыть файл\n\n";
			}
			break;
		case 3:
			if (ContainerToConsole(dec))
			{
				std::cout << "Полученный контейнер (из каждого числа вычтена сумма):\n";
				NewDec = dec;
				Modify(NewDec);
				PrintContainer(NewDec);
			}
			break;
		case 4:
		{
			std::deque<int>::iterator first, last;
			int indexFirst, indexLlast;
			bool ok = false;
			if (ContainerToConsole(dec))
			{
				std::cout << "Введите диааозон: ([first; last))\n";
				while (!ok)
				{
					std::cout << "индекс начала - ";
					std::cin >> indexFirst;
					std::cout << "индекс конца - ";
					std::cin >> indexLlast;
					ok = (indexFirst > 0) && (indexFirst <= dec.size()) && (indexLlast <=( dec.size() +1) && (indexFirst < indexLlast));
					if (!ok)
					{
						std::cout << "Диапазон указан неверно, повторите ввод [1-"; std::cout << (dec.size() + 1); std::cout << "]:\n";
					}
				} 
				std::cout << std::endl;

				NewDec = dec;
				first = NewDec.begin() + indexFirst - 1;
				last = NewDec.begin() + indexLlast - 1;

				ModifyPart(first, last);
				std::cout << "Полученный контейнер (из каждого числа промежутка вычтена их сумма):\n";
				PrintContainer(NewDec);
			}
			break;
		}
		case 5:
			if (ContainerToConsole(dec))
			{
				NewDec = dec;
				ModifyTransform(NewDec);
				std::cout << "Полученный контейнер (из каждого числа вычтена сумма):\n";
				PrintContainer(NewDec);
			}
			break;
		case 6:
			if (ContainerToConsole(dec))
			{
				NewDec = dec;
				ModifyForEach(NewDec);
				std::cout << "Полученный контейнер (из каждого числа вычтена сумма):\n";
				PrintContainer(NewDec);
			}
			break;
		case 7:
			if (ContainerToConsole(dec)) 
			{
				std::cout << "Сумма чисел: " << SumContainer(dec.begin(),dec.end()) << std::endl;
				std::cout << "Среднее арифметическое: " << Average(dec) << std::endl << std::endl;
			}
			break;
		case 8:
			if (!NewDec.empty())
			{
				fileName = GetFileName();
				SaveToFile(fileName, NewDec);
				std::cout << "Сохранен результат\n\n";
			}
			else if (!dec.empty())
			{
				fileName = GetFileName();
				SaveToFile(fileName, dec);
				std::cout << "Сохранен контейнер\n\n";
			}
			else
				std::cout << "Контейнер пуст\n\n";
			break;
		case 9:
			if (!NewDec.empty())
				ContainerToConsole(NewDec);
			else
				ContainerToConsole(dec);
			break;
		case 0:
			return 0;
		}
	}
}