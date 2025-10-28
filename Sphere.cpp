#include <GLFW/glfw3.h>
#include <cmath>

const int sectorCount = 40;
const int stackCount = 40;
const float PI = 3.14159265358979323846f;

void drawSphere(float radius) {
    glColor3f(1.0f, 0.0f, 0.0f); // красный шар

    for (int stackStep = 0; stackStep < stackCount; stackStep++) {
        // Вычисляем углы φ для текущего и следующего стека
        float phi0 = PI / 2.0f - PI * (float)stackStep / stackCount;
        float phi1 = PI / 2.0f - PI * (float)(stackStep + 1) / stackCount;

        // z 
        float z0 = radius * sin(phi0);
        float z1 = radius * sin(phi1);

        glBegin(GL_QUAD_STRIP);

        for (int sectorStep = 0; sectorStep <= sectorCount; sectorStep++) {
            // Вычисляем угол θ для текущего сектора
            float theta = 2.0f * PI * (float)sectorStep / sectorCount;

            // x
            float x0 = (radius * cos(phi0)) * cos(theta);
            float x1 = (radius * cos(phi1)) * cos(theta);
            // y
            float y0 = (radius * cos(phi0)) * sin(theta);
            float y1 = (radius * cos(phi1)) * sin(theta);

            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        }

        glEnd();
    }
}
