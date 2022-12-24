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

const int MINUTES = 32;

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

void add_game(map<vector<int>, game> &new_games, game next_game) {
	if (new_games[{next_game.ore_robots, next_game.clay_robots, next_game.obsidian_robots, next_game.geode_robots}].geode <= next_game.geode) {
		new_games[{next_game.ore_robots, next_game.clay_robots, next_game.obsidian_robots, next_game.geode_robots}] = next_game;
	}
	if (new_games[{next_game.ore_robots, next_game.clay_robots, next_game.obsidian_robots, next_game.geode_robots}].obsidian <= next_game.obsidian) {
		new_games[{next_game.ore_robots, next_game.clay_robots, next_game.obsidian_robots, next_game.geode_robots}] = next_game;
	}
}

void robot_options(blueprint blueprint, map<vector<int>, game> games, map<vector<int>, game> &new_games, game game1) {

	// buy geode
	if ((game1.ore >= blueprint.geode_cost.first && game1.obsidian >= blueprint.geode_cost.second
		&& game1.ore-game1.ore_robots < blueprint.geode_cost.first) || 
		(game1.ore >= blueprint.geode_cost.first && game1.obsidian >= blueprint.geode_cost.second
		&& game1.obsidian-game1.obsidian_robots < blueprint.geode_cost.second)) {
	//if (game1.ore >= blueprint.geode_cost.first && game1.obsidian >= blueprint.geode_cost.second) {
		game next_game = game1;

		// consume materials
		next_game.ore -= blueprint.geode_cost.first;
		next_game.obsidian -= blueprint.geode_cost.second;

		// mine materials
		mine_materials(next_game);

		// finish creating robot
		next_game.geode_robots++;
		add_game(new_games, next_game);
	}
	//else {

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
		add_game(new_games, next_game);
	}

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
		add_game(new_games, next_game);
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
		add_game(new_games, next_game);
	}


	
	mine_materials(game1);
	add_game(new_games, game1);
	//}
}

game max_geode_count(map<vector<int>, game> games) {
	game ans;

	for (auto & [robot_nums, game1] : games)
	{
		if (game1.geode >= ans.geode){
			ans = game1;
		}
	}

	return ans;
}


int largest_geodes(blueprint b) {
	game starter;
	//vector<game> games;
	map<vector<int>, game> games;
	games[{starter.ore_robots, starter.clay_robots, starter.obsidian_robots, starter.geode_robots}] = starter;

	for (int i = 1; i <= MINUTES; ++i)
	{
		map<vector<int>, game> new_games;
		if (i%4 == 0)
			cout << "minutes: " << i << "  size: " << games.size() << endl;
		for (auto & [robot_nums, game1] : games)
		{
			// if (top_geode_robots > 0) {
			// 	if (games[k].geode < top_geodes && games[k].geode_robots < top_geode_robots)
			// 		continue;
			// }
			// else {
			// 	if (games[k].obsidian < top_obsidian && games[k].obsidian_robots < top_obsidian)
			// 		continue;
			// }

			// if (games[k].geode > top_geodes)
			// 	top_geodes = games[k].geode;
			// if (games[k].geode_robots > top_geode_robots)
			// 	top_geode_robots = games[k].geode_robots;

			// if (games[k].obsidian > top_obsidian)
			// 	top_geodes = games[k].obsidian;
			// if (games[k].obsidian_robots > top_obsidian_robots)
			// 	top_obsidian_robots = games[k].obsidian_robots;

			robot_options(b, games, new_games, game1);
		}
		games = new_games;
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


	/*
	LMAO ok so on the test input I was getting different answers for using map trimmming strategy
	vs using vector trimming strategy (what I did for part a, which runs suprisingly fast (<1sec)
	with 32 mins) so I just decided to combine my highest geode answers from both strategies for
	part b and it worked lolololololol
	
	Ok ok I will have to come back and do this one properly, probably still do map trimming but just
	a little differently, or fix vector trimming from part a to not undershoot sometimes
	*/

	int answer = 1;
	for (int i = 1; i <= 3; ++i)
	{
		cout << "starting game " << i << endl;
		top_geodes = 0;
		top_geode_robots = 0;
		top_obsidian = 0;
		top_geode_robots = 0;
		int l = largest_geodes(blueprints[i-1]);
		answer *= l;
		cout << "ANSWER FOR NUMBER " << i << "  " << l << endl;
	}
	printf("answer: %d\n", answer);

	//5814

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