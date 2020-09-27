#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 25

typedef struct {
    int x;
    int y;
} Point;

typedef struct deck {
    Point p;
    struct deck *next;
    struct deck *prev;
} Deck;

Deck* createDeck ();
Point getFront (Deck *d);
Point getRear (Deck *d);
Deck* insertFront (Deck *d, Point p, char field[][SIZE]);
Deck* insertRear (Deck *d, Point p, char field[][SIZE]);
Deck* deleteFront (Deck *d, char field[][SIZE]);
Deck* deleteRear (Deck *d, char field[][SIZE]);
int kbhit(void);
void initialize_field (char field[SIZE][SIZE]);
void print_field (char field[SIZE][SIZE], int points);
int finish (Deck *d);
Deck* pointerGoToHead (Deck* pointer);
void clearDeck (Deck* d);

// Extras, colocar um objetivo
Point novoObjeto (Deck* d, char field[SIZE][SIZE]);
int playerCollidesObject (Deck* player, Point object);