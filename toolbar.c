#include "headers/figure.h"
#include "headers/toolbar.h"

#include <gl.h>
#include <stdlib.h>
#include <stdio.h>

#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0


//Formas para alterar a cor atual
Form* palette;
int nPalettes = 5;

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

float xStartActive = 0;
float xStartColors = 0;
float xStartForms = 0;
float xStartMode = 0;



void setRegions() {
    sizeRegionActive = xSize * TOOLBAR_ACTIVE;
    sizeRegionColor = xSize * TOOLBAR_COLOR;
    sizeRegionForms = xSize * TOOLBAR_FORMS;
    sizeRegionMode = xSize * TOOLBAR_MODES;

    xStartColors = sizeRegionActive;
    xStartForms = sizeRegionActive + sizeRegionColor;
    xStartMode = sizeRegionActive + sizeRegionColor + sizeRegionForms;

    // printf("Ativa: %f\n", sizeRegionActive);
    // printf("Cor: %f\n", sizeRegionColor);
    // printf("Forms: %f\n", sizeRegionForms);
    // printf("Modo: %f\n", sizeRegionMode);
}

void resize(float newWidth, float newHeight) {
    xSize = newWidth;
    ySize = newHeight;
    setRegions();

    //update new positions
    for (int i = 0; i < nPalettes; i++) {
        if (palette[i] != NULL)
        {
            palette[i]->x = xStartColors + 10 + ( 30*i );
        }
    }

}

void drawLinesToolBar() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(sizeRegionActive, 0);
    glVertex2f(sizeRegionActive, ySize);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(sizeRegionActive+sizeRegionColor, 0);
    glVertex2f(sizeRegionActive+sizeRegionColor, ySize);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(sizeRegionActive+sizeRegionColor+sizeRegionForms, 0);
    glVertex2f(sizeRegionActive+sizeRegionColor+sizeRegionForms, ySize);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, ySize);
    glVertex2f(sizeRegionActive+sizeRegionColor+sizeRegionForms+sizeRegionMode, ySize);
    glEnd();

    glFlush();
}

void drawToolBar() {

    //Desenhando os limites das seções
    drawLinesToolBar();

    for (int i = 0; i < nPalettes; i++)
    {
        if (palette[i] != NULL)
        {
            drawForm(palette[i]);
        }
    }

}


void createToolBar(const float toolBarX, const float toolBarY) {
    xSize = toolBarX;
    ySize = toolBarY;
    setRegions();

    //Criando as formas para alterar a cor
    palette = malloc(sizeof(Form) * nPalettes);
    float startX = sizeRegionActive + 10;

    palette[0] = newSquare(startX, ySize/2 - 10, 20);
    setBackgroundColor(palette[0], 1.0, 0.0, 0.0);

    palette[1] = newSquare(startX + 30, ySize/2 - 10, 20);
    setBackgroundColor(palette[1], 1.0, 0.0, 1.0);

    palette[2] = newSquare(startX + 60, ySize/2 - 10, 20);
    setBackgroundColor(palette[2], 0.0, 1.0, 0.0);

    palette[3] = newSquare(startX + 90, ySize/2 - 10, 20);
    setBackgroundColor(palette[3], 0.0, 0.0, 1.0);

    palette[4] = newSquare(startX + 120, ySize/2 - 10, 20);
    setBackgroundColor(palette[4], 1.0, 1.0, 0.0);

    palette[5] = newSquare(startX + 150, ySize/2 - 10, 20);
    setBackgroundColor(palette[5], 0.0, 1.0, 1.0);
}

void pickColor(Form actualForm, float x, float y) {
    Form f = NULL;
    for (int i = 0; i < nPalettes;i++)
    {
        if (palette[i] != NULL && pickForm(palette[i], x, y)) {
            f = palette[i];
            break;
        }
    }
    if (f == NULL) return;
    setBackgroundColor(actualForm, f->r, f->g, f->b);
}


int pickRegion(const float x, float y) {

    // printf("X clicado: %f\n", x);

    //Não está na toolbar
    if (y > ySize) return -1;

    float actualSum = sizeRegionActive;

    if (x < actualSum) {
        return REGION_ACTIVE;
    }


    actualSum+= sizeRegionColor;
    if (x < actualSum)
    {
        return REGION_COLOR;
    }

    actualSum += sizeRegionForms;
    if (x < actualSum)
    {
        return REGION_FORMS;
    }

    return REGION_MODE;
}

