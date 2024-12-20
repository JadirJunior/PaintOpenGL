#ifndef _FORM_H
#define _FORM_H

#define RECTANGLE 0
#define SQUARE 1
#define TRIANGLE_ISO 2
#define HEXAGON 3
#define CIRCLE 4
#define TRIANGLE_EQ 5
#define STAR 6

//Defining modes
#define MODE_INSERT 11
#define MODE_DELETE 12
#define MODE_MOVE 13
#define MODE_RESIZE 14
#define MODE_CLEAR_SCREEN 15
#define MODE_ADD_POINTS 16
#define MODE_REMOVE_POINTS 17

typedef struct form* Form;

struct form {
    int type;
    float x;
    float y;
    float xSize, ySize;

    int points;
    int boundingBox;
    float r, g, b;

    float rBorder, gBorder, bBorder;
};


Form newRectangle(float x, float y, float xSize, float ySize);
Form newSquare(float x, float y, float side);
Form newTriangleIso(float x, float y, float xSize, float ySize);
Form newHexagon(float x, float y, float xSize, float ySize);
Form newCircle(float x, float y, float radius);
Form newTriangleEq(float x, float y, float side);
Form newRectangleC(float x, float y, float xSize, float ySize);
Form newSquareC(float x, float y, float side);
Form newTriangleIsoC(float x, float y, float xSize, float ySize);
Form newHexagonC(float x, float y, float xSize, float ySize);
Form newCircleC(float x, float y, float radius);
Form newTriangleEqC(float x, float y, float side);
Form newRectangle2Point(float xi, float yi, float xf, float yf);
Form newForm2Point(float xi, float yi, float xf, float yf, int type);
Form newCircle2Point(float xi, float yi, float xf, float yf);
Form newStar(float x, float y, float xSize, float ySize);

//Check if XY is inside form
int pickForm(Form f, float x, float y);

void recalculate(Form f, float x, float y);
void changeSecondPoint(Form f, float x, float y);
void getBGColor(Form f, float *c);
void deleteForm(Form f);
void printfForm(Form f);
void drawForm(Form f);
void setBackgroundColor(Form f, float r, float g, float b);
void setBorderColor(Form f, float r, float g, float b);
void changeFormPosition(Form f, float x, float y);
void formatSize(Form f);

Form newInsertMode(float x, float y, float side);
Form newDeleteMode(float x, float y, float side);
Form newResizeMode(float x, float y, float side);
Form newCleanScreenMode(float x, float y, float side);
Form newMoveMode(float x, float y, float side);
Form newAddPointsMode(float x, float y, float side);
Form newRemovePointsMode(float x, float y, float side);

int getStarPoints();
void setStarPoints(int starPoints);
#endif
