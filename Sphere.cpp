#include "Sphere.h"
#include <GLFW/glfw3.h>
#include <cmath>

static const unsigned int stackCount = 40;
static const float PI = 3.14159265358979f;

void drawSphere(float radius, unsigned int sectorCount) {
    glColor3f(1, 1, 1); // обязательно белый цвет для текстуры

    for (unsigned int stack = 0; stack < stackCount; stack++) {
        float phi0 = PI / 2 - PI * stack / stackCount;
        float phi1 = PI / 2 - PI * (stack + 1) / stackCount;

        float z0 = radius * sinf(phi0);
        float z1 = radius * sinf(phi1);

        glBegin(GL_QUAD_STRIP);

        for (unsigned int sector = 0; sector <= sectorCount; sector++) {
            float theta = 2 * PI * sector / sectorCount;

            float cos0 = radius * cosf(phi0);
            float cos1 = radius * cosf(phi1);

            float x0 = cos0 * cosf(theta);
            float y0 = cos0 * sinf(theta);

            float x1 = cos1 * cosf(theta);
            float y1 = cos1 * sinf(theta);

            float u = (float)sector / sectorCount;
            float v0 = (float)stack / stackCount;
            float v1 = (float)(stack + 1) / stackCount;

            glTexCoord2f(u, v0);
            glVertex3f(x0, z0, y0);

            glTexCoord2f(u, v1);
            glVertex3f(x1, z1, y1);
        }

        glEnd();
    }
}
