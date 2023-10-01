#include <iostream>
#include <vector>
#include <string>
#include <fstream>


void getData(std::string& data, std::ifstream& file)
{
	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			data += line;
		}
	}	
	else
	{
		std::cout << "File can't open!" << std::endl;
	}

}



void KMP(std::string& text, std::string& pattern)
{
	std::vector<int> p(pattern.size(), 0);

	int j = 0;
	int i = 1;

	while (i<pattern.size()) //Заполнение массива максимальных суффиксов и префиксов
	{
		if (pattern[j] == pattern[i])
		{
			p[i] = j + 1;
			i++;
			j++;
		}
		else
		{
			if (j == 0)
			{
				p[i] = 0;
				i++;
			}
			else
			{
				j = p[j - 1];
			}		
		}
	}

	int m = pattern.size();
	int n = text.size();

	i = 0;
	j = 0;

	while (i < text.size()) //Проход по всему тексту
	{
		if(text[i] == pattern[j])
		{
			i++;
			j++;

			if (j == pattern.size())
			{
				std::cout << j+1 << std::endl; //начиная с какого индека в текста начинается подстрока
				break;
			}			
		}
		else
		{
			if (j > 0)
			{
				j = p[j - 1];
			}
			else
			{
				i++;
			}
		}
	}
	
	if (i == n)
	{
		std::cout << -1 << std::endl;
	}
}


void main()
{
	std::ifstream file;
	file.open("text_dm.txt");

	std::string text = "";
	getData(text, file);

	setlocale(LC_ALL, "rus");

	std::cout << "Введите строку для поиска: ";

	std::string pattern;
	std::cin >> pattern;

	KMP(text, pattern);
}