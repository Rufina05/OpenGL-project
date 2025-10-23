#include <GLFW/glfw3.h>
#include "Sphere.h"
#include "Cube.h"
#include "Lines.h"
#include <cmath>

float camY = 0;          // только горизонтальное вращение
double lastX;
bool rotating = false;

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Air Balloon", 0, 0);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    const float sphereRadius = 0.3f;
    const float cubeY = -0.4f;
    const float cubeSize = 0.4f;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Вращение мышью (только X)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            if (!rotating) { lastX = x; rotating = true; }
            camY += (x - lastX) * 0.005f;  // только горизонтальное движение
            lastX = x;
        }
        else rotating = false;

        // Проекция
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        float aspect = 800.0f / 600.0f;
        float top = 0.1f * tan(45 * 3.14159 / 360);
        glFrustum(-top * aspect, top * aspect, -top, top, 0.1, 10);

        // Видовая матрица
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glTranslatef(0, 0, -2);
        glRotatef(camY * 180 / 3.14159f, 0, 1, 0); // только вращение вокруг Y

        // Рисуем объекты
        glPushMatrix();
        glTranslatef(0, 0.4f, 0);
        drawSphere(sphereRadius);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, cubeY, 0);
        drawCube(cubeSize);
        glPopMatrix();

        drawLines(cubeSize, sphereRadius, cubeY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
