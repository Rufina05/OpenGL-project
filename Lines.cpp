#include <GLFW/glfw3.h>
#include "Lines.h"

void drawLines(float cubeSize, float sphereRadius, float cubeY) {
    float s = cubeSize / 2.0f;
    float sphereY = 0.4f; // высота шара

    float offsets[4][3] = {
        {-s, cubeY + s, 0.0f},  // лева€
        { s, cubeY + s, 0.0f},  // права€
        {0.0f, cubeY + s,  s},  // передн€€
        {0.0f, cubeY + s, -s}   // задн€€
    };

    float sphereOffsets[4][3] = {
        {-sphereRadius, sphereY, 0.0f},
        { sphereRadius, sphereY, 0.0f},
        {0.0f, sphereY,  sphereRadius},
        {0.0f, sphereY, -sphereRadius}
    };

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        glVertex3f(offsets[i][0], offsets[i][1], offsets[i][2]);
        glVertex3f(sphereOffsets[i][0], sphereOffsets[i][1], sphereOffsets[i][2]);
    }
    glEnd();
}
