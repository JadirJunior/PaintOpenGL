#include "headers/figure.h"
#include "headers/DBForms.h"
#include "headers/toolbar.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>


#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

int cont;
int windowWidth = 500;
int windowHeight = 500;

// state variable
int type = RECTANGLE;
float rState = 1.0;
float gState = 1.0;
float bState = 1.0;
float deltaColor = 0.1;

int creatingForm = 0;

Form selectedForm = NULL;

//feedback
Form activeColor;

int xLastClick;
int yLastClick;

int yToolBarSize = 40;


void displayForms() {
    srand(time(NULL));
    glClear(GL_COLOR_BUFFER_BIT);

    cont++;

    printf("Contador: %d\n", cont);


    drawAllForms();
    drawToolBar();
    drawForm(activeColor);

    glFlush();
}

void insertForm(int x, int y) {
    Form f = createRandomFigure2(type, x, y, 200);
    setBackgroundColor(f, rState, gState, bState);

    if (!insertDBForm(f)) {
        printf("Memory Full\n");
        deleteForm(f);
    }
    else glutPostRedisplay();
}

void deleteScreenForm(int x, int y) {
    Form f = pick(x, y);
    if (f != NULL) {
        printfForm(f);
        deleteFormDBForms(f);
        glutPostRedisplay();
    }
    else {
        printf("NO Form..\n");
    }
}

void mykey(unsigned char key, int x, int y)
{
    if (key == 'Q' | key == 'q')
        exit(0);

    switch (key) {
        case 'r':
        case 'R':
            type = RECTANGLE; break;
        case 't':
        case 'T':
            type = TRIANGLE_ISO; break;
        case 's':
        case 'S':
            type = SQUARE; break;
        case '1':
            rState += deltaColor; 
            if (rState > 1.0) rState = 1.0;
            break;
        case '2':
            gState += deltaColor;
            if (gState > 1.0) gState = 1.0;
            break;
        case '3':
            bState += deltaColor;
            if (bState > 1.0) bState = 1.0;
            break;
        
        case '4':
            rState -= deltaColor; 
            if (rState < 0.0) rState = 0.0;
            break;
        case '5':
            gState -= deltaColor;
            if (gState < 0.0) gState = 0.0;
            break;
        case '6':
            bState -= deltaColor;
            if (bState < 0.0) bState = 0.0;
            break;

        case 'i':
        case 'I':
            insertForm(x, y);
            break;

        case 'd':
        case 'D':
            deleteScreenForm(x, y);

    }
    setBackgroundColor(activeColor, rState, gState, bState);
    glutPostRedisplay();
}

void myMouseCanvas(GLint button, GLint state, GLint x, GLint y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        printf("LEFT BUTTON PRESSED\n");
        // if (type == RECTANGLE) {
            if (creatingForm) {
                recalculate(selectedForm, x, y);
                creatingForm = 0;
                selectedForm = NULL;
                glutPostRedisplay();
            }
            else {
                //First click
                selectedForm = newForm2Point(x, y, x, y, type);
                setBackgroundColor(selectedForm, rState, gState, bState);

                if (!insertDBForm(selectedForm)) {
                    printf("MEMORY FULL!!\n");
                    deleteForm(selectedForm);
                    selectedForm = NULL;
                }
                else {
                    creatingForm = 1;
                    glutPostRedisplay();
                }
            }
        // }
        // else {
        //     insertForm(x, y);
        // }

    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        //printf("Click with the right button (X, Y) (%d, %d)\n", x, y);
        printf("RIGHT BUTTON PRESSED\n");
        deleteScreenForm(x, y);
    }
}

void mouseMotion(int x, int y) {
    y = windowHeight - y;

    

    //printf("Moving pressing some button... (%i, %i)\n", x, y);
}

void mousePassiveMotion(int x, int y) {
    y = windowHeight - y;

    if (creatingForm) {
        changeSecondPoint(selectedForm, x, y);
        glutPostRedisplay();
    }

    //printf("Moving... (%i, %i)\n", x, y);
}

void mouseClick(GLint button, GLint state, GLint x, GLint y) {

    y = windowHeight - y;
    int region = pickRegion(x, y);

    if (region != -1) {

        switch (region)
        {
            case REGION_ACTIVE:
                printf("Region active\n");
                break;
            case REGION_COLOR:
                pickColor(activeColor, x, y);
                rState = activeColor->r;
                gState = activeColor->g;
                bState = activeColor->b;
                break;
            case REGION_FORMS:
                pickChangeForm(activeColor, x, y);
                type = activeColor->type;
                setBackgroundColor(activeColor, rState, gState, bState);
                break;
            default:
                printf("Resto\n");
                break;
        }
    }
    else {
        myMouseCanvas(button, state, x, y);
    }
}

void init(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
}

void reShape(int width, int height) {
    windowHeight = height;
    windowWidth = width;
    resize(windowWidth, yToolBarSize);
    glViewport(0, 0, width, height);
    init(width, height);
}

void setupOpenGL() {
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Janela para figuras");
    init(windowWidth, windowHeight);
    glutDisplayFunc(displayForms);
    glutMouseFunc(mouseClick);
    glutReshapeFunc(reShape);
    glutKeyboardFunc(mykey);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
}

int main(int argc, char** argv) {

    srand(time(NULL));
    cont = 0;
    initDBForms(10);
    printForms();
    activeColor = newSquare(10, 10, 20);
    setBackgroundColor(activeColor, rState, gState, bState);
    createToolBar(activeColor, windowWidth, yToolBarSize);

    glutInit(&argc, argv);
    setupOpenGL();

    return 0;
}
