#include <stdio.h>
#include <stdlib.h>

/*DEFINICION DE MACROS*/
#define ARRAY_LENGTH 4
#define MAX_ITER 10

/*DEFINICION DE TIPOS*/
typedef struct Explorer_tag
{
    float x;
    float y;
    float vel_x;

    float x_prev;
    float y_prev;

    int id;
}Explorer;


/*DECLARACION DE VARIABLES*/


/*DEFINICION DE FUNCIONES*/
void Init_Explorer(Explorer *ex, float x_val, float (*p_fun)(float), float vel_x_val, int id_val)
{
    ex->x = x_val;
    ex->y = p_fun(ex->x);
    ex->vel_x = vel_x_val;

    ex->x_prev = ex->x;
    ex->y_prev = ex->y;

    ex->id = id_val;
}

void Print_Explorers(Explorer *ex, int array_length)
{
    int i;
    for(i = 0; i < array_length; ++i)
        printf("Explorer # %i -> x = %.2f, y = %.2f, vel_x = %.2f\r\n", ex[i].id, ex[i].x, ex[i].y, ex[i].vel_x);
}

void Move_Explorers(Explorer *ex, float (*p_fun)(float), int array_length )
{
    int i;
    for(i = 0; i < array_length; ++i)
    {
        ex[i].x_prev = ex[i].x;
        ex[i].y_prev = ex[i].y;

        ex[i].x += ex[i].vel_x;
        ex[i].y = p_fun(ex[i].x);
    }
}

void Accel_Explorer(Explorer *ex, float accel_fact)
{
    ex->vel_x += accel_fact;
}

void Eval_Explorers_Position(Explorer *ex, int array_length)
{
    int i,j;
    for(i = 0; i < array_length; ++i)
    {
        if(ex[i].y >= ex[i].y_prev) continue; // ">" para maximos, "<" para minimos
        for(j = 0; j < array_length; ++j)
        {
        }
    }
}


float Math_Func(float x)
{
    return x*x;
}

/*FUNCION PRINCIPAL*/
int main()
{
    float (*p_eval_func)(float);
    p_eval_func = Math_Func;
    Explorer explorers[ARRAY_LENGTH];

    Init_Explorer(&explorers[0], -3.0, p_eval_func, -0.5, 0);
    Init_Explorer(&explorers[1], -2.0, p_eval_func, 0.5, 1);
    Init_Explorer(&explorers[2], 2.0, p_eval_func, -0.5, 2);
    Init_Explorer(&explorers[3], 3.0, p_eval_func, 0.5, 3);

    Print_Explorers(explorers, ARRAY_LENGTH);
    Move_Explorers(explorers, p_eval_func, ARRAY_LENGTH);
    Print_Explorers(explorers, ARRAY_LENGTH);

    return 0;
}

/*ALGORITMO DE ENJAMBRE*/
//OBJETIVOS DEL AUTOMATA
//  >ESCALAR UNA MONTAÑA
//  >DESCENDER A UNA CUEVA
//
//DEFINICION DEL AUTOMATA
//  +POSICION
//  +VELOCIDAD
//
//FUNCIONES DEL AUTOMATA
//  *MOVE() NUEVA POSICION = POSICION ACTUAL + VELOCIDAD
//  *ACELERAR() NUEVA VELOCIDAD = VELOCIDAD ANTERIOR + FACTOR DE ACELERACION
//
//CONOCIMIENTOS DEL AUTOMATA
//  -SUBI O BAJE CON RESPECTO A MI POSICION ANTERIOR
//  -MIS COMPAÑEROS DE LA DERECHA  IZQUIERDA ESTAN MAS ARRIBA O MAS ABAJO QUE YO
//
//LOGICA DE DECISIONES
//  ()SI CON RESPECTO A MI POSICION ANTERIOR ME ACERQUE A MI OBJETIVO, ME VUELVO A MOVER EN ESA DIRECCION
//
//  ()SI CON RESPECTO A MI POSICION ANTERIOR ME ALEJE DE MI OBJETIVO, PREGUNTO
//      #SI MI COMPAÑERO DE LA IZQUIERDA ESTA MAS CERCA DEL OBJETIVO, ME MUEVO EN ESA DIRECCION
//      #SI MI COMPAÑERO DE LA DERECHA ESTA MAS CERCA DE MI OBJETIVO, ME MUEVO EN ESA DIRECCION
