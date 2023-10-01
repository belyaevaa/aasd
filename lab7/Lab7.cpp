#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef std::vector<std::vector<int>> graph;

int to_int(std::string str)
{
	int result = 0;
	if (str.size() == 2)
	{
		result = (str[0] - 48) * 10 + str[1] - 48;
	}
	else if (str.size() == 1)
	{
		result = str[0] - 48;
	}

	return result;
}


void fillMatrix(graph& matrix, std::ifstream& file, int n)
{
	if (file.is_open())
	{
		std::string line;
		int  k = 0;

		while (std::getline(file, line)) 
		{
			int cnt = 0;

			for (int i = 0; i < n - 1; i++)
			{
				int g = 0;

				if (line[i] == ' ')
				{
					for (int j = i + 1; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							std::string test = line.substr(i + 1, j - i - 1);
							matrix[k][g] = to_int(line.substr(i + 1, j - i - 1));
							i = j;
							g++;
						}
					}
				}
			}

			k++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}
}


int countingTops(std::ifstream& file)
{
	int tops = 0;

	if (file.is_open())
	{
		file.seekg(0); 
		std::string line;

		while (std::getline(file, line))
		{
			tops++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return tops;
}


bool isExist(std::vector<std::vector<int>> woods, int value)
{
	bool result = false;

	for (const auto wood : woods)
	{		
		for (int i = 0; i < 2; i++)
		{
			if (wood[i] == value)
			{
				result = true;
			}
		}
	}

	return result;
}


bool isAllChecked(std::vector<bool> used)
{
	bool result = true;

	for (auto c : used)
	{
		if (c == false)
		{
			result = false;
		}
	}

	return result;
}

void prim(graph& matrix, std::vector<std::vector<int>>& woods, std::vector<int>& components, std::vector<bool> &used) // ����� �� �������� ��������, �� �� ��
{																													  // ����� ������� ��� ��������
	bool isCanContinue = false;
	
	int k = 0;
	int g = 0;

	for (int i = 0; i < components.size();)
	{
		int minValue = 1000000;

		for (int j = 0; j < matrix[i].size();j++)
		{
			int z = i;

			if (matrix[z][j] != 0 && matrix[z][j] < minValue && !(isExist(woods, j) && isExist(woods,z)))
			{
				minValue = matrix[z][j];
				k = z;
				g = j;
				isCanContinue = true;
			}
			if (isExist(woods, j))
			{
				used[z] = true;
				used[j] = true;
			}
		}

		if (isCanContinue)
		{
			woods.push_back({ k,g,minValue });
			isCanContinue = false;
			used[k] = true;
			used[g] = true;
			i = g;
		}
		else
		{
			i++;
		}
	}
}


void main()
{
	std::ifstream file;
	file.open("graph.txt");
	int n = countingTops(file);
	file.close();
	file.open("graph.txt");
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);
	std::vector<bool> used(n);
	std::vector<std::vector<int>> woods; //spaning woods
	std::vector<int> components = { 0,1,2,3,4,5,6,7,8,9 }; 

	while (!isAllChecked(used))  
	{
		for (int i = 0; i < used.size(); i++)
		{
		    prim(matrix, woods, components, used);
		}
	}

	for (int i = 0; i < woods.size(); i++)
	{
		for (int j = 0; j < woods[i].size(); j++)
		{
			std::cout << woods[i][j] << "\t";
		}

		std::cout << "\n";
	}
}