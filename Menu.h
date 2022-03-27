#pragma once
#include <iostream>
#include<windows.h>
#include<conio.h>
#include <io.h>
#include <fcntl.h>
#include "CursorFunctions.h"
#include "PrintShipFunctions.h"
#include "Loading.h"
#include "StartGame.h"
using namespace std;

void ShowMenu();
void ShowChoices()
{
    TextColor(BLACK, WHITE);
    int Set[] = { GREY,GREY,GREY };
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

        PrintBATTLESHIP();
        CursorCoordinates(0, 17);
        PrintShips();

        CursorCoordinates(55, 12);
        TextColor(Set[0]);
        wprintf(L"PLAY GAME");

        CursorCoordinates(54, 13);
        TextColor(Set[1]);
        wprintf(L"HOW TO PLAY");

        CursorCoordinates(57, 14);
        TextColor(Set[2]);
        wprintf(L"EXIT");

        key = _getch();

        if (key == 72 && (counter > 1))
        {
            counter--;
        }
        if (key == 80 && (counter < 3))
        {
            counter++;
        }
        if (key == '\r')
        {
            if (counter == 1)
            {
                // Loading
                ShowLoadingScreen();
                Sleep(50); 
                // GAME
                //system("cls");
                StartGame();
                //system("cls");

                //ShowMenu();
            }
            if (counter == 2)
            {
                // HOW TO PLAY
            }
            if (counter == 3)
            {
                // EXIT
                system("cls");
                system("exit");
                break;
            }
        }

        Set[0] = GREY;
        Set[1] = GREY;
        Set[2] = GREY;

        if (counter == 1)
        {
            Set[0] = GREEN;
        }
        if (counter == 2)
        {
            Set[1] = GREEN;
        }
        if (counter == 3)
        {
            Set[2] = GREEN;
        }
    }
}

void ShowMenu()
{
    ShowChoices();

}
