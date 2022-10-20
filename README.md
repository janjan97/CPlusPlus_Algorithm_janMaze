# 미로 알고리즘 (오른손의 법칙)
Maze Algorithm (right-hand rule) Study
+ Language : C++ 
+ Tools : Visual Studio


![maze_right_hand](https://user-images.githubusercontent.com/66328790/196883001-d13c25ea-8a71-484f-a517-ded30dc58643.gif)

![미로 시작(플레이어 시작위치,출구)](https://user-images.githubusercontent.com/66328790/194760599-b1984fbe-75f5-467c-a93f-22e9a53770f5.jpg)


미로를 탈출하기 위해 오른손의 법칙을 사용하여 탈출을 해보고자 한다.

이 방식으로 `Player`를 움직인다고 하면,
1. `Player`가 현재 바라보는 뱡향을 기준으로 오른쪽으로 갈 수 있는지 확인한다.
2. `Player`가 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인한다.
3. `1`, `2`의 상황이 적용되지 않으면(`else`) 왼쪽 방향으로 90도 회전한다.

---

### 왼쪽 방향으로 회전하기

가장 간단한 세번째 상황인 왼쪽으로 90도 회전하는 부분을 구현해보면

![maze1](https://user-images.githubusercontent.com/66328790/196882425-9a1decec-e337-44fc-a51b-e908ac630484.png)
![maze2](https://user-images.githubusercontent.com/66328790/196882492-e5e263f9-f9a4-4235-909d-45169ec9a72a.png)

`switch`문을 사용하여 `Player`의 방향(`_dir`)이 위, 아래, 좌, 우에 맞춰서 방향을 바꿔줄 수 있다.
하지만 `switch`문을 사용하지 않고 더 간결하게 표현할 수 있다.

`pch.h`에서 `Player`의 방향(`Dir`)을 `enum`을 사용하여 만들었는데, 방향을 위, 아래, 좌, 우가 아닌
시계 방향이나 시계 반대 방향으로 표현하였다. 이런 방식의 규칙있는 표현이 좋다.
`Player`의 아래 방향(`DIR_DOWN = 2`)일 때 왼쪽으로 90도 회전을 하게되면  오른쪽(`DIR_RIGHT = 3`)이 된다. 
즉 왼쪽으로 회전한다는 것은 `Player`의 방향(`_dir`) 값을 `+1` 한다는 뜻이고, 오른쪽으로 회전한다는 것은 방향 값을 `-1`한다는 것이다.

![maze3](https://user-images.githubusercontent.com/66328790/196882552-6665b099-ac76-41da-beeb-4fb57731b145.png)

왼쪽으로 회전하는 `Player`의 방향(`_dir`)은 현재 방향에 `+1`을 한 값이고, `DIR_COUNT`로 나머지 연산을 하여 `Player`가 오른쪽 방향(`DIR_RIGHT`)일 때 `3`을 넘기 때문에 위 방향(`DIR_UP = 0`)을 표현해준다. 

---

### 오른쪽으로 갈 수 있다면, 오른쪽으로 회전하고 앞으로 가기

```cpp
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
```

앞서 왼쪽으로 회전했던 방식을 똑같이 적용하여 `Player`기준 오른쪽 방향은(`newDir`)
`(_dir - 1 + DIR_COUNT) % DIR_COUNT;`이 된다.

여기서 `Player`가 이동할 수 있는지라는 것은 다른 상황들(2. 앞으로 전진할 수 있는지 등)에서도 
쓰이기 때문에 `CanGo()`라는 별도의 함수로 따로 빼내어 준다.

![maze4](https://user-images.githubusercontent.com/66328790/196882556-9e76897d-4e75-4018-8e97-79ec3dd54e5f.png)

`bool`타입으로 `CanGo()`를 생성한다. 타일 종류(`TileType`)를 체크하고 보드(`_board`)에 `GetTileType(pos)`의 포지션(`pos`)을 체크해서 타일 종류(`TileType`)을 추출한 다음에 
내가 갈 수 있는 구역(`TileType::EMPTY`)일 때를 `return`해준다.

![maze5](https://user-images.githubusercontent.com/66328790/196882558-0ed9be09-f5c8-4e6f-9c76-afe4b59969bb.png)

앞으로 가는 것을 4개의 배열(`front[4]`)로 만든다. 여기서 좌표는 배열의 좌표기 때문에
위쪽은(`-1, 0`)이 되고, 아래쪽은(`1, 0`)으로 위로는 감소하고 아래로 갈 때는 증가한다. (`y, x`)

`if (CanGo(pos + front[newDir]))` 현재위치 + 새로운 방향으로 갈 수 있다면 `Player`의 방향(`_dir`)은 새로운 방향(`newDir`)이 되고 앞으로 전진한다. 

`path.push_back(pos)`는 가야되는 길을 저장한다.

### 앞으로 갈 수 있는지 확인

![maze6](https://user-images.githubusercontent.com/66328790/196882564-c4957cd9-cc76-4ae6-b91b-5769c9c4a7d0.png)

위의 방식을 활용하여 앞으로 갈 수 있는지 확인하고 전진하는 것도 쉽게 구현할 수 있다.

![maze7](https://user-images.githubusercontent.com/66328790/196882566-c870efbc-08c4-4743-868e-eec36bb23012.png)


`Player`가 좌표를 기준으로 한칸씩 움직이는데 컴퓨터는 엄청 빠르게 이동하기 때문에 눈으로 확인하지 못 할 수가 있다. 이것을 약 0.1초마다 움직이도록 조절한다.
`if (_pathIndex >= _path.size())` 만약에 `_pathIndex`가 `_path.size()`보다 크다면 이동을 다 한 것이기 때문에 `return`한다. `_sumTick`이라는 임시 변수에 `deltaTick`(각 프레임마다 경과시간)을 담아둔다.

그 후에 `if (_sumTick >= MOVE_TICK)` :만약 0.1초(`MOVE_TICK`)가 지난다면
먼저 `_sumTick`을 다시 0.1초를 세기위해 `0`으로 초기화 해놓는다.

그 후 `_pathIndex++`로 `1`씩 증가하여 다음 좌표로 이동한다.


---
