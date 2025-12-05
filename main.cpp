#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <GLFW/glfw3.h>

#include "Sphere.h"
#include "Cube.h"
#include "Lines.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLuint sphereTexture = 0;
GLuint cubeTexture = 0;
GLuint ropeTexture = 0;

float cubeY = -0.4f;
float cubeSize = 0.4f;
float sphereRadius = 0.3f;

// -------- облака --------
struct Cloud { float x, y; float speed; float scaleX, scaleY; };
const int cloudCount = 7;
Cloud clouds[cloudCount];

// -------- звёзды --------
struct Star { float x, y; float brightness; };
const int starCount = 50;
Star stars[starCount];

// -------- текстуры --------
GLuint loadTexture(const char* file) {
    int w, h, ch;
    unsigned char* data = stbi_load(file, &w, &h, &ch, 3);
    if (!data) { printf("ERROR loading texture: %s\nSTB reason: %s\n", file, stbi_failure_reason()); return 0; }
    GLuint id; glGenTextures(1, &id); glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data); return id;
}

// -------- облака (рисуем овалы) --------
void drawCloudReal(float x, float y, float sx, float sy) {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x, y, 0); glScalef(sx, sy, 1.0f);
    glColor4f(1, 1, 1, 0.75f);
    float offsets[7][2] = {
        {-0.4f,0.0f},{-0.2f,0.15f},{0.0f,0.2f},{0.2f,0.1f},{0.4f,0.0f},{-0.1f,-0.15f},{0.2f,-0.12f}
    };
    for (int i = 0; i < 7; i++) {
        glPushMatrix(); glTranslatef(offsets[i][0], offsets[i][1], 0);
        glBegin(GL_TRIANGLE_FAN); glVertex2f(0, 0);
        for (int a = 0; a <= 32; a++) { float ang = 2 * M_PI * a / 32; glVertex2f(cos(ang), sin(ang)); }
        glEnd(); glPopMatrix();
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

// -------- горы --------
void drawMountains() {
    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.6f, 0.65f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.2f, -1.0f); glVertex2f(-0.9f, -0.55f); glVertex2f(-0.6f, -1.0f);
    glVertex2f(-0.7f, -1.0f); glVertex2f(-0.3f, -0.6f);  glVertex2f(0.1f, -1.0f);
    glVertex2f(0.0f, -1.0f);  glVertex2f(0.45f, -0.65f); glVertex2f(0.9f, -1.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

// -------- рисуем звёзды --------
void drawStars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < starCount; i++) {
        float b = stars[i].brightness * (0.8f + 0.4f * (rand() / (float)RAND_MAX));
        glColor3f(b, b, b);
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

int main() {
    srand((unsigned int)time(nullptr));

    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Air Balloon", 0, 0);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat ambientLight[] = { 0.5f,0.5f,0.5f,1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat lightPos[] = { 2,2,2,0 };
    GLfloat lightDiffuse[] = { 1.0f,1.0f,0.9f,1.0f };
    GLfloat lightSpecular[] = { 0.8f,0.8f,0.8f,1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    sphereTexture = loadTexture("balloon.png");
    cubeTexture = loadTexture("cube.jfif");
    ropeTexture = loadTexture("rope.png");

    // --- облака ---
    for (int i = 0; i < cloudCount; i++) {
        clouds[i].x = -1.3f + i * 0.45f;
        clouds[i].y = -0.15f + i * 0.25f;
        clouds[i].speed = 0.0003f + i * 0.00012f;
        clouds[i].scaleX = 0.14f + (i % 3) * 0.03f;
        clouds[i].scaleY = 0.08f + (i % 2) * 0.02f;
    }

    // --- звёзды ---
    for (int i = 0; i < starCount; i++) {
        stars[i].x = -1.0f + 2.0f * (rand() / (float)RAND_MAX);
        stars[i].y = -0.2f + 1.0f * (rand() / (float)RAND_MAX);
        stars[i].brightness = 0.6f + 0.4f * (rand() / (float)RAND_MAX);
        if (stars[i].x > -0.35f && stars[i].x < 0.35f && stars[i].y > 0.1f && stars[i].y < 0.7f) {
            stars[i].y = 0.7f + 0.1f * (rand() / (float)RAND_MAX);
        }
    }

    float balloonRotation = 0.0f;
    float rotations = 0.0f;
    bool isNight = false;

    while (!glfwWindowShouldClose(window)) {
        // вращение шара + корзина + канаты
        balloonRotation += 0.07f; // медленнее
        if (balloonRotation >= 360.0f) {
            balloonRotation -= 360.0f;
            rotations += 1.0f;
            if (rotations >= 1.0f) { rotations = 0; isNight = !isNight; }
        }

        float timeFactor = isNight ? 1.0f : 0.0f;

        // фон
        float skyR = 0.53f * (1.0f - 0.5f * timeFactor);
        float skyG = 0.81f * (1.0f - 0.5f * timeFactor);
        float skyB = 0.98f * (1.0f - 0.5f * timeFactor);
        glClearColor(skyR, skyG, skyB, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2D фон
        glMatrixMode(GL_PROJECTION); glLoadIdentity(); glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        drawMountains();

        if (isNight) drawStars();
        else {
            for (int i = 0; i < cloudCount; i++) {
                clouds[i].x += clouds[i].speed;
                if (clouds[i].x > 1.3f) clouds[i].x = -1.3f;
                drawCloudReal(clouds[i].x, clouds[i].y, clouds[i].scaleX, clouds[i].scaleY);
            }
        }

        // 3D сцена
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        float aspect = 800.0f / 600.0f;
        float top = 0.1f * tan(45.0 * M_PI / 360.0);
        glFrustum(-top * aspect, top * aspect, -top, top, 0.1, 10);
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glTranslatef(0, 0, -2.2f);

        GLfloat diff[] = { 1.0f - 0.5f * timeFactor,1.0f - 0.5f * timeFactor,0.9f - 0.5f * timeFactor,1.0f };
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);

        glPushMatrix();
        glRotatef(balloonRotation, 0, 1, 0);

        glPushMatrix();
        glTranslatef(0, 0.4f, 0);
        glBindTexture(GL_TEXTURE_2D, sphereTexture);
        glColor3f(1, 1, 1);
        drawSphere(sphereRadius, 40);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        glPushMatrix();
        glTranslatef(0, cubeY, 0);
        drawCube(cubeSize);
        glPopMatrix();

        drawLines(cubeSize, sphereRadius, cubeY, ropeTexture);

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
