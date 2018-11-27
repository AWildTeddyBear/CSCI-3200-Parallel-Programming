/*
	Compilation Instructions:
	g++ main.cpp -fopenmp -o out

	Run Instructions:
	./out

	Compiled with Ubuntu 18.04 with G++ (apt-get install g++)
	This was compiled with Windows Linux Subsystem using Ubuntu 18.04
*/

#include <iostream>
#include <cstring>

#define N 11
#define MAXI 2147483647

int final_path[N + 1];
bool visited[N];

int final_res = MAXI;

// Function Prototypes
void copyToFinal(int curr_path[]);
int firstMin(int adj[N][N], int i);
int secondMin(int adj[N][N], int i);
void TSPRec(int adj[N][N], int curr_bound, int curr_weight, int level, int curr_path[]);
void TSP(int adj[N][N]);

int main(void) {
	int adj[N][N] = {
		{MAXI,	7, 		98,		95, 	152, 	88, 	52,		51, 	91, 	51, 	81},
		{7,		MAXI,	95,		92,		151,	87,		58,		58,		88,		58,		79},
		{98, 	95,		MAXI,	4,		61,		185,	109,	108,	8,		109,	19},
		{95, 	92,		4,		MAXI,	65,		182,	114,	113,	5,		114,	16},
		{152, 	151,	61,		65,		MAXI,	241,	124,	123,	68,		124,	76},
		{88, 	87,		185,	182,	241,	MAXI,	114,	113,	177,	113,	167},
		{52, 	58,		109,	114,	124,	114,	MAXI,	1,		110,	2,		106},
		{51, 	58,		108,	113,	123,	113,	1,		MAXI,	109,	1,		105},
		{91, 	88,		8,		5,		68,		177,	110,	109,	MAXI,	110,	8},
		{51, 	58,		109,	114,	124,	113,	2,		1,		110,	MAXI,	105},
		{81, 	79,		19,		16,		76,		167,	106,	105,	8,		105,	MAXI}
	};

	TSP(adj);

	std::cout << "Total Miles: " << final_res << std::endl << std::endl;
	
	std::cout << "Path Taken:" << std::endl;
	for (int i = 0; i <= N; i++) {
		std::cout << "Vertex[" << final_path[i] << "]: ";
		switch (final_path[i]) {
			case 0: { std::cout << "AUM"; break; }
			case 1: { std::cout << "Capital Farmers Market"; break; }
			case 2: { std::cout << "Chai Market"; break; }
			case 3: { std::cout << "Super Oriental Market"; break; }
			case 4: { std::cout << "Rainbow City International Market"; break; }
			case 5: { std::cout << "Daleville Oriental Groceries"; break; }
			case 6: { std::cout << "Nyopi Asain Market"; break; }
			case 7: { std::cout << "Asain Supermarket"; break; }
			case 8: { std::cout << "Asia Market Birmingham"; break; }
			case 9: { std::cout << "Earth Fare"; break; }
			case 10: { std::cout << "Mi-Pueblo Supermarket"; break; }
		}
		std::cout << std::endl;
	}

	return 0;
}

void copyToFinal(int curr_path[]) {
    #pragma omp simd
	for (int i = 0; i < N; ++i) { final_path[i] = curr_path[i]; }

	final_path[N] = curr_path[0];
}

int firstMin(int adj[N][N], int i) {
	int min = MAXI;

    #pragma omp simd
	for (int k = 0; k < N; ++k) { if (adj[i][k] < min && i != k) { min = adj[i][k]; } }
	
	return min;
}

int secondMin(int adj[N][N], int i) {
	int first = MAXI, second = MAXI;

    #pragma omp for
	for (int j = 0; j < N; ++j) {
		if (adj[i][j] <= first) {
			second = first;
			first = adj[i][j];
		} else if (adj[i][j] <= second && adj[i][j] != first) {
			second = adj[i][j];
		}	
	}

	return second;
}

void TSPRec(int adj[N][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
	if (level == N) {
		if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
			int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];

			if (curr_res < final_res) {
				copyToFinal(curr_path);
				final_res = curr_res;
			}
		}
		return;
	}

    #pragma omp for
	for (int i = 0; i < N; ++i) {
		if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
			int temp = curr_bound;

			curr_weight += adj[curr_path[level - 1]][i];
			curr_bound -= ((level == 1) ? firstMin(adj, curr_path[level - 1]) : secondMin(adj, curr_path[level - 1])) + (firstMin(adj, i) / 2);

			if (curr_bound + curr_weight < final_res) {
				curr_path[level] = i;
				visited[i] = true;

				TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
			}

			curr_weight -= adj[curr_path[level - 1]][i];
			curr_bound = temp;

			memset(visited, false, sizeof(visited));

            #pragma omp simd
			for (int j = 0; j <= level - 1; ++j) { visited[curr_path[j]] = true; };
		}
	}
}

void TSP(int adj[N][N]) {
	int curr_path[N + 1];
	int curr_bound = 0;

	memset(curr_path, -1, sizeof(curr_path));
	memset(visited, 0, sizeof(curr_path));

    #pragma omp simd
	for (int i = 0; i < N; i++) { curr_bound += (firstMin(adj, i) + secondMin(adj, i)); }

	curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;
	visited[0] = true;
	curr_path[0] = 0;

	TSPRec(adj, curr_bound, 0, 1, curr_path);
}