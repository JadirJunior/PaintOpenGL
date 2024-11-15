#ifndef _DBFORMS_H
#define _DBFORMS_H
#include "figure.h"

void initDBForms(int num);
void drawAllForms();
void removeRandomFigure();
void generateRandomFigures(int maxSize);
int insertDBForm(Form f);
void printForms();
Form pick(float x, float y);
int deleteFormDBForms(Form f);
#endif