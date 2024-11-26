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
int nForms = 7;

//Formas para alterar o modo
Form* modes;
int nModes = 7;

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
            forms[i]->x = xStartForms + 10 + ( 30.0*i );
        }
    }

    for (int i = 0; i < nModes; i++) {
        if (modes[i] != NULL)
        {
            modes[i]->x = xStartMode + 10 + ( 30.0*i );
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

    for(int i = 0; i < nModes; i++) {
        if(modes[i] != NULL) {
            drawForm(modes[i]);
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
    forms[1] = newCircle(xStartForms + 40, ySize/2 - 10, 20);
    forms[2] = newTriangleIso(xStartForms + 50, ySize/2 - 10, 20, 10);
    forms[3] = newHexagon(xStartForms + 100, ySize/2 - 10, 20, 20);
    forms[4] = newStar(xStartForms + 130, ySize/2 - 10, 20, 20);
    forms[5] = newTriangleEq(xStartForms + 160, ySize/2 - 10, 20);
    forms[6] = newRectangle(xStartForms + 190, ySize/2 - 10, 30, 20);
}



void setMode()
{
    //inserir
    //apagar
    //redimensionar
    //limpar tela
    //mover

    modes = malloc(sizeof(Form) * nModes);
    float r=1.0,g=1.0,b=1.0;

    // Modo inserir
    modes[0] = newInsertMode(xStartMode, ySize / 2 - 10, 20);
    setBackgroundColor(modes[0], 0, 1, 0); // Cor verde para representar inserir

    // Modo apagar
    modes[1] = newDeleteMode(xStartMode + 30, ySize / 2 - 10, 20);
    setBackgroundColor(modes[1], r, g, b); // Cor vermelha para apagar

    // Modo redimensionar
    modes[2] = newResizeMode(xStartMode + 60, ySize / 2 - 10, 20);
    setBackgroundColor(modes[2], r, g, b); // Cor azul para redimensionar

    // Modo limpar tela
    modes[3] = newCleanScreenMode(xStartMode + 90, ySize / 2 - 10, 20);
    setBackgroundColor(modes[3], r, g, b); // Cor amarela para limpar tela

    // Modo mover
    modes[4] = newMoveMode(xStartMode + 120, ySize / 2 - 10, 20);
    setBackgroundColor(modes[4], r, g, b); // Cor laranja para mover

    // Adicionando pontas na estrela
    modes[5] = newAddPointsMode(xStartMode + 150, ySize / 2 - 10, 20);
    setBackgroundColor(modes[5], 1.0, 1.0, 0.0);

    //Removendo pontas na estrela
    modes[6] = newRemovePointsMode(xStartMode + 180, ySize / 2 - 10, 20);
    setBackgroundColor(modes[6], 1.0, 0.0, 0.0);

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

void pickColor(Form actualForm, float x, float y, int isBorder) {
    Form f = NULL;
    for (int i = 0; i < nPalettes;i++)
    {
        if (palette[i] != NULL && pickForm(palette[i], x, y)) {
            f = palette[i];
            break;
        }
    }
    if (f == NULL) return;

    if (isBorder)
    {
        float r, g, b;
        r = f->r;
        g = f->g;
        b = f->b;
        setBorderColor(actualForm, r, g, b);
    } else
    {
        float r, g, b;
        r = f->r;
        g = f->g;
        b = f->b;
        setBackgroundColor(actualForm, r, g, b);
    }

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
    int type = f->type;
    actualForm->type = type;
    printf("Setando Points no Form: %d", f->points);
    actualForm->points = f->points;
}

void pickChangeFormAndSize(Form actualForm, float x, float y) {
    Form f = NULL;
    for (int i = 0; i < nForms;i++)
    {
        if (forms[i] != NULL && pickForm(forms[i], x, y)) {
            f = forms[i];
            break;
        }
    }
    if (f == NULL) return;

    int type = f->type;
    actualForm->type = type;
    actualForm->xSize = f->xSize;
    actualForm->ySize = f->ySize;
    actualForm->x = actualForm->x + (actualForm->xSize - f->xSize) / 2;
    actualForm->y = actualForm->y + (actualForm->ySize - f->ySize) / 2;
    actualForm->points = f->points;
}


void pickChangeMode(Form activeColor, int *actualMode, float x, float y) {
    Form f = NULL;
    for (int i = 0; i < nModes;i++) {
        if(modes[i] != NULL) {
            if (modes[i]->type != MODE_ADD_POINTS && modes[i]->type != MODE_REMOVE_POINTS)
                setBackgroundColor(modes[i], 1,1,1);

            if (pickForm(modes[i], x, y)) {
                f = modes[i];
            }
        }
    }

    if (f == NULL) return;

    if (f->type == MODE_ADD_POINTS) {
        forms[4]->points = forms[4]->points + 1 > 10 ? 10 : forms[4]->points + 1;
        if (activeColor->type == STAR)
        {
            activeColor->points = forms[4]->points;
        }

    } else if (f->type == MODE_REMOVE_POINTS) {
        forms[4]->points = forms[4]->points - 1 < 5 ? 5 : forms[4]->points - 1;
        if (activeColor->type == STAR)
        {
            activeColor->points = forms[4]->points;
        }
    } else {
        *actualMode = f->type;
        setBackgroundColor(f, 0, 1,0);
    }
}



int pickRegion(const float x, float y) {
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

