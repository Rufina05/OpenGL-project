#include <GLFW/glfw3.h>

void drawCube(float size) {
    float s = size / 2.0f;
    float verts[8][3] = {
        {-s, -s, -s}, {s, -s, -s}, {s, s, -s}, {-s, s, -s},
        {-s, -s, s},  {s, -s, s},  {s, s, s},  {-s, s, s}
    };

    int faces[6][4] = {
        {4,5,6,7}, // передн€€
        {0,1,2,3}, // задн€€
        {0,4,7,3}, // лева€
        {1,5,6,2}, // права€
        {3,7,6,2}, // верхн€€
        {0,4,5,1}  // нижн€€
    };

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f); // коричневый
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            glVertex3f(verts[faces[i][j]][0], verts[faces[i][j]][1], verts[faces[i][j]][2]);
    glEnd();
}
