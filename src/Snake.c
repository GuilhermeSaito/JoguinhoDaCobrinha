#include "../header/Snake.h"

Deck* createDeck () 
{
    return NULL;
}

Point getFront (Deck *d) 
{   
    return d->p;
}

Point getRear (Deck *d)
{
    Deck* aux = d;
    aux = pointerGoToHead (aux);
    return aux->p;
}

Deck* insertFront (Deck *d, Point p, char field[][SIZE]) 
{
    Deck* novo = (Deck*)malloc(sizeof(Deck));
    novo->p = p;
    novo->next = d;
    novo->prev = NULL;
    if (d != NULL)
        d->prev = novo;

    field[p.x][p.y] = '*'; /*Ponto inserido faz parte do corpo da Snake!*/

    return novo;
}

Deck* insertRear (Deck *d, Point p, char field[][SIZE]) 
{
    Deck* aux = d;
    Deck* novo = (Deck*)malloc(sizeof(Deck));
    novo->p = p;
    novo->next = NULL;
    novo->prev = NULL;
    if (aux == NULL)
        d = novo;
    else
    {
        aux = pointerGoToHead (aux);
        aux->next = novo;
        novo->prev = aux;
    }

    field[p.x][p.y] = '*'; /*Ponto inserido faz parte do corpo da Snake!*/

    return d;
}

Deck* deleteFront (Deck *d, char field[][SIZE]) 
{
    Deck* aux = d->next;
    Point p = d->p;
    field[p.x][p.y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
    aux->prev = NULL;
    free (d);
    return aux;
}

Deck* deleteRear (Deck *d, char field[][SIZE]) 
{
    Deck* aux = d;
    aux = pointerGoToHead (aux);
    Point p = aux->p;
    field[p.x][p.y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
    Deck* aux2 = aux->prev;
    aux2->next = NULL;
    free (aux);
    return d;
}

int kbhit(void) 
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void initialize_field (char field[SIZE][SIZE]) 
{
    int i, j;
    for (i = 0; i < SIZE; i++) 
        for (j = 0; j < SIZE; j++) 
            field[i][j] = ' ';
}

void print_field (char field[SIZE][SIZE], int points) 
{
    int i, j;
    printf("  ");
    for (i = 0; i < SIZE; i++)
        printf(" #");
    printf("\n");
    for (i = 0; i < SIZE; i++) 
    {
        printf(" # ");
        for (j = 0; j < SIZE; j++)
            printf("%c ", field[i][j]);
        printf("#\n");
    }
    printf("  ");
    for (i = 0; i < SIZE; i++)
        printf(" #");
    printf("\nPoints: %d\n", points);
}

int finish (Deck *d) 
{
/*Terminar!*/
    Point p = getFront (d);
    if (p.x < 1 || p.x > SIZE-2 || p.y < 1 || p.y > SIZE-1)
        return 1;
    else
        return 0;
}

Deck* pointerGoToHead (Deck* pointer)
{
    while (pointer->next != NULL)
        pointer = pointer->next;
    return pointer;
}

void clearDeck (Deck* d)
{
    Deck* aux = d;
    while (aux != NULL)
    {
        d = d->next;
        free (aux);
        aux = d;
    }
}

// Extras

Point novoObjeto (Deck* d, char field[SIZE][SIZE])
{
    Point p;
    do
    {
        p.x = (rand() % (SIZE-1)) + 1;
        p.y = (rand() % (SIZE-1)) + 1;
    } while ((p.x != getFront(d).x) && ((p.y != getFront(d).y)));
    field[p.x][p.y] = '@';
    return p;
}

int playerCollidesObject (Deck* player, Point object)
{
    if ((getFront (player).x == object.x) && (getFront (player).y == object.y))
        return 1;
    return 0;
}