#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day19a.cpp cpplite.cpp -o day19a.exe -std=c++1z
*/

struct blueprint {
	int ore_cost; // in ore
	int clay_cost; // in ore
	pair<int, int> obsidian_cost; // in ore and clay
	pair<int, int> geode_cost; // in ore and obsidian
};

struct game {
	int ore_robots = 1;
	int ore = 0;

	int clay_robots = 0;
	int clay = 0;

	int obsidian_robots = 0;
	int obsidian = 0;

	int geode_robots = 0;
	int geode = 0;

	string debug = "";
};

const int MINUTES = 24;

void blueprint_setup(vector<blueprint> &blueprints);
void print_blueprint(blueprint b);
void mine_materials(game &game);

void print_game(game game) {
	printf("game: \n");
	printf("  ore robots: %d, ore: %d\n", game.ore_robots, game.ore);
	printf("  clay robots: %d, clay: %d\n", game.clay_robots, game.clay);
	printf("  obsidian robots: %d, obsidian: %d\n", game.obsidian_robots, game.obsidian);
	printf("  geode robots: %d, geodes: %d\n\n", game.geode_robots, game.geode);
}

int top_geodes = 0;
int top_geode_robots = 0;
int top_obsidian = 0;
int top_obsidian_robots = 0;

void robot_options(blueprint blueprint, vector<game> games, vector<game> &new_games, game game1) {

	// buy geode
	if ((game1.ore >= blueprint.geode_cost.first && game1.obsidian >= blueprint.geode_cost.second
		&& game1.ore-game1.ore_robots < blueprint.geode_cost.first) || 
		(game1.ore >= blueprint.geode_cost.first && game1.obsidian >= blueprint.geode_cost.second
		&& game1.obsidian-game1.obsidian_robots < blueprint.geode_cost.second)) {
		game next_game = game1;

		// consume materials
		next_game.ore -= blueprint.geode_cost.first;
		next_game.obsidian -= blueprint.geode_cost.second;

		// mine materials
		mine_materials(next_game);

		// finish creating robot
		next_game.geode_robots++;
		new_games.push_back(next_game);
	}
	else {

	// buy obsidian
	if ((game1.ore >= blueprint.obsidian_cost.first && game1.clay >= blueprint.obsidian_cost.second
		&& game1.ore-game1.ore_robots < blueprint.obsidian_cost.first)
		|| 
		(game1.ore >= blueprint.obsidian_cost.first && game1.clay >= blueprint.obsidian_cost.second
		&& game1.clay-game1.clay_robots < blueprint.obsidian_cost.second)) {
		game next_game = game1;

		// consume materials
		next_game.ore -= blueprint.obsidian_cost.first;
		next_game.clay -= blueprint.obsidian_cost.second;

		// mine materials
		mine_materials(next_game);

		// finish creating robot
		next_game.obsidian_robots++;
		new_games.push_back(next_game);
	}
	else {

	// buy ore
	if (game1.ore >= blueprint.ore_cost && game1.ore-game1.ore_robots < blueprint.ore_cost) {
		int a = 5;
		game next_game = game1;

		// consume materials
		next_game.ore -= blueprint.ore_cost;

		// mine materials
		mine_materials(next_game);

		// finish creating robot
		next_game.ore_robots++;
		new_games.push_back(next_game);
	}

	// buy clay
	if (game1.ore >= blueprint.clay_cost && game1.ore-game1.ore_robots < blueprint.clay_cost) {
		game next_game = game1;

		// consume materials
		next_game.ore -= blueprint.clay_cost;

		// mine materials
		mine_materials(next_game);

		// finish creating robot
		next_game.clay_robots++;
		new_games.push_back(next_game);
	}


	

	mine_materials(game1);
	new_games.push_back(game1);
	}
	}
}

game max_geode_count(vector<game> games) {
	game ans;

	for (int i = 0; i < games.size(); ++i)
	{
		if (games[i].geode >= ans.geode){
			ans = games[i];
		}
	}

	return ans;
}


int largest_geodes(blueprint b) {
	game starter;
	vector<game> games;
	games.push_back(starter);

	for (int i = 1; i <= MINUTES; ++i)
	{
		vector<game> new_games;
		for (int k = 0; k < games.size(); ++k)
		{
			if (top_geode_robots > 0) {
				if (games[k].geode < top_geodes && games[k].geode_robots < top_geode_robots)
					continue;
			}
			else {
				if (games[k].obsidian < top_obsidian && games[k].obsidian_robots < top_obsidian)
					continue;
			}

			if (games[k].geode > top_geodes)
				top_geodes = games[k].geode;
			if (games[k].geode_robots > top_geode_robots)
				top_geode_robots = games[k].geode_robots;

			if (games[k].obsidian > top_obsidian)
				top_geodes = games[k].obsidian;
			if (games[k].obsidian_robots > top_obsidian_robots)
				top_obsidian_robots = games[k].obsidian_robots;

			robot_options(b, games, new_games, games[k]);
		}
		games = new_games;
		// printf("num games at turn %d is %d\n", i, games.size());
		// print_game(games[0]);
	}

	printf("LARGEST GEODE GAME:\n");
	print_game(max_geode_count(games));
	return max_geode_count(games).geode;
}


int main() {

	vector<string> input = slurp();
	vector<blueprint> blueprints;

	for (int i = 0; i < input.size()/32; ++i)
	{
		blueprint b;
		b.ore_cost = stoi(input[i*32 + 6]);
		b.clay_cost = stoi(input[i*32 + 12]);
		b.obsidian_cost = {stoi(input[i*32 + 18]), stoi(input[i*32 + 21])};
		b.geode_cost = {stoi(input[i*32 + 27]), stoi(input[i*32 + 30])};

		blueprints.push_back(b);
	}


	int answer = 0;
	for (int i = 1; i <= blueprints.size(); ++i)
	{
		cout << "starting game " << i << endl;
		top_geodes = 0;
		top_geode_robots = 0;
		top_obsidian = 0;
		top_geode_robots = 0;
		int l = largest_geodes(blueprints[i-1]);
		cout << "ANSWER FOR NUMBER " << i << " IS " << l << endl;
		answer += i*l;
	}
	printf("answer: %d\n", answer);

}





void mine_materials(game &game) {
	game.ore += game.ore_robots;
	game.clay += game.clay_robots;
	game.obsidian += game.obsidian_robots;
	game.geode += game.geode_robots;
}




void print_blueprint(blueprint b) {
	cout << "blueprint: " << endl;
	printf("  ore_cost: %d  clay_cost: %d  obsidian_cost: %d %d  geode_cost: %d %d \n", b.ore_cost, b.clay_cost, 
		b.obsidian_cost.first, b.obsidian_cost.second, b.geode_cost.first, b.geode_cost.second);
}

// void blueprint_setup(vector<blueprint> &blueprints) {

// 	for (int i = 0; i < input.size()/32; ++i)
// 	{
// 		blueprint b;
// 		b.ore_cost = stoi(input[i*32 + 6]);
// 		b.clay_cost = stoi(input[i*32 + 12]);
// 		b.obsidian_cost = {stoi(input[i*32 + 18]), stoi(input[i*32 + 21])};
// 		b.geode_cost = {stoi(input[i*32 + 27]), stoi(input[i*32 + 30])};

// 		blueprints.push_back(b);
// 	}
// }