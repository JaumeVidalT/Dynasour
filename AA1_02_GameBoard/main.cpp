
#include "cell.h"
#include "player.h"
#include <iostream>
#include <fstream>
std::ifstream OpenFile(std::string path)
{
	std::ifstream outputFile(path);
	try
	{
		if (!outputFile.is_open())
		{
			throw std::exception("unable to open file");
		}
		return outputFile;
	}
	catch (const std::exception c)
	{
		std::cout<< "Error" << c.what() << std::endl;
	} 	
}
Cell** InitializeBoard(Player* player, int width, int height)
{
	Cell** board;
	int realBoardSize = (width - 1) * (height - 1);
	int MaxGems=(25.0f/100.0f)*(float)realBoardSize; 
	int MaxSpikes=(15.0f/100.0f) *(float)realBoardSize;
	int gems=0;
	int spikes=0;
	board = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new Cell[width];
		for (int j = 0; j < width; j++)
		{
			char type = 'N';
			if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
			{	
				int randomNumber = rand() % 3;
				switch (randomNumber)
				{
				case 0:
					if (gems < MaxGems) { type = 'G'; gems++; }
					break;
				case 1:
					if (spikes < MaxSpikes){ type = 'S'; spikes++;}		
					break;
				}
			}
			else
			{
				type = 'X';
			}
			board[i][j] = Cell(type);
		}
	}
	board[player->position.Y][player->position.X]= Cell(player->GetName());
	return board;
}
void DrawBoard(Cell** board, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << board[i][j].GetType();			
		}
		std::cout<<std::endl;
	}
}
bool ExistGem(Vector2 pos, PlayerMovement movement,Cell** board)
{
	switch (movement)
	{
	case PlayerMovement::UP:
		pos.Y--;
		break;
	case PlayerMovement::DOWN:
		pos.Y++;
		break;
	case PlayerMovement::LEFT:
		pos.X--;
		break;
	case PlayerMovement::RIGHT:
		pos.X++;
		break;
	}
	return board[pos.Y][pos.X].GetType() == 'G';

}
bool CheckMovement(Cell**board, Vector2 pos)
{
	return board[pos.Y][pos.X].GetType() != 'X';
}
void MovePlayer(Player* player, Cell** board)
{
	int choice;
	PlayerMovement movement;
	Vector2 newPos;
	do {
		newPos = player->position;
		std::cout << "Elige movimiento: 0.Up 1.Down 2.Left 3.Right" << std::endl;
		std::cin >> choice;
		board[newPos.Y][newPos.X].SetType('N');
		switch (choice)
		{
		case 0:
			movement = PlayerMovement::UP;
			newPos.Y--;
			break;
		case 1:
			movement = PlayerMovement::DOWN;
			newPos.Y++;
			break;
		case 2:
			movement = PlayerMovement::LEFT;
			newPos.X--;
			break;
		case 3:
			movement = PlayerMovement::RIGHT;
			newPos.X++;
			break;
		default:
			break;
		}
	} while (!CheckMovement(board,newPos));	
	if (ExistGem(newPos, movement, board))
	{
		player->AddScore();
	}
	if (board[newPos.Y][newPos.X].GetType() != 'S')
	{
		board[newPos.Y][newPos.X].SetType('J');
		player->SetPosition(newPos);
	}

}
bool GameOver(Cell** board, int width, int height)
{
	bool playerAlive = false;
	bool stillGems = false;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j].GetType() == 'J')
			{
				playerAlive = true;
			}
			else if (board[i][j].GetType() == 'G')
			{
				stillGems = true;
			}
		}
	}
	return playerAlive && stillGems;
}
void DestroyBoard(Cell**& board, int height)
{
	for (int i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	board = nullptr;
}
void main()
{
	srand(time(NULL));

	int boardWidth;
	int boardHeight;
	std::ifstream boardFile = OpenFile("Board.txt");
	boardFile >> boardHeight >> boardWidth;

	int playerX = rand() % (boardWidth - 2) + 1;
	int playerY = rand() % (boardHeight - 2) + 1;
	Player* player= new Player(Vector2(playerX,playerY));
	Cell** board = InitializeBoard(player,boardWidth, boardHeight);
	while (GameOver(board, boardWidth, boardHeight))
	{
		DrawBoard(board, boardWidth, boardHeight);
		MovePlayer(player,board);
	}
	DestroyBoard(board, boardHeight);

}