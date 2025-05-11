#pragma once
#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    int Initialise();

    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    bool* getsKeys() { return keys; }

    GLfloat getXChange();
    GLfloat getYChange();
    void swapBuffers() { return glfwSwapBuffers(mainWindow); }

    GLfloat getrotay() { return rotay; }
    GLfloat getrotax() { return rotax; }
    GLfloat getrotaz() { return rotaz; }

    // Iluminación por teclado
    GLfloat getIluminacionTeclado() { return banderaLuces; }

    // Animaciones específicas
    GLfloat getAnimacion_Simp1_DP() { return banderaAnimacion1_DP; }
    GLfloat getAnimacion_Simp1_P() { return banderaAnimacion1_P; }

    // Animación dados
    GLfloat getDadosGirando() { return dadosGirando; }

    // Animación monedas
    GLfloat getMonedaEnElAire() { return monedaEnElAire; }

    // Lanzamiento de dardo (tecla G)
    bool getDardoLanzado() const { return dardoLanzado; }
    void activarDardoLanzado() { dardoLanzado = true; }
    void desactivarDardoLanzado() { dardoLanzado = false; }

    // Golpe de mazo (tecla SPACE)
    bool getMazoGolpeando() const { return mazoGolpeando; }
    void activarMazoGolpeando() { mazoGolpeando = true; }
    void desactivarMazoGolpeando() { mazoGolpeando = false; }

    //Hacha (tecla M)
    GLfloat getTeclaMHacha() { return teclaMHacha; }
    void setTeclaMHacha(bool estado) { teclaMHacha = estado; }

    //Boliche tecla F
    bool getBolaLnazada() const { return bolaLanzada; }
    void desactivarBolaLanzada() { bolaLanzada = false; }

    // Béisbol (tecla N)
    bool getBolaBaseGolpeada() const { return bolaBaseGolpeada; }
    void desactivarBolaBaseGolpeada() { bolaBaseGolpeada = false; }



    ~Window();

private:
    GLFWwindow* mainWindow;
    GLint width, height;
    GLfloat rotax, rotay, rotaz;
    bool banderaLuces;
    bool banderaAnimacion1_DP, banderaAnimacion1_P;
    bool animacionTopos;
    bool dadosGirando;
    bool monedaEnElAire;
    bool dardoLanzado;
    bool mazoGolpeando;
    bool teclaMHacha;
    bool bolaLanzada;
    bool bolaBaseGolpeada;

    bool keys[1024];
    GLint bufferWidth, bufferHeight;
    GLfloat lastX, lastY;
    GLfloat xChange, yChange;
    bool mouseFirstMoved;

    void createCallbacks();
    static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
    static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};
