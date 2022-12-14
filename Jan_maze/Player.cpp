#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;  //임시포지션

	_path.clear(); //init두번호출 방지
	_path.push_back(pos); //현재위치 

	//목적지 도착하기 전까지 실행
	Pos dest = board->GetExitPos();

	Pos front[4] = // y, x
	{
		Pos { -1, 0},	//UP  배열좌표
		Pos { 0, -1},	//LEFT
		Pos { 1, 0},	//DOWN
		Pos { 0, 1},	//RIGHT
	};
	
	while (pos != dest)
	{
		// 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir])) //현재위치 + 앞으로
		{
			// 오른쪽 방향으로 90도 회전.
			_dir = newDir;
			// 앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}

		// 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인.
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT;

			/*
			switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;
			}
			*/
		}
	}
}

void Player::Update(uint64 deltaTick) //각프레임마다 경과시간
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK) //MOVE_TICK보다 크면(100ms가 지났다)
	{
		_sumTick = 0; //다시 100ms를 세기위해 0으로 초기화

		_pos = _path[_pathIndex];
		_pathIndex++; //다음좌표
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}
