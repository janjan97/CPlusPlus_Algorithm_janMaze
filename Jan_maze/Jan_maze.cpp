// Jan_maze.cpp : This 
#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board; //�����Ҵ絵���� ���⼱ ����
Player player;

int main()
{
	::srand(static_cast<unsigned>(time(nullptr))); // time�� �̿��� �����õ弳��
	board.init(25, &player);
	player.init(&board);

	uint64 lastTick = 0;
	while (true)
	{
#pragma region ������ ����
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick; //����ð�
		lastTick = currentTick;
#pragma endregion

		// �Է�

		// ����
		player.Update(deltaTick);

		// ������
		board.Render();


	}

}
