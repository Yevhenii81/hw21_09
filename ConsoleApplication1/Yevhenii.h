#include <iostream>
#include <windows.h>
using namespace std;

// 1) определение (создание) функции

// ОПИСАНИЕ ФУНКЦИИ:
    // установка курсора в определённую позицию
    // + окрашивание текста в определённый цвет
    // + вывод строки текста
void SetCursor(int x, int y, int color, string text) // пример функции с 4 параметрами
{
    // дескриптор окна консоли (уникальный номер окна в консоли, нужен для того чтобы найти конкретное окно и выполнить именно над ним определённые действия)
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    // специальный структурный тип для работы с координатами (для перестановки курсора)
    COORD position;
    position.X = x; // настройка конкретных координат
    position.Y = y;
    SetConsoleCursorPosition(h, position); // установка курсора в заданную точку
    SetConsoleTextAttribute(h, color); // смена цвета
    cout << text; // вывод строки текста
    cout << "\n";
}