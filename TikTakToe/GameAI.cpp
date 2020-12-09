#include "GameAI.h"

void GameAI::SetGameMode(GameMode mode)
{
	this->gameMode = mode;
}

pair<int, int> GameAI::PredictNext(vector<vector<GameBoard::ItemType>>& matrix)
{
	vector<pair<int, int>> res;
	res.reserve(9);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA)
				res.emplace_back(i, j);
		}
	}
	time_t t = time(0);
	srand(t);
	if (res.size() == 0) return { -1,-1 };
	int val = rand() % res.size();
	return res[val];
}
