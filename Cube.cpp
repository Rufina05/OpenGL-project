#include <GLFW/glfw3.h>

void drawCube(float size) {
    float s = size / 2.0f;
    // Вершины куба по координатам
    float verts[8][3] = {
        {-s,  s, -s}, // [0] 
        { s,  s, -s}, // [1] 
        { s, -s, -s}, // [2] 
        {-s, -s, -s}, // [3] 
        {-s,  s,  s}, // [4] 
        { s,  s,  s}, // [5] 
        { s, -s,  s}, // [6] 
        {-s, -s,  s}  // [7] 
    };
    // Грани куба
    int faces[6][4] = {
        {4, 5, 6, 7}, 
        {1, 0, 3, 2}, 
        {0, 4, 7, 3}, 
        {5, 1, 2, 6}, 
        {0, 1, 5, 4}, 
        {3, 7, 6, 2}  
    };

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f); // коричневый
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            glVertex3f(verts[faces[i][j]][0], 
                       verts[faces[i][j]][1],
                       verts[faces[i][j]][2]);
    glEnd();
}