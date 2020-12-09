#include "GameEvent.h"
#include<iostream>
void GameEvent::Init(GameBoard &board)
{
	float verticalSegment = board.GetHeight() / 3.0f, horizontalSegment = board.GetWidth() / 3.0f;
	Vector2f boardPosition = board.getPosition();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			blocks[i][j] = make_pair(Vector2f(boardPosition.x + horizontalSegment * j,boardPosition.y + verticalSegment * i),Vector2f(boardPosition.x + horizontalSegment * (j+1), boardPosition.y + verticalSegment * (i+1)));
		}
	}
}

void GameEvent::HoverEffect(RenderWindow& window, Event event, vector<vector<GameBoard::ItemType>>& matrix,Color color)
{
	float x = event.mouseMove.x, y = event.mouseMove.y;
	if (isCompleted) return;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((matrix[i][j] == GameBoard::ItemType::NA) && blocks[i][j].first.x <= x && x < blocks[i][j].second.x && blocks[i][j].first.y <= y && y < blocks[i][j].second.y) {
				RectangleShape shape(Vector2f(blocks[i][j].second.x - blocks[i][j].first.x, blocks[i][j].second.y - blocks[i][j].first.y));
				shape.setPosition(blocks[i][j].first);
				shape.setFillColor(color);
				window.draw(shape);
				break;
			}
		}
	}
}

pair<int, int> GameEvent::GetBlock(Event event)
{
	if (isCompleted) return { -1,-1 };
	float x = event.mouseButton.x;
	float y = event.mouseButton.y;
	int row = -1, col = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (blocks[i][j].first.x <= x && x < blocks[i][j].second.x && blocks[i][j].first.y <= y && y < blocks[i][j].second.y) {
				row = i;
				col = j;
				break;
			}
		}
	}
	return pair<int, int>({row,col});
}

pair<pair<int, int>, pair<int, int>> GameEvent::isGameWin(vector<vector<GameBoard::ItemType>>& matrix)
{
	for (int i = 0; i < 3; i++) {
		bool colWin = true;   //col check
		bool rowWin = true;   //row check
		for (int j = 1; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA || matrix[i][j - 1] == GameBoard::ItemType::NA || matrix[i][j] != matrix[i][j - 1])
				rowWin = false;
			if (matrix[j][i] == GameBoard::ItemType::NA || matrix[j - 1][i] == GameBoard::ItemType::NA || matrix[j][i] != matrix[j - 1][i])
				colWin = false;

		}
		if (rowWin) {
			isCompleted = true;
			return { {i,0},{i,2} };
		}

		if (colWin) {
			isCompleted = true;
			return { {0,i},{2,i} };
		}
	}

	bool diag1Win = true;
	bool diag2Win = true;
	for (int i = 1; i < 3; i++) {
		if (matrix[i][i] == GameBoard::ItemType::NA || matrix[i - 1][i - 1] == GameBoard::ItemType::NA || matrix[i][i] != matrix[i - 1][i - 1])
			diag1Win = false;

		if (matrix[i][2 - i] == GameBoard::ItemType::NA || matrix[i - 1][3 - i] == GameBoard::ItemType::NA || matrix[i][2 - i] != matrix[i - 1][3 - i])
			diag2Win = false;
	}

	if (diag1Win) {
		isCompleted = true;
		return { {0,0},{2,2} };
	}  

	if (diag2Win) {
		isCompleted = true;
		return { {0,2},{2,0} };
	}

	return { {-1,-1},{-1,-1} };
}

bool GameEvent::GetIsCompleted()
{
	return isCompleted;
}
