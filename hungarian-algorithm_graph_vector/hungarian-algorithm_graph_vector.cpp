#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

const int inf = numeric_limits<int>::max();

int main()
{
	setlocale(LC_ALL, "Russian");
	double absolut;
	srand(time(0));
	cout << "Введите размер матрицы: ";
	int n;
	cin >> n;
	vector<vector<int>> x(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) x[i].push_back((rand() % 40) + 10);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << x[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	vector<vector<double>> y(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) y[i].push_back(1.0 / x[i][j]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << y[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	int height = y.size(), width = y[0].size();
	vector<double> u(height, 0), v(width, 0);
	vector<double> markIndices(width, -1);
	for (int i = 0; i < height; i++) {
		vector<double> links(width, -1);
		vector<double> mins(width, inf);
		vector<double> visited(width, 0);
		int markedI = i, markedJ = -1, j;
		while (markedI != -1) {
			j = -1;
			for (int j1 = 0; j1 < width; j1++)
				if (!visited[j1]) {
					if (y[markedI][j1] - u[markedI] - v[j1] < mins[j1]) {
						absolut = abs(y[markedI][j1] - u[markedI]);
						links[j1] = markedJ;
						mins[j1] = absolut - v[j1];
					}
					if (j == -1 || mins[j1] < mins[j]) j = j1;
				}
			double delta = mins[j];
			for (int j1 = 0; j1 < width; j1++)
				if (visited[j1]) {
					u[markIndices[j1]] += delta;
					v[j1] -= delta;
				}
				else mins[j1] -= delta;
			u[i] += delta;
			visited[j] = 1;
			markedJ = j;
			markedI = markIndices[j];
		}
		for (; links[j] != -1; j = links[j]) markIndices[j] = markIndices[links[j]];
		markIndices[j] = i;
	}
	vector<pair<int, int>> result;
	for (int j = 0; j < width; j++) if (markIndices[j] != -1) result.push_back(pair<int, int>(markIndices[j], j));
	for (int i = 0; i < n; i++) cout << result[i].first + 1 << " -> " << result[i].second + 1 << endl;


	//пункт Б
	/*
	#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

const int inf = numeric_limits<int>::max();

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	cout << "Введите размер матрицы: ";
	int n;
	cin >> n;
	vector<vector<int>> x(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) x[i].push_back((rand() % 40) + 10);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << x[i][j] << " ";
		cout << endl;
	}

	cout << endl;
	int height = x.size(), width = x[0].size();
	vector<int> u(height, 0), v(width, 0);
	vector<int> markIndices(width, -1);
	for (int i = 0; i < height; i++) {
		vector<int> links(width, -1);
		vector<int> maxs(width, inf);
		vector<int> visited(width, 0);
		int markedI = i, markedJ = -1, j;
		while (markedI != -1) {
			j = -1;
			for (int j1 = 0; j1 < width; j1++)
				if (!visited[j1]) {
					if (x[markedI][j1] - u[markedI] - v[j1] < maxs[j1]) {
						maxs[j1] = x[markedI][j1] - u[markedI] - v[j1];
						links[j1] = markedJ;
					}
					if (j == -1 || maxs[j1] > maxs[j]) j = j1;
				}
			int delta = maxs[j];
			for (int j1 = 0; j1 < width; j1++)
				if (visited[j1]) {
					u[markIndices[j1]] += delta;
					v[j1] -= delta;
				}
				else maxs[j1] -= delta;
			u[i] += delta;
			visited[j] = 1;
			markedJ = j;
			markedI = markIndices[j];
		}
		for (; links[j] != -1; j = links[j]) markIndices[j] = markIndices[links[j]];
		markIndices[j] = i;
	}

	vector<pair<int, int>> result;
	for (int j = 0; j < width; j++) if (markIndices[j] != -1) result.push_back(pair<int, int>(markIndices[j], j));
	for (int i = 0; i < n; i++) cout << result[i].first+1 << " -> " << result[i].second+1 << endl;
}
	*/
}