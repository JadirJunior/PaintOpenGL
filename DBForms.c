#include "headers/figure.h"
#include "headers/DBForms.h"
#include <stdlib.h>
#include <stdio.h>

#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

Form* figuras;

int* positionFigures;
int actualPosition;

int N;

void initDBForms(int number) {
    N = number;
    figuras = malloc(sizeof(Form) * N);
    positionFigures = malloc(sizeof(int) * N);
    actualPosition = 0;

    for (int i = 0; i < N; i++) {
        figuras[i] = NULL;
    }

}

int insertDBForm(Form f) {
    for (int i = 0; i < N; i++) {
        if (figuras[i] == NULL) {
            figuras[i] = f;

            positionFigures[actualPosition] = i;
            actualPosition++;
            return 1;
        }
    }

    return 0;
}

void shiftToLeft(int posInitial, int *arr, int *size) {

    if (posInitial == 0 && (*size) == 1) {
        arr[0] = NULL;
        (*size)--;
        return;
    }

    for (int i = posInitial+1; i < (*size); i++) {
        arr[i - 1] = arr[i];
    }

    (*size)--;
}

void drawAllForms() {
    for (int i = 0; i < N; i++) {
        if (figuras[i] != NULL) {
            drawForm(figuras[i]);
        }
    }
}

void deleteAllForms() {
    for (int i = 0; i < N; i++) {
        //free(figuras);
        figuras[i] = NULL;

    }
}

void printForms() {
    for (int i = 0; i < N; i++) {
        if (figuras[i] != NULL) {
            printf("Figura %d: ", i);
            printfForm(figuras[i]);
            printf("\n");
        }
    }
}

Form pick(float x, float y) {
    
    for (int i = N-1; i >= 0; i--) {
        if (figuras[i] != NULL && pickForm(figuras[i], x, y)) {
            return figuras[i];
        }
    }

    return NULL;
}

int deleteFormDBForms(Form f) {
    int i;
    int formDeleted = 0;
    for (i = 0; i < N && (figuras[i] != NULL); i++) {
        if (figuras[i] == f) {
            deleteForm(figuras[i]);
            formDeleted = 1;
            break;
        }
    }

    if (formDeleted) {
        for (i = i + 1; i < N && (figuras[i] != NULL); i++) {
            figuras[i - 1] = figuras[i];
        }

        figuras[i - 1] = NULL;
    }


    
}