#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include "CursorFunctions.h"
#include "PrintShipFunctions.h"
#include "Loading.h"
#include "Entities.h"
using namespace std;

const int length = 41;
const int width = 21;
int player_board[width][length] = {};
int computer_board[width][length] = {};
const int number_of_random_X = 10;
const int number_of_random_Y = 10;
int random_X_arr[number_of_random_X] = { 2,6,10,14,18,22,26,30,34,38 };
int random_Y_arr[number_of_random_Y] = { 1,3,5,7,9,11,13,15,17,19 };

int size_s = 0;
Coordinates** coordinates_shot_before_by_computer = new Coordinates * [size_s] {};

enum board_codes { WALL = 8, SPACE = 0, GREEN_SHIP = 1, MISSED_SHOT = 66, SHIPSIDE = 11, RED_SHIP = 2,
	               COMPUTER_SHIP = 3, BOUNDARY_AREA = 7, HIT = 104, DESTROYED_SHIP = 13 };

enum Directions { UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75, ROTATE = 114 }; 

int ship_color[1] = { GREEN };

void PrintNumbers(int x, int y)
{
	TextColor(BLACK);
	CursorCoordinates(x - 1, y + 2);
	wprintf(L"\x0031");
	CursorCoordinates(x - 1, y + 4);
	wprintf(L"\x0032");
	CursorCoordinates(x - 1, y + 6);
	wprintf(L"\x0033");
	CursorCoordinates(x - 1, y + 8);
	wprintf(L"\x0034");
	CursorCoordinates(x - 1, y + 10);
	wprintf(L"\x0035");
	CursorCoordinates(x - 1, y + 12);
	wprintf(L"\x0036");
	CursorCoordinates(x - 1, y + 14);
	wprintf(L"\x0037");
	CursorCoordinates(x - 1, y + 16);
	wprintf(L"\x0038");
	CursorCoordinates(x - 1, y + 18);
	wprintf(L"\x0039");
	CursorCoordinates(x - 2, y + 20);
	wprintf(L"\x0031");
	wprintf(L"\x0030");
}

void PrintLetters(int x, int y)
{
	TextColor(BLACK);
	CursorCoordinates(x, y);
	wprintf(L"   ");
	wprintf(L"\x0041");
	wprintf(L"   ");
	wprintf(L"\x0042");
	wprintf(L"   ");
	wprintf(L"\x0043");
	wprintf(L"   ");
	wprintf(L"\x0044");
	wprintf(L"   ");
	wprintf(L"\x0045");
	wprintf(L"   ");
	wprintf(L"\x0046");
	wprintf(L"   ");
	wprintf(L"\x0047");
	wprintf(L"   ");
	wprintf(L"\x0048");
	wprintf(L"   ");
	wprintf(L"\x0049");
	wprintf(L"   ");
	wprintf(L"\x004A");
}

void FillBoardWithNumbers(int arr[width][length])
{
	CursorCoordinates(11, 4);
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			// Sides
			if (y == 0 || y == width - 1 || x == 0 || x == length - 1)
			{
				arr[y][x] = WALL;
			}
			else if (y >= 0 && y <= width && x >= 0 && x <= length)
			{
				arr[y][x] = SPACE;
			}
		}
	}
}

bool IsBoundaryArea(const int y, const int x, int arr[width][length]);

void DrawPlayerBoard()
{
	system("cls");

	CursorCoordinates(17, 1);
	TextColor(RED);
	wprintf(L"Player Board");
	PrintLetters(2,4);
	CursorCoordinates(5, 4);
	TextColor(BLACK);
	for (int y = 0; y < width; y++)
	{
		wprintf(L"\n   ");
		for (int x = 0; x < length; x++)
		{
			// Up-Left Corner
			if (x == 0 && y == 0)
			{
				wprintf(L"\x2554");
			}
			// Up-Right Corner
			else if (x == length - 1 && y == 0)
			{
				wprintf(L"\x2557");
			}
			// Down-Left Corner
			else if (x == 0 && y == width - 1)
			{
				wprintf(L"\x255A");
			}
			// Down-Right Corner
			else if (x == length - 1 && y == width - 1)
			{
				wprintf(L"\x255D");
			}
			// Up Side
			else if (x % 4 == 0 && y == 0)
			{
				wprintf(L"\x2566");
			}
			else if (x % 4 != 0 && y == 0)
			{
				wprintf(L"\x2550");
			}

			// Down Side
			else if (x % 4 == 0 && y == width - 1)
			{
				wprintf(L"\x2569");
			}
			else if (x % 4 != 0 && y == width - 1)
			{
				wprintf(L"\x2550");
			}
			// Left Side
			else if (y % 2 != 0 && x == 0 && y != width - 1)
			{
				wprintf(L"\x2551");
			}
			else if (y % 2 == 0 && x == 0 && y != width - 1)
			{
				wprintf(L"\x2560");
			}
			// Right Side
			else if (y % 2 != 0 && x == length - 1 && y != width - 1)
			{
				wprintf(L"\x2551");
			}
			else if (y % 2 == 0 && x == length - 1 && y != width - 1)
			{
				wprintf(L"\x2563");
			}
			// Inside
			else if (x % 4 == 0 && y % 2 == 0)
			{
				wprintf(L"\x256C");
			}
			else if (y % 2 == 0 && x % 4 != 0)
			{
				wprintf(L"\x2550");
			}
			else if (y % 2 != 0 && x % 4 == 0)
			{
				wprintf(L"\x2551");
			}

			else if (player_board[y][x] == SPACE)
			{
				wprintf(L" ");
			}
			else if (player_board[y][x] == GREEN_SHIP)
			{
				TextColor(ship_color[0]);
				wprintf(L"\x2588");
				TextColor(BLACK);
			}	
			else if (player_board[y][x] == SHIPSIDE)
			{
				TextColor(ship_color[0]);
				if (player_board[y][x + 1] == GREEN_SHIP)
				{
					wprintf(L"\x2590");
				}
				else
				{
					wprintf(L"\x258C");

				}
				TextColor(BLACK);
			}
			else if (player_board[y][x] == RED_SHIP)
			{
				TextColor(RED);
				wprintf(L"\x2592");
				TextColor(BLACK);
			}
			else if (player_board[y][x] == BOUNDARY_AREA)
			{
				wprintf(L" ");
			}
			else if (player_board[y][x] == DESTROYED_SHIP)
			{
				TextColor(RED);
				wprintf(L"X");
				TextColor(BLACK);
			}
			else if (player_board[y][x] == MISSED_SHOT)
			{
				TextColor(PURPLE);
				wprintf(L"M");
				TextColor(BLACK);
			}
		}
	}
	PrintNumbers(2,4);
}

void DrawComputerBoard()
{
	CursorCoordinates(91, 1);
	TextColor(RED);
	wprintf(L"Computer Board");
	PrintLetters(77,4);
	CursorCoordinates(13, 4);
	TextColor(BLACK);
	for (int y = 0; y < width; y++)
	{
		wprintf(L"\n\t\t\t\t\t\t\t\t\t      ");
		for (int x = 0; x < length; x++)
		{
			// Up-Left Corner
			if (x == 0 && y == 0)
			{
				wprintf(L"\x2554");
			}
			// Up-Right Corner
			else if (x == length - 1 && y == 0)
			{
				wprintf(L"\x2557");
			}
			// Down-Left Corner
			else if (x == 0 && y == width - 1)
			{
				wprintf(L"\x255A");
			}
			// Down-Right Corner
			else if (x == length - 1 && y == width - 1)
			{
				wprintf(L"\x255D");
			}
			// Up Side
			else if (x % 4 == 0 && y == 0)
			{
				wprintf(L"\x2566");
			}
			else if (x % 4 != 0 && y == 0)
			{
				wprintf(L"\x2550");
			}

			// Down Side
			else if (x % 4 == 0 && y == width - 1)
			{
				wprintf(L"\x2569");
			}
			else if (x % 4 != 0 && y == width - 1)
			{
				wprintf(L"\x2550");
			}
			// Left Side
			else if (y % 2 != 0 && x == 0 && y != width - 1)
			{
				wprintf(L"\x2551");
			}
			else if (y % 2 == 0 && x == 0 && y != width - 1)
			{
				wprintf(L"\x2560");
			}
			// Right Side
			else if (y % 2 != 0 && x == length - 1 && y != width - 1)
			{
				wprintf(L"\x2551");
			}
			else if (y % 2 == 0 && x == length - 1 && y != width - 1)
			{
				wprintf(L"\x2563");
			}
			// Inside
			else if (x % 4 == 0 && y % 2 == 0)
			{
				wprintf(L"\x256C");
			}
			else if (y % 2 == 0 && x % 4 != 0)
			{
				wprintf(L"\x2550");
			}
			else if (y % 2 != 0 && x % 4 == 0)
			{
				wprintf(L"\x2551");
			}
			else if (computer_board[y][x] == BOUNDARY_AREA)
			{
				wprintf(L" ");
			}
			else if (computer_board[y][x] == GREEN_SHIP)
			{
				wprintf(L"S");
			}
			else if (computer_board[y][x] == SHIPSIDE)
			{
				wprintf(L" ");
			}
			else if (computer_board[y][x] == SPACE)
			{
				wprintf(L" ");
			}			
			else if (computer_board[y][x] == DESTROYED_SHIP)
			{
				TextColor(RED);
				wprintf(L"X");
				TextColor(BLACK);
			}
			else if (computer_board[y][x] == MISSED_SHOT)
			{
				TextColor(PURPLE);
				wprintf(L"M");
				TextColor(BLACK);
			}
		}
	}
	PrintNumbers(77,4);
}

void DrawGameScreen()
{
	DrawPlayerBoard();
	DrawComputerBoard();
}

inline bool IsSpace(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == SPACE)
	{
		return true;
	}
	return false;
}

inline bool IsShip(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == GREEN_SHIP || arr[y][x] == DESTROYED_SHIP)
	{
		return true;
	}
	return false;
}

inline bool IsBoundaryArea(int y, const int x, int arr[width][length])
{
	if (arr[y][x] == BOUNDARY_AREA)
	{
		return true;
	}
	return false;
}

inline bool IsWall(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == WALL)
	{
		return true;
	}
	return false;
}

inline void TurnIntoSpace(int y, int x, int arr[width][length])
{
	arr[y][x] = SPACE;
	arr[y][x - 1] = SPACE;
	arr[y][x + 1] = SPACE;
}

inline void TurnIntoBoundaryArea(int y, int x, int arr[width][length])
{
	arr[y][x] = BOUNDARY_AREA;
}

bool ShipIsHorizontal(int y, int x, const int ship_length, int arr[width][length]);

inline void TurnIntoBlueShip(int y, int x, int arr[width][length])
{
	arr[y][x] = GREEN_SHIP;
	arr[y][x - 1] = SHIPSIDE;
	arr[y][x + 1] = SHIPSIDE;
}

inline void TurnIntoRedShip(int y, int x, int arr[width][length])
{
	arr[y][x] = RED_SHIP;
}

bool ShipIsVertical(int y, int x, const int ship_length, int arr[width][length])
{
	for (int e = 0; e < ship_length; e++)
	{
		if (!IsShip(y + (2 * e), x, arr))
		{
			return false;
		}
	}
	return true;
}

bool ShipIsHorizontal(int y, int x, const int ship_length, int arr[width][length])
{
	for (int s = 0; s < ship_length; s++)
	{
		if (!IsShip(y, x + (4 * s), arr))
		{
			return false;
		}
	}
	return true;
}

void FreePlaceVertically(int y, int x, const int ship_length, int arr[width][length])
{
	for (int a = 0; a < ship_length; a++)
	{
		TurnIntoSpace(y + (2 * a), x, arr);
	}
}

void FreePlaceHorizontally(int y, int x, const int ship_length, int arr[width][length])
{
	for (int b = 0; b < ship_length; b++)
	{
		TurnIntoSpace(y, x + (4 * b), arr);
	}
}

void PlaceShipVertically(int y, int x, const int ship_length, int fg, int arr[width][length])
{
	if (fg == BLUE)
	{
		for (int b = 0; b < ship_length; b++)
		{
			TurnIntoBlueShip(y + (2 * b), x, arr);
		}
	}
	else if(fg == RED)
	{
		for (int c = 0; c < ship_length; c++)
		{
			TurnIntoBlueShip(y + (2 * c), x, arr);
		}
	}
}

void PlaceShipHorizontally(int y, int x, const int ship_length, int fg, int arr[width][length])
{
	if (fg == BLUE)
	{
		for (int b = 0; b < ship_length; b++)
		{
			TurnIntoBlueShip(y, x + (4 * b), arr);
		}
	}
	else if (fg == RED)
	{
		for (int c = 0; c < ship_length; c++)
		{
			TurnIntoRedShip(y, x + (4 * c), arr);
		}
	}			
	
}

bool CanVerticallyGoUp(int y, int x, int arr[width][length])
{
	if (IsShip(y - 2, x, arr) || IsBoundaryArea(y - 2, x, arr))
	{
		return false;
	}
	else if (IsSpace(y - 1, x, arr))
	{
		return true;
	}
	return false;
}

bool CanVerticallyGoDown(int y, int x, const int ship_length, int arr[width][length])
{
	if (IsShip(y + (ship_length * 2), x, arr) || IsBoundaryArea(y + (ship_length * 2), x, arr))
	{
		return false;
	}
	if (IsSpace(y + (2*ship_length) - 1, x, arr))
	{
		return true;
	}
	return false;
}

bool CanVerticallyGoRight(int y, int x, const int ship_length, int arr[width][length])
{
	for (int t = 0; t < ship_length; t++)
	{
		if (!IsSpace(y + (2 * t), x + 2, arr) || IsShip(y + (2 * t), x + 4, arr) || IsBoundaryArea(y + (2 * t), x + 4, arr))
		{
			return false;
		}
	}
	return true;
}

bool CanVerticallyGoLeft(int y, int x, const int ship_length, int arr[width][length])
{
	for (int w = 0; w < ship_length; w++)
	{
		if (!IsSpace(y + (2 * w), x - 2, arr) || IsShip(y + (2 * w), x - 4, arr) || IsBoundaryArea(y + (2 * w), x - 4, arr))
		{
			return false;
		}
	}
	return true;
}

bool CanHorizontallyGoUp(int y, int x, const int ship_length, int arr[width][length])
{
	for (int p = 0; p < ship_length; p++)
	{
		if (!IsSpace(y - 1, x + (4 * p), arr) || IsShip(y - 2, x + (4 * p), arr) || IsBoundaryArea(y - 2, x + (4 * p), arr))
		{
			return false;
		}
	}
	return true;
}

bool CanHorizontallyGoDown(int y, int x, const int ship_length, int arr[width][length])
{
	for (int u = 0; u < ship_length; u++)
	{
		if (!IsSpace(y + 1, x + (4 * u), arr) || IsShip(y + 2, x + (4 * u), arr) || IsBoundaryArea(y + 2, x + (4 * u), arr))
		{
			return false;
		}
	}
	return true;
}

bool CanHorizontallyGoRight(int y, int x, const int ship_length, int arr[width][length])
{
	if (IsShip(y, x + (4 * ship_length), arr) || IsBoundaryArea(y, x + (4 * ship_length), arr))
	{
		return false;
	}
	else if (IsSpace(y, x + (4 * ship_length) - 2, arr))
	{
		return true;
	}
	return false;
}

bool CanHorizontallyGoLeft(int y, int x, const int ship_length, int arr[width][length])
{
	if (IsShip(y, x - 4, arr) || IsBoundaryArea(y, x - 4, arr))
	{
		return false;
	}
	if (IsSpace(y, x - 2, arr))
	{
		return true;
	}
	return false;
}

bool ShipIsCarrier(int y, int x, int arr[width][length])
{
	if (IsShip(y + 2, x, arr) || IsShip(y - 2, x, arr) || IsShip(y, x + 4, arr) || IsShip(y, x - 4, arr))
	{
		return false;
	}
	return true;
}

void FillBoundaryAreas(int arr[width][length])
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if (arr[y][x] == GREEN_SHIP)
			{
				if (ShipIsCarrier(y, x, arr))
				{
					if (!IsShip(y + 2, x + 4, arr) && !IsWall(y + 2, x + 4, arr))
					{
						TurnIntoBoundaryArea(y + 2, x + 4, arr);
					}
					if (!IsShip(y + 2, x - 4, arr) && !IsWall(y + 2, x - 4, arr))
					{
						TurnIntoBoundaryArea(y + 2, x - 4, arr);
					}
					if (!IsShip(y - 2, x + 4, arr) && !IsWall(y - 2, x + 4, arr))
					{
						TurnIntoBoundaryArea(y - 2, x + 4, arr);
					}
					if (!IsShip(y - 2, x - 4, arr) && !IsWall(y - 2, x - 4, arr))
					{
						TurnIntoBoundaryArea(y - 2, x - 4, arr);
					}
					if (!IsShip(y, x + 4, arr) && !IsWall(y, x + 4, arr))
					{
						TurnIntoBoundaryArea(y, x + 4, arr);
					}
					if (!IsShip(y, x - 4, arr) && !IsWall(y, x - 4, arr))
					{
						TurnIntoBoundaryArea(y, x - 4, arr);
					}
					if (!IsShip(y + 2, x, arr) && !IsWall(y + 2, x, arr))
					{
						TurnIntoBoundaryArea(y + 2, x, arr);
					}
					if (!IsShip(y - 2, x, arr) && !IsWall(y - 2, x, arr))
					{
						TurnIntoBoundaryArea(y - 2, x, arr);
					}
				}
				else
				{
					// Fill around of ship with boundary areas
					if (!IsShip(y + 2, x, arr) && !IsWall(y + 2, x, arr))
					{
						TurnIntoBoundaryArea(y + 2, x, arr);
					}
					if (!IsShip(y - 2, x, arr) && !IsWall(y - 2, x, arr))
					{
						TurnIntoBoundaryArea(y - 2, x, arr);
					}
					if (!IsShip(y, x + 4, arr) && !IsWall(y, x + 4, arr))
					{
						TurnIntoBoundaryArea(y, x + 4, arr);
					}
					if (!IsShip(y, x - 4, arr) && !IsWall(y, x - 4, arr))
					{
						TurnIntoBoundaryArea(y, x - 4, arr);
					}
					if (IsShip(y + 2, x, arr) || IsShip(y - 2, x, arr)) // If Ship Is Vertical (Corners)
					{
						for (int f = 0; f < 4; f++)
						{
							if (!IsShip(y + (2 * f), x, arr) && IsShip(y + (2 * (f - 1)), x, arr))
							{
								TurnIntoBoundaryArea(y + (2 * f), x + 4, arr);
								TurnIntoBoundaryArea(y + (2 * f), x - 4, arr);
							}
							if (!IsShip(y - (2 * f), x, arr) && IsShip(y - (2 * (f - 1)), x, arr))
							{
								TurnIntoBoundaryArea(y - (2 * f), x + 4, arr);
								TurnIntoBoundaryArea(y - (2 * f), x - 4, arr);
							}
						}
					}
					if (IsShip(y, x + 4, arr) || IsShip(y, x - 4, arr)) // If Ship Is Vertical (Corners)
					{
						for (int f = 0; f < 4; f++)
						{
							if (!IsShip(y, x + (4 * f), arr) && IsShip(y, x + (4 * (f - 1)), arr))
							{
								TurnIntoBoundaryArea(y + 2, x + (4 * f), arr);
								TurnIntoBoundaryArea(y - 2, x + (4 * f), arr);
							}
							if (!IsShip(y, x - (4 * f), arr) && IsShip(y, x - (4 * (f - 1)), arr))
							{
								TurnIntoBoundaryArea(y + 2, x - (4 * f), arr);
								TurnIntoBoundaryArea(y - 2, x - (4 * f), arr);
							}
						}
					}
				}
			}
		}
	}
}

bool CanRotateToHorizontal(int y, int x, const int ship_length, int arr[width][length])
{
	if (ship_length == 4)
	{
		if (IsSpace(y, x + 4, arr) && IsSpace(y, x + 8, arr) && IsSpace(y, x + 12, arr) && x + 12 < length)
		{
			return true;
		}
		return false;
	}
	else if (ship_length == 3)
	{
		if (IsSpace(y, x + 4, arr) && IsSpace(y, x + 8, arr) && x + 8 < length)
		{
			return true;
		}
		return false;
	}
	else if (ship_length == 2)
	{
		if (IsSpace(y, x + 4, arr) && x + 4 < length)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

bool CanRotateToVertical(int y, int x, const int ship_length, int arr[width][length])
{
	if (ship_length == 4)
	{
		if (IsSpace(y + 2, x, arr) && IsSpace(y + 4, x, arr) && IsSpace(y + 6, x, arr) && y + 6 < width)
		{
			return true;
		}
		return false;
	}
	else if (ship_length == 3)
	{
		if (IsSpace(y + 2, x, arr) && IsSpace(y + 4, x, arr) && y + 4 < width)
		{
			return true;
		}
		return false;
	}
	else if (ship_length == 2 && y + 2 < width)
	{
		if (IsSpace(y + 2, x, arr))
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

bool CanCreateShipVertically(int y, int x, const int ship_length, int arr[width][length])
{
	for (int r = 0; r < ship_length; r++)
	{
		if (!IsSpace(y + (2 * r), x, arr))
		{
			return false;
		}
	}
	return true;
}

bool CanCreateShipHorizontally(int y, int x, const int ship_length, int arr[width][length])
{
	for (int f = 0; f < ship_length; f++)
	{
		if (!IsSpace(y, x + (4 * f), arr))
		{
			return false;
		}
	}
	return true;
}

void PlaceAShip(const int ship_length, int arr[width][length])
{
	int Y = 0;
	int X = 0;
	bool ship_is_horizontal = false;
	while (true)
	{
		int index_for_Y = 0 + rand() % (number_of_random_Y);
		int index_for_X = 0 + rand() % (number_of_random_X);

		Y = random_Y_arr[index_for_Y];
		X = random_X_arr[index_for_X];


		if (X % 4 == 2 && Y % 2 == 1)
		{
			if (CanCreateShipHorizontally(Y, X, ship_length, arr))
			{
				ship_is_horizontal = true;
				break;
			}
		}
		else if (X % 4 == 2 && Y % 2 == 1)
		{
			if (CanCreateShipVertically(Y, X, ship_length, arr))
			{
				break;
			}
		}
	}

	if (ship_is_horizontal)
	{
		PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
	}
	else
	{
		PlaceShipVertically(Y, X, ship_length, BLUE, arr);
	}

	while (true)
	{
		DrawPlayerBoard();
		CursorCoordinates(34, 10);
		wprintf(LR"(				 	      _/___
									_____/______|
								_______/_____\_______\_____
								\    PLACE THE WARSHIP     |
							   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)");
		char symbol = _getch();
		if (symbol == -32)
		{
			symbol = _getch();
			int no = symbol;
			if (no == UP) // Going UP
			{
				if (ShipIsVertical(Y, X, ship_length, arr))
				{
					if (CanVerticallyGoUp(Y, X, arr))
					{
						FreePlaceVertically(Y, X, ship_length, arr);
						Y -= 2;
						PlaceShipVertically(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
				else
				{
					if (CanHorizontallyGoUp(Y, X, ship_length, arr))
					{
						FreePlaceHorizontally(Y, X, ship_length, arr);
						Y -= 2;
						PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
			}
			else if (no == DOWN) // Going DOWN
			{
				if (ShipIsVertical(Y, X, ship_length, arr))
				{
					if (CanVerticallyGoDown(Y, X, ship_length, arr))
					{
						FreePlaceVertically(Y, X, ship_length, arr);
						Y += 2;
						PlaceShipVertically(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
				else
				{
					if (CanHorizontallyGoDown(Y, X, ship_length, arr))
					{
						FreePlaceHorizontally(Y, X, ship_length, arr);
						Y += 2;
						PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
			}
			else if (no == RIGHT) // Going RIGHT
			{
				if (ShipIsVertical(Y, X, ship_length, arr))
				{
					if (CanVerticallyGoRight(Y, X, ship_length, arr))
					{
						FreePlaceVertically(Y, X, ship_length, arr);
						X += 4;
						PlaceShipVertically(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
				else
				{
					if (CanHorizontallyGoRight(Y, X, ship_length, arr))
					{
						FreePlaceHorizontally(Y, X, ship_length, arr);
						X += 4;
						PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
			}
			else if (no == LEFT) // Going LEFT
			{
				if (ShipIsVertical(Y, X, ship_length, arr))
				{
					if (CanVerticallyGoLeft(Y, X, ship_length, arr))
					{
						FreePlaceVertically(Y, X, ship_length, arr);
						X -= 4;
						PlaceShipVertically(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
				else
				{
					if (CanHorizontallyGoLeft(Y, X, ship_length, arr))
					{
						FreePlaceHorizontally(Y, X, ship_length, arr);
						X -= 4;
						PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
			}
		}
		else if (symbol == ROTATE)
		{
			if (ship_length == 1)
			{
				continue;
			}
			else
			{
				// Situation 1 (When ship is vertical)
				if (ShipIsVertical(Y, X, ship_length, arr))
				{
					if (CanRotateToHorizontal(Y, X, ship_length, arr))
					{
						FreePlaceVertically(Y, X, ship_length, arr);
						PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
				// Situation 2 (When ship is horizontal)
				else
				{
					if (CanRotateToVertical(Y, X, ship_length, arr))
					{
						FreePlaceHorizontally(Y, X, ship_length, arr);
						PlaceShipVertically(Y, X, ship_length, BLUE, arr);
					}
					else
					{
						wprintf(L"\a"); // Add Music
					}
				}
			}
		}
		else if (symbol == '\r')
		{
			FillBoundaryAreas(arr);
			ship_color[0] = BLUE;
			DrawPlayerBoard();
			ship_color[0] = GREEN;
			break;
		}
	}
}

void PlaceShipsManually(int arr[width][length]);

void PlaceShipsRandomly(int arr[width][length]);

void ChooseShipsToBePlaced(int arr[width][length]);

void ChooseAutoOrManuallyShipFilling(int arr[width][length])
{
	system("cls");

	TextColor(RED);
	wprintf(L"\n\n\n\n\n\n\n\n\n\n\t\t\t     Would you like the ships to be placed manually or randomly?");

	int Set[] = { GREY,GREY };
	int counter = 1;
	bool first_entry = true;
	char key;
	int result = _setmode(_fileno(stdout), _O_U16TEXT);

	HideCursor();
	while (true)
	{
		if (first_entry)
		{
			Set[0] = GREEN;
			first_entry = false;
		}
		CursorCoordinates(51, 12);
		TextColor(Set[0]);
		wprintf(L" << MANUALLY >>");

		CursorCoordinates(51, 13);
		TextColor(Set[1]);
		wprintf(L" << RANDOMLY >>");

		key = _getch();

		if (key == 72 && (counter > 1))
		{
			counter--;
		}
		if (key == 80 && (counter < 2))
		{
			counter++;
		}
		if (key == '\r')
		{
			if (counter == 1)
			{
				PlaceShipsManually(arr);
				break;
			}
			if (counter == 2)
			{
				PlaceShipsRandomly(arr);
				break;
			}
		}

		Set[0] = GREY;
		Set[1] = GREY;

		if (counter == 1)
		{
			Set[0] = GREEN;
		}
		if (counter == 2)
		{
			Set[1] = GREEN;
		}
	}
}

void ChooseShipsToBePlaced(int arr[width][length])
{
	DrawPlayerBoard();
	int Set[] = { GREY,GREY,GREY,GREY };
	int counter = 1;
	bool first_entry = true;
	char key;
	int result = _setmode(_fileno(stdout), _O_U16TEXT);

	int destroyer_counter = 1;
	int submarine_counter = 2;
	int battleship_counter = 3;
	int carrier_counter = 4;

	bool destroyer_finished = false;
	bool submarine_finished = false;
	bool battleship_finished = false;
	bool carrier_finished = false;

	int total_ship_count = 0;


	HideCursor();
	while (true)
	{
		//counter = 1;
		if (first_entry)
		{
			Set[0] = GREEN;
			first_entry = false;
		}

		CursorCoordinates(62, 12);
		TextColor(RED);
		wprintf(L" |  WARSHIP  | SIZE |  REMAINING | ");

		CursorCoordinates(62, 13);
		TextColor(Set[0]);
		wprintf(L" << DESTROYER  (4x) >> ");
		wprintf(L" ~ %d", destroyer_counter);

		CursorCoordinates(62, 14);
		TextColor(Set[1]);
		wprintf(L" << SUBMARINE  (3x) >> ");
		wprintf(L" ~ %d", submarine_counter);

		CursorCoordinates(62, 15);
		TextColor(Set[2]);
		wprintf(L" << BATTLESHIP (2x) >> ");
		wprintf(L" ~ %d", battleship_counter);

		CursorCoordinates(62, 16);
		TextColor(Set[3]);
		wprintf(L" << CARRIER    (1x) >> ");
		wprintf(L" ~ %d", carrier_counter);

		key = _getch();

		if (total_ship_count == 10)
		{
			break;
		}
		if (key == 72 && (counter > 1))
		{
			counter--;
		}
		if (key == 80 && (counter < 4))
		{
			counter++;
		}
		if (key == '\r')
		{
			if (counter == 1)
			{
				if (destroyer_counter > 0)
				{
					PlaceAShip(4, arr);
					destroyer_counter--;
					total_ship_count++;
				}
				else
				{
					destroyer_finished = true;
					wprintf(L"\a");
					// ADD MUSIC
				}
			}
			if (counter == 2)
			{
				if (submarine_counter > 0)
				{
					PlaceAShip(3, arr);
					submarine_counter--;
					total_ship_count++;
				}
				else
				{
					submarine_finished = true;
					wprintf(L"\a");
					// ADD MUSIC
				}
			}
			if (counter == 3)
			{
				if (battleship_counter > 0)
				{
					PlaceAShip(2, arr);
					battleship_counter--;
					total_ship_count++;
				}
				else
				{
					battleship_finished = true;
					wprintf(L"\a");
					// ADD MUSIC
				}
			}
			if (counter == 4)
			{
				if (carrier_counter > 0)
				{
					PlaceAShip(1, arr);
					carrier_counter--;
					total_ship_count++;
				}
				else
				{
					carrier_finished = true;
					wprintf(L"\a");
					// ADD MUSIC
				}
			}
		}

		Set[0] = GREY;
		Set[1] = GREY;
		Set[2] = GREY;
		Set[3] = GREY;

		if (counter == 1 && destroyer_finished == false)
		{
			Set[0] = GREEN;
		}
		else if (counter == 1 && destroyer_finished == true)
		{
			Set[0] = RED;
		}
		if (counter == 2 && submarine_finished == false)
		{
			Set[1] = GREEN;
		}
		else if (counter == 2 && submarine_finished == true)
		{
			Set[1] = RED;
		}
		if (counter == 3 && battleship_finished == false)
		{
			Set[2] = GREEN;
		}
		else if (counter == 3 && battleship_finished == true)
		{
			Set[2] = RED;
		}
		if (counter == 4 && carrier_finished == false)
		{
			Set[3] = GREEN;
		}
		else if (counter == 4 && carrier_finished == true)
		{
			Set[3] = RED;
		}
	}
}

void PlaceShipsManually(int arr[width][length])
{
	srand(time(0));
	ChooseShipsToBePlaced(arr);
}

bool CanCreateRandomHorizontalShip(int y, int x, int ship_length, int arr[width][length])
{
	if (ship_length == 1)
	{
		if (!IsSpace(y, x, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x + 4, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x + 4, arr))
		{
			return false;
		}
		if (!IsSpace(y, x + 4, arr))
		{
			return false;
		}
		return true;
	}
	else
	{
		for (int a = y - 2; a < y + 3; a += 2)
		{
			for (int b = x - 4; b < x + (ship_length * 4) + 1; b += 4)
			{
				if (!IsSpace(a, b, arr))
				{
					return false;
				}
			}
		}
		return true;
	}
}

bool CanCreateRandomVerticalShip(int y, int x, int ship_length, int arr[width][length])
{
	if (ship_length == 1)
	{
		if (!IsSpace(y, x, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y, x - 4, arr))
		{
			return false;
		}
		if (!IsSpace(y - 2, x + 4, arr))
		{
			return false;
		}
		if (!IsSpace(y + 2, x + 4, arr))
		{
			return false;
		}
		if (!IsSpace(y, x + 4, arr))
		{
			return false;
		}
		return true;
	}
	else
	{
		for (int a = y - 2; a < y + (ship_length * 2) + 1; a += 2)
		{
			for (int b = x - 4; b < x + 5; b += 4)
			{
				if (!IsSpace(a, b, arr))
				{
					return false;
				}
			}
		}
		return true;
	}
}

void GetRandomShip(const int ship_length, int arr[width][length])
{
	srand(time(0));
	int Y = 0;
	int X = 0;
	int index_for_Y = 0;
	int index_for_X = 0;
	bool ship_is_horizontal = false;
	while (true)
	{
		index_for_Y = 0 + rand() % (number_of_random_Y);
		index_for_X = 0 + rand() % (number_of_random_X);

		Y = random_Y_arr[index_for_Y];
		X = random_X_arr[index_for_X];

		if (CanCreateRandomHorizontalShip(Y, X, ship_length, arr) && X + (4 * ship_length) < length)
		{
			ship_is_horizontal = true;
			break;
		}
		else if (CanCreateRandomVerticalShip(Y, X, ship_length, arr) && Y + (2 * ship_length) < width)
		{
			break;
		}
	}

	if (ship_is_horizontal)
	{
		PlaceShipHorizontally(Y, X, ship_length, BLUE, arr);
	}
	else
	{
		PlaceShipVertically(Y, X, ship_length, BLUE, arr);
	}
}

void PlaceShipsRandomly(int arr[width][length])
{
	GetRandomShip(4, arr);
	GetRandomShip(3, arr);
	GetRandomShip(3, arr);
	GetRandomShip(2, arr);
	GetRandomShip(2, arr);
	GetRandomShip(2, arr);
	GetRandomShip(1, arr);
	GetRandomShip(1, arr);
	GetRandomShip(1, arr);
	GetRandomShip(1, arr);
	FillBoundaryAreas(arr);
	DrawPlayerBoard();
}

bool players_turn = true;

bool HitTheCoordinates(int y, int x, int arr[width][length])
{
	if (arr[y][x] == GREEN_SHIP)
	{
		arr[y][x] = DESTROYED_SHIP;
		if (!players_turn)
		{
			player_board[y][x + 1] = SPACE;
			player_board[y][x - 1] = SPACE;
		}
		return true;
	}
	else
	{
		arr[y][x] = MISSED_SHOT;
		return false;
	}

}

char EnterX()
{
	CursorCoordinates(49, 8);
	wprintf(L"Enter X (Letter) : ");
	char X = 0;
	cin >> X;
	return X;
}

int EnterY()
{
	CursorCoordinates(49, 9);
	wprintf(L"Enter Y (Number) : ");
	int Y = 0;
	cin >> Y;
	return Y;
}

bool game_is_not_finished = true;

bool ShotBeforeByComputer(int y, int x)
{
	for (int a = 0; a < size_s; a++)
	{
		if (coordinates_shot_before_by_computer[a]->x == x && coordinates_shot_before_by_computer[a]->y == y)
		{
			return true;
		}
	}
	return false;
}

void AddNewCoordinatesShotBeforeByComputerArray(int y, int x)
{
	Coordinates* new_xy = new Coordinates[]{y,x};
	Coordinates** new_coordinates = new Coordinates * [size_s + 1]{};
	for (int a = 0; a < size_s; a++)
	{
		new_coordinates[a] = coordinates_shot_before_by_computer[a];
	}
	new_coordinates[size_s] = new_xy;
	coordinates_shot_before_by_computer = new_coordinates;
	new_xy = nullptr;
	new_coordinates = nullptr;
	size_s++;
}

int GetBaseCoordinateX(int y, int x, int arr[width][length])
{
	if (IsShip(y, x + 4, arr) || IsShip(y, x - 4, arr)) // Ship Is Horizontal
	{
		if (!IsShip(y, x - 4, arr))
		{
			return x;
		}
		else
		{
			for (int a = 1; a < 5; a++)
			{
				if (!IsShip(y, x - (a * 4), arr))
				{
					return x - ((a - 1) * 4);
				}
			}
		}
	}
	else if (IsShip(y + 2, x, arr) || IsShip(y - 2, x, arr)) // Ship Is Vetical
	{
		return x;
	}
	else
	{
		return -1;
	}
}

int GetBaseCoordinateY(int y, int x, int arr[width][length])
{
	if (IsShip(y, x + 4, arr) || IsShip(y, x - 4, arr)) // Ship Is Horizontal
	{
 		return y;
	}
	if (IsShip(y + 2, x, arr) || IsShip(y - 2, x, arr)) // Ship Is Vetical
		{
		if (!IsShip(y - 2, x, arr))
		{
			return y;
		}
		else
		{
			for (int a = 1; a < 5; a++)
			{
				if (!IsShip(y - (a * 2), x, arr))
				{
					return y - ((a - 1) * 2);
				}
			}
		}
	}
	else
	{
		return -1;
	}
}

int GetShipLength(int y, int x, int arr[width][length])
{
	int counter = 0;
	if (!IsShip(y, x + 4, arr) && !IsShip(y, x - 4, arr) && !IsShip(y - 2, x, arr) && !IsShip(y + 2, x, arr))
	{
		return 1;
	}
	else
	{
		int Y = GetBaseCoordinateY(y, x, arr);
		int X = GetBaseCoordinateX(y, x, arr);

		if (IsShip(Y, X + 4, arr)) // Ship Is Horizontal
		{
			for (int a = 0; a < 4; a++)
			{
				if (!IsShip(Y, X + (a * 4), arr))
				{
					break;
				}
				else if (IsShip(Y, X + (a * 4), arr))
				{
					counter++;
				}
			}
			return counter;
		}
		else if (IsShip(Y + 2, X, arr))  // Ship Is Vertical
		{
			for (int a = 0; a < 4; a++)
			{
				if (!IsShip(Y + (a * 2), X, arr))
				{
					break;
				}
				else if (IsShip(Y + (a * 2), X, arr))
				{
					counter++;
				}
			}
			return counter;
		}
	}
}

bool ShipDestroyedCompletely(int y, int x, int arr[width][length])
{
	int ship_length = GetShipLength(y, x, arr);

	if (ship_length == 1)
	{
		return true;
	}
	else
	{
		int Y = GetBaseCoordinateY(y, x, arr);
		int X = GetBaseCoordinateX(y, x, arr);
		if (ShipIsHorizontal(y, x, ship_length, arr))
		{
			for (int e = 0; e < ship_length; e++)
			{
				if (arr[Y][X + (e * 4)] != DESTROYED_SHIP)
				{
					return false;
				}
			}
			return true;
		}
		else
		{

			for (int e = 0; e < ship_length; e++)
			{
				if (arr[Y + (e * 2)][X] != DESTROYED_SHIP)
				{
					return false;
				}
			}
			return true;
		}
	}
}

int index = 0;

bool hit_was_successful = false;

bool tried_left_until_missed_shot = false;
bool was_trying_left = false;

bool tried_right_until_missed_shot = false;
bool was_trying_right = false;

bool tried_up_until_missed_shot = false;
bool was_trying_up = false;

bool tried_down_until_missed_shot = false;
bool was_trying_down = false;

bool has_found_a_ship = false;

int tried_left_times = 0;

bool breakk = false;

int Y = 0;
int X = 0;

void ComputerHits()
{
	srand(time(0));

	int index_for_X = 0;
	int index_for_Y = 0;

	while (true)
	{
		Sleep(700);
		DrawGameScreen();
		Sleep(700);
		if (has_found_a_ship)
		{
			// Try right, if there is a ship in the right (it means ship is horizontal) 
			// continue shooting in this direction until it is missed shot. If it is misses shot and 
			// ship is not destroyed, from the starting point try left until ship is destroyed

			if (!ShipDestroyedCompletely(Y, X, player_board))
			{
				if (tried_right_until_missed_shot == false)
				{
					X += 4;
					was_trying_right = true;
				}
				if (tried_right_until_missed_shot == true && tried_left_until_missed_shot == false)
				{
					X -= 4;
					was_trying_left = true;
				}
				if (tried_right_until_missed_shot == true && tried_left_until_missed_shot == true && tried_up_until_missed_shot == false)
				{
					Y -= 2;
					was_trying_up = true;
				}
				if (tried_right_until_missed_shot == true && tried_left_until_missed_shot == true && tried_up_until_missed_shot == true && tried_down_until_missed_shot == false)
				{
					Y += 2;
					was_trying_down = true;
				}





				if (!ShipDestroyedCompletely(Y, X, player_board))
				{
					if (!ShotBeforeByComputer(Y, X))
					{
						hit_was_successful = HitTheCoordinates(Y, X, player_board);
						AddNewCoordinatesShotBeforeByComputerArray(Y, X);
					}
					if (was_trying_right && !hit_was_successful)
					{
						tried_right_until_missed_shot = true;
						was_trying_right = false;
					}
					if (was_trying_left && !hit_was_successful)
					{
						tried_left_until_missed_shot = true;
						was_trying_left = false;
					}
					if (was_trying_up && !hit_was_successful)
					{
						tried_up_until_missed_shot = true;
						was_trying_up = false;
					}
					if (was_trying_down && !hit_was_successful)
					{
						tried_down_until_missed_shot = true;
						was_trying_down = false;
					}
				}

				if (ShipDestroyedCompletely(Y, X, player_board))
				{
					hit_was_successful = false;

					tried_left_until_missed_shot = false;
					was_trying_left = false;

					tried_right_until_missed_shot = false;
					was_trying_right = false;

					tried_up_until_missed_shot = false;
					was_trying_up = false;

					tried_down_until_missed_shot = false;
					was_trying_down = false;

					has_found_a_ship = false;
				}
			}
		}
		else
		{
			if (!hit_was_successful)
			{
				index_for_Y = 0 + rand() % (number_of_random_Y);
				index_for_X = 0 + rand() % (number_of_random_X);

				Y = random_Y_arr[index_for_Y];
				X = random_X_arr[index_for_X];

			}

			if (!ShotBeforeByComputer(Y, X))
			{
				hit_was_successful = HitTheCoordinates(Y, X, player_board);
				AddNewCoordinatesShotBeforeByComputerArray(Y, X);
			}

			if (ShipDestroyedCompletely(Y, X, player_board))
			{
				has_found_a_ship = false;
				breakk = false;
			}


			else if (hit_was_successful == true && has_found_a_ship == false && ShipDestroyedCompletely(Y, X, player_board) == false)
			{
				has_found_a_ship = true;
				index = size_s - 1;
			}
		}

		if (!hit_was_successful && breakk)
		{

			hit_was_successful = false;
			if (ShipDestroyedCompletely(Y, X, player_board))
			{
				has_found_a_ship = false;
			}
			//players_turn = true;
			break;
		}
	}
}

void StartWar()
{
	int y = 0;
	int x = 0;
	while (game_is_not_finished)
	{
		players_turn = false;
		if (players_turn)
		{
			CursorCoordinates(56, 1);
			wprintf(L"YOUR TURN");
		}
		else
		{
			CursorCoordinates(52, 1);
			wprintf(L"WAITING FOR COMPUTER");
		}
		if (players_turn)
		{
		//	DrawGameScreen();
		//	CursorCoordinates(48, 6);
		//	wprintf(L"| - Enter coordinates - |");
		//	x = EnterX();
		//	x -= 64;
		//	x *= 4;
		//	x -= 2;
		//	y = EnterY();
		//	y = (y * 2) - 1;

		//	if (x < 0 || x > 41 || y < 0 || y > 21)
		//	{
		//		CursorCoordinates(48, 6);
		//		wprintf(L"| -  Incorrect Input!  - |");
		//		Sleep(1000);
		//	}
		//	else
		//	{
		//		bool successfull = HitTheCoordinates(y, x, computer_board);
		//		if (!successfull)
		//		{
		//			players_turn = false;
		//		}
		//		else
		//		{
		//			if (ShipDestroyedCompletely(y, x, computer_board))
		//			{
		//				CursorCoordinates(44, 6);
		//				wprintf(L" - You Destroyed A Complete Ship -");
		//				Sleep(2000);
		//			}
		//			players_turn = true;
		//		}
		//	}
		}

		else
		{
			ComputerHits();
		}
 	}
}

void StartGame()
{
	FillBoardWithNumbers(player_board);
	FillBoardWithNumbers(computer_board);
	ChooseAutoOrManuallyShipFilling(player_board);
	PlaceShipsRandomly(computer_board);
	StartWar();

	system("pause");
}