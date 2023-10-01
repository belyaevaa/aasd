#include <iostream>
#include <vector>
#include<algorithm>
typedef std::pair<int, int> point; 


void sort(std::vector<point>& surface) 
{
	bool swapped = false;

	do
	{
		swapped = false;

		for (int i = 0; i < surface.size() - 1; i++)
		{
			if (surface[i].first > surface[i + 1].first)
			{
				std::swap(surface[i], surface[i + 1]);
				swapped = true;
			}
			else if (surface[i].first == surface[i + 1].first)
			{
				if (surface[i].second > surface[i + 1].second)
				{
					std::swap(surface[i], surface[i + 1]);
					swapped = true;
				}
			}
		}
	} while (swapped);
}


bool isLeftAngle(point& last, point& current, point& next) 
{
	return ((current.first - last.first) * (next.second - current.second) - 
		(current.second - last.second) * (next.first - current.first)) >= 0;
}

std::vector<point> build(std::vector<point>& surface) 
{	
	sort(surface);
	point left = surface.front();
	point right = surface.back();

	std::vector <point> hull = {left};
	int cnt = 0;
	for (int i = 1; surface[i]!=right; i++)
	{
		if (surface[i].second < right.second || surface[i].second < left.second) 
		{
			hull.push_back(surface[i]);
			cnt++;

			while (hull.size() >= 3 && !isLeftAngle(hull[cnt - 2], hull[cnt - 1], hull[cnt]))
			{
				hull.erase(hull.end() - 2);
				cnt--;
			}				
		}		
	}

	for (int j = surface.size()-1; surface[j] != left; j--)
	{
		if (surface[j].second >= right.second || surface[j].second >= left.second) 
		{
			hull.push_back(surface[j]);
			cnt++;

			while (hull.size() >= 3 && !isLeftAngle(hull[cnt - 2], hull[cnt - 1], hull[cnt]))
			{
				hull.erase(hull.end() - 2);
				cnt--;
			}
		}
	}

	if(hull.size() >= 3 && !isLeftAngle(hull[cnt - 1], hull[cnt], left)) 
	{
		hull.erase(hull.end() - 1);
		cnt--;
	}
	
	return hull;
}


void main()
{
	std::vector<point> surface = { {-3,-3}, {-3,-1}, {-3,2}, {-1,1}, {-1,4}, {3,4}, {2,2}, {5,3}, {4,1}, {1,-1}, {2,-2} };
	surface.clear();
	surface.push_back({0, 0}); 
	surface.push_back({ 0, 100 });
	surface.push_back({ 100, 0 });
	surface.push_back({ 1, 1 });
	surface.push_back({ 0, 5 });
	surface.push_back({ 0, 10 });
	surface.push_back({ 10, 0 });
	surface.push_back({ 99, 99 });


	auto result = build(surface);

	for (const auto& point : result)
	{
		std::cout << point.first << "\t" << point.second << std::endl;
	}
}