//
// Created by jadir on 15/11/2024.
//

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "figure.h"

#define SIDE_TOP 0
#define SIDE_LEFT 1
#define SIDE_BOTTOM 2
#define SIDE_RIGHT 3


//Defining Regions
#define REGION_ACTIVE 0
#define REGION_COLOR 1
#define REGION_FORMS 2
#define REGION_MODE 3


//Defining ToolBar percentual sections
#define TOOLBAR_ACTIVE 0.1f
#define TOOLBAR_COLOR 0.4f
#define TOOLBAR_FORMS 0.2f
#define TOOLBAR_MODES 0.3f


int pickRegion(float x, float y);
void createToolBar(float toolBarX, float toolBarY);

void resize(float newWidth, float newHeight);
void drawToolBar();
void pickColor(Form actualForm, float x, float y);
void pickChangeForm(Form actualForm, float x, float y);
void pickChangeMode(Form actualForm, float x, float y);

#endif
