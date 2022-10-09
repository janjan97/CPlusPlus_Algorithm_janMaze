#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::init(Board* board)
{
	_pos = board->GetEnterPos();
	board = board;
}

void Player::Update(uint64 deltaTick)
{
}
