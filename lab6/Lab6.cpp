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


void fillMatrix(graph& matrix, std::ifstream& file,int n)
{
	if (file.is_open())
	{
		std::string line;
		int  k = 0;

		while (std::getline(file, line)) 
		{
			int cnt = 0;

			for (int i = 0; i < n-1; i++)
			{
				int g = 0;

				if (line[i] == ' ')
				{
					for (int j = i + 1; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							std::string test = line.substr(i+1, j - i-1);
							matrix[k][g] = to_int(line.substr(i+1, j-i-1));
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

		while (std::getline(file,line))
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


bool isExist(std::vector<int>v, int value)
{
	bool result = false;

	for (const auto c : v)
	{
		if (c == value)
		{
			result = true;
		}
	}

	return result;
}


void crusak(graph& matrix, std::vector<std::vector<int>>& woods,std::vector<int>& components)  
{																							   															
	bool isCanContinue = false;																  

	int minValue = 100000000;
	int k = 0;
	int g = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != 0 && matrix[i][j] < minValue && (isExist(components,i) || isExist(components, j)))
			{
				minValue  = matrix[i][j];
				k = i; 
				g = j;
				isCanContinue = true;
			}
		}
	}

	if (isCanContinue)
	{
		if (isExist(components, k)) 
		{
			components.erase(std::find(components.begin(), components.end(), k));
		}
	    if(isExist(components, g))
		{
			components.erase(std::find(components.begin(), components.end(), g));
		}

		woods.push_back({ k,g,minValue });
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
	fillMatrix(matrix, file,n);
	std::vector<std::vector<int>> woods; //spaning woods
	std::vector<int> components = {0,1,2,3,4,5,6,7,8,9}; 
	
	while (!components.empty()) 
	{
		crusak(matrix, woods, components);
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