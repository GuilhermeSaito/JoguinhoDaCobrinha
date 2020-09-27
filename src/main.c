#include "../header/Snake.h"

/*
    Obs.:   O *d vai ficar apontado para o Front 
            W = Up, D = Right, S = Down, A = Left
*/

int main () 
{
    srand(time(NULL));

    char field[SIZE][SIZE];
    initialize_field (field); 
    int center = SIZE/2;
    int snake_size = 5;
    Deck *d = createDeck ();

    /* Inserindo a Snake no centro do campo: */
    int i;
    for (i = center-snake_size/2; i <= center+snake_size/2; i++) {
        d = insertFront (d, (Point){center, i}, field);
    }

    char pressionou_prv = ' ';
    char pressionou_act = 'a';
    int reverse = 0; /*variável para inverter cabeça com cauda (e vice-versa)*/
    Point object = novoObjeto (d, field);
    int totalPoints = 0;
    while (!finish(d)) {
        while((!kbhit()) && (!finish(d))) {
            if (reverse) {
                Point p = getFront (d);
                if (pressionou_act ==  'w') { d = insertFront (d, (Point){p.x-1, p.y}, field); }
                else if (pressionou_act ==  's') { d = insertFront (d, (Point){p.x+1, p.y}, field); }
                else if (pressionou_act ==  'a') { d = insertFront (d, (Point){p.x, p.y-1}, field); }
                else { d = insertFront (d, (Point){p.x, p.y+1}, field); }
                d = deleteRear (d, field);
            }
            else {
                Point p = getRear (d);
                if (pressionou_act ==  'w') { d = insertRear (d, (Point){p.x-1, p.y}, field); }
                else if (pressionou_act ==  's') { d = insertRear (d, (Point){p.x+1, p.y}, field); }
                else if (pressionou_act ==  'a') { d = insertRear (d, (Point){p.x, p.y-1}, field); }
                else { d = insertRear (d, (Point){p.x, p.y+1}, field); }
                d = deleteFront (d, field);
            }  
            if (playerCollidesObject (d, object))
            {
                Point p = getRear (d);
                if (pressionou_act ==  'w') { d = insertRear (d, (Point){p.x-1, p.y}, field); }
                else if (pressionou_act ==  's') { d = insertRear (d, (Point){p.x+1, p.y}, field); }
                else if (pressionou_act ==  'a') { d = insertRear (d, (Point){p.x, p.y-1}, field); }
                else { d = insertRear (d, (Point){p.x, p.y+1}, field); }
                object = novoObjeto(d, field);
                totalPoints++;
            }
            print_field (field, totalPoints);
            usleep(250000);
            system("clear");
        }
        if (!finish(d)) {
            /*Cada vez que uma tecla é pressionada o controle executa esse trecho: */
            pressionou_prv = pressionou_act;
            pressionou_act = getchar();
            if ((pressionou_act ==  's') && (pressionou_prv ==  'w')) { reverse = !reverse; }
            else if ((pressionou_act ==  'w') && (pressionou_prv ==  's')) { reverse = !reverse; }
            else if ((pressionou_act ==  'a') && (pressionou_prv ==  'd')) { reverse = !reverse; }
            else if ((pressionou_act ==  'd') && (pressionou_prv ==  'a')) { reverse = !reverse; }
        }
    }
    printf ("#### Perdeu :(  \n");
    clearDeck (d);
    return 0;
}
