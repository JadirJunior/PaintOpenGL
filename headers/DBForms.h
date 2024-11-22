#ifndef _DBFORMS_H
#define _DBFORMS_H
#include "figure.h"

void initDBForms(int num);
void drawAllForms();
int insertDBForm(Form f);
void printForms();
Form pick(float x, float y);
int deleteFormDBForms(Form f);
void deleteAllForms();
#endif