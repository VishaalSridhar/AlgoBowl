//Author: Vishaal Sridhar
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	int N, V;
	ifstream inFile;
	inFile.open("algo1.txt");

	if (!inFile) {
		cout << "Unable to open file points.txt";
		exit(1);   // call system to stop
	}

	inFile >> N >> V; //stores the first row which is the number of points and vertices

	int costs[N][N] = { 0 }; //creates a matrix of zeros
	int pt1;
	int pt2;
	int cost;

	while (inFile >> pt1 >> pt2 >> cost) {
		pt1--;
		pt2--;
		costs[pt1][pt2] = cost;
		costs[pt2][pt1] = cost;
	}

	inFile.close();

	int group1[N / 2];
	int group2[N - sizeof(group1)];

	int tempGroup1[N / 2];
	int tempGroup2[N - sizeof(group1)];

	for (int i = 0; i<N; i++) {
		if (i < N / 2) {
			group1[i] = i++;
			tempGroup1[i] = i++;
		}
		else {
			group2[i - N / 2] = i++;
			tempGroup2[i - N / 2] = i++;
		}
	}

	int prevCost = 0;
	for (int i = 0; i<sizeof(group1); i++) {
		for (int j = 0; j<sizeof(group2); j++) {
			prevCost = prevCost + costs[group1[i] - 1][group2[j] - 1];
		}
	}


	int nextCost = -1;
	int externalPoint;
	int internalPoint;

	while (prevCost>nextCost) {
		if (nextCost != -1) {
			prevCost = nextCost;
			group1[externalPoint] = tempGroup1[externalPoint];
			group2[internalPoint] = tempGroup2[internalPoint];
		}

		int externalCost = 0;
		externalPoint = 0;

		for (int i = 0; i < N; i++) {
			int tempCost = 0;
			for (int j = 0; j < N; j++) {
				tempCost = tempCost + costs[i][j];
			}
			if (externalCost < tempCost) {
				externalCost = tempCost;
				externalPoint = i + 1;
			}
		}

		bool externalGroup1 = false;

		for (int i = 0; i < sizeof(group1); i++) {
			if (group1[i] == externalPoint) {
				externalGroup1 = true;
				externalPoint = i;
			}
		}

		int internalCost = -1;
		internalPoint = 0;

		if (externalGroup1) {
			for (int i = 0; i < sizeof(group2); i++) {
				int tempCost = 0;
				for (int j = 0; j < sizeof(group2); j++) {
					tempCost = tempCost + costs[group2[i] - 1][group2[j] - 1];
				}
				if (internalCost > tempCost || internalCost == -1) {
					internalCost = tempCost;
					internalPoint = i;
				}
			}

		}
		else {
			for (int i = 0; i < sizeof(group1); i++) {
				int tempCost = 0;
				for (int j = 0; j < sizeof(group1); j++) {
					tempCost = tempCost + costs[group1[i] - 1][group1[j] - 1];
				}
				if (internalCost > tempCost || internalCost == -1) {
					internalCost = tempCost;
					internalPoint = i + 1;
				}
			}

			for (int i = 0; i < sizeof(group2); i++) {
				if (group2[i] == externalPoint) {
					externalPoint = i;
				}
			}
		}
		tempGroup1[externalPoint] = group2[internalPoint];
		tempGroup2[internalPoint] = group1[externalPoint];

		for (int i = 0; i<sizeof(group1); i++) {
			for (int j = 0; j<sizeof(group2); j++) {
				nextCost = nextCost + costs[tempGroup1[i] - 1][tempGroup2[j] - 1];
			}
		}
	}

	int finalCost;

	for (int i = 0; i<sizeof(group1); i++) {
		for (int j = 0; j<sizeof(group2); j++) {
			finalCost = finalCost + costs[group1[i] - 1][group2[j] - 1];
		}
	}

	cout << finalCost << endl;
	for (int i = 0; i < sizeof(group1); i++) {
		cout << group1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < sizeof(group2); i++) {
		cout << group2[i] << " ";
	}
	cout << endl << endl;

}