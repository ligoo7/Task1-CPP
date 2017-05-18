/*6. ������� �� ������� ����� ����� ���� �����
B) ������������ ������� (std::deque)
��������� �����*/

#include "stdafx.h"
#include <iostream> 
#include <sstream>
#include <fstream>
#include <deque>
#include <vector>
#include <iterator> 
#include <algorithm>

//����������� ��������� �����
std::fstream& FillingFileCycle(std::string fileName, int N, int M) 
{
	std::fstream fout(fileName, std::ios::out);
	for (int i = 0; i < N; i++) {
		fout << (rand() % (2 * M + 1) - M) << "\n";
	}
	fout.close();
	return fout;
}

//���������� ����� � �������������� ��������� std::generate
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

//��������� ���������� �� �����
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

//������ ����������
void PrintContainer(std::deque<int> dec) 
{
	for (std::deque<int>::iterator it = dec.begin(); it != dec.end(); ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << "\n\n";
}

//���������� ����� ���������� ���������� 
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

//����� ����� ���������
int SumContainer(std::deque<int>::iterator first, std::deque<int>::iterator last) 
{
	if (first == last)
	{
		throw "��������� ����";
	}
	int sum = *first;
	for (std::deque<int>::iterator it = ++first; it != last; ++it)
		sum += *it;
	return sum;
}

//�������������� ���������� 
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

//�������������� ����� ����������
void ModifyPart(std::deque<int>::iterator first, std::deque<int>::iterator last) 
{
	try
	{
		int sum = SumContainer(first, last);
		std::cout << "����� ����� ���������: ";
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

//�������������� � transform
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

//�������������� � foreach
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

//������� �������������� ���� �����         
double Average(std::deque<int> dec)
{
	return (double)SumContainer(dec.begin(), dec.end()) / dec.size();
}

//���� ����������
void InputParametrs(int &N, int &M)
{
	N = -1;
	while (N <= 0)
	{
		std::cout << "\n������� ���������� �����: ";
		std::cin >> N;
	}
	std::cout << "\n������� ������� ��������� M: ";
	std::cin >> M;
	M = abs(M);
	std::cout << std::endl;
}

//��������� ����� �����
std::string GetFileName() 
{
	std::string fileName;
	std::cout << "������� ��� �����: ";
	std::cin >> fileName;
	std::cout << std::endl;
	return fileName + ".txt";
}

//����� ���������� �� �����
bool ContainerToConsole(std::deque<int> dec)
{
	if (!dec.empty())
	{
		std::cout << "��������: ";
		PrintContainer(dec);
		return true;
	}
	else
		std::cout << "��������� ����\n\n";
	return false;
}

//������ �������
void printMenu()
{
	std::cout << "1. ���������� ����� ���������� ������� � ��������� �� -M �� M\n";
	std::cout << "2. ���������� ���������� ������� �� �����\n";
	std::cout << "3. �������������� ����������\n";
	std::cout << "4. �������������� ����� ����������\n";
	std::cout << "5. �������������� � �������������� ��������� std::transform\n";
	std::cout << "6. �������������� � �������������� ��������� std::for_each\n";
	std::cout << "7. ����� � ������� �������������� �����, ������������ � ����������\n";
	std::cout << "8. ��������� ��������� � ����\n";
	std::cout << "9. ������� ��������� �� �����\n";
	std::cout << "0. �����\n\n";
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
			std::cout << "�������� ������\n\n";
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
				std::cout << "1. ��������� � �����\n";
				std::cout << "2. ��������� � �������������� ��������� std::generate\n\n";
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
				std::cout << "���������� ������� ����\n\n";
			}
			break;
		case 3:
			if (ContainerToConsole(dec))
			{
				std::cout << "���������� ��������� (�� ������� ����� ������� �����):\n";
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
				std::cout << "������� ��������: ([first; last))\n";
				while (!ok)
				{
					std::cout << "������ ������ - ";
					std::cin >> indexFirst;
					std::cout << "������ ����� - ";
					std::cin >> indexLlast;
					ok = (indexFirst > 0) && (indexFirst <= dec.size()) && (indexLlast <=( dec.size() +1) && (indexFirst < indexLlast));
					if (!ok)
					{
						std::cout << "�������� ������ �������, ��������� ���� [1-"; std::cout << (dec.size() + 1); std::cout << "]:\n";
					}
				} 
				std::cout << std::endl;

				NewDec = dec;
				first = NewDec.begin() + indexFirst - 1;
				last = NewDec.begin() + indexLlast - 1;

				ModifyPart(first, last);
				std::cout << "���������� ��������� (�� ������� ����� ���������� ������� �� �����):\n";
				PrintContainer(NewDec);
			}
			break;
		}
		case 5:
			if (ContainerToConsole(dec))
			{
				NewDec = dec;
				ModifyTransform(NewDec);
				std::cout << "���������� ��������� (�� ������� ����� ������� �����):\n";
				PrintContainer(NewDec);
			}
			break;
		case 6:
			if (ContainerToConsole(dec))
			{
				NewDec = dec;
				ModifyForEach(NewDec);
				std::cout << "���������� ��������� (�� ������� ����� ������� �����):\n";
				PrintContainer(NewDec);
			}
			break;
		case 7:
			if (ContainerToConsole(dec)) 
			{
				std::cout << "����� �����: " << SumContainer(dec.begin(),dec.end()) << std::endl;
				std::cout << "������� ��������������: " << Average(dec) << std::endl << std::endl;
			}
			break;
		case 8:
			if (!NewDec.empty())
			{
				fileName = GetFileName();
				SaveToFile(fileName, NewDec);
				std::cout << "�������� ���������\n\n";
			}
			else if (!dec.empty())
			{
				fileName = GetFileName();
				SaveToFile(fileName, dec);
				std::cout << "�������� ���������\n\n";
			}
			else
				std::cout << "��������� ����\n\n";
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