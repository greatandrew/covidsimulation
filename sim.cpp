#include <vector>
#include <random>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using u32 = unsigned int;

std::mt19937 Rand(time(0) * ((unsigned long long)new char));

constexpr u32 Rand_max = -1u;

constexpr long double eps = 1e-6;

constexpr int Max_x = 220, Max_y = 220;

constexpr int M = 10000;
constexpr int New_infect = 0;
// constexpr int New_infect = 50;

constexpr int Move_range = 2;

constexpr int Incubation_time = 3;
constexpr int Date = 10;

constexpr double Max_immune = 1.0;

constexpr double Dec_immune = 0.996156587;
constexpr double Virus_infection = 0.5;

inline double Rand_real_number () {
	return (double)Rand() / Rand_max;
}

int m;

struct Node {
	int x, y;
	int dx, dy;
	int kind;
	bool infected;
	int count_down;
	long double max_immune, immune;
} node[M];

std::vector <int> buc[Max_x][Max_y];

int new_infection;
int last_inf = -1;

std::pair <int, int> norm (int x, int y) {
	return {(x + Max_x) % Max_x, (y + Max_y) % Max_y};
}

void update_infect_data( Node &node ){
    node.kind = 1;
    node.infected = 1;
    node.count_down = Incubation_time + Date;
}

bool infect (int i, int j) {
    if (node[j].infected) {
        return 0;
    }

	if (!node[i].infected || node[i].count_down > Date) {
		return 0;
	}
	
	if (node[j].immune < Virus_infection) {
		new_infection ++ ;
        update_infect_data( node[j] );
		return 1;
	} else {
		return 0;
	}
}

void move (int i) {
	if (node[i].infected) {
		node[i].count_down -- ;
		
		if (node[i].count_down == 0) {
			node[i].kind = 2;
			node[i].infected = 0;
			node[i].immune = node[i].max_immune;
		}
	}
	
	if (node[i].immune > eps) {
		node[i].immune *= Dec_immune;
	}
	
	int tx = node[i].x, ty = node[i].y;
	int dx = int(Rand() % (2 * Move_range + 1)) - Move_range;
	int dy = int(Rand() % (2 * Move_range + 1)) - Move_range;
	auto [nx, ny] = norm(tx + dx, ty + dy);
	
	if (dx != 0 || dy != 0) {
		int flg = 0;
		auto &v = buc[tx][ty];
		for (int j = 0; j < (int)v.size(); ++ j) {
			if (v[j] == i) {
				v.erase(v.begin() + j);
				flg = 1;
				break;
			}
		}
		assert(flg);
		
		node[i].x = nx;
		node[i].y = ny;
		
		buc[nx][ny].push_back(i);
	}
}

void new_comer (int i, int knd) {
	int ox = node[i].x, oy = node[i].y, flg = 0;
	auto &v = buc[ox][oy];
	for (int j = 0; j < (int)v.size(); ++ j) {
		if (v[j] == i) {
			v.erase(v.begin() + j);
			flg = 1;
			break;
		}
	}
	assert(flg);
	
	const int a = Rand() % Max_x, b = Rand() % Max_y;
	node[i].x = a, node[i].y = b;
	node[i].kind = knd;
	node[i].infected = (knd == 1);
	node[i].count_down = (knd == 1 ? (Incubation_time + Date) / 2 : 0);
	node[i].max_immune = Max_immune - 0.1 * Rand_real_number();
	node[i].immune = (knd != 2 ? 0.0 : node[i].max_immune);
	buc[a][b].push_back(i);
}

void update (int x, int y) {
	const auto &v = buc[x][y];
	const int sz1 = (int)v.size();
	
	for (int i = 0; i < sz1 - 1; ++ i) {
		for (int j = i + 1; j < sz1; ++ j) {
			if (!infect(v[i], v[j])) {
				infect(v[j], v[i]);
			}
		}
	}
}

int main () {
	
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);
	
	m = 10000;
	
	for (int i = 0; i < m; ++ i) {
		const int a = Rand() % Max_x, b = Rand() % Max_y;
		node[i].x = a, node[i].y = b;
		node[i].kind = 0;
		node[i].infected = 0;
		node[i].count_down = 0;
		node[i].max_immune = Max_immune - 0.1 * Rand_real_number();
		node[i].immune = 0.0;
		buc[a][b].push_back(i);
	}
	
	new_infection = 1;
	update_infect_data(node[0]);
	std::cout << 0 << '\t' << new_infection << '\n';
	
	for (int t = 1; t <= 2000; ++ t) {
		new_infection = 0;
		
		for (int i = 0; i < New_infect; ++ i) {
			new_comer(i, 1);
		}
		for (int i = New_infect; i < m; ++ i) {
			move(i);
		}
		
		for (int x = 0; x < Max_x; ++ x) {
			for (int y = 0; y < Max_y; ++ y) {
				update(x, y);
			}
		}
        
        last_inf = new_infection;
        
		std::cout << t << '\t' << new_infection << '\n';
	}
	
	return 0;
}
