#include "Lines.h"
#include <cmath>

const int segments = 20;   // сегменты вдоль линии
const int circleSegs = 8;  // сегменты окружности цилиндра
const float ropeRadius = 0.02f; // радиус каната

// Рисуем один канат между start и end
void drawRope(float start[3], float end[3], GLuint ropeTex) {
    float ctrlX = (start[0] + end[0]) / 2.0f;
    float ctrlY = (start[1] + end[1]) / 2.0f - 0.1f; // прогиб вниз
    float ctrlZ = (start[2] + end[2]) / 2.0f;

    glBindTexture(GL_TEXTURE_2D, ropeTex);

    for (int i = 0; i < segments; i++) {
        float t0 = i / (float)segments;
        float t1 = (i + 1) / (float)segments;

        float u0 = 1 - t0;
        float x0 = u0 * u0 * start[0] + 2 * u0 * t0 * ctrlX + t0 * t0 * end[0];
        float y0 = u0 * u0 * start[1] + 2 * u0 * t0 * ctrlY + t0 * t0 * end[1];
        float z0 = u0 * u0 * start[2] + 2 * u0 * t0 * ctrlZ + t0 * t0 * end[2];

        float u1 = 1 - t1;
        float x1 = u1 * u1 * start[0] + 2 * u1 * t1 * ctrlX + t1 * t1 * end[0];
        float y1 = u1 * u1 * start[1] + 2 * u1 * t1 * ctrlY + t1 * t1 * end[1];
        float z1 = u1 * u1 * start[2] + 2 * u1 * t1 * ctrlZ + t1 * t1 * end[2];

        float dx = x1 - x0, dy = y1 - y0, dz = z1 - z0;
        float length = sqrt(dx * dx + dy * dy + dz * dz);
        if (length == 0) continue;
        dx /= length; dy /= length; dz /= length;

        float ax = -dz, ay = 0, az = dx;
        float alen = sqrt(ax * ax + ay * ay + az * az);
        ax /= alen; ay /= alen; az /= alen;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= circleSegs; j++) {
            float angle = j / (float)circleSegs * 2.0f * 3.14159f;
            float cx = cos(angle) * ropeRadius;
            float cz = sin(angle) * ropeRadius;

            float u = j / (float)circleSegs;
            float v0 = t0;
            float v1 = t1;

            glTexCoord2f(u, v0); glVertex3f(x0 + ax * cx, y0 + ay * cx, z0 + az * cx);
            glTexCoord2f(u, v1); glVertex3f(x1 + ax * cx, y1 + ay * cx, z1 + az * cx);
        }
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

// Рисуем все 4 каната между кубом и шаром
void drawLines(float cubeSize, float sphereRadius, float cubeY, GLuint ropeTex) {
    float s = cubeSize / 2.0f;
    float sphereY = 0.4f;

    float cubePoints[4][3] = {
        {-s, cubeY + s, 0.0f},
        { s, cubeY + s, 0.0f},
        {0.0f, cubeY + s,  s},
        {0.0f, cubeY + s, -s}
    };

    float spherePoints[4][3] = {
        {-sphereRadius, sphereY, 0.0f},
        { sphereRadius, sphereY, 0.0f},
        {0.0f, sphereY,  sphereRadius},
        {0.0f, sphereY, -sphereRadius}
    };

    for (int i = 0; i < 4; i++) {
        drawRope(cubePoints[i], spherePoints[i], ropeTex);
    }
}
