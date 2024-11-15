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

float sizeRegionActive = 50;
float sizeRegionColor = 0;
float sizeRegionForms = 0;
float sizeRegionMode = 0;

float xStartActive = 0;
float xStartColors = 0;
float xStartForms = 0;
float xStartMode = 0;



void setRegions() {
    sizeRegionColor = (xSize - sizeRegionActive) * TOOLBAR_COLOR;
    sizeRegionForms = (xSize - sizeRegionActive) * TOOLBAR_FORMS;
    sizeRegionMode = (xSize - sizeRegionActive) * TOOLBAR_MODES;

    xStartColors = sizeRegionActive;
    xStartForms = sizeRegionActive + sizeRegionColor;
    xStartMode = sizeRegionActive + sizeRegionColor + sizeRegionForms;
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

    for (int i = 0; i < nForms; i++) {
        if (forms[i] != NULL)
        {
            forms[i]->x = xStartForms + 10 + ( 30*i );
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

    for (int i = 0; i < nForms; i++)
    {
        if (forms[i] != NULL)
        {
            drawForm(forms[i]);
        }
    }

}

void setPalettes()
{
    palette = malloc(sizeof(Form) * nPalettes);

    palette[0] = newSquare(xStartColors, ySize/2 - 10, 20);
    setBackgroundColor(palette[0], 1.0, 0.0, 0.0);

    palette[1] = newSquare(xStartColors + 30, ySize/2 - 10, 20);
    setBackgroundColor(palette[1], 1.0, 0.0, 1.0);

    palette[2] = newSquare(xStartColors + 60, ySize/2 - 10, 20);
    setBackgroundColor(palette[2], 0.0, 1.0, 0.0);

    palette[3] = newSquare(xStartColors + 90, ySize/2 - 10, 20);
    setBackgroundColor(palette[3], 0.0, 0.0, 1.0);

    palette[4] = newSquare(xStartColors + 120, ySize/2 - 10, 20);
    setBackgroundColor(palette[4], 1.0, 1.0, 0.0);

    palette[5] = newSquare(xStartColors + 150, ySize/2 - 10, 20);
    setBackgroundColor(palette[5], 0.0, 1.0, 1.0);
}

void setForms()
{
    forms = malloc(sizeof(Form) * nForms);

    forms[0] = newSquare(xStartForms, ySize/2 - 10, 20);
    forms[1] = newCircle(xStartForms + 30, ySize/2 - 10, 20);
    forms[2] = newTriangleEq(xStartForms + 60, ySize/2 - 10, 20);
    forms[3] = newHexagon(xStartForms + 90, ySize/2 - 10, 20, 20);
}

void setMode()
{

}

void createToolBar(Form actualForm, const float toolBarX, const float toolBarY) {
    xSize = toolBarX;
    ySize = toolBarY;
    setRegions();

    actualForm->x = xStartActive + (sizeRegionActive/4);
    actualForm->y = ySize/2 - 10;

    //Criando as formas para alterar a cor
    setPalettes();

    //Criando as formas para alterar a forma
    setForms();

    //Criando as formas para alterar o modo
    setMode();
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

void pickChangeForm(Form actualForm, float x, float y)
{
    Form f = NULL;
    for (int i = 0; i < nForms;i++)
    {
        if (forms[i] != NULL && pickForm(forms[i], x, y)) {
            f = forms[i];
            break;
        }
    }
    if (f == NULL) return;

    actualForm->type = f->type;
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

