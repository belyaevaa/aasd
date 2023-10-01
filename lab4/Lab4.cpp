#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<int>> graph; 

int fillMatrix(graph& matrix, std::ifstream& file, int n)
{
	if (file.is_open())
	{
		file.seekg(0); 
		std::string line;
		int i = 0;

		while (std::getline(file, line)) 
		{
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = line.at(j) - 48;
			}

			i++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return matrix.size();
}


bool isAllUsed(std::vector<bool>& tops)
{
	bool result = true;

	for (const auto t : tops)
	{
		if (t == false)
		{
			result = false;
		}
	}

	return result;
}


void dfs(graph& matrix, int s, int n,std::vector<bool>&used,std::vector<int>&d)
{
	if (d.empty())
	{
		d[s]++;
		used[s] = true;
	}

	for (int i = 0; i < matrix[s].size(); i++)
	{
		if (matrix[s][i]!=0 && used[i] == false)
		{
			d[i] = d[s] + 1;
			used[i] = true;
			dfs(matrix, i, n,used,d);
		}
	}
}


int countingTops(std::ifstream& file)
{
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		return line.size();
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
		return -1;
	}
}

void print(std::vector<int> v)
{
	for (const auto c : v)
	{
		std::cout << c << "\t";
	}

	std::cout << "\n";
}


void clean(std::vector<int>& v)
{
	for (auto& e : v)
	{
		e = 0;
	}
}


void main()
{

	std::ifstream file;
	file.open("doublegraph.txt");
	int n = countingTops(file); 
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n); 
	std::vector<bool> used(n);
	std::vector<int> d(n);

	std::vector<std::vector<int>> allWays;

	while (!isAllUsed(used)) 
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (used[i] == false)
			{
				clean(d); 
				dfs(matrix, i, n, used, d);
				
				std::vector<int> temp; 

				for (int i = 0; i < d.size(); i++)
				{
					if (d[i] != 0)
					{
						temp.push_back(i);
					}
				}

				allWays.push_back(temp); 
			}			
		}
	}
	
	for (const auto& v : allWays)
	{
		print(v);
	}
	
}