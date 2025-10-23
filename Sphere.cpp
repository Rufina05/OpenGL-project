#include <GLFW/glfw3.h>
#include <cmath>

const int slices = 40;
const int stacks = 40;
const float PI = 3.14159265358979323846f;

void drawSphere(float radius) {
    glColor3f(1.0f, 0.0f, 0.0f); // красный шар

    for (int i = 0; i < stacks; i++) {
        float lat0 = PI * (-0.5f + (float)i / stacks);
        float lat1 = PI * (-0.5f + (float)(i + 1) / stacks);
        float z0 = radius * sin(lat0), z1 = radius * sin(lat1);
        float r0 = radius * cos(lat0), r1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);  // строим полосу между слоями
        for (int j = 0; j <= slices; j++) {
            float lng = 2 * PI * j / slices;
            float x0 = cos(lng) * r0, y0 = sin(lng) * r0;
            float x1 = cos(lng) * r1, y1 = sin(lng) * r1;

            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
}
