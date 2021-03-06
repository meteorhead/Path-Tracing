// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <complex>
#include <algorithm>
#include <iterator>
#include <set>
#include <sstream>
#include <cstdint>
#include <string>
#include <complex>
#include <iomanip>
#include <time.h> 



using namespace std;

void polarized(vector<pair<int, int> > & vec)
{
	pair<int, int> norm(abs(vec.front().first), abs(vec.front().second));
	for (size_t i = 0; i < vec.size(); ++i)
	{
		vec[i].first += norm.first;
		vec[i].second += norm.second;
	}

}

void translate(vector<pair<int, int> > & vec, int xmin, int ymin)
{

	if (!(xmin))
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			++(vec[i].first);
		}

	}
	if (!(ymin))
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			++(vec[i].second);
		}
	}
	if (xmin)
	{

		for (size_t i = 0; i < vec.size(); ++i)
		{
			vec[i].first -= xmin + 1;
		}

	}
	if (ymin)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			vec[i].second -= (ymin - 1);
		}

	}
}

int maxSecond(vector<pair<int, int> >::const_iterator begin, vector<pair<int, int> >::const_iterator end)
{

	int max = begin->second;
	while (begin != end)
	{

		if (max < begin->second)
			max = begin->second;
		++begin;
	}
	return max;
}

int minSecond(vector<pair<int, int> >::const_iterator begin, vector<pair<int, int> >::const_iterator end)
{

	int min = begin->second;
	while (begin != end)
	{

		if (min > begin->second)
			min = begin->second;
		++begin;
	}
	return min;
}


int main(int argc, char * argv[])
{

	vector<string> moves{"down","down","left","left","up","up","up","left","left"};
	vector<pair<int, int> > coordinates;


	string oneMove;
	/* while (getline(cin, oneMove))
	{
		moves.push_back(oneMove);
	} */

	int j = 0, k = 0;

	coordinates.push_back(pair<int, int>(j, k));


	for (size_t i = 0; i < moves.size(); ++i)
	{
		if (moves[i] == "down")
		{
			++j;
			coordinates.push_back(pair<int, int>(j, k));
		}
		if (moves[i] == "up")
		{
			--j;
			coordinates.push_back(pair<int, int>(j, k));
		}
		if (moves[i] == "right")

		{
			++k;
			coordinates.push_back(pair<int, int>(j, k));
		}
		if (moves[i] == "left")
		{
			--k;
			coordinates.push_back(pair<int, int>(j, k));
		}

	}

	auto start = coordinates.front();
	auto end = coordinates.back();
	sort(coordinates.begin(), coordinates.end());
	auto newStart = find(coordinates.begin(), coordinates.end(), start);
	auto newEnd = find(coordinates.begin(), coordinates.end(), end);
	polarized(coordinates);
	auto x_max = std::max_element(coordinates.begin(), coordinates.end())->first;
	auto x_min = (std::min_element(coordinates.begin(), coordinates.end()))->first;
	auto rows = x_max - x_min + 1;

	auto y_max = maxSecond(coordinates.begin(), coordinates.end());
	auto y_min = minSecond(coordinates.begin(), coordinates.end());
	auto cols = y_max - y_min + 1;

	translate(coordinates, x_min, y_min);

	int width = cols + 2, length = rows + 2;

	char **map = new char*[length];
	{
		for (int i = 0; i < length; i++)
		{
			map[i] = new char[width];
		}
	}

	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if ((i == 0) || (i == length - 1) || (j == 0) || (j == width - 1))
			{

				map[i][j] = '#';
				continue;
			}
			else
				map[i][j] = ' ';

		}

	}

	for (size_t i = 0; i < coordinates.size(); ++i)
	{
		map[coordinates[i].first][coordinates[i].second] = '*';
	}

	map[newStart->first][newStart->second] = 'S';
	map[newEnd->first][newEnd->second] = 'E';

	for (int l = 0; l < length; ++l)
	{
		for (int k = 0; k < width; ++k)
		{
			cout << map[l][k];
		}
		cout << endl;
	}


	for (int i = 0; i < length; ++i)
	{
		delete[] map[i];
	}
	delete[] map;

	//printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	return 0;
}