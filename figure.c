#include "headers/figure.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>

#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

#define PI 3.1415
//TODO: REFACTORS
/*
    alterar cor
    desenhar quadrado e retângulo
    triangulo equilátero
    trocar numero de faces da estrela
    leve bug parece que a figura sobe
 */


void recalculatingPoints(float* xi, float* yi, float* xf, float* yf) {
    float aux1, aux2;
    float xSide = fmaxf((*xf) - (*xi), (*xi) - (*xf));
    float ySide = fmaxf((*yf) - (*yi), (*yi) - (*yf));

    if ( (*xf) < (*xi) && (*yf) < (*yi)) {
        aux1 = *xi, aux2 = *yi;
        *xi = *xf;
        *yi = *yf;

        *xf = aux1;
        *yf = aux2;
    }
    else if ( (*xf) < (*xi)) {
        *xi = (*xi) - xSide;
        *xf = (*xf) + xSide;
    }
    else if ( (*yf) < (*yi)) {
        *yi = (*yi) - ySide;
        *yf = (*yf) + ySide;
    }
}


Form newForm(float x, float y, float xSize, float ySize, int type) {
    Form f = (Form)malloc(sizeof(struct form));
    f->x = x;
    f->y = y;
    f->xSize = xSize;
    f->ySize = ySize;

    f->r = 1.0;
    f->g = 1.0;
    f->b = 1.0;

    f->type = type;

    return f;
}

Form newFormC(float x, float y, float xSize, float ySize, int type) {
    return newForm(x - (xSize / 2), y - (ySize / 2), xSize, ySize, type);
}

Form newRectangle(float x, float y, float xSize, float ySize) {
    return newForm(x,y,xSize,ySize, RECTANGLE);
}

Form newRectangleC(float x, float y, float xSize, float ySize) {
    return newFormC(x, y, xSize, ySize, RECTANGLE);
}

Form newSquare(float x, float y, float side) {
    return newForm(x, y, side, side, SQUARE);
}

Form newSquareC(float x, float y, float side) {
    return newFormC(x, y, side, side, SQUARE);
}

Form newTriangleIso(float x, float y, float xSize, float ySize) {
    return newForm(x, y, xSize, ySize, TRIANGLE_ISO);
}

Form newRectangle2Point(float xi, float yi, float xf, float yf) {
    recalculatingPoints(&xi, &yi, &xf, &yf);

    return newForm(xi, yi, xf-xi, yf-yi, RECTANGLE);
}

Form newForm2Point(float xi, float yi, float xf, float yf, int type) {
    //recalculatingPoints(&xi, &yi, &xf, &yf);

    return newForm(xi, yi, xf-xi, yf-yi, type);
}

Form newCircle2Point(float xi, float yi, float xf, float yf) {
    //recalculatingPoints(&xi, &yi, &xf, &yf);
    float r = sqrt(pow((xf-xi), 2) + pow((yf-yi), 2));
    return newCircle(xi, yi, r);
}

Form newTriangleIsoC(float x, float y, float xSize, float ySize) {
    return newFormC(x, y, xSize, ySize, TRIANGLE_ISO);
}

Form newHexagon(float x, float y, float xSize, float ySize) {
    return newForm(x, y, xSize, ySize, HEXAGON);
}

Form newHexagonC(float x, float y, float xSize, float ySize) {
    return newFormC(x, y, xSize, ySize, HEXAGON);
}

Form newStar(float x, float y, float xSize, float ySize) {
    return newForm(x, y, xSize, ySize, STAR);
}


Form newCircle(float x, float y, float radius) {
    return newForm(x, y, radius, radius, CIRCLE);
}

Form newCircleC(float x, float y, float radius) {
    return newFormC(x, y, radius, radius, CIRCLE);
}

Form newTriangleEq(float x, float y, float side) {
    return newForm(x, y, side, ( (side*sqrtf(3)) / 2), TRIANGLE_EQ);
}

Form newTriangleEqC(float x, float y, float side) {
    return newFormC(x, y, side, ((side * sqrtf(3)) / 2), TRIANGLE_EQ);
}

void formatSize(Form f) {
    if ((f->xSize < 0 && f->ySize < 0)) { //Terceiro quadrante
        f->xSize = abs(f->xSize) < abs(f->ySize) ? f->ySize : f->xSize;
        f->ySize = f->xSize;
    } else if ( (f->xSize < 0 && f->ySize > 0) ) { //Segundo Quadrante

        f->xSize = abs(f->xSize) > f->ySize ? f->xSize : -f->ySize;
        f->ySize = -f->xSize;

    } else if ( f->xSize > 0 && f->ySize < 0 ) {
        f->xSize = f->xSize > abs(f->ySize) ? f->xSize : -f->ySize;
        f->ySize = -f->xSize;
    } else
    {
        f->xSize = fmaxf(f->xSize, f->ySize);
        f->ySize = f->xSize;
    }
}

void setBackgroundColor(Form f, float r, float g, float b) {
    f->r = r;
    f->g = g;
    f->b = b;
}

Form newInsertMode(float x, float y, float side) {
    return newForm(x, y, side, side, MODE_INSERT);
}

Form newDeleteMode(float x, float y, float side) {
    return newForm(x, y, side, side, MODE_DELETE);
}
Form newResizeMode(float x, float y, float side) {
    return newForm(x, y, side, side, MODE_RESIZE);
}
Form newCleanScreenMode(float x, float y, float side) {
    return newForm(x, y, side, side, MODE_CLEAR_SCREEN);

}
Form newMoveMode(float x, float y, float side) {
    return newForm(x, y, side, side, MODE_MOVE);
}


void changeSecondPoint(Form f, float x, float y)
{
    f->xSize = x - f->x;
    f->ySize = y - f->y;
    if (f->type == SQUARE) formatSize(f);
}

void changeFormPosition(Form f, float x, float y) {
    f->x = x - f->xSize / 2;
    f->y = y - f->ySize / 2;
}

void recalculate(Form f, float x, float y) {
    //recalculatingPoints((&f->x), (&f->y), &x, &y);
    changeSecondPoint(f, x, y);

    switch (f->type)
    {
        case SQUARE:
        case CIRCLE:
            formatSize(f);
            break;

    }
}

void getBGColor(Form f, float* c) {
    c[0] = f->r;
    c[1] = f->g;
    c[2] = f->b;
}

void deleteForm(Form f) {
    free(f);
}

void updateForm(Form f, float dx, float dy) {
    f->x += dx;
    f->y += dy;
}


void printfForm(Form f) {
    printf("Graphical Form BBox: (%.2f,%.2f), (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\t",
        f->x, f->y,
        f->x, f->y + f->ySize,
        f->x + f->xSize, f->y + f->ySize,
        f->x + f->xSize, f->y);


    printf("Center(%.2f,%.2f) Size{%.2f,%.2f}\n",
        f->x + (f->xSize / 2), f->y + (f->ySize / 2),
        f->xSize, f->ySize);

}

int pickForm(Form f, float x, float y) {
    return (x <= f->x + f->xSize && x >= f->x && y <= f->y + f->ySize && y >= f->y) || //Primeiro quadrante
        ( x >= f->x + f->xSize && x <= f->x && y <= f->y + f->ySize && y >= f->y) || //Segundo quadrante
        ( x >= f->x + f->xSize && x <= f->x && y >= f->y + f->ySize && y <= f->y) || //Terceiro quadrante
        ( x <= f->x + f->xSize && x >= f->x && y >= f->y + f->ySize && y <= f->y); //Quarto quadrante
    ;
}

Form createRandomFigure(int x, int y, int maxSize) {
    Form f;

    switch (rand() % 6) {
    case RECTANGLE:
        f = newRectangle(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
        break;
    case SQUARE:
        f = newSquare(x, y, (rand() % (maxSize / 4)));
        break;
    case CIRCLE:
        f = newCircle(x, y, (rand() % (maxSize / 4)));
        break;
    case TRIANGLE_ISO:
        f = newTriangleIso(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
        break;
    case TRIANGLE_EQ:
        f = newTriangleEq(x, y, (rand() % (maxSize / 4)));
        break;
    case HEXAGON:
        f = newHexagon(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
        break;
    default:
        f = newRectangle(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
        break;
    }

    return f;

}

Form createRandomFigure2(int type, int x, int y, int maxSize) {
    Form f;

    switch (type) {
        case RECTANGLE:
            f = newRectangleC(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
            break;
        case SQUARE:
            f = newSquareC(x, y, (rand() % (maxSize / 4)));
            break;
        case CIRCLE:
            f = newCircleC(x, y, (rand() % (maxSize / 4)));
            break;
        case TRIANGLE_ISO:
            f = newTriangleIsoC(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
            break;
        case TRIANGLE_EQ:
            f = newTriangleEqC(x, y, (rand() % (maxSize / 4)));
            break;
        case HEXAGON:
            f = newHexagonC(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
            break;
        default:
            f = newRectangleC(x, y, (rand() % (maxSize / 4)), (rand() % (maxSize / 4)));
            break;
    }

    return f;

}

void drawRectangle(Form f) {

    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x, f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x, f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y);
    glEnd();


}

void drawTriangle(Form f) {
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x + (f->xSize / 2), f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y);
    glEnd();


    //glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x + (f->xSize / 2.0), f->y + f->ySize);
        glVertex2f(f->x + f->xSize, f->y);
    glEnd();
}

void drawCircle(Form f, float radius, float faces) {

    float centerX = f->x + (f->xSize / 2);
    float centerY = f->y + (f->ySize / 2);

    float step = (2 * PI) / faces;

    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 2*PI; i += step) {
        float x = centerX + radius * cos(i);
        float y = centerY + radius * sin(i);

        glVertex2f(x, y);
    }

    glEnd();

}

void drawTriangleEq(Form f) {


    glColor3f(f->r, f->g, f->b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x + (f->xSize / 2), f->y + (f->ySize) );
        glVertex2f(f->x + (f->xSize), f->y);
    glEnd();


    //glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(f->x, f->y);
        glVertex2f(f->x + (f->xSize / 2), f->y + (f->ySize));
        glVertex2f(f->x + (f->xSize), f->y);
    glEnd();

}

void drawStar(Form f) {

    float radius = f->xSize / 4;
    float faces = 10;
    float centerX = f->x + (f->xSize / 2);
    float centerY = f->y + (f->ySize / 2);

    float step = (2 * PI) / faces;

    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    for (float i = PI/12; i < 2*PI; i += step) {
        float x = centerX + radius * cos(i);
        float y = centerY + radius * sin(i);

        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (float i = PI / 12; i < 2 * PI; i += step) {
        float x = centerX + radius * cos(i);
        float y = centerY + radius * sin(i);

        glVertex2f(x, y);

        glVertex2f(x + radius*cos(i + step), y + radius*sin(i + step));


        float x2 = centerX + radius * cos(i + step);
        float y2 = centerY + radius * sin(i + step);

        glVertex2f(x2, y2);
    }
    glEnd();

}

void drawInsert(Form f) {
    float xCenter = f->x + (f->xSize / 2);
    float yCenter = f->y + (f->ySize / 2);

    glColor3f(f->r, f->g, f->b);
    glBegin(GL_LINES);
    glVertex2f(xCenter, yCenter - f->ySize/2);
    glVertex2f(xCenter, yCenter + f->ySize/2);
    glVertex2f(xCenter - f->xSize/2, yCenter);
    glVertex2f(xCenter + f->xSize/2, yCenter); // Diagonal 2
    glEnd();
}

void drawX(Form f) {

    float xCenter = f->x + (f->xSize / 2);
    float yCenter = f->y + (f->ySize / 2);

    glColor3f(f->r, f->g, f->b);
    glBegin(GL_LINES);
    glVertex2f(xCenter - f->xSize/2, yCenter - f->ySize/2);
    glVertex2f(xCenter + f->xSize/2, yCenter + f->ySize/2); // Diagonal 1
    glVertex2f(xCenter - f->xSize/2, yCenter + f->ySize/2);
    glVertex2f(xCenter + f->xSize/2, yCenter - f->ySize/2); // Diagonal 2
    glEnd();
}

void drawIconMove(Form f) {
    float xCenter = f->x + (f->xSize / 2);
    float yCenter = f->y + (f->ySize / 2);

    float arrowLength = f->xSize / 2; // Comprimento das linhas principais
    float arrowHeadSize = fmin(f->xSize, f->ySize) / 4; // Tamanho das pontas das setas

    glColor3f(f->r, f->g, f->b);

    // Linhas principais
    glBegin(GL_LINES);
    // Linha horizontal
    glVertex2f(xCenter - arrowLength, yCenter);
    glVertex2f(xCenter + arrowLength, yCenter);

    // Linha vertical
    glVertex2f(xCenter, yCenter - arrowLength);
    glVertex2f(xCenter, yCenter + arrowLength);
    glEnd();

    // Triângulos para as setas
    glBegin(GL_TRIANGLES);
    // Seta esquerda
    glVertex2f(xCenter - arrowLength, yCenter);
    glVertex2f(xCenter - arrowLength + arrowHeadSize / 2, yCenter + arrowHeadSize / 2);
    glVertex2f(xCenter - arrowLength + arrowHeadSize / 2, yCenter - arrowHeadSize / 2);

    // Seta direita
    glVertex2f(xCenter + arrowLength, yCenter);
    glVertex2f(xCenter + arrowLength - arrowHeadSize / 2, yCenter + arrowHeadSize / 2);
    glVertex2f(xCenter + arrowLength - arrowHeadSize / 2, yCenter - arrowHeadSize / 2);

    // Seta superior
    glVertex2f(xCenter, yCenter + arrowLength);
    glVertex2f(xCenter - arrowHeadSize / 2, yCenter + arrowLength - arrowHeadSize / 2);
    glVertex2f(xCenter + arrowHeadSize / 2, yCenter + arrowLength - arrowHeadSize / 2);

    // Seta inferior
    glVertex2f(xCenter, yCenter - arrowLength);
    glVertex2f(xCenter - arrowHeadSize / 2, yCenter - arrowLength + arrowHeadSize / 2);
    glVertex2f(xCenter + arrowHeadSize / 2, yCenter - arrowLength + arrowHeadSize / 2);
    glEnd();
}

void drawIconResize(Form f) {
    float xCenter = f->x + (f->xSize / 2);
    float yCenter = f->y + (f->ySize / 2);

    float arrowHeadSize = fmin(f->xSize, f->ySize) / 4;

    glColor3f(f->r, f->g, f->b);

    // Desenha a linha diagonal
    glBegin(GL_LINES);
    glVertex2f(xCenter - f->xSize / 2, yCenter - f->ySize / 2);
    glVertex2f(xCenter + f->xSize / 2, yCenter + f->ySize / 2);
    glEnd();

    // Desenha as setas
    glBegin(GL_TRIANGLES);
    // Seta inferior esquerda
    glVertex2f(xCenter - f->xSize / 2, yCenter - f->ySize / 2);
    glVertex2f(xCenter - f->xSize / 2 + arrowHeadSize, yCenter - f->ySize / 2);
    glVertex2f(xCenter - f->xSize / 2, yCenter - f->ySize / 2 + arrowHeadSize);

    // Seta superior direita
    glVertex2f(xCenter + f->xSize / 2, yCenter + f->ySize / 2);
    glVertex2f(xCenter + f->xSize / 2 - arrowHeadSize, yCenter + f->ySize / 2);
    glVertex2f(xCenter + f->xSize / 2, yCenter + f->ySize / 2 - arrowHeadSize);
    glEnd();

}

void drawClearScreenIcon(Form f) {
    //validar se a tela ta limpa ou nao deixar verde(nao tem nada para limpar) ou vermelho(tem coisa para limpar)


    drawRectangle(f);
    setBackgroundColor(f, 1, 0, 0);
    drawX(f);

}




void drawForm(Form f) {

    switch (f->type) {
    case RECTANGLE:
        drawRectangle(f);
        break;
    case TRIANGLE_ISO:
        drawTriangle(f);
        break;
    case SQUARE:
        drawRectangle(f);
        break;
    case HEXAGON:
        drawCircle(f, f->xSize/2, 6);
        break;
    case CIRCLE:
        drawCircle(f, f->xSize/2, 50);
        break;
    case TRIANGLE_EQ:
        drawTriangleEq(f);
        break;
    case STAR:
        drawStar(f);
        break;
    case MODE_INSERT:
        drawInsert(f);
        break;
    case MODE_DELETE:
        drawX(f);
        break;
    case MODE_MOVE:
        drawIconMove(f);
        break;
    case MODE_RESIZE:
        drawIconResize(f);
        break;
    case MODE_CLEAR_SCREEN:
        drawClearScreenIcon(f);
        break;
    }
}

