// Jan_maze.cpp : This 
#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board; //동적할당도가능 여기선 전역
Player player;

int main()
{
	::srand(static_cast<unsigned>(time(nullptr))); // time을 이용한 랜덤시드설정
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;
	while (true)
	{
		
#pragma region 프레임관리
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick; //경과시간
		lastTick = currentTick;
#pragma endregion

		// 입력

		// 로직
		player.Update(deltaTick);

		// 렌더링
		board.Render();


	}

}
