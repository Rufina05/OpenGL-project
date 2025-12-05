#include "Cube.h"
#include <GLFW/glfw3.h>

void drawCube(float s) {
    float h = s / 2.0f;

    glColor3f(1, 1, 1); // белый — чтобы не портить текстуру

    glBegin(GL_QUADS);

    // ---------- ПЕРЕД ----------
    glTexCoord2f(0, 0); glVertex3f(-h, -h, h);
    glTexCoord2f(1, 0); glVertex3f(h, -h, h);
    glTexCoord2f(1, 1); glVertex3f(h, h, h);
    glTexCoord2f(0, 1); glVertex3f(-h, h, h);

    // ---------- ЗАД ----------
    glTexCoord2f(0, 0); glVertex3f(h, -h, -h);
    glTexCoord2f(1, 0); glVertex3f(-h, -h, -h);
    glTexCoord2f(1, 1); glVertex3f(-h, h, -h);
    glTexCoord2f(0, 1); glVertex3f(h, h, -h);

    // ---------- ЛЕВО ----------
    glTexCoord2f(0, 0); glVertex3f(-h, -h, -h);
    glTexCoord2f(1, 0); glVertex3f(-h, -h, h);
    glTexCoord2f(1, 1); glVertex3f(-h, h, h);
    glTexCoord2f(0, 1); glVertex3f(-h, h, -h);

    // ---------- ПРАВО ----------
    glTexCoord2f(0, 0); glVertex3f(h, -h, h);
    glTexCoord2f(1, 0); glVertex3f(h, -h, -h);
    glTexCoord2f(1, 1); glVertex3f(h, h, -h);
    glTexCoord2f(0, 1); glVertex3f(h, h, h);

    // ---------- ВЕРХ ----------
    glTexCoord2f(0, 0); glVertex3f(-h, h, h);
    glTexCoord2f(1, 0); glVertex3f(h, h, h);
    glTexCoord2f(1, 1); glVertex3f(h, h, -h);
    glTexCoord2f(0, 1); glVertex3f(-h, h, -h);

    // ---------- НИЗ ----------
    glTexCoord2f(0, 0); glVertex3f(-h, -h, -h);
    glTexCoord2f(1, 0); glVertex3f(h, -h, -h);
    glTexCoord2f(1, 1); glVertex3f(h, -h, h);
    glTexCoord2f(0, 1); glVertex3f(-h, -h, h);

    glEnd();
}
