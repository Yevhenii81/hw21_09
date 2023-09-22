// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <ctime> // time
#include <Windows.h> // окрашивание, работа с координатами
#include <conio.h> // configurate input output
#include "Yevhenii.h"

using namespace std;

enum Directions {LEFT = 75, RIGTH = 77, DOWN = 80, UP = 72};
enum Colors {RED = 12, BLACK = 0, DARKBLUE = 3, YELLOW = 14, PINK = 13};
enum ObjectTypes { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, MEDICINE = 4 };


int main()
{
	system("title Maze");

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100; // 1...100
	SetConsoleCursorInfo(h, &info);

	srand(time(0));

	const int width = 60; //ширина лабиринта
	const int heigth = 20; //высота лабиринта 
	int maze[heigth][width] = {};// заготовка


	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5;

			if (x == 0 || y == 0 || x == width - 1 || y == heigth - 1)
			{
				maze[y][x] = WALL;
			}
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 || x == width - 1 && y == heigth - 3) {
				maze[y][x] = HALL;

			}

			if (maze[y][x] == ENEMY)
			{
				int probality = rand() % 10;
				if (probality != 0)
				{
					maze[y][x] = HALL;
				}
			}

			
			if (maze[y][x] == MEDICINE)
			{
				int probality_m = rand() % 10;
				if (probality_m != 0)
				{
					maze[y][x] = HALL;
				}
			}
			
		}
	}

	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (maze[y][x] == HALL)
			{
				SetConsoleTextAttribute(h, BLACK); 
				cout << " "; // коридор
			}
			else if (maze[y][x] == WALL)
			{
				SetConsoleTextAttribute(h, DARKBLUE); 
				cout << (char)178; // стена
				// cout << "#";
			}
			else if (maze[y][x] == COIN)
			{
				SetConsoleTextAttribute(h, YELLOW); 
				cout << "."; 
			}
			else if (maze[y][x] == ENEMY)
			{
				// cout << "*"; // враг
				SetConsoleTextAttribute(h, RED); 
				cout << (char)1;
			}
			else if (maze[y][x] == MEDICINE)
			{
				SetConsoleTextAttribute(h, 91);
				cout << (char)5;
			}
		}
		cout << "\n";
	}

	COORD position;
	position.X = 0;
	position.Y = 2;
	SetCursor(0, 2, PINK, "\x01");


	int coins = 0;
	int hp = 100, enemyDamage = 25, medicineRestore = 25;
	while (true) {
		int code = _getch();
		if (code == 224)
		{
			code = _getch();
		}
	
		//cout << code << "\n";
		
		SetConsoleCursorPosition(h, position);
		cout << " ";
		if (code == RIGTH && maze[position.Y][position.X + 1] != WALL)
		{
			position.X++;
		}
		else if (code == LEFT && maze[position.Y][position.X - 1] != WALL)
		{
			position.X--;
		}
		else if (code == DOWN && maze[position.Y + 1][position.X] != WALL)
		{
			position.Y++;
		}
		else if (code == UP && maze[position.Y - 1][position.X] != WALL)
		{
			position.Y--;
		}

		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, PINK);
		cout << (char)1;
		
		///////////////////////////////////

		if (position.X == width - 1 && position.Y == heigth - 3)
		{
			MessageBoxA(0, "найден выход из лабиринта!", "ПОБЕДА!", MB_OK);
			break;
		}

		if (maze[position.Y][position.X] == COIN)
		{
			coins++;
			maze[position.Y][position.X] = HALL;
			COORD coins_info;
			coins_info.X = width + 2;
			coins_info.Y = 1;
			SetConsoleCursorPosition(h, coins_info);
			SetConsoleTextAttribute(h, YELLOW);
			cout << "COIN: " << coins;
		}

		if (maze[position.Y][position.X] == ENEMY)
		{
			hp -= enemyDamage;
			maze[position.Y][position.X] = HALL;
			COORD hp_info;
			hp_info.X = width + 1;
			hp_info.Y = 2;
			SetConsoleCursorPosition(h, hp_info);
			SetConsoleTextAttribute(h, RED);
			cout << " HP: " << hp << " %";


			if (hp <= 0)
			{
				MessageBoxA(0, "Вас атаковали враги! Игра окончена!", "ПОРАЖЕНИЕ!", MB_OK);
				break;
			}
		}

		if (maze[position.Y][position.X] == MEDICINE)
		{
			if (hp < 100)
			{
				hp += medicineRestore;
				if (hp > 100)
				{
					hp = 100;
				}
				maze[position.Y][position.X] = HALL;
				COORD hp_info;
				hp_info.X = width + 1;
				hp_info.Y = 2;
				SetConsoleCursorPosition(h, hp_info);
				SetConsoleTextAttribute(h, RED);
				cout << " HP: " << hp << " %";
			}
		}

	}

	system("cls");
	cout << "YOU WIN!!!\n\n";


	Sleep(INFINITE);



	// коридоры - 0
	// стены - 1
	// монетки - 2
	// враги - 3
}


// Было 222, стало - 210






















// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
