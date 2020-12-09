#pragma once
#include "GameBoard.h"
class GameEvent
{

public:
	GameEvent() {
		isCompleted = false;
	}
	void Init(GameBoard &board);
	void HoverEffect(RenderWindow& window, Event event, vector<vector<GameBoard::ItemType>>& matrix,Color color = Color(0,210,12,30));
	pair<int,int> GetBlock(Event event);
	pair<pair<int, int>, pair<int, int>> isGameWin(vector<vector<GameBoard::ItemType>>& matrix);
	bool GetIsCompleted();
private:
	pair<Vector2f, Vector2f> blocks[3][3];
	bool isCompleted;
};

