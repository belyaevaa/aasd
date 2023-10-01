#include <iostream>
#include <vector>
#include <fstream>
#include <string>
typedef std::vector<std::vector<int>> graph;

int fillMatrix(graph& matrix, std::ifstream& file,int n)
{
	if (file.is_open())
	{
		std::string line;
		int i = 0;

		while (std::getline(file, line)) // ��������� ������� ���������
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

bool hasOddDegree(graph& matrix) // ���������, ����� ������ ������� ����� ������ ������� (����� �� ������� �������� ������ ���-�� �����)
{
	bool result = true;

	for (int i = 0; i < matrix.size(); i++)
	{
		int cnt = 0;

		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				cnt++;
			}
		}

		if (cnt % 2 == 1)
		{
			result = false;
		}
	}

	return result;
}


void clean(std::vector<int>& v)
{
	for (auto& e : v)
	{
		e = 0;
	}
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


void dfs(graph& matrix, int s, int n,std::vector<bool>&used,std::vector<int>&d) // ��� �������� ����� �� ������� �������� ����
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


bool isExist(std::vector<std::pair<int, int>>& usedEdges, std::pair<int, int> edge)
{
	bool result = false;

	for (auto pair : usedEdges)
	{
		if (pair == edge || (pair.first == edge.second && pair.second == edge.first))
		{
			result = true;
		}
	}

	return result;
}


void eulearDfs(graph& matrix, int s, std::vector<std::pair<int, int>>& usedEdges, std::vector<std::pair<int, int>>& distEdges) // ������� dfs , ��� ���������� ����� � �������
{
	for (int i = 0; i < matrix[s].size(); i++)
	{
		std::pair <int, int> edge(s, i);

		if (matrix[s][i] != 0 && !isExist(usedEdges, edge))
		{
			distEdges.push_back(edge);
			usedEdges.push_back(edge);
			eulearDfs(matrix, i, usedEdges, distEdges);
		}
	}
}


bool checkComponents(graph& matrix, int n, std::vector<bool>& used, std::vector<int>&d) // �����, ����� ���� ���� ��� 1 ����������, ���� 2,  �� ������ �� ����� ����� (�.�. ������ �������)
{
	std::vector<std::vector<int>> allWays;
	bool result = true;
	int cnt = 0;
	
	while (!isAllUsed(used))
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (used[i] == false)
			{
				clean(d); //������ ��������� ������ ������ ����������, �� ���������� ����� ����������
				dfs(matrix, i, n, used, d);
				
				std::vector<int> temp; //������ ����������, ������ �� ���������� ����������.
	
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

	for (auto& way : allWays)
	{
		if (way.size() != 0)
		{
			cnt++;
		}
	}

	if (cnt >1)
	{
		result = false;
	}

	return result;
}


bool checkForEulearPath(graph& matrix, int n, std::vector<bool>& used, std::vector<int>& d) // ��������� ���� ����� ����� ������ � ��������� ����� (�������� �� ���)
{
	return checkComponents(matrix, n, used, d) && hasOddDegree(matrix);
}



void eulearLoop(graph& matrix, int n, std::vector<bool>& used, std::vector<int>& d) // ���������� �������� �����
{
	if (checkForEulearPath(matrix, n, used, d))
	{
		std::vector<std::pair<int, int>> distEdges;
		std::vector<std::pair<int, int>> usedEdges;

		eulearDfs(matrix, 0, usedEdges, distEdges);

		for (auto edge : distEdges)
		{
			std::cout << edge.first << "\t" << edge.second << std::endl;
		}
	}
	else
	{
		std::cout << "�� ��������� ����! ����� �� ���������!" << std::endl;
	}
}

void main()
{
	setlocale(LC_ALL, "rus");
	std::ifstream file;
	file.open("simplegraph.txt"); // ��� ������������ ������ �� �� ��������� �����, �������� �������� ����� �� doublegraph.txt ������� ��� ���� ������������� graph_image
	int n = countingTops(file); //���-�� ������ � �����
	file.close();
	file.open("simplegraph.txt"); // ��� ������������ ������ �� �� ��������� �����, �������� �������� ����� �� doublegraph.txt ������� ��� ���� ������������� graph_image
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file,n);  //���������� ������� ���������
	std::vector<bool> used(n);
	std::vector<int> d(n);
	eulearLoop(matrix, n, used, d);
}