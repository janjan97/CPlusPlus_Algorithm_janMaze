#pragma once
#include "ConsoleHelper.h"

class Player;

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY, //갈수있는공간
	WALL, //갈수없는공간
};

class Board
{
public:
	Board();
	~Board();

	void			init(int32 size,Player* player);
	void			Render();

	void			GenerateMap();
	TileType		GetTileType(Pos pos); //어느위치에 어느타일이있는지 체크
	ConsoleColor	GetTileColor(Pos pos); //어느위치에 어느색상으로 그릴지

	Pos				GetEnterPos() { return Pos{ 1,1 }; }
	Pos				GetExitPos() { return Pos{_size - 2, _size - 2 }; }

private:
	TileType	_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE]={};
	int32		_size = 0;
	Player*		_player = nullptr;
};

