#include "Window.h"

Window::Window()
{
    width = 800;
    height = 600;
    animacionTopos = false;
    dardoLanzado = false;      // NUEVO
    mazoGolpeando = false;     // NUEVO

    for (size_t i = 0; i < 1024; i++)
        keys[i] = 0;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;
    rotax = rotay = rotaz = 0.0f;
    banderaAnimacion1_DP = false;
    banderaAnimacion1_P = false;
    animacionTopos = false;
    banderaLuces = false;
    dadosGirando = false;
    monedaEnElAire = false;
    dardoLanzado = false;      
    mazoGolpeando = false;     
    teclaMHacha = false;

    for (size_t i = 0; i < 1024; i++)
        keys[i] = 0;
}

int Window::Initialise()
{
    if (!glfwInit())
    {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "Proyecto CGEIHC: Feria", NULL, NULL);
    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);

    createCallbacks();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, ManejaTeclado);
    glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Window::getYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_E)
        theWindow->rotax += 10.0;
    if (key == GLFW_KEY_R)
        theWindow->rotay += 10.0;
    if (key == GLFW_KEY_T)
        theWindow->rotaz += 10.0;

    // Danny Phantom
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        theWindow->banderaAnimacion1_DP = !theWindow->banderaAnimacion1_DP;

    // Pánico
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        theWindow->banderaAnimacion1_P = !theWindow->banderaAnimacion1_P;

    // ACTIVAR animación de topos
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        theWindow->animacionTopos = true;

    // DESACTIVAR animación de topos
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        theWindow->animacionTopos = false;

    // Activar luces por teclado
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        theWindow->banderaLuces = !theWindow->banderaLuces;

    // Dados
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        theWindow->dadosGirando = true;
    if (key == GLFW_KEY_H && action == GLFW_RELEASE)
        theWindow->dadosGirando = false;

    // Monedas
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
        theWindow->monedaEnElAire = true;
    if (key == GLFW_KEY_K && action == GLFW_RELEASE)
        theWindow->monedaEnElAire = false;

    // Lanzar dardo con tecla G
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        theWindow->dardoLanzado = true;
    if (key == GLFW_KEY_G && action == GLFW_RELEASE)
        theWindow->dardoLanzado = false;

    // Golpe de mazo con tecla SPACE
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        theWindow->mazoGolpeando = true;
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        theWindow->mazoGolpeando = false;

    //Hacha con tecla M
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
        theWindow->teclaMHacha = true;
    if (key == GLFW_KEY_M && action == GLFW_RELEASE)
        theWindow->teclaMHacha = false;

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            theWindow->keys[key] = true;
        else if (action == GLFW_RELEASE)
            theWindow->keys[key] = false;
    }

    
}
void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
