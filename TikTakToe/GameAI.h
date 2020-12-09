#pragma once
#include "GameBoard.h"

class GameAI
{
public:
	enum class GameMode { EASY, MEDUIM, HARD };
	GameAI() {
		gameMode = GameMode::EASY;
	}
	void SetGameMode(GameMode mode);
	pair<int,int> PredictNext(vector<vector<GameBoard::ItemType>>& matrix);
private:
	GameMode gameMode;
};

