// TikTakToe.cpp
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "GameEvent.h"
#include "GameAI.h"

using namespace std;
using namespace sf;

int windowHeight = 720, windowWidth = 1280;

int main()
{
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tik Tac Toe");
    GameBoard board;
    vector<vector<GameBoard::ItemType>> matrix(3, vector<GameBoard::ItemType>(3, GameBoard::ItemType::NA));
    
    board.SetSize(500, 500);
    board.ShowGrid(true);
    board.CenteredAlign(true);
    board.Init(); 

    GameEvent gameEvent;
    gameEvent.Init(board);

    GameAI gameAi;

    int counter = 0;
    bool isUserTurn;
    while (window.isOpen()) {
        isUserTurn = false;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                pair<int, int> pos = gameEvent.GetBlock(event);
                if (pos.first != -1 && pos.second != -1) {
                    if (matrix[pos.first][pos.second] == GameBoard::ItemType::NA) {
                        counter++;
                        isUserTurn = true;
                        matrix[pos.first][pos.second] = GameBoard::ItemType::X;
                    }
                }
            }
        }

        if (!isUserTurn && counter % 2 == 1 && !gameEvent.GetIsCompleted()) {
            Clock clock;
            clock.restart();
            while (clock.getElapsedTime().asMilliseconds() != 1000); //wait 1s
            counter++;
            pair<int, int> block = gameAi.PredictNext(matrix);
            if (block.first != -1)
                matrix[block.first][block.second] = GameBoard::ItemType::O;
        }

        window.clear();
        board.DrawBoard(window);
        gameEvent.HoverEffect(window, event,matrix);
        board.DrawItems(window, matrix);
        board.DrawWinLine(window,gameEvent.isGameWin(matrix));
        window.display();

    }


}
