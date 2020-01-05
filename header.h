#ifndef header_h
#define header_h

#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <fstream>

using namespace std;

DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);

struct enemy{
int run;
int rise;
int xpos;
int ypos;
bool alive;
};

struct projectile{
int xpos;
int ypos;
int prad;
int rise;
int run;
int velocity;
};

struct slope{//struct to store slope values, contains rise run and slope
int rise;
int run;
float ror;
};

int clickhitdetect(POINT click, enemy a[], int zrad);//checks if the player clicks within a zombie

int bullethitdetect(POINT click, enemy a[], int zrad);//checks if the bullet hits a zombie

void spawn (enemy a[], int zrad);//displays the zombies immediately at spawn, first circle print

slope calculation(POINT coordinate);//calculates slope of any point in cartesian format

int hitdetect(POINT coordinate, int xmax, int ymax, slope equation, int zrad, int brad);//takes cartesian input along with max value and slope to make equations

POINT cartesian(int midx, int midy, int x, int y);//converts screen coordinates to cartesian

void resetbool(enemy a[]);//sets all 'alive' struct members to false so rng spawn works

void move(enemy a[],int zrad, int velocity);//moves zombies towards center but doesnt delete the old circles yet

bool gameover(enemy a[], int zrad);

int gcd(int x, int y);
#endif
