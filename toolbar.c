#include "headers/figure.h"
#include "headers/toolbar.h"
#include <stdlib.h>
#include <stdio.h>

#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0


//Formas para alterar a cor atual
Form* palette;
int nPalettes = 10;

//Formas para alterar a forma atual
Form* forms;
int nForms = 4;

//Tamanho da toolbar
float ySize = 40;
float xSize = 500;

float sizeRegionActive = 0;
float sizeRegionColor = 0;
float sizeRegionForms = 0;
float sizeRegionMode = 0;



void setRegions() {
    sizeRegionActive = xSize * TOOLBAR_ACTIVE;
    sizeRegionColor = xSize * TOOLBAR_COLOR;
    sizeRegionForms = xSize * TOOLBAR_FORMS;
    sizeRegionMode = xSize * TOOLBAR_MODES;

    // printf("Ativa: %f\n", sizeRegionActive);
    // printf("Cor: %f\n", sizeRegionColor);
    // printf("Forms: %f\n", sizeRegionForms);
    // printf("Modo: %f\n", sizeRegionMode);
}

void resize(float newWidth, float newHeight) {
    xSize = newWidth;
    ySize = newHeight;
    setRegions();
}

void createToolBar(const float toolBarX, const float toolBarY) {
    xSize = toolBarX;
    ySize = toolBarY;
    setRegions();
}

int pickRegion(const float x, float y) {

    // printf("X clicado: %f\n", x);

    //Não está na toolbar
    if (y > ySize) return -1;

    float actualSum = sizeRegionActive;

    if (x < actualSum) {
        printf("Regiao ativa\n");
        return REGION_ACTIVE;
    }


    actualSum+= sizeRegionColor;
    if (x < actualSum)
    {
        printf("Regiao das cores\n");
        return REGION_COLOR;
    }

    actualSum += sizeRegionForms;
    if (x < actualSum)
    {
        printf("Regiao para selecionar forma\n");
        return REGION_FORMS;
    }

    printf("Regiao para alterar o modo\n");
    return REGION_MODE;
}

