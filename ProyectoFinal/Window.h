

#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    int Initialise();
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    bool getShouldClose() {
        return  glfwWindowShouldClose(mainWindow);
    }
    bool* getsKeys() { return keys; }
    GLfloat getXChange();
    GLfloat getYChange();
    void swapBuffers() { return glfwSwapBuffers(mainWindow); }
    GLfloat getrotay() { return rotay; }
    GLfloat getrotax() { return rotax; }
    GLfloat getrotaz() { return rotaz; }
    GLfloat getarticulacion1() { return articulacion1; }
    GLfloat getarticulacion2() { return articulacion2; }

    GLfloat getarticulacion3() { return articulacion3; }
    GLfloat getvalor() { return valor; }
    GLfloat getvalor2() { return valor2; }
    GLfloat getvalor3() { return valor3; }
    GLfloat getarticulacion4() { return articulacion4; }
    GLfloat getarticulacion5() { return articulacion5; }

    //Animaci�n Danny Phantom
    GLfloat getAnimacion_Simp1_DP() { return banderaAnimacion1_DP; }
    //Animaci�n Furia
    GLfloat getAnimacion_Simp1_F() { return banderaAnimacion1_F; }
    //Animaci�n Panico
    GLfloat getAnimacion_Simp1_P() { return banderaAnimacion1_P; }

    GLfloat getMovAdelante_Furia() { return mov_furia; }

	GLfloat getMovLados_Furia() { return mov_furia2; }

    GLfloat getMovBanqueta_Furia() { return furia_jump; }

    GLfloat getMovBanqueta_Furia_Bandera() { return furia_jump_valid; }


    ~Window();
private:
    GLFWwindow* mainWindow;
    GLint width, height;
    GLfloat rotax, rotay, rotaz, articulacion1, articulacion2, articulacion3, valor, articulacion4, articulacion5, valor2, valor3, mov_furia, mov_furia2, furia_jump;
    bool banderaAnimacion1_DP, banderaAnimacion1_F, banderaAnimacion1_P,furia_jump_valid;
    bool keys[1024];
    GLint bufferWidth, bufferHeight;
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;
    void createCallbacks();
    static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
    static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};