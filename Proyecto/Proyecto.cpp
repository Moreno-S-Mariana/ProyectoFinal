
//*****************************************FERIA PULQUE**********************************************
/*GARCÍA SOTO JEAN CARLO
  MINO GUZMÁN YARA AMAIRANI
  MORENO SANTOYO MARIANA
  */
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

  //para probar el importer
  //#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//***************************************** Variable para ciclo Dia y Noche*****************************************
float intensidad = 0.0f;
float velocidadDN = 0.1f;	//Cercano a 1->Rapido	o	0->Lento
double lastToggleTime = glfwGetTime();
float tiempoSkybox = 0.0f;
bool esDeDia = true;
//******************************************************************************************************************
//***************************************** Variable para juego martillo*****************************************
float anguloMartillo = 0.0f;
float velocidadOscilacion = 2.0f;		// Puedes ajustar la velocidad
bool direccionDerecha = true;
float limiteAngulo = 90.0f;				// Máximo a cada lado: 90 grados
//***************************************** Variable para juego carrusel*****************************************
float angulovaria = 0.0f;
//******************************************************************************************************************
//***************************************** Variable animación de Danny Phantom*****************************************
GLfloat vueloDP = 0.0f;
//***************************************** Variable animación de Furia*****************************************
GLfloat saltoFuria = 0.0f;
GLfloat desplazamientoY_F = 0.0f;
GLfloat anguloBrazoF = 0.0f;
static bool prevUp = false, prevDown = false;
static bool prevLeft = false, prevRight = false;
static float walkCycle = 0.0f;
const float stepDist = 0.3f;
const float walkCycleStep = glm::radians(45.0f);
const float legSwing = 30.0f;
const float armSwing = 20.0f;
const float stepAng = glm::radians(1.0f);
const float velocidadGiroFuria = glm::radians(2.0f);
float furiaGolpe = 0.0f;
bool animandoGolpe = false;
bool golpeBajando = false;
bool teclaGolpePresionada = false;
//***************************************** Variable animación de Panico*****************************************
GLfloat anguloBrazoP = 0.0f;
GLfloat mueveCuerpoPanico = 0.0f;
//***************************************** Variable animación juego dados*****************************************
/*bool dadosGirando = false;
float anguloDados = 0.0f;
float alturaDados = 0.8f;
float rotacionFinalDado1 = 0.0f;
float rotacionFinalDado2 = 0.0f;
bool cayoDado = false;*/
//***************************************** Variable animación de Hercules*****************************************
GLfloat anguloBrazoEspada = 0.0f;
//***************************************** Variable animación monedas*****************************************
bool animarMoneda = false;
bool monedaMostrada = false;
float alturaMoneda = 0.8f;
float velocidadMoneda = 0.05f;
//***************************************** JUEGO DARDOS VS GLOBOS *****************************************
bool dardoLanzado = false;
bool globoVisible[12] = { true, true, true, true, true, true, true, true, true, true, true, true };
glm::vec3 posicionDardo = glm::vec3(-90.0f, 4.0f, 83.0f);
glm::vec3 posicionesGlobos[12] = {
	{-80.0f, 26.0f, 99.0f}, {-80.0f, 20.0f, 99.0f}, {-80.0f, 14.0f, 99.0f}, {-80.0f, 8.0f, 99.0f},
	{-88.0f, 26.0f, 91.0f}, {-88.0f, 20.0f, 91.0f}, {-88.0f, 14.0f, 91.0f}, {-88.0f, 8.0f, 91.0f},
	{-72.0f, 26.0f, 107.0f}, {-72.0f, 20.0f, 107.0f}, {-72.0f, 14.0f, 107.0f}, {-72.0f, 8.0f, 107.0f}
};
//float velocidadDardo =0.1f;
//glm::vec3 direccionDardo = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)); // Dirección hacia adelante (ajusta según tu orientación)
float tiempoDardo = 0.0f;
double tiempoDesaparicionGlobo[12] = { 0.0 };
const double TIEMPO_REAPARICION_GLOBO = 10.0;
//*********************** Variables para animación del juego del topo ***********************
float tiempoDesaparicionTopo = 0.0f;
bool mazoGolpeando = false;
float anguloMazo = 0.0f;
float velocidadGolpe = 10.0f;
float tiempoEsperaReaparicion = 5.0f;
float tiempoAnimacionMazo = 0.0f;
bool mazoBajando = true;
float tiempoTopoOculto = 0.0f;         // Tiempo que el topo está oculto
float tiempoParaMostrarTopo = 2.0f;    // Tiempo que tarda en reaparecer el topo
float anguloRotacionTopo = 0.0f;
bool topo1Visible = true;
bool topo2Visible = true;
bool topo3Visible = true;
float tiempoTopo1Oculto = 0.0f;
float tiempoTopo2Oculto = 0.0f;
float tiempoTopo3Oculto = 0.0f;
bool topo1Golpeado = false;
bool topo2Golpeado = false;
bool topo3Golpeado = false;
int mazoAparece = 0;
//*********************** Variables para animación del juego de las hachas ***********************
GLfloat desplazamientoHacha = 0.0f;
bool hachaVolando = false;
float velocidadHacha = 5.0f;
float anguloRotacionHacha = 0.0f;
//*********************** Variables para animación del boliche ***********************
float bolaBoliche = 0.0f;
float velocidadBola = 0.2f;

// Estados de rotación individuales
float rotacionPino0 = 0.0f, rotacionPino1 = 0.0f, rotacionPino2 = 0.0f;
float rotacionPino3 = 0.0f, rotacionPino4 = 0.0f, rotacionPino5 = 0.0f;
float rotacionPino6 = 0.0f, rotacionPino7 = 0.0f, rotacionPino8 = 0.0f, rotacionPino9 = 0.0f;

// Estados de caída
bool pinoCaido0 = false, pinoCaido1 = false, pinoCaido2 = false;
bool pinoCaido3 = false, pinoCaido4 = false, pinoCaido5 = false;
bool pinoCaido6 = false, pinoCaido7 = false, pinoCaido8 = false, pinoCaido9 = false;

glm::vec3 ejeCaidaPino0 = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 ejeCaidaPino1 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 ejeCaidaPino2 = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 ejeCaidaPino3 = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 ejeCaidaPino4 = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 ejeCaidaPino5 = glm::vec3(1.0f, 0.0f, 1.0f);
glm::vec3 ejeCaidaPino6 = glm::vec3(-1.0f, 0.0f, 1.0f);
glm::vec3 ejeCaidaPino7 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 ejeCaidaPino8 = glm::vec3(1.0f, 0.0f, -1.0f);
glm::vec3 ejeCaidaPino9 = glm::vec3(-1.0f, 0.0f, -1.0f);


// Control general
float tiempoCaidaPinos = 3.0f;
bool animarCaidaPinos = false;

bool pinoCaido = false;
float rotacionPino = 0.0f;
float tiempoInicioCaida = 0.0f;
float tiempoPinoCaido = 0.0f;
bool restaurarPino = false;

bool bolichePendiente = false;
//*********************** Variables para animación del juego baseball ***********************
bool bolaGolpeada = false;
float bolaY = 3.0f;
float bolaZ = -75.0f;
float velocidadBolaBase = 1.0f;  // ajusta según necesidad
float rotacionBolaBase = 0.0f;
float anguloBate = 0.0f;
bool bateAnimando = false;
glm::vec3 posicionBate = glm::vec3(-15.0f, 4.0f, -70.0f);  // posición actual del bate
//*********************** Variables para animación de Alegría ***********************
float alegriaSaltoY = 0.0f;
float alegriaAnguloBrazo = 0.0f;
float alegriaTiempo = 0.0f;
//*********************** Variables para animación de Tristeza ***********************
float tristezaBalanceo = 0.0f;
float tiempoTristeza = 0.0f;
float tristezaBrazoAngulo = 0.0f;
//*********************** Variables para animación de Ember ***********************
float emberTiempo = 0.0f;
float emberAlturaY = 0.0f;
float emberBrazoAngulo = 0.0f;
float emberPiernaAngulo = 0.0f;
//*********************** Variables para animación de Sam ***********************
float samTiempo = 0.0f;
float samBrazoAngulo = 0.0f;
float samPiernaAngulo = 0.0f;
//*********************** Variables para animación de Pena ***********************
float penaTiempo = 0.0f;
float penaAnguloBalanceo = 0.0f;
float penaBrazoAngulo = 0.0f;
float penaCabezaOffset = 0.0f;

bool animarPena = false;
float tiempoAnimacionPena = 0.0f;
bool sonidoPenaReproducido = false;
int canalPena = -1;

//bool animarPena = false;
float tiempoPena = 0.0f;
float penaTemblor = 0.0f;

//*****************************************Parámetros generales*****************************************
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture plainTexture;
Texture pisoTexture;

//***************************************** EDIFICIOS *****************************************

Model Iglesia;
Model Portales;
Model chaparrin;
Model rojita;
Model verde;
Model rosa;
Model aqua;
Model banqueta;

//***************************************** DECORACIONES DE CALLE *****************************************

Model Banca;
Model BoteBasuraVerde;
Model BoteBasuraAzul;
Model Letrero;
Model Quiosco_modelo;
Model Lamparas;
Model Parquimetro;
Model LamparaSuelo;

//***************************************** AREAS VERDES *****************************************

Model pasto;
Model arbol;
Model arbusto;

//***************************************** JUEGOS MECANICOS  *****************************************

Model Carrousel;
Model Caballo1;
Model Caballo2;
Model Caballo3;
Model Caballo4;
Model Martillo;
Model MartilloFrontal;
Model MartilloTrasero;

//***************************************** JUEGOS DE FERIA  *****************************************
//***************************************** DADOS  *****************************************
Model mesa_dado;
Model Mesa_Pock;
Model Dados;

//***************************************** GLOBOS *****************************************
Model GlobosP;
Model Globos;
Model Dardos;

//***************************************** TOPOS *****************************************
Model Topo;
Model Monito_TOPO;
Model Mazo;

//***************************************** HACHAS *****************************************
Model HachasP;
Model Centro;
Model Hacha;

//***************************************** BOLICHE *****************************************
Model Boliche;
Model Pino;
Model Bolaboliche;

//***************************************** JAULA BATEO *****************************************
Model Jaula;
Model Bola;
Model Bat;

//***************************************** Cobro Moneda *****************************************
Model Coin;
Model Mesa;
Model Cuenco;

//***************************************** PERSONAJES *****************************************

Model Panico_Mar;
Model PanicoBDer;
Model PanicoBizq;
Model PanicoPDer;
Model PanicoPIzq;
Model Furia_cuerpo;
Model Furia_BrazoDer;
Model Furia_BrazoIzq;
Model Furia_PiernaDer;
Model Furia_PiernaIzq;
Model DannyP_cuerpo;
Model DannyP_BrazoIzq;
Model DannyP_BrazoDer;
Model DannyP_PiernaIzq;
Model DannyP_PiernaDer;
//***************************************** NPC´S  *****************************************
//***************************************** Tristeza*****************************************
Model Tristeza;
Model BrazoIzq_T;
Model BrazoDer_T;
Model PiernaIzq_T;
Model PiernaDer_T;
//***************************************** Alegría*****************************************
Model Alegria;
Model BrazoIzq_A;
Model BrazoDer_A;
Model PiernaIzq_A;
Model PiernaDer_A;
//***************************************** Pena *****************************************
Model Pena;
Model BrazoIzq_Pena;
Model BrazoDer_Pena;
Model PiernaIzq_Pena;
Model PiernaDer_Pena;
//***************************************** Hercules *****************************************
Model Hercules;
Model BrazoIzq_Hercules;
Model BrazoDer_Hercules;
Model PiernaIzq_Hercules;
Model PiernaDer_Hercules;
//***************************************** Ember *****************************************
Model Ember;
Model BrazoIzq_Ember;
Model BrazoDer_Ember;
Model PiernaIzq_Ember;
Model PiernaDer_Ember;
//***************************************** Sam *****************************************
Model Sam;
Model BrazoIzq_Sam;
Model BrazoDer_Sam;
Model PiernaIzq_Sam;
Model PiernaDer_Sam;
//***************************************** COMIDA *****************************************

Model PuestoElotes;
Model PuestoComida;
Model PuestoTacos;
Model PuestoAlgodon;
Model PuestoDulces;
Model Taco;

//materiales
Material Plastico_mate;
Material Plastico_brillante;
Material Aluminio;
Material Acero;
Material Hormigon;
Material Madera;
Material Piel;
Material Oro;
Material Fantasma;
Material Peluche;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
//PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights1[MAX_POINT_LIGHTS];	//PointLight Lámparas
PointLight pointLights2[MAX_POINT_LIGHTS];	//PointLigth Quiosko
SpotLight spotLights[MAX_SPOT_LIGHTS];		// Luces Varias parque
SpotLight spotLights2[MAX_SPOT_LIGHTS];		// Luces globos
SpotLight spotLights3[MAX_SPOT_LIGHTS];		// Luces Boliche
SpotLight spotLights4[MAX_SPOT_LIGHTS];		//Luces por teclado edificios
SpotLight spotLights5[MAX_SPOT_LIGHTS];		// Luces dados
SpotLight spotLights6[MAX_SPOT_LIGHTS];		// Luces hachas
SpotLight spotLights7[MAX_SPOT_LIGHTS];		//Luces topos

// Arreglo temporal para luces activas
SpotLight lucesActivas[MAX_SPOT_LIGHTS];
int totalLucesActivas = 0;

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

CameraMode currentCameraMode = THIRD_PERSON;
int attractionIndex = 0;
bool attractionInitialized = false;

//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

bool estaCerca(const glm::vec3& posCamara, const glm::vec3& posLuz, float distanciaMaxima) {
	return glm::distance(posCamara, posLuz) <= distanciaMaxima;
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();




	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	static glm::vec3 furiaPos(-185.0f, 10.0f, 45.0f);
	static float furiaYaw = glm::radians(90.0f);
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();

	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/empedrado.tga");
	pisoTexture.LoadTextureA();

	//***************************************** EDIFICIOS *****************************************
	Iglesia = Model();
	Iglesia.LoadModel("Models/Edificios/Iglesia_optim.obj");

	rojita = Model();
	rojita.LoadModel("Models/Edificios/casaroja_optim.obj");

	rosa = Model();
	rosa.LoadModel("Models/Edificios/casarosa_optim.obj");

	verde = Model();
	verde.LoadModel("Models/Edificios/casaverde_optim.obj");

	aqua = Model();
	aqua.LoadModel("Models/Edificios/casaaqua_optim.obj");

	Portales = Model();
	Portales.LoadModel("Models/Edificios/portales_optim.obj");

	chaparrin = Model();
	chaparrin.LoadModel("Models/Edificios/TercerLarge_optim.obj");

	banqueta = Model();
	banqueta.LoadModel("Models/Edificios/banqueta.obj");

	//***************************************** DECORACIONES DE CALLE *****************************************

	Banca = Model();
	Banca.LoadModel("Models/Decoraciones_Calle/Banca_optim.obj");

	BoteBasuraVerde = Model();
	BoteBasuraVerde.LoadModel("Models/Decoraciones_Calle/BoteBasuraVerde.obj");

	BoteBasuraAzul = Model();
	BoteBasuraAzul.LoadModel("Models/Decoraciones_Calle/BoteBasuraAzul.obj");

	Quiosco_modelo = Model();
	Quiosco_modelo.LoadModel("Models/Decoraciones_Calle/Quiosco_optim.obj");

	Lamparas = Model();
	Lamparas.LoadModel("Models/Decoraciones_Calle/Faroles.obj");

	Letrero = Model();
	Letrero.LoadModel("Models/Decoraciones_Calle/pulqueletras_optim.obj");

	Parquimetro = Model();
	Parquimetro.LoadModel("Models/Decoraciones_Calle/Parquimetro.obj");

	LamparaSuelo = Model();
	LamparaSuelo.LoadModel("Models/Decoraciones_Calle/LamparaSuelo_optim.obj");

	//***************************************** AREAS VERDES *****************************************
	pasto = Model();
	pasto.LoadModel("Models/Areas_Verdes/grass_optim.obj");

	arbol = Model();
	arbol.LoadModel("Models/Areas_Verdes/Arbol_lp.obj");

	arbusto = Model();
	arbusto.LoadModel("Models/Areas_Verdes/Arbusto.obj");

	//***************************************** JUEGOS MECANICOS  *****************************************
	Carrousel = Model();
	Carrousel.LoadModel("Models/Juegos_Mecanicos/carruseltexturizado_optim.obj");

	Caballo1 = Model();
	Caballo1.LoadModel("Models/Juegos_Mecanicos/Caballo1.obj");

	Caballo2 = Model();
	Caballo2.LoadModel("Models/Juegos_Mecanicos/Caballo2.obj");

	Caballo3 = Model();
	Caballo3.LoadModel("Models/Juegos_Mecanicos/Caballo3.obj");

	Caballo4 = Model();
	Caballo4.LoadModel("Models/Juegos_Mecanicos/Caballo4.obj");

	Martillo = Model();
	Martillo.LoadModel("Models/Juegos_Mecanicos/KAMIKAZE_optim.obj");

	MartilloFrontal = Model();
	MartilloFrontal.LoadModel("Models/Juegos_Mecanicos/martilloFrontal.obj");

	MartilloTrasero = Model();
	MartilloTrasero.LoadModel("Models/Juegos_Mecanicos/martilloTrasero.obj");

	//***************************************** JUEGOS DE LA FERIA  *****************************************
	//************************ DADOS *******************************
	mesa_dado = Model();
	mesa_dado.LoadModel("Models/Juegos_Feria/Dados/MesaConSillas_optim.obj");

	Mesa_Pock = Model();
	Mesa_Pock.LoadModel("Models/Juegos_Feria/Dados/mesaDados_optim.obj");

	Dados = Model();
	Dados.LoadModel("Models/Juegos_Feria/Dados/Dadotexturizado.obj");

	//***************************************** GLOBOS *****************************************

	GlobosP = Model();
	GlobosP.LoadModel("Models/Juegos_Feria/Globos/ParedParaGlobos.obj");

	Globos = Model();
	Globos.LoadModel("Models/Juegos_Feria/Globos/GloboRojo.obj");

	Dardos = Model();
	Dardos.LoadModel("Models/Juegos_Feria/Globos/dardo.obj");

	//***************************************** TOPOS *****************************************

	Topo = Model();
	Topo.LoadModel("Models/Juegos_Feria/Topos/juegotopo.obj");

	Monito_TOPO = Model();
	Monito_TOPO.LoadModel("Models/Juegos_Feria/Topos/topos.obj");

	Mazo = Model();
	Mazo.LoadModel("Models/Juegos_Feria/Topos/Mazo.obj");

	//***************************************** HACHAS *****************************************
	HachasP = Model();
	HachasP.LoadModel("Models/Juegos_Feria/Hachas/paredhachastexturizado.obj");

	Centro = Model();
	Centro.LoadModel("Models/Juegos_Feria/Hachas/CentroHachasMadera.obj");

	Hacha = Model();
	Hacha.LoadModel("Models/Juegos_Feria/Hachas/hacha.obj");

	//***************************************** BOLICHE *****************************************
	Boliche = Model();
	Boliche.LoadModel("Models/Edificios/Boliche.obj");

	Pino = Model();
	Pino.LoadModel("Models/Edificios/PinoBoliche.obj");

	Bolaboliche = Model();
	Bolaboliche.LoadModel("Models/Edificios/BolaBoliche.obj");


	//***************************************** JAULA BATEO *****************************************
	Jaula = Model();
	Jaula.LoadModel("Models/Juegos_Feria/Bateo/MallaRejas.obj");

	Bat = Model();
	Bat.LoadModel("Models/Juegos_Feria/Bateo/baseballbat.obj");

	Bola = Model();
	Bola.LoadModel("Models/Juegos_Feria/Bateo/BolaBaseball.obj");

	//***************************************** Moneda *****************************************
	Coin = Model();
	Coin.LoadModel("Models/Moneda/Coin.obj");
	Mesa = Model();
	Mesa.LoadModel("Models/Moneda/Mesa.obj");
	Cuenco = Model();
	Cuenco.LoadModel("Models/Moneda/Cuenco.obj");

	//***************************************** PERSONAJES *****************************************

	Panico_Mar = Model();
	Panico_Mar.LoadModel("Models/Personajes/CuerpoPanico.obj");
	PanicoBDer = Model();
	PanicoBDer.LoadModel("Models/Personajes/PanicoBDer.obj");
	PanicoBizq = Model();
	PanicoBizq.LoadModel("Models/Personajes/PanicoBIzq.obj");
	PanicoPDer = Model();
	PanicoPDer.LoadModel("Models/Personajes/PanicoPDer.obj");
	PanicoPIzq = Model();
	PanicoPIzq.LoadModel("Models/Personajes/PanicoPIzq.obj");

	Furia_cuerpo = Model();
	Furia_cuerpo.LoadModel("Models/Personajes/Cuerpo_F.obj");
	Furia_BrazoDer = Model();
	Furia_BrazoDer.LoadModel("Models/Personajes/BrazoDer_F.obj");
	Furia_BrazoIzq = Model();
	Furia_BrazoIzq.LoadModel("Models/Personajes/BrazoIzq_F.obj");
	Furia_PiernaIzq = Model();
	Furia_PiernaIzq.LoadModel("Models/Personajes/PiernaIzq_F.obj");
	Furia_PiernaDer = Model();
	Furia_PiernaDer.LoadModel("Models/Personajes/PiernaDer_F.obj");

	DannyP_cuerpo = Model();
	DannyP_cuerpo.LoadModel("Models/Personajes/dannyphantom.obj");
	DannyP_BrazoIzq = Model();
	DannyP_BrazoIzq.LoadModel("Models/Personajes/BrazoIzq_DP.obj");
	DannyP_BrazoDer = Model();
	DannyP_BrazoDer.LoadModel("Models/Personajes/BrazoDer_DP.obj");
	DannyP_PiernaIzq = Model();
	DannyP_PiernaIzq.LoadModel("Models/Personajes/PiernaIzq_DP.obj");
	DannyP_PiernaDer = Model();
	DannyP_PiernaDer.LoadModel("Models/Personajes/PiernaDer_DP.obj");

	Tristeza = Model();
	Tristeza.LoadModel("Models/Personajes/cuerpo_Tristeza.obj");
	BrazoDer_T = Model();
	BrazoDer_T.LoadModel("Models/Personajes/BrazoDer_T.obj");
	BrazoIzq_T = Model();
	BrazoIzq_T.LoadModel("Models/Personajes/BrazoIzq_T.obj");
	PiernaDer_T = Model();
	PiernaDer_T.LoadModel("Models/Personajes/PiernaDer_T.obj");
	PiernaIzq_T = Model();
	PiernaIzq_T.LoadModel("Models/Personajes/PiernaIzq_T.obj");

	Alegria = Model();
	Alegria.LoadModel("Models/Personajes/Cuerpo_A.obj");
	BrazoDer_A = Model();
	BrazoDer_A.LoadModel("Models/Personajes/BrazoDer_A.obj");
	BrazoIzq_A = Model();
	BrazoIzq_A.LoadModel("Models/Personajes/BrazoIzq_A.obj");
	PiernaDer_A = Model();
	PiernaDer_A.LoadModel("Models/Personajes/PiernaDer_A.obj");
	PiernaIzq_A = Model();
	PiernaIzq_A.LoadModel("Models/Personajes/PiernaIzq_A.obj");

	Pena = Model();
	Pena.LoadModel("Models/Personajes/CuerpoPena.obj");
	BrazoDer_Pena = Model();
	BrazoDer_Pena.LoadModel("Models/Personajes/BrazoDer_Pena.obj");
	BrazoIzq_Pena = Model();
	BrazoIzq_Pena.LoadModel("Models/Personajes/BrazoIzq_Pena.obj");
	PiernaDer_Pena = Model();
	PiernaDer_Pena.LoadModel("Models/Personajes/PiernaDer_Pena.obj");
	PiernaIzq_Pena = Model();
	PiernaIzq_Pena.LoadModel("Models/Personajes/PiernaIzq_Pena.obj");

	Hercules = Model();
	Hercules.LoadModel("Models/Personajes/CuerpoHercules.obj");
	BrazoDer_Hercules = Model();
	BrazoDer_Hercules.LoadModel("Models/Personajes/BrazoDer_H.obj");
	BrazoIzq_Hercules = Model();
	BrazoIzq_Hercules.LoadModel("Models/Personajes/BrazoIzq_H.obj");
	PiernaDer_Hercules = Model();
	PiernaDer_Hercules.LoadModel("Models/Personajes/PiernaDer_H.obj");
	PiernaIzq_Hercules = Model();
	PiernaIzq_Hercules.LoadModel("Models/Personajes/PiernaIzq_H.obj");

	Ember = Model();
	Ember.LoadModel("Models/Personajes/cuerpo_Ember.obj");
	BrazoDer_Ember = Model();
	BrazoDer_Ember.LoadModel("Models/Personajes/BrazoDer_Ember.obj");
	BrazoIzq_Ember = Model();
	BrazoIzq_Ember.LoadModel("Models/Personajes/BrazoIzq_Ember.obj");
	PiernaDer_Ember = Model();
	PiernaDer_Ember.LoadModel("Models/Personajes/PiernaDer_Ember.obj");
	PiernaIzq_Ember = Model();
	PiernaIzq_Ember.LoadModel("Models/Personajes/PiernaIzq_Ember.obj");

	Sam = Model();
	Sam.LoadModel("Models/Personajes/Cuerpo_Sam.obj");
	BrazoDer_Sam = Model();
	BrazoDer_Sam.LoadModel("Models/Personajes/BrazoDer_Sam.obj");
	BrazoIzq_Sam = Model();
	BrazoIzq_Sam.LoadModel("Models/Personajes/BrazoIzq_Sam.obj");
	PiernaDer_Sam = Model();
	PiernaDer_Sam.LoadModel("Models/Personajes/PiernaDer_Sam.obj");
	PiernaIzq_Sam = Model();
	PiernaIzq_Sam.LoadModel("Models/Personajes/PiernaIzq_Sam.obj");
	//***************************************** PUESTOS DE COMIDA ****************************************

	PuestoElotes = Model();
	PuestoElotes.LoadModel("Models/Puestos/PuestoElotes.obj");

	PuestoTacos = Model();
	PuestoTacos.LoadModel("Models/Puestos/puestotacos.obj");

	PuestoComida = Model();
	PuestoComida.LoadModel("Models/Puestos/PuestoComida.obj");

	PuestoAlgodon = Model();
	PuestoAlgodon.LoadModel("Models/Puestos/Algodones.obj");

	PuestoDulces = Model();
	PuestoDulces.LoadModel("Models/Puestos/Dulces.obj");

	Taco = Model();
	Taco.LoadModel("Models/Comida/Taco.obj");

	// puestos

	//skybox Día
	std::vector<std::string> skyboxFacesDay = {


		"Textures/Skybox/SunnyRight.tga",
		"Textures/Skybox/SunnyFront.tga",
		"Textures/Skybox/SunnyDown.tga",
		"Textures/Skybox/SunnyUp.tga",
		"Textures/Skybox/SunnyLeft.tga",
		"Textures/Skybox/SunnyBack.tga"
	};

	//skybox Noche
	std::vector<std::string> skyboxFacesNight = {
		"Textures/Skybox/nightright.tga",
		"Textures/Skybox/nightleft.tga",
		"Textures/Skybox/nightbottom.tga",
		"Textures/Skybox/nighttop.tga",
		"Textures/Skybox/nightfront.tga",
		"Textures/Skybox/nightback.tga"
	};

	Skybox skybox(skyboxFacesDay, skyboxFacesNight);


	Plastico_mate = Material(0.2f, 8);			//Botes de basura, dados
	Plastico_brillante = Material(0.6f, 64);	//Topos
	Aluminio = Material(0.9f, 128);				//Puestos y bate 
	Acero = Material(0.7f, 64);					//Martillo y Carrusel
	Hormigon = Material(0.1f, 4);				//Edificios 
	Madera = Material(0.5f, 32);				//Pared
	Piel = Material(0.3f, 16);					//Personajes
	Oro = Material(1.0f, 64); ;					//Moneda
	Fantasma = Material(0.8f, 128);				//Danny phantom y Ember
	Peluche = Material(0.1f, 4);				//Furia, Alegria y Tristeza


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.03f, 0.03f,
		0.0f, 0.0f, -1.0f);

	//*************************************************************************************************************************************************
	unsigned int pointLightCount_ARRAY1 = 0;
	// Luz 1
	pointLights1[0] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,
		160.0f, 60.0f, -185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	// Luz 2
	pointLights1[1] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,
		160.0f, 60.0f, 185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	// Luz 3
	pointLights1[2] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,
		-160.0f, 60.0f, -185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	// Luz 4
	pointLights1[3] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,
		-160.0f, 60.0f, 185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	unsigned int pointLightCount_ARRAY2 = 0;
	pointLights2[0] = PointLight(1.0f, 0.0f, 0.0f,
		4.0f, 30.0f,
		0.0f, 20.0f, 0.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY2++;
	//*************************************************************************************************************************************************

	unsigned int spotLightCount = 0;
	// Lámpara izquierda
	spotLights[0] = SpotLight(1.0f, 0.843f, 0.6f,
		10.0f, 80.0f,
		-28.0f, 9.0f, 93.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.1f,
		55.0f
	);
	spotLightCount++;

	// Lámpara derecha
	spotLights[1] = SpotLight(1.0f, 0.843f, 0.6f,
		10.0f, 80.0f,
		28.0f, 9.0f, 90.0f,
		-1.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.1f,
		55.0f
	);
	spotLightCount++;

	//Carrusel
	spotLights[2] = SpotLight(1.0f, 0.843f, 0.6f,
		10.0f, 80.0f,
		0.0f, 40.0f, 60.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		75.0f
	);
	spotLightCount++;

	//Martillo
	spotLights[3] = SpotLight(1.0f, 0.843f, 0.6f,
		10.0f, 80.0f,
		0.0f, 60.0f, -50.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		80.0f
	);
	spotLightCount++;

	unsigned int spotLightCount2 = 0;

	//Dardo y globos
	spotLights2[0] = SpotLight(0.5f, 0.0f, 0.5f,
		10.0f, 80.0f,
		-80.0f, 40.0f, 108.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		90.0f
	);
	spotLightCount2++;

	spotLights2[1] = SpotLight(0.5f, 1.0f, 1.0f,
		10.0f, 80.0f,
		-80.0f, 40.0f, 113.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		90.0f
	);
	spotLightCount2++;

	unsigned int spotLightCount3 = 0;

	//Luz boliche 
	spotLights3[0] = SpotLight(0.6f, 0.0f, 0.8f,
		10.0f, 80.0f,
		-80.0f, 9.0f, 250.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount3++;

	spotLights3[1] = SpotLight(0.0f, 0.4f, 1.0f,
		10.0f, 80.0f,
		-80.0f, 9.0f, 260.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount3++;

	spotLights3[2] = SpotLight(0.5f, 1.0f, 0.0f,
		10.0f, 80.0f,
		-80.0f, 9.0f, 240.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount3++;

	spotLights3[3] = SpotLight(1.0f, 0.0f, 0.5f,
		10.0f, 80.0f,
		-80.0f, 9.0f, 270.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount3++;

	unsigned int spotLightCount4 = 0;				//Edificio izquierda

	spotLights4[0] = SpotLight(1.0f, 0.0f, 0.0f,
		10.0f, 80.0f,
		-200.0f, 65.0f, 20.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount4++;

	spotLights4[1] = SpotLight(0.0f, 1.0f, 0.0f,	//Edificio derecha
		10.0f, 80.0f,
		200.0f, 65.0f, 20.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount4++;

	spotLights4[2] = SpotLight(0.0f, 0.0f, 1.0f,	//Edificio de frente
		10.0f, 80.0f,
		0.0f, 35.0f, 190.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.09f, 0.032f,
		70.0f
	);
	spotLightCount4++;

	unsigned int spotLightCount5 = 0;

	//Dados
	spotLights5[0] = SpotLight(1.0f, 1.0f, 0.0f,
		10.0f, 80.0f,
		85.0f, 30.0f, 100.0f,
		0.0f, -1.0f, 0.0f,
		0.5f, 0.6f, 0.15f,
		55.0f
	);
	spotLightCount5++;

	spotLights5[1] = SpotLight(0.0f, 1.0f, 0.0f,
		10.0f, 80.0f,
		85.0f, 30.0f, 105.0f,
		0.0f, -1.0f, 0.0f,
		0.5f, 0.6f, 0.15f,
		55.0f
	);
	spotLightCount5++;

	unsigned int spotLightCount6 = 0;

	//Hachas
	spotLights6[0] = SpotLight(0.133f, 0.545f, 0.133f,
		10.0f, 80.0f,
		70.0f, 45.0f, -90.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		80.0f
	);
	spotLightCount6++;

	spotLights6[1] = SpotLight(1.0, 0.65f, 0.0f,
		10.0f, 80.0f,
		70.0f, 45.0f, -95.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		80.0f
	);
	spotLightCount6++;

	unsigned int spotLightCount7 = 0;

	//Topos
	spotLights7[0] = SpotLight(0.502f, 0.0f, 0.502f,
		10.0f, 80.0f,
		-70.0f, 12.0f, -90.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		80.0f
	);
	spotLightCount7++;

	spotLights7[1] = SpotLight(0.5f, 0.5f, 0.5f,
		10.0f, 80.0f,
		-70.0f, 12.0f, -95.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.09f, 0.032f,
		80.0f
	);
	spotLightCount7++;

	unsigned int spotLightCount8 = 0;

	// Variables para la luz
	float intensidad = 0.0f;
	const float dayDuration = 20.0f;
	const float nightDuration = 20.0f;
	const float fadeDuration = 13.0f;
	float cycleTime = 0.0f;
	float t = 0.0f;
	float blendFactor = 0.0f;

	// 2) Ángulo del sol [?90°, 270°): empieza en el horizonte este, sube al cenit, cae al horizonte oeste
	float sunAngleDeg = 0.0f;
	float sunRad = 0.0f;

	//
	static double lastSwitchTime = 0.0;
	double currentTime = 0.0f;
	bool camaraCercaDeLuces3 = false;


	static float tiempoAcumulado = 0.0f;
	int indiceActivo = 0;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Error al iniciar SDL: %s\n", SDL_GetError());
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Error al iniciar SDL_mixer: %s\n", Mix_GetError());
		return -1;
	}

	Mix_Music* musicaFondo = Mix_LoadMUS("Sounds/intensamente_corto.wav");
	Mix_Music* musicaBoliche = Mix_LoadMUS("Sounds/heros_gauntlet_optimized.wav");
	Mix_Music* musicaHacha = Mix_LoadMUS("Sounds/danny_phantom_hacha.wav");
	Mix_Music* musicaGlobos = Mix_LoadMUS("Sounds/intensamente_2min.wav");
	Mix_Music* musicaDados = Mix_LoadMUS("Sounds/dados.wav");
	Mix_Music* musicaTopos = Mix_LoadMUS("Sounds/danny_phantom_alt.wav");
	Mix_Music* musicaBateo = Mix_LoadMUS("Sounds/recorte_minuto8.wav");
	Mix_Chunk* sonidoAmbiente = Mix_LoadWAV("Sounds/feria.wav");
	Mix_Chunk* sonnidoCarrusel = Mix_LoadWAV("Sounds/carrousel.wav");
	Mix_Chunk* sonidoMartillo = Mix_LoadWAV("Sounds/coaster-01_optimized.wav");
	Mix_Chunk* sonidoBoliche = Mix_LoadWAV("Sounds/boliche.wav");
	Mix_Chunk* sonidoPena = Mix_LoadWAV("Sounds/PAIN.wav");
	Mix_Chunk* sonidoMoneda = Mix_LoadWAV("Sounds/moneda.wav");
	Mix_Chunk* sonidoGlobo = Mix_LoadWAV("Sounds/GLOBO.wav");
	Mix_Chunk* sonidoDados = Mix_LoadWAV("Sounds/DADOSSE.wav");
	Mix_Chunk* sonidoPanico = Mix_LoadWAV("Sounds/panico.wav");
	Mix_Chunk* sonidoHercules = Mix_LoadWAV("Sounds/hercules.wav");
	Mix_Chunk* sonidoHacha = Mix_LoadWAV("Sounds/hacha.wav");
	Mix_Chunk* sonidoDanny = Mix_LoadWAV("Sounds/DANNY.wav");
	Mix_Chunk* sonidoBateo = Mix_LoadWAV("Sounds/BEISBOL.wav");
	Mix_Chunk* sonidoTopos = Mix_LoadWAV("Sounds/toposSonido.wav");



	bool ToposActivo = false;
	bool DannyActivo = false;
	bool bolicheActivo = false;
	bool hachaActiva = false;
	bool globosActivos = false;
	bool dadosActivos = false;
	bool toposActivos = false;
	bool bateoActivo = false;
	bool carrouselActivo = false;
	bool martilloActivo = false;
	bool penaActiva = false;
	bool monedaActiva = false;
	bool globoActivo = false;
	bool dadosGirando = false;
	bool panicoActiva = false;
	bool herculesActivado = false;
	bool hachaActivado = false;
	bool beisbolActivo = false;
	int CanalBeisbol = -1;
	int CanalDanny = -1;
	int canalHachas = -1;
	int canalPanico = -1;
	int canalDados = -1;
	int canalMineda = -1;
	int canalPena = -1;
	int canalMartillo = -1;
	int canalCarrousel = -1;
	int canalAmbiente = -1;
	int canalGlobo = -1;
	int canalHERCULES = -1;
	int canalTopos = -1;

	if (!musicaFondo) printf("Error cargando musica fondo: %s\n", Mix_GetError());
	if (!musicaBoliche) printf("Error cargando musica boliche: %s\n", Mix_GetError());
	if (!musicaHacha) printf("Error cargando musica hacha: %s\n", Mix_GetError());
	if (!musicaGlobos) printf("Error cargando musica globos: %s\n", Mix_GetError());
	if (!musicaDados) printf("Error cargando musica dados: %s\n", Mix_GetError());
	if (!musicaTopos) printf("Error cargando musica topos: %s\n", Mix_GetError());
	if (!musicaBateo) printf("Error cargando musica bateo: %s\n", Mix_GetError());
	if (!sonidoAmbiente) printf("Error cargando ambiente: %s\n", Mix_GetError());
	if (!sonnidoCarrusel) printf("Error cargando carrusel: %s\n", Mix_GetError());
	if (!sonidoMartillo) printf("Error cargando martillo: %s\n", Mix_GetError());
	if (!sonidoBoliche) printf("Error cargando boliche: %s\n", Mix_GetError());
	if (!sonidoPena) printf("Error cargando sonido pena: %s\n", Mix_GetError());
	if (!sonidoGlobo) printf("Error cargando sonido globo: %s\n", Mix_GetError());
	if (!sonidoMoneda) printf("Error cargando sonido moneda: %s\n", Mix_GetError());
	if (!sonidoDados) printf("Error cargando sonido dados: %s\n", Mix_GetError());
	if (!sonidoPanico) printf("Error cargando sonido panico: %s\n", Mix_GetError());
	if (!sonidoHercules) printf("Error cargando sonido hercules: %s\n", Mix_GetError());
	if (!sonidoHacha) printf("Error cargando sonido hacha: %s\n", Mix_GetError());
	if (!sonidoDanny) printf("Error cargando sonido danny: %s\n", Mix_GetError());
	if (!sonidoBateo) printf("Error cargando sonido beisbol: %s\n", Mix_GetError());
	if (!sonidoTopos) printf("Error cargando sonido topos: %s\n", Mix_GetError());


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())

	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 0.3f * deltaTime;

		/*
		 *
		 *						AQUI INICIAN LAS ANIMACIONES CORREGIDAS
		 *
		*/

		// ---------------------------- DADOS + NPC PANICO ----------------------------

				// ---------------------------- ESTADOS PARA DADOS ----------------------------
		static enum EstadoDados { DADOS_ESPERANDO, DADOS_ANIMANDO_MONEDA, DADOS_GIRANDO_SUBIENDO, DADOS_GIRANDO_BAJANDO } estadoDados = DADOS_ESPERANDO;
		static bool monedaSubiendoDados = false;
		static bool sonidoDadosReproducido = false;
		static float alturaMonedaDados = 0.8f;
		static float alturaDados = 0.8f;
		static float anguloDados = 0.0f;
		static float rotacionFinalDado1 = 0.0f;
		static float rotacionFinalDado2 = 0.0f;
		static bool dadosYaCayeron = false;

		static float velocidadSubidaMoneda = 0.5f; // menor = mas lento
		static float velocidadSubidaDados = 50.5f;  // menor = mas lento

		static bool animacionSustoActiva = false;
		static float anguloBrazoSusto = 0.0f;
		static float retrocesoCuerpo = 0.0f;

		// ---------------------------- ANIMACION SUSTO AUTOMATICA ----------------------------
		static bool activarSusto = false;
		static float temporizadorSusto = 0.0f;
		const float duracionSusto = 100.0f; // segundos
		static bool sonidoPanicoReproducido = false;

		if (activarSusto && !animacionSustoActiva) {
			animacionSustoActiva = true;
			temporizadorSusto = 0.0f;
			sonidoPanicoReproducido = false;
		}

		if (animacionSustoActiva) {
			temporizadorSusto += deltaTime;
			anguloBrazoSusto += 180.0f * deltaTime;
			retrocesoCuerpo = 0.3f * sin(2.0f * anguloBrazoSusto);

			if (!sonidoPanicoReproducido && sonidoPanico) {
				Mix_PlayChannel(-1, sonidoPanico, 0);
				sonidoPanicoReproducido = true;
			}

			if (temporizadorSusto >= duracionSusto) {
				activarSusto = false;
				animacionSustoActiva = false;
				anguloBrazoSusto = 0.0f;
				retrocesoCuerpo = 0.0f;
			}
		}

		// ---------------------------- ANIMACION DADOS ----------------------------
		if (estadoDados == DADOS_ESPERANDO && mainWindow.getDadosGirando()) {
			estadoDados = DADOS_ANIMANDO_MONEDA;
			animarMoneda = true;
			monedaMostrada = true;
			monedaSubiendoDados = true;
			alturaMonedaDados = 0.8f;
			alturaDados = 0.8f;
			anguloDados = 0.0f;
		}

		if (estadoDados == DADOS_ANIMANDO_MONEDA) {
			if (monedaSubiendoDados) {
				alturaMonedaDados += velocidadMoneda / velocidadSubidaMoneda * deltaTime;
				if (alturaMonedaDados >= 2.0f) {
					monedaSubiendoDados = false;
				}
			}
			else {
				alturaMonedaDados -= velocidadMoneda / velocidadSubidaMoneda * deltaTime;
				if (alturaMonedaDados <= 0.8f) {
					alturaMonedaDados = 0.8f;
					animarMoneda = false;
					monedaMostrada = false;
					if (sonidoMoneda) Mix_PlayChannel(-1, sonidoMoneda, 0);
					estadoDados = DADOS_GIRANDO_SUBIENDO;
					sonidoDadosReproducido = false;
					dadosYaCayeron = false;
					alturaDados = 0.8f;
					anguloDados = 0.0f;
				}
			}
		}

		if (estadoDados == DADOS_GIRANDO_SUBIENDO) {
			if (!sonidoDadosReproducido && sonidoDados) {
				Mix_PlayChannel(-1, sonidoDados, 0);
				sonidoDadosReproducido = true;
			}

			alturaDados += 5.0f / velocidadSubidaDados * deltaTime;
			anguloDados += 10.0f * deltaTime;

			if (alturaDados >= 5.0f) {
				alturaDados = 5.0f;
				estadoDados = DADOS_GIRANDO_BAJANDO;
				dadosYaCayeron = true;
				rotacionFinalDado1 = (rand() % 4) * 90.0f;
				rotacionFinalDado2 = (rand() % 4) * 90.0f;
			}
		}

		if (estadoDados == DADOS_GIRANDO_BAJANDO) {
			alturaDados -= 5.0f / velocidadSubidaDados * deltaTime;
			anguloDados += 10.0f * deltaTime;

			if (alturaDados <= 0.8f) {
				alturaDados = 0.8f;
				anguloDados = 0.0f;
				estadoDados = DADOS_ESPERANDO;
				activarSusto = true;
			}
		}

		//*********************************************************************************************************************************************************************************************************7

			// ---------------------------- BOLICHE + NPC PENA ----------------------------

		static float alturaMonedaBoliche = 0.8f;
		static float velocidadMonedaBoliche = 0.1f;
		static float bolaBoliche = 0.0f;
		static float velocidadBola = 0.1f;
		static float tiempoCaidaPinos = 0.0f;
		static bool animarCaidaPinos = false;
		static bool animarMonedaBoliche = false;
		static bool monedaMostradaBoliche = false;
		static enum EstadoJuego { ESPERANDO, ANIMANDO_MONEDABOLICHE, ANIMANDO_BOLICHE } estado = ESPERANDO;
		static bool monedaSubiendoBoliche = false;
		static bool sonidoStrikeReproducido = false;

		if (estado == ESPERANDO && mainWindow.getBolaLnazada()) {
			estado = ANIMANDO_MONEDABOLICHE;
			animarMonedaBoliche = true;
			monedaMostradaBoliche = true;
			monedaSubiendoBoliche = true;
		}

		if (estado == ANIMANDO_MONEDABOLICHE) {
			if (monedaSubiendoBoliche) {
				alturaMonedaBoliche += velocidadMonedaBoliche * deltaTime;
				if (alturaMonedaBoliche >= 2.0f) {
					monedaSubiendoBoliche = false;
				}
			}
			else {
				alturaMonedaBoliche -= velocidadMonedaBoliche * deltaTime;
				if (alturaMonedaBoliche <= 0.8f) {
					alturaMonedaBoliche = 0.8f;
					animarMonedaBoliche = false;
					monedaMostradaBoliche = false;
					if (sonidoMoneda)
					{
						Mix_PlayChannel(-1, sonidoMoneda, 0);
					}
					estado = ANIMANDO_BOLICHE;
					bolaBoliche = 0.0f;
					sonidoStrikeReproducido = false;
				}
			}
		}

		if (estado == ANIMANDO_BOLICHE) {
			bolaBoliche += velocidadBola * deltaTime;

			if (!sonidoStrikeReproducido && sonidoBoliche) {
				Mix_PlayChannel(-1, sonidoBoliche, 0);
				sonidoStrikeReproducido = true;
			}

			if (bolaBoliche >= 7.0f) {
				bolaBoliche = 0.0f;
				sonidoStrikeReproducido = false;
				mainWindow.desactivarBolaLanzada();
				estado = ESPERANDO;
			}
		}

		if (!animarCaidaPinos && bolaBoliche >= 4.8f) {
			animarCaidaPinos = true;
			tiempoCaidaPinos = 0.0f;
			pinoCaido0 = pinoCaido1 = pinoCaido2 = pinoCaido3 = pinoCaido4 =
				pinoCaido5 = pinoCaido6 = pinoCaido7 = pinoCaido8 = pinoCaido9 = true;
		}

		if (animarCaidaPinos) {
			tiempoCaidaPinos += deltaTime;

			auto caer = [](bool& caido, float& rotacion) {
				if (caido && rotacion < 90.0f) {
					rotacion += 60.0f * deltaTime;
					if (rotacion > 90.0f) rotacion = 90.0f;
				}
				};

			caer(pinoCaido0, rotacionPino0); caer(pinoCaido1, rotacionPino1);
			caer(pinoCaido2, rotacionPino2); caer(pinoCaido3, rotacionPino3);
			caer(pinoCaido4, rotacionPino4); caer(pinoCaido5, rotacionPino5);
			caer(pinoCaido6, rotacionPino6); caer(pinoCaido7, rotacionPino7);
			caer(pinoCaido8, rotacionPino8); caer(pinoCaido9, rotacionPino9);

			if (tiempoCaidaPinos >= 10.0f) {
				pinoCaido0 = pinoCaido1 = pinoCaido2 = pinoCaido3 = pinoCaido4 =
					pinoCaido5 = pinoCaido6 = pinoCaido7 = pinoCaido8 = pinoCaido9 = false;

				rotacionPino0 = rotacionPino1 = rotacionPino2 = rotacionPino3 = rotacionPino4 =
					rotacionPino5 = rotacionPino6 = rotacionPino7 = rotacionPino8 = rotacionPino9 = 0.0f;

				animarCaidaPinos = false;
			}
		}
		const float DURACION_ANIMACION_PENA = 80.0f;

		if (animarPena) {
			tiempoAnimacionPena += deltaTime;

			// Reproducir sonido solo una vez
			if (!sonidoPenaReproducido) {
				Mix_HaltChannel(-1);  // Silencia otros sonidos
				canalPena = Mix_PlayChannel(-1, sonidoPena, 0);
				if (canalPena != -1)
					Mix_Volume(canalPena, MIX_MAX_VOLUME);
				sonidoPenaReproducido = true;
			}

			// Movimiento sincronizado con tiempo
			float progreso = tiempoAnimacionPena / DURACION_ANIMACION_PENA;
			progreso = glm::clamp(progreso, 0.0f, 1.0f);

			anguloBrazoP = 130.0f * progreso; // sube hasta 130° en 5s
			penaTemblor = sin(tiempoAnimacionPena * 20.0f) * 0.1f;

			if (tiempoAnimacionPena >= DURACION_ANIMACION_PENA) {
				animarPena = false;
			}
		}
		else {
			// Regreso suave a estado base
			if (anguloBrazoP > 0.0f) {
				anguloBrazoP -= 100.0f * deltaTime;
				if (anguloBrazoP < 0.0f) anguloBrazoP = 0.0f;
			}
			penaTemblor = 0.0f;
		}

		//*********************************************************************************************************************************************************************************************************7

		// ---------------------------- DARDOS + HÉRCULES ----------------------------

		enum EstadoDardo { D_ESPERANDO, D_ANIMANDO_MONEDA, D_LANZANDO_DARDO };
		static EstadoDardo estadoDardo = D_ESPERANDO;

		static bool monedaSubiendoDardo = false;
		static float alturaMonedaDardo = 1.8f;
		static bool monedaMostrada = false;
		static bool animarMonedaDardo = false;

		static glm::vec3 posicionInicialDardo = glm::vec3(-70.0f, 14.0f, 83.0f);
		static glm::vec3 posicionDardo = posicionInicialDardo;
		static glm::vec3 direccionDardo = glm::vec3(0.0f);
		static float velocidadDardo = 0.5f;
		static bool direccionCalculada = false;

		static float rotacionDardo = 0.0f;

		const float TIEMPO_REAPARICION_GLOBO = 1.5f;
		const float velocidadMoneda2 = 0.1f;

		// -------------------- VARIABLES ANIMACIÓN HÉRCULES --------------------
		static bool animarPatadaHercules = false;
		static float tiempoAnimacionPatada = 0.0f;
		const float DURACION_PATADA_TOTAL = 39.846f; // duración del sonido
		static float anguloPiernaDer_Hercules = 0.0f;
		static float anguloPiernaIzq_Hercules = 0.0f;
		static float desplazamientoHerculesY = 0.0f;
		static bool sonidoPatadaReproducido = false;

		// -------------------- MONEDA --------------------
		if (estadoDardo == D_ESPERANDO && mainWindow.getDardoLanzado()) {
			estadoDardo = D_ANIMANDO_MONEDA;
			animarMonedaDardo = true;
			monedaMostrada = true;
			monedaSubiendoDardo = true;
			direccionCalculada = false;
			rotacionDardo = 45.0f;
		}

		if (estadoDardo == D_ANIMANDO_MONEDA) {
			if (monedaSubiendoDardo) {
				alturaMonedaDardo += velocidadMoneda2 * deltaTime;
				if (alturaMonedaDardo >= 2.0f)
					monedaSubiendoDardo = false;
			}
			else {
				alturaMonedaDardo -= velocidadMoneda2 * deltaTime;
				if (alturaMonedaDardo <= 0.8f) {
					alturaMonedaDardo = 0.8f;
					animarMonedaDardo = false;
					monedaMostrada = false;

					if (sonidoMoneda)
						Mix_PlayChannel(-1, sonidoMoneda, 0);

					estadoDardo = D_LANZANDO_DARDO;
				}
			}
		}

		// -------------------- LANZAMIENTO DARDOS --------------------
		if (estadoDardo == D_LANZANDO_DARDO) {
			if (!direccionCalculada) {
				glm::vec3 objetivo = glm::vec3(0.0f);
				int encontrados = 0;
				for (int i = 0; i < 12; ++i) {
					if (globoVisible[i]) {
						objetivo += posicionesGlobos[i];
						encontrados++;
					}
				}
				if (encontrados > 0) {
					objetivo /= float(encontrados);
					glm::vec3 destinoXZ = glm::vec3(objetivo.x, posicionDardo.y, objetivo.z);
					direccionDardo = glm::normalize(destinoXZ - posicionDardo);
				}
				else {
					direccionDardo = glm::vec3(0.0f, 0.0f, 1.0f);
				}
				direccionCalculada = true;
			}

			posicionDardo += direccionDardo * velocidadDardo * deltaTime;
			rotacionDardo = 45.0f;

			for (int i = 0; i < 12; ++i) {
				if (globoVisible[i]) {
					float distancia = glm::distance(posicionDardo, posicionesGlobos[i]);
					if (distancia < 2.5f) {
						animarPatadaHercules = true;
						tiempoAnimacionPatada = 0.0f;
						sonidoPatadaReproducido = false;
						globoVisible[i] = false;
						tiempoDesaparicionGlobo[i] = glfwGetTime();

						if (sonidoGlobo)
							Mix_PlayChannel(-1, sonidoGlobo, 0);

						mainWindow.desactivarDardoLanzado();
						posicionDardo = posicionInicialDardo;
						estadoDardo = D_ESPERANDO;
						rotacionDardo = 0.0f;
						break;
					}
				}
			}

			if (glm::distance(posicionDardo, posicionInicialDardo) > 100.0f) {
				mainWindow.desactivarDardoLanzado();
				posicionDardo = posicionInicialDardo;
				estadoDardo = D_ESPERANDO;
				rotacionDardo = 0.0f;
			}
		}

		// -------------------- REAPARICIÓN GLOBOS --------------------
		for (int i = 0; i < 12; ++i) {
			if (!globoVisible[i]) {
				double tiempoActual = glfwGetTime();
				if (tiempoActual - tiempoDesaparicionGlobo[i] >= TIEMPO_REAPARICION_GLOBO)
					globoVisible[i] = true;
			}
		}

		// -------------------- ANIMACIÓN HÉRCULES --------------------

		if (animarPatadaHercules) {
			tiempoAnimacionPatada += deltaTime;

			float progreso = tiempoAnimacionPatada / DURACION_PATADA_TOTAL;
			progreso = glm::clamp(progreso, 0.0f, 1.0f);

			// Dos patadas (1 ciclo completo = 0–0.5, 0.5–1.0)
			float fase = fmod(progreso * 2.0f, 1.0f); // 0 a 1 dos veces

			anguloPiernaDer_Hercules = 65.0f * sin(fase * glm::pi<float>());
			anguloPiernaIzq_Hercules = -45.0f * sin(fase * glm::pi<float>());
			desplazamientoHerculesY = 1.2f * sin(fase * glm::pi<float>());

			// Reproducir solo una vez el sonido al inicio
			if (!sonidoPatadaReproducido && sonidoHercules) {
				Mix_PlayChannel(-1, sonidoHercules, 0);
				sonidoPatadaReproducido = true;
			}

			if (tiempoAnimacionPatada >= DURACION_PATADA_TOTAL) {
				animarPatadaHercules = false;
				anguloPiernaDer_Hercules = 0.0f;
				anguloPiernaIzq_Hercules = 0.0f;
				desplazamientoHerculesY = 0.0f;
			}
		}

		//*********************************************************************************************************************************************************************************************************7

		// ---------------------------- ANIMACION DE HACHA + DANNY ----------------------------

		static enum EstadoHacha { HACHA_ESPERANDO, HACHA_MONEDA, HACHA_VOLANDO, HACHA_CLAVADA, HACHA_VOLVIENDO } estadoHacha = HACHA_ESPERANDO;
		static float alturaMonedaHacha = 0.8f;
		static bool monedaSubiendoHacha = false;
		static bool monedaMostradaHacha = false;

		static float desplazamientoHacha = 0.0f;
		static float rotacionHacha = 0.0f;

		static float velocidadHachaAnim = 1.5f;

		static float tiempoHachaVuelo = 0.0f;
		static const float TIEMPO_TOTAL_VUELO = 5.0f;
		static float tiempoClavado = 0.0f;
		static const float TIEMPO_ESPERA_CLAVADO = 50.0f;

		static bool animacionDisparoDP = false;
		static float tiempoDisparoDP = 0.0f;
		static const float TIEMPO_DISPARO_DP = 100.0f;

		static float desplazamientoDP_X = 0.0f;
		static float desplazamientoDP_Y = 0.0f;
		static float desplazamientoDP_Z = 0.0f;

		static float vueloDP = 0.0f;

		if (estadoHacha == HACHA_ESPERANDO && mainWindow.getTeclaMHacha()) {
			estadoHacha = HACHA_MONEDA;
			monedaSubiendoHacha = true;
			monedaMostradaHacha = true;
			alturaMonedaHacha = 0.8f;
			desplazamientoHacha = 0.0f;
			rotacionHacha = 0.0f;
			tiempoHachaVuelo = 0.0f;
			tiempoClavado = 0.0f;
			animacionDisparoDP = false;
			tiempoDisparoDP = 0.0f;
			desplazamientoDP_X = 0.0f;
			desplazamientoDP_Y = 0.0f;
			desplazamientoDP_Z = 0.0f;
		}

		if (estadoHacha == HACHA_MONEDA) {
			if (monedaSubiendoHacha) {
				alturaMonedaHacha += velocidadMoneda * deltaTime;
				if (alturaMonedaHacha >= 2.0f) {
					monedaSubiendoHacha = false;
				}
			}
			else {
				alturaMonedaHacha -= velocidadMoneda * deltaTime;
				if (alturaMonedaHacha <= 0.8f) {
					alturaMonedaHacha = 0.8f;
					monedaMostradaHacha = false;
					estadoHacha = HACHA_VOLANDO;
					if (sonidoMoneda) Mix_PlayChannel(-1, sonidoMoneda, 0);
					tiempoHachaVuelo = 0.0f;
				}
			}
		}

		if (estadoHacha == HACHA_VOLANDO) {
			tiempoHachaVuelo += deltaTime;
			desplazamientoHacha -= velocidadHachaAnim * deltaTime;
			rotacionHacha += 90.0f * deltaTime;

			if (desplazamientoHacha <= -20.0f) {
				desplazamientoHacha = -20.0f;
				rotacionHacha = 0.0f;
				estadoHacha = HACHA_CLAVADA;
				tiempoClavado = 0.0f;
				animacionDisparoDP = true;
				tiempoDisparoDP = 0.0f;
				if (sonidoHacha) Mix_PlayChannel(-1, sonidoHacha, 0);
			}
		}

		if (estadoHacha == HACHA_CLAVADA) {
			tiempoClavado += deltaTime;
			if (animacionDisparoDP) {
				tiempoDisparoDP += deltaTime;
				desplazamientoDP_X = -1.0f * sin(tiempoDisparoDP * 1.0f);
				desplazamientoDP_Y = 0.5f * sin(tiempoDisparoDP * 1.0f);
				if (sonidoDanny) Mix_PlayChannel(-1, sonidoDanny, 0);
			}
			if (tiempoClavado >= TIEMPO_ESPERA_CLAVADO) {
				desplazamientoHacha = 0.0f;
				rotacionHacha = 0.0f;
				tiempoHachaVuelo = 0.0f;
				estadoHacha = HACHA_ESPERANDO;
				mainWindow.setTeclaMHacha(false);
				animacionDisparoDP = false;
				tiempoDisparoDP = 0.0f;
				desplazamientoDP_X = 0.0f;
				desplazamientoDP_Y = 0.0f;
			}
		}

		if (estadoHacha == HACHA_VOLVIENDO) {
			estadoHacha = HACHA_ESPERANDO;
			desplazamientoHacha = 0.0f;
			rotacionHacha = 0.0f;
			tiempoHachaVuelo = 0.0f;
			mainWindow.setTeclaMHacha(false);
		}

		if (mainWindow.getAnimacion_Simp1_DP()) {
			vueloDP += 0.3f * deltaTime;
			desplazamientoDP_X = 2 * sin(glm::radians(3 * vueloDP + 90.0f));
			desplazamientoDP_Y = 3 * sin(glm::radians(3 * vueloDP));
		}
		else if (animacionDisparoDP) {

		}
		else {
			vueloDP = 0.0f;
			desplazamientoDP_X = 0.0f;
			desplazamientoDP_Y = 0.0f;
		}

		//*********************************************************************************************************************************************************************************************************7

				// ---------------------------- ANIMACION DE BATE ----------------------------


		static enum EstadoBeisbol { BEISBOL_ESPERANDO, BEISBOL_MONEDA, BEISBOL_BATEADO } estadoBeisbol = BEISBOL_ESPERANDO;

		static float alturaMonedaBeisbol = 0.0f;
		static bool monedaSubiendoBeisbol = false;
		static bool monedaMostradaBeisbol = false;

		static float bolaY = 3.0f;
		static float bolaZ = -75.0f;
		static float rotacionBolaBase = 0.0f;
		static float velocidadBolaBase = 1.0f;

		static float anguloBate = 0.0f;
		static glm::vec3 posicionBate = glm::vec3(-15.0f, 4.0f, -70.0f);

		static bool beisbolActivo = false;

		if (estadoBeisbol == BEISBOL_ESPERANDO && mainWindow.getBolaBaseGolpeada()) {
			estadoBeisbol = BEISBOL_MONEDA;
			monedaSubiendoBeisbol = true;
			monedaMostradaBeisbol = true;
			alturaMonedaBeisbol = 0.0f;
			bolaZ = -75.0f;
			bolaY = 3.0f;
			rotacionBolaBase = 0.0f;
			anguloBate = 0.0f;
			posicionBate = glm::vec3(-15.0f, 4.0f, -70.0f);
		}

		if (estadoBeisbol == BEISBOL_MONEDA) {
			if (monedaSubiendoBeisbol) {
				alturaMonedaBeisbol += 0.5f * deltaTime;
				if (alturaMonedaBeisbol >= 5.5f) {
					monedaSubiendoBeisbol = false;
				}
			}
			else {
				alturaMonedaBeisbol -= 0.5f * deltaTime;
				if (alturaMonedaBeisbol <= 3.0f) {
					monedaMostradaBeisbol = false;
					estadoBeisbol = BEISBOL_BATEADO;
					if (sonidoMoneda) Mix_PlayChannel(-1, sonidoMoneda, 0);
				}
			}
		}

		if (estadoBeisbol == BEISBOL_BATEADO) {
			if (!beisbolActivo) {
				CanalBeisbol = Mix_PlayChannel(-1, sonidoBateo, 0);
				beisbolActivo = true;
			}

			bolaZ -= velocidadBolaBase * deltaTime;

			if (bolaY < 15.0f) {
				bolaY += 20.0f * deltaTime;
				if (bolaY > 15.0f) bolaY = 15.0f;
			}

			rotacionBolaBase += 20.0f * deltaTime;
			if (rotacionBolaBase >= 360.0f) rotacionBolaBase -= 360.0f;

			if (anguloBate < 45.0f) {
				anguloBate += 5.0f * deltaTime;
				if (anguloBate > 45.0f) anguloBate = 45.0f;
			}
			posicionBate = glm::vec3(-15.0f, 15.0f, -70.0f);

			if (bolaZ <= -110.0f) {
				bolaZ = -75.0f;
				bolaY = 3.0f;
				rotacionBolaBase = 0.0f;
				anguloBate = 0.0f;
				posicionBate = glm::vec3(-15.0f, 4.0f, -70.0f);
				beisbolActivo = false;
				estadoBeisbol = BEISBOL_ESPERANDO;
				mainWindow.desactivarBolaBaseGolpeada();
			}
		}

		//*********************************************************************************************************************************************************************************************************7


		// Nuevas configuraciones con nombres actualizados
		static float velocidadSubidaMonedaTopo = 0.25f;
		static float velocidadBajadaMonedaTopo = 0.25f;

		static enum EstadoTopo { TOPO_ESPERANDO, TOPO_MONEDA, TOPO_GOLPEANDO } estadoTopo = TOPO_ESPERANDO;

		static float alturaMonedaTopo = 0.8f;
		static bool monedaSubiendoTopo = false;
		static bool monedaMostradaTopo = false;

		static float anguloMazo = 0.0f;
		static float velocidadGolpe = 2.0f;
		static bool bajandoMazo = true;
		static bool golpeando = false;

		static int contadorGolpes = 0;
		static const int TOTAL_GOLES = 3;

		static bool topoVisible[3] = { true, true, true };
		static bool topoGolpeado[3] = { false, false, false };
		static int mazoObjetivo = 0;

		static float desplazamientoTopoY[3] = { 0.0f, 0.0f, 0.0f };
		static float rotacionTopo[3] = { 0.0f, 0.0f, 0.0f };

		if (estadoTopo == TOPO_ESPERANDO && mainWindow.getMazoGolpeando()) {
			estadoTopo = TOPO_MONEDA;
			monedaSubiendoTopo = true;
			monedaMostradaTopo = true;
			alturaMonedaTopo = 0.8f;
			anguloMazo = 0.0f;
			bajandoMazo = true;
			golpeando = false;
			contadorGolpes = 0;

			for (int i = 0; i < 3; ++i) {
				topoVisible[i] = true;
				topoGolpeado[i] = false;
				desplazamientoTopoY[i] = 0.0f;
				rotacionTopo[i] = 0.0f;
			}

			mazoObjetivo = rand() % 3;
		}

		if (estadoTopo == TOPO_MONEDA) {
			if (monedaSubiendoTopo) {
				alturaMonedaTopo += velocidadSubidaMonedaTopo * deltaTime;
				if (alturaMonedaTopo >= 2.0f) {
					monedaSubiendoTopo = false;
				}
			}
			else {
				alturaMonedaTopo -= velocidadBajadaMonedaTopo * deltaTime;
				if (alturaMonedaTopo <= 0.8f) {
					alturaMonedaTopo = 0.8f;
					monedaMostradaTopo = false;

					estadoTopo = TOPO_GOLPEANDO;
					golpeando = true;

					if (sonidoMoneda) Mix_PlayChannel(-1, sonidoMoneda, 0);
				}
			}
		}

		if (estadoTopo == TOPO_GOLPEANDO && golpeando) {
			if (bajandoMazo) {
				anguloMazo += velocidadGolpe * deltaTime;
				if (anguloMazo >= 45.0f) {
					anguloMazo = 45.0f;
					bajandoMazo = false;

					if (topoVisible[mazoObjetivo]) {
						topoVisible[mazoObjetivo] = false;
						topoGolpeado[mazoObjetivo] = true;
						desplazamientoTopoY[mazoObjetivo] = 0.5f;
						rotacionTopo[mazoObjetivo] = 30.0f;

						if (sonidoTopos) Mix_PlayChannel(-1, sonidoTopos, 0);
					}
				}
			}
			else {
				anguloMazo -= velocidadGolpe * deltaTime;
				if (anguloMazo <= 0.0f) {
					anguloMazo = 0.0f;
					contadorGolpes++;
					if (contadorGolpes >= TOTAL_GOLES) {
						golpeando = false;
						estadoTopo = TOPO_ESPERANDO;
						mainWindow.desactivarMazoGolpeando();
					}
					else {
						mazoObjetivo = rand() % 3;
						bajandoMazo = true;
						for (int i = 0; i < 3; ++i) {
							topoVisible[i] = true;
							topoGolpeado[i] = false;
							desplazamientoTopoY[i] = 0.0f;
							rotacionTopo[i] = 0.0f;
						}
					}
				}
			}
		}




		anguloRotacionTopo += 10.0f * deltaTime;  // Velocidad de rotación
		if (anguloRotacionTopo >= 360.0f) {
			anguloRotacionTopo -= 360.0f;
		}






		//Animación alegría
		alegriaTiempo += deltaTime;
		alegriaSaltoY = abs(sin(alegriaTiempo * 3.0f)) * 0.5f; // Subidas y bajadas suaves
		alegriaAnguloBrazo = sin(alegriaTiempo * 5.0f) * 30.0f; // Oscila entre -30° y 30°

		//Animación tristeza
		tiempoTristeza += deltaTime;
		tristezaBalanceo = sin(tiempoTristeza * 0.2f) * 2.0f;  // Oscilación suave
		tristezaBrazoAngulo = sin(tiempoTristeza * 0.5f) * 1.0f;

		//Animación ember
		emberTiempo += deltaTime;
		emberAlturaY = abs(sin(emberTiempo * 0.2f)) * 0.3f;  // pequeño salto suave
		emberBrazoAngulo = sin(emberTiempo * 0.2f) * 25.0f;
		emberPiernaAngulo = sin(emberTiempo * 0.2f + glm::radians(90.0f)) * 15.0f;

		//Animación sam
		samTiempo += deltaTime;
		samBrazoAngulo = sin(samTiempo * 0.2f) * 20.0f;
		samPiernaAngulo = sin(samTiempo * 0.2f + glm::radians(180.0f)) * 10.0f;

		//Animación Pena
		penaTiempo += deltaTime;
		penaAnguloBalanceo = sin(penaTiempo * 0.5f) * 5.0f;     // Movimiento sutil de balanceo
		penaBrazoAngulo = sin(penaTiempo * 0.4f) * 10.0f;        // Brazos que se abrazan suavemente
		penaCabezaOffset = abs(sin(penaTiempo * 0.3f)) * 0.05f;  // Ligero descenso y subida de cabeza
		cycleTime = dayDuration + nightDuration + 2 * fadeDuration;

		t = fmod(glfwGetTime(), cycleTime);
		blendFactor = 0.0f;

		//0.3->Dia		0.1->Noche

		intensidad = 0.1f + 0.2f * (0.5f + 0.5f * sin(lastTime * velocidadDN));
		mainLight.UpdateLightIntensity(intensidad, intensidad);

		//Recibir eventos del usuario
		glfwPollEvents();

		glm::vec3 cameraOffsets[] = {
			glm::vec3(0.0f, 5.0f, -28.0f),  // Globos
			glm::vec3(0.0f, 5.0f, 15.0f), // Boliche
			glm::vec3(0.0f, 5.0f, -25.0f), // Dados
			glm::vec3(-25.0f, -5.0f, 0.0f), // Hachas
			glm::vec3(0.0f, 5.0f, 22.0f)  // Topos
		};
		if (currentCameraMode != ATTRACTIONS) {
			camera.keyControl(mainWindow.getsKeys(), deltaTime, currentCameraMode);
		}
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		bool* keys = mainWindow.getsKeys();


		static bool pPresionadoAntes = false;
		if (keys[GLFW_KEY_P] && !pPresionadoAntes) {
			animarPena = true;
			tiempoAnimacionPena = 0.0f;
			sonidoPenaReproducido = false;
			pPresionadoAntes = true;
		}
		if (!keys[GLFW_KEY_P]) pPresionadoAntes = false;




		if (keys[GLFW_KEY_1]) currentCameraMode = FIRST_PERSON;
		if (keys[GLFW_KEY_2]) currentCameraMode = THIRD_PERSON;
		if (keys[GLFW_KEY_3]) currentCameraMode = TOP_VIEW;
		if (keys[GLFW_KEY_4]) {
			currentCameraMode = ATTRACTIONS;
			attractionInitialized = false;  // Reinicia bandera de inicialización
		}

		// Control de giro de Furia con las flechas izquierda/derecha
		if (keys[GLFW_KEY_D]) {
			furiaYaw -= velocidadGiroFuria * deltaTime;
		}
		if (keys[GLFW_KEY_A]) {
			furiaYaw += velocidadGiroFuria * deltaTime;
		}

		// Coordenadas de las atracciones 
		glm::vec3 posDados(80.0f, 3.0f, 100.0f);
		glm::vec3 posJaula(0.0f, 3.0f, -110.0f); // Coordenada corregida de la jaula
		glm::vec3 posTopos(-70.0f, 3.0f, -90.0f);
		glm::vec3 posHachas(70.0f, 3.0f, -90.0f);
		glm::vec3 posDardos(-80.0f, 3.0f, 105.0f);
		glm::vec3 posBoliche(0.0f, 3.0f, 235.0f); // Coordenadas nuevas del boliche (ajusta si es necesario)

		float distanciaCambioCamara = 35.0f;

		bool cercaDeAlguna =
			glm::distance(furiaPos, posDados) < distanciaCambioCamara ||
			glm::distance(furiaPos, posJaula) < distanciaCambioCamara ||
			glm::distance(furiaPos, posTopos) < distanciaCambioCamara ||
			glm::distance(furiaPos, posHachas) < distanciaCambioCamara ||
			glm::distance(furiaPos, posDardos) < distanciaCambioCamara ||
			glm::distance(furiaPos, posBoliche) < distanciaCambioCamara;

		if (cercaDeAlguna && currentCameraMode != FIRST_PERSON) {
			currentCameraMode = FIRST_PERSON;
		}
		else if (!cercaDeAlguna && currentCameraMode == FIRST_PERSON) {
			currentCameraMode = THIRD_PERSON;
		}

		lastSwitchTime = 0.0f;
		currentTime = glfwGetTime();
		if (currentCameraMode == ATTRACTIONS) {
			SpotLight* spotLightArrays[] = { spotLights2, spotLights3, spotLights5, spotLights6, spotLights7 };
			int spotLightCounts[] = { spotLightCount2, spotLightCount3, spotLightCount5, spotLightCount6, spotLightCount7 };

			if (keys[GLFW_KEY_E] && currentTime - lastSwitchTime > 0.3) {
				attractionIndex = (attractionIndex + 1) % 5;
				SpotLight* currentArray = spotLightArrays[attractionIndex];
				int currentCount = spotLightCounts[attractionIndex];
				int index = static_cast<int>(glfwGetTime() / 10.0f) % currentCount;
				glm::vec3 attractionPos = currentArray[index].GetPosition();
				glm::vec3 offset = cameraOffsets[attractionIndex];
				camera.setPosition(attractionPos + offset);
				glm::vec3 target = attractionPos + glm::vec3(0.0f, -5.0f, 0.0f); // apúntale más bajo
				camera.setDirection(glm::normalize(target - camera.getCameraPosition()));
				lastSwitchTime = currentTime;
			}

			if (keys[GLFW_KEY_Q] && currentTime - lastSwitchTime > 0.3) {
				attractionIndex = (attractionIndex - 1 + 5) % 5;
				SpotLight* currentArray = spotLightArrays[attractionIndex];
				int currentCount = spotLightCounts[attractionIndex];
				int index = static_cast<int>(glfwGetTime() / 10.0f) % currentCount;
				glm::vec3 attractionPos = currentArray[index].GetPosition();
				glm::vec3 offset = cameraOffsets[attractionIndex];
				camera.setPosition(attractionPos + offset);
				glm::vec3 target = attractionPos + glm::vec3(0.0f, -5.0f, 0.0f); // apúntale más bajo
				camera.setDirection(glm::normalize(target - camera.getCameraPosition()));
				lastSwitchTime = currentTime;
			}
		}
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glm::mat4 view;
		switch (currentCameraMode) {
		case FIRST_PERSON:
			camera.setPosition(furiaPos + glm::vec3(0.0f, 8.0f, 0.0f));
			view = camera.calculateViewMatrix();  // ¡NO ajustar el yaw manualmente!
			break;
		case THIRD_PERSON:
		{
			glm::vec3 offset = glm::vec3(0.0f, 10.0f, 20.0f); // distancia detrás de Furia
			glm::vec3 thirdPersonPos = furiaPos - glm::normalize(camera.getCameraDirection()) * 20.0f + glm::vec3(0.0f, 10.0f, 0.0f);
			camera.setPosition(thirdPersonPos);
			view = camera.calculateViewMatrix();
			break;
		}
		case TOP_VIEW:
		{
			static bool primeraVez = true;
			if (primeraVez) {
				camera.setPosition(glm::vec3(0.0f, 150.0f, 0.0f));
				primeraVez = false;
			}

			// Fijar la dirección de la cámara hacia abajo
			glm::vec3 pos = camera.getCameraPosition();
			glm::vec3 target = pos + glm::vec3(0.0f, -1.0f, 0.0f); // mira hacia abajo
			glm::vec3 up = glm::vec3(0.0f, 0.0f, -1.0f); // mantener eje horizontal como 'arriba'

			view = glm::lookAt(pos, target, up);
			break;
		}
		case ATTRACTIONS:
			SpotLight* spotLightArrays[] = { spotLights2, spotLights3, spotLights5, spotLights6, spotLights7 };
			int spotLightCounts[] = { spotLightCount2, spotLightCount3, spotLightCount5, spotLightCount6, spotLightCount7 };

			if (!attractionInitialized) {
				SpotLight* currentArray = spotLightArrays[attractionIndex];
				int currentCount = spotLightCounts[attractionIndex];
				int index = static_cast<int>(glfwGetTime() / 10.0f) % currentCount;
				glm::vec3 attractionPos = currentArray[index].GetPosition();
				glm::vec3 offset = cameraOffsets[attractionIndex];
				camera.setPosition(attractionPos + offset);
				camera.setDirection(glm::normalize(attractionPos - camera.getCameraPosition()));
				camera.setYaw(glm::radians(180.0f));  // Opcional: ajusta orientación
				attractionInitialized = true;
			}
			view = camera.calculateViewMatrix();
			break;
		}

		static bool sonidoIniciado = false;
		if (!sonidoIniciado && musicaFondo && sonidoAmbiente) {
			Mix_PlayMusic(musicaFondo, -1);
			canalAmbiente = Mix_PlayChannel(-1, sonidoAmbiente, -1);
			sonidoIniciado = true;
		}
		else if (!Mix_Playing(canalAmbiente)) {
			canalAmbiente = Mix_PlayChannel(-1, sonidoAmbiente, -1);
		}

		float distancia = glm::distance(furiaPos, posBoliche);
		float distanciaHacha = glm::distance(furiaPos, posHachas);
		float distanciaGlobos = glm::distance(furiaPos, posDardos);
		float distanciaDados = glm::distance(furiaPos, posDados);
		float distanciaTopos = glm::distance(furiaPos, posTopos);
		float distanciaJaula = glm::distance(furiaPos, posJaula);

		if (distancia < 60.0f && !bolicheActivo && musicaBoliche) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaBoliche, -1);
			bolicheActivo = true;
			hachaActiva = false;
			globosActivos = false;
			dadosActivos = false;
			toposActivos = false;
			bateoActivo = false;
		}
		else if (distanciaHacha < 30.0f && !hachaActiva && musicaHacha) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaHacha, -1);
			hachaActiva = true;
			globosActivos = false;
			bolicheActivo = false;
			dadosActivos = false;
			toposActivos = false;
			bateoActivo = false;
		}
		else if (distanciaGlobos < 30.0f && !globosActivos && musicaGlobos) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaGlobos, -1);
			hachaActiva = false;
			bolicheActivo = false;
			globosActivos = true;
			dadosActivos = false;
			toposActivos = false;
			bateoActivo = false;
		}
		else if (distanciaDados < 30.0f && !dadosActivos && musicaDados) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaDados, -1);
			dadosActivos = true;
			hachaActiva = false;
			bolicheActivo = false;
			globosActivos = false;
			toposActivos = false;
			bateoActivo = false;

		}
		else if (distanciaTopos < 30.0f && !toposActivos && musicaTopos) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaTopos, -1);
			toposActivos = true;
			hachaActiva = false;
			bolicheActivo = false;
			globosActivos = false;
			dadosActivos = false;
			bateoActivo = false;
		}
		else if (distanciaJaula < 30.0f && !bateoActivo && musicaBateo) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaBateo, -1);
			bateoActivo = true;
			hachaActiva = false;
			bolicheActivo = false;
			globosActivos = false;
			dadosActivos = false;
			toposActivos = false;
		}

		else if (distancia >= 40.0f && distanciaHacha >= 30.0f && distanciaGlobos >= 30.0f && distanciaDados >= 30.0f && distanciaTopos >= 30.0f && distanciaJaula >= 30.0f
			&& (bolicheActivo || hachaActiva || globosActivos || dadosActivos || toposActivos || bateoActivo)) {
			Mix_HaltMusic();
			Mix_PlayMusic(musicaFondo, -1);
			bolicheActivo = false;
			hachaActiva = false;
			globosActivos = false;
			dadosActivos = false;
			toposActivos = false;
			bateoActivo = false;
		}

		glm::vec3 posCarrousel(0.0f, 3.0f, 60.0f);
		float distanciaCarrousel = glm::distance(furiaPos, posCarrousel);
		if (distanciaCarrousel < 50.0f && !carrouselActivo && sonnidoCarrusel) {
			canalCarrousel = Mix_PlayChannel(-1, sonnidoCarrusel, -1); // Repetir
			carrouselActivo = true;
		}
		else if (distanciaCarrousel >= 50.0f && carrouselActivo) {
			Mix_HaltChannel(canalCarrousel);
			carrouselActivo = false;
		}

		glm::vec3 posMartillo(0.0f, 3.0f, -50.0f);
		float distanciaMartillo = glm::distance(furiaPos, posMartillo);
		if (distanciaMartillo < 50.0f && !martilloActivo && sonidoMartillo) {
			canalMartillo = Mix_PlayChannel(-1, sonidoMartillo, -1); // Repetir
			martilloActivo = true;
		}
		else if (distanciaMartillo >= 50.0f && martilloActivo) {
			Mix_HaltChannel(canalMartillo);
			martilloActivo = false;
		}


		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// día completo
		if (t < dayDuration) {
			blendFactor = 0.0f;
		}
		// fundido día ? noche
		else if (t < dayDuration + fadeDuration) {
			blendFactor = (t - dayDuration) / fadeDuration;
		}
		// noche completa
		else if (t < dayDuration + fadeDuration + nightDuration) {
			blendFactor = 1.0f;
		}
		// fundido noche ? día
		else {
			blendFactor = 1.0f - (t - dayDuration - fadeDuration - nightDuration) / fadeDuration;
		}


		// 2) Ángulo del sol [?90°, 270°): empieza en el horizonte este, sube al cenit, cae al horizonte oeste
		sunAngleDeg = (t / cycleTime) * 360.0f - 90.0f;


		// 3) Vector dirección del sol: barrido en el plano X–Y (Z fijo o pequeño para inclinar)
		glm::vec3 sunDir = glm::normalize(glm::vec3(
			cosf(sunRad),      // componente X: este/oeste
			sinf(sunRad),      // componente Y: horizonte?cenit?horizonte
			0.2f               // un poco de Z para que la luz no venga exactamente del foco
		));

		// 4) Actualiza la dirección de mainLight
		mainLight.SetDirection(sunDir);
		// luego dibujas:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Matrices para el skybox
		glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.calculateViewMatrix())); // sin traslación
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f),
			(GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(),
			0.1f, 100.0f);
		glDepthFunc(GL_LEQUAL);
		skybox.DrawSkybox(viewMatrix, projectionMatrix, blendFactor);
		// Dibuja skybox actual
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		shaderList[0].SetDirectionalLight(&mainLight);							//Habilita luz principal

		//Arreglo para los arreglos de luces
		// Obtenemos posición de la cámara
		glm::vec3 camPos(camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		totalLucesActivas = 0;

		// ---------- Arreglo 1: spotLights[] (enciende solo si están cerca)
		for (int i = 0; i < spotLightCount; ++i) {
			if (estaCerca(camPos, spotLights[i].GetPosition(), 90.0f)) {
				lucesActivas[totalLucesActivas++] = spotLights[i];
			}
		}

		// ---------- Arreglo 3: spotLights3[] (una luz encendida a la vez cíclicamente)
		camaraCercaDeLuces3 = false;
		for (int i = 0; i < spotLightCount3; ++i) {
			if (estaCerca(camPos, spotLights3[i].GetPosition(), 90.0f)) {
				camaraCercaDeLuces3 = true;
				break;
			}
		}

		//tiempoAcumulado = 0.0f;
		tiempoAcumulado += deltaTime;

		if (mainWindow.getIluminacionTeclado()) {
			totalLucesActivas = 0;
			for (int i = 0; i < spotLightCount4; ++i) {
				lucesActivas[i] = spotLights4[i];
				totalLucesActivas++;
			}
		}

		if (camaraCercaDeLuces3) {
			int indiceActivo = static_cast<int>(tiempoAcumulado / 10.0f) % spotLightCount3;
			lucesActivas[totalLucesActivas++] = spotLights3[indiceActivo];
		}

		// GLOBOS
		if (glm::distance(furiaPos, posDardos) < 35.0f) {
			int indiceActivo = static_cast<int>(tiempoAcumulado / 10.0f) % spotLightCount2;
			lucesActivas[totalLucesActivas++] = spotLights2[indiceActivo];
		}

		// DADOS
		if (glm::distance(furiaPos, posDados) < 50.0f) {
			int indiceActivo = static_cast<int>(tiempoAcumulado / 10.0f) % spotLightCount5;
			lucesActivas[totalLucesActivas++] = spotLights5[indiceActivo];
		}

		// HACHAS
		if (glm::distance(furiaPos, posHachas) < 35.0f) {
			int indiceActivo = static_cast<int>(tiempoAcumulado / 10.0f) % spotLightCount6;
			lucesActivas[totalLucesActivas++] = spotLights6[indiceActivo];
		}

		// TOPOS
		if (glm::distance(furiaPos, posTopos) < 35.0f) {
			int indiceActivo = static_cast<int>(tiempoAcumulado / 10.0f) % spotLightCount7;
			lucesActivas[totalLucesActivas++] = spotLights7[indiceActivo];
		}

		// ---------- Activar luces finales
		shaderList[0].SetSpotLights(lucesActivas, totalLucesActivas);

		//0.3 dia
		//0.1 noche
		if (intensidad < 0.175f) {
			shaderList[0].SetPointLights(pointLights1, pointLightCount_ARRAY1);		//Habilita luces del pointlight
		}
		else if (intensidad > 0.175f) {
			shaderList[0].SetPointLights(pointLights2, pointLightCount_ARRAY2);		//Habilita luces del pointlight
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux2(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//****************************************** EDIFICIOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -245.0f));
		model = glm::scale(model, glm::vec3(14.0f, 14.0f, 14.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Iglesia.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-230.0f, -6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Portales.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(230.0f, -6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Portales.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -6.0f, 235.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		chaparrin.RenderModel();

		//************************Boliche**********************************************************
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Boliche.RenderModel();
		// Ejes de caída individuales
		glm::vec3 ejeCaidaPino0 = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 ejeCaidaPino1 = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 ejeCaidaPino2 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 ejeCaidaPino3 = glm::vec3(-1.0f, 0.0f, 0.0f);
		glm::vec3 ejeCaidaPino4 = glm::vec3(1.0f, 0.0f, 1.0f);
		glm::vec3 ejeCaidaPino5 = glm::vec3(-1.0f, 0.0f, -1.0f);
		glm::vec3 ejeCaidaPino6 = glm::vec3(1.0f, 0.0f, -1.0f);
		glm::vec3 ejeCaidaPino7 = glm::vec3(-1.0f, 0.0f, 1.0f);
		glm::vec3 ejeCaidaPino8 = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 ejeCaidaPino9 = glm::vec3(0.0f, 0.0f, -1.0f);

		// Renderizado de cada pino con su eje
		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.0f, 1.5f, 0.0f));
		if (pinoCaido0) {
			model = glm::rotate(model, glm::radians(rotacionPino0), glm::normalize(ejeCaidaPino0));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, 0.15f));
		if (pinoCaido1) {
			model = glm::rotate(model, glm::radians(rotacionPino1), glm::normalize(ejeCaidaPino1));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -0.15f));
		if (pinoCaido2) {
			model = glm::rotate(model, glm::radians(rotacionPino2), glm::normalize(ejeCaidaPino2));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, 0.3f));
		if (pinoCaido3) {
			model = glm::rotate(model, glm::radians(rotacionPino3), glm::normalize(ejeCaidaPino3));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -0.3f));
		if (pinoCaido4) {
			model = glm::rotate(model, glm::radians(rotacionPino4), glm::normalize(ejeCaidaPino4));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.0f, 1.5f, -3.4f));
		if (pinoCaido5) {
			model = glm::rotate(model, glm::radians(rotacionPino5), glm::normalize(ejeCaidaPino5));
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -3.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -3.55f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -3.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -3.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f - bolaBoliche, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolaboliche.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 1.5f, -3.4f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolaboliche.RenderModel();

		//************************* NPC Pena ***************************************************************
		// =================== PENA (animación de miedo) ===================
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.5f + penaTemblor, 2.0f, -3.0f)); // posición con temblor
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(penaAnguloBalanceo), glm::vec3(0.0f, 1.0f, 0.0f)); // balanceo
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pena.RenderModel();  // cuerpo

		// Pierna derecha
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.15f, -0.22f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaDer_Pena.RenderModel();

		// Pierna izquierda
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.15f, -0.22f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_Pena.RenderModel();

		// Brazo derecho (sube con miedo)
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.18f, 0.1f, -0.04f));
		model = glm::rotate(model, glm::radians(anguloBrazoP), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_Pena.RenderModel();

		// Brazo izquierdo (sube con miedo)
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.18f, 0.1f, -0.04f));
		model = glm::rotate(model, glm::radians(anguloBrazoP), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_Pena.RenderModel();


		//************************Mesa cobro moneda boliche************************************************ 
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.7f, 1.2f, -1.5f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.005f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.72f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaBoliche - 0.72, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//*****************************************************************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, -7.0f, -215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rojita.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, -7.0f, -215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		verde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, -7.0f, 215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rosa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, -7.0f, 215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		aqua.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -7.0f, 15.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 17.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hormigon.UseMaterial(uniformSpecularIntensity, uniformShininess);
		banqueta.RenderModel();

		//***************************************** DECORACIONES DE CALLE *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, 3.0f, -39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 3.0f, -39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-155.0f, 3.0f, 160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, -160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, 160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, -160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraAzul.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 3.0f, -55.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBasuraAzul.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, -185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, -50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, 50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, 185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, -185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, -50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, 50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, 185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Quiosco_modelo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, 115.0f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acero.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Letrero.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-24.0f, -2.3f, -25.0f));
		model = glm::scale(model, glm::vec3(3.0f, -3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LamparaSuelo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(28.0f, -2.3f, -25.0f));
		model = glm::scale(model, glm::vec3(3.0f, -3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LamparaSuelo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, 100.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Parquimetro.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Parquimetro.RenderModel();

		//***************************************** AREAS VERDES *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 110.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -95.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-81.50f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, 3.0f, -39.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(105.0f, 3.0f, 165.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-105.0f, 3.0f, 165.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(99.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//***************************************** JUEGOS MECANICOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 60.0f));
		model = glm::rotate(model, glm::radians(angulovaria), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Carrousel.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), 3.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo1.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), 0.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo2.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.15f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), -3.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo3.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(3.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), -0.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -50.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acero.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Martillo.RenderModel();

		// Parte Frontal: rota en dirección opuesta a la trasera
		// Martillo frontal - rota hacia un lado
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.6f, 7.1f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloMartillo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acero.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MartilloFrontal.RenderModel();

		// Parte Trasera: rota en dirección contraria
		// Martillo trasero - rota al lado opuesto
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.9f, 7.1f, 0.0f));
		model = glm::rotate(model, glm::radians(-anguloMartillo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acero.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MartilloTrasero.RenderModel();

		//***************************************** JUEGOS DE LA FERIA *****************************************
		//***************************************** DADOS  *****************************************

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(80.0f, 3.0f, 100.0f));  // Posición base de la mesa
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		mesa_dado.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 10.85f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa_Pock.RenderModel();

		// Primer dado
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, 1.3f + alturaDados, 0.0f));
		if (estadoDados == DADOS_GIRANDO_SUBIENDO || estadoDados == DADOS_GIRANDO_BAJANDO)
			model = glm::rotate(model, glm::radians(anguloDados), glm::vec3(1.0f, 1.0f, 0.0f));
		else
			model = glm::rotate(model, glm::radians(rotacionFinalDado1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dados.RenderModel();

		// Segundo dado
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.0f, 1.3f + alturaDados, 0.0f));
		if (estadoDados == DADOS_GIRANDO_SUBIENDO || estadoDados == DADOS_GIRANDO_BAJANDO)
			model = glm::rotate(model, glm::radians(anguloDados), glm::vec3(1.0f, 1.0f, 0.0f));
		else
			model = glm::rotate(model, glm::radians(rotacionFinalDado1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dados.RenderModel();

		//************************cobro moneda dados************************************************ 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-10.0f, 10.9f, 0.0f));
		modelaux2 = model;
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaDados, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//***************************************** GLOBOS *****************************************

		// Globos principales
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-80.0f, 3.0f, 105.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(6.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		GlobosP.RenderModel();

		// Globos individuales con visibilidad
		for (int i = 0; i < 12; ++i) {
			if (!globoVisible[i]) continue;

			model = glm::mat4(1.0f);
			model = glm::translate(model, posicionesGlobos[i]);
			model = glm::scale(model, glm::vec3(2.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Plastico_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			Globos.RenderModel();
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, posicionDardo);
		model = glm::scale(model, glm::vec3(7.0f));
		model = glm::rotate(model, glm::radians(rotacionDardo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dardos.RenderModel();

		//******************************** NPC Hercules *************************************************************
		// === Cuerpo de Hércules ===
		model = modelaux;
		model = glm::translate(model, glm::vec3(-15.0f, 12.8f + desplazamientoHerculesY, -30.0f)); // aplica salto
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Hercules.RenderModel();

		// === Pierna izquierda ===
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.21f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloPiernaIzq_Hercules), glm::vec3(1.0f, 0.0f, 0.0f)); // aplica animación
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_Hercules.RenderModel();

		// === Pierna derecha ===
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.21f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloPiernaDer_Hercules), glm::vec3(1.0f, 0.0f, 0.0f)); // aplica animación
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaDer_Hercules.RenderModel();

		// === Brazo izquierdo ===
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, 0.98f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_Hercules.RenderModel();

		// === Brazo derecho (espada) ===
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.03f, 0.97f, 0.0f));
		anguloBrazoEspada += 0.5 * deltaTime;
		model = glm::rotate(model, glm::radians(-130.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(50 * sin(glm::radians(10 * anguloBrazoEspada))), glm::vec3(1.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_Hercules.RenderModel();


		//************************ Mesa cobro moneda Dardos ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(25.0f, -1.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaDardo, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//***************************************** TOPOS *****************************************
// Rend// Render de la máquina base
// Render máquina base
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 3.0f, -90.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo.RenderModel();

		// Posiciones
		glm::vec3 posicionesTopos[3] = {
			glm::vec3(5.0f, 11.0f, 0.0f),
			glm::vec3(4.5f, 11.0f, 2.5f),
			glm::vec3(4.5f, 11.0f, -2.5f)
		};

		glm::vec3 posicionesMazos[3] = {
			glm::vec3(14.0f, 15.0f, 0.0f),
			glm::vec3(14.0f, 15.0f, 4.5f),
			glm::vec3(14.0f, 15.0f, -2.5f)
		};

		// Render topos
		for (int i = 0; i < 3; ++i) {
			if (topoVisible[i]) {
				model = modelaux;
				model = glm::translate(model, posicionesTopos[i] + glm::vec3(0.0f, desplazamientoTopoY[i], 0.0f));
				model = glm::rotate(model, glm::radians(rotacionTopo[i]), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, glm::radians(anguloRotacionTopo), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Monito_TOPO.RenderModel();
			}
		}

		glm::vec3 mazoPos = posicionesMazos[mazoObjetivo];

		// Agrega desplazamiento si el objetivo es el topo del centro (índice 1)
		if (mazoObjetivo == 1) {
			mazoPos.y += 2.0f;     // subir un poco
			mazoPos.x -= 1.5f;     // mover a la izquierda
		}

		model = modelaux;
		model = glm::translate(model, mazoPos);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-anguloMazo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo.RenderModel();



		//******************************* NPC EMBER *****************************************************
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.0f, 11.8f + emberAlturaY, -18.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ember.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.05f, -0.13f, 0.0f));
		model = glm::rotate(model, glm::radians(emberPiernaAngulo), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_Ember.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.05f, -0.13f, 0.0f));
		model = glm::rotate(model, glm::radians(-emberPiernaAngulo), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaDer_Ember.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.085f, 0.227f, 0.0f));
		model = glm::rotate(model, glm::radians(emberBrazoAngulo), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_Ember.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.09f, 0.225f, 0.0f));
		model = glm::rotate(model, glm::radians(-emberBrazoAngulo), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_Ember.RenderModel();

		//************************ Mesa cobro moneda topos ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 20.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaTopo, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//***************************************** HACHAS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 11.0f, -90.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(8.0f, 5.0f, 8.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HachasP.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(10.0f, -0.5f, 10.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, -0.5f, -8.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-11.0f, 3.3f, 20.0f + desplazamientoHacha));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionHacha), glm::vec3(0.0f, 0.0f, 1.0f)); // cartoon spin
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acero.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Hacha.RenderModel();


		//************************ Mesa cobro moneda hachas ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-20.0f, -9.0f, -5.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaHacha, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//***************************************** JAULA BATEO *****************************************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -110.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 2.0f));
		model = glm::rotate(model, glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, bolaY, bolaZ));
		model = glm::rotate(model, glm::radians(rotacionBolaBase), glm::vec3(0.0f, 1.0f, 0.0f)); // rotación sobre eje Y
		model = glm::scale(model, glm::vec3(5.0f, 6.0f, 5.0f));  // asegúrate de conservar esto si ya lo tenías
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plastico_mate.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, posicionBate);
		model = glm::rotate(model, glm::radians(anguloBate), glm::vec3(0.0f, 1.0f, 0.0f)); // gira en eje X como si lo bajaras
		model = glm::scale(model, glm::vec3(5.0f, 6.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bat.RenderModel();

		//************************ Mesa cobro moneda Baseball ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-35.0f, 0.0f, 25.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.10f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 7.3f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, alturaMonedaBeisbol, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coin.RenderModel();

		//***************************************** PERSONAJES *****************************************
		/******************************************* Panico ***************************************************/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(93.0f, 10.0f, 100.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if (mainWindow.getAnimacion_Simp1_P()) {
			mueveCuerpoPanico += 0.3f * deltaTime;
			model = glm::translate(model, glm::vec3(5.0f * sin(glm::radians(3 * mueveCuerpoPanico)), 0.0f, 0.0f));
		}

		if (animacionSustoActiva) {
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -retrocesoCuerpo));
		}

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Panico_Mar.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.6f, -1.3f, -0.15f));
		if (mainWindow.getAnimacion_Simp1_P()) {
			float anguloPierna = +25.0f * sin(glfwGetTime() * 4.0f);

			model = glm::rotate(model, glm::radians(anguloPierna), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PanicoPDer.RenderModel();

		// Pierna izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, -1.3f, -0.15f));
		if (mainWindow.getAnimacion_Simp1_P()) {
			float anguloPierna = -25.0f * sin(glfwGetTime() * 4.0f);

			model = glm::rotate(model, glm::radians(anguloPierna), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PanicoPIzq.RenderModel();
		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.835f, 2.15f, 0.1f));

		if (mainWindow.getAnimacion_Simp1_P()) {
			anguloBrazoP += 0.3f * deltaTime;
		}

		if (mainWindow.getAnimacion_Simp1_P() || animacionSustoActiva) {
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			if (animacionSustoActiva)
				model = glm::rotate(model, glm::radians(70.0f * sin(anguloBrazoSusto)), glm::vec3(1.0f, 0.0f, 0.0f));
			else
				model = glm::rotate(model, glm::radians(25.0f * sin(glm::radians(10 * anguloBrazoP))), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			anguloBrazoP = 0.0f;
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PanicoBDer.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, 1.85f, -0.15f));

		if (animacionSustoActiva) {
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(70.0f * sin(anguloBrazoSusto)), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PanicoBizq.RenderModel();



		/********************************************Furia****************************************************/
		{
			bool up = keys[GLFW_KEY_W];
			bool down = keys[GLFW_KEY_S];
			bool left = keys[GLFW_KEY_D];
			bool right = keys[GLFW_KEY_A];

			glm::vec3 forward = glm::vec3(sin(furiaYaw), 0.0f, cos(furiaYaw));

			int stepDir = 0;

			if (up) {
				furiaPos += forward * stepDist * deltaTime * 0.5f;
				stepDir = +1;
			}
			if (down) {
				furiaPos -= forward * stepDist * deltaTime * 0.5f;
				stepDir = -1;
			}
			if (right) {
				furiaYaw += velocidadGiroFuria * deltaTime;
				stepDir = +1;
			}
			if (left) {
				furiaYaw -= velocidadGiroFuria * deltaTime;
				stepDir = +1;
			}

			if (stepDir != 0) {
				walkCycle += stepDir * walkCycleStep * deltaTime * 0.5f;
			}

			float legAngle = sin(walkCycle) * legSwing;
			float armAngle = sin(walkCycle) * armSwing;

			model = glm::mat4(1.0f);
			model = glm::translate(model, furiaPos);
			model = glm::rotate(model, furiaYaw, glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			modelaux = model;

			if (currentCameraMode != FIRST_PERSON) {
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
				Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Furia_cuerpo.RenderModel();

				model = modelaux;
				model = glm::translate(model, glm::vec3(0.145f, -0.125f, 0.0f));
				model = glm::rotate(model, glm::radians(-legAngle), glm::vec3(1, 0, 0));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Furia_PiernaIzq.RenderModel();

				model = modelaux;
				model = glm::translate(model, glm::vec3(-0.143f, -0.128f, 0.0f));
				model = glm::rotate(model, glm::radians(legAngle), glm::vec3(1, 0, 0));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Furia_PiernaDer.RenderModel();

				model = modelaux;
				model = glm::translate(model, glm::vec3(0.275f, 0.085f, 0.0f));
				model = glm::rotate(model, glm::radians(-armAngle), glm::vec3(1, 0, 0));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Furia_BrazoIzq.RenderModel();
			}

			if (currentCameraMode != FIRST_PERSON) {
				model = modelaux;
				model = glm::translate(model, glm::vec3(-0.26f, 0.088f, 0.0f));
				model = glm::rotate(model, glm::radians(armAngle), glm::vec3(1, 0, 0));

				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Furia_BrazoDer.RenderModel();
			}
		}
		/********************************************Danny Phantom****************************************************/
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(81.0f + desplazamientoDP_X, 16.0f + desplazamientoDP_Y, -67.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Vuelo animado clásico
		if (mainWindow.getAnimacion_Simp1_DP()) {
			vueloDP += 0.3f * deltaTime;
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(
				2.0f * sin(glm::radians(3 * vueloDP + 90.0f)),
				5.0f + 3.0f * sin(glm::radians(3 * vueloDP)),
				0.0f
			));
		}
		else if (!animacionDisparoDP) {
			vueloDP = 0.0f;
		}

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		DannyP_cuerpo.RenderModel();

		// Pierna izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.19f, -1.57f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		DannyP_PiernaIzq.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.19f, -1.56f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		DannyP_PiernaDer.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.78f, 0.57f, -0.255f));
		if (mainWindow.getAnimacion_Simp1_DP()) {
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		DannyP_BrazoIzq.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.84f, 0.52f, -0.23f));
		if (mainWindow.getAnimacion_Simp1_DP()) {
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		DannyP_BrazoDer.RenderModel();


		//***************************************** PUESTOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-93.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(19.0f, 19.0f, 19.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoComida.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.0f, 3.0f, 35.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoElotes.RenderModel();

		//******************************** NPC Alegría con animación *************************************************************

		float bounce = sin(currentTime * 4.0f) * 0.5f;  // Salto suave (amplitud 0.5 en Y)
		float armSwing = sin(currentTime * 6.0f) * glm::radians(30.0f); // Oscilación de brazos +/-30 grados

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 11.0f + bounce, 10.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Alegria.RenderModel();

		// Pierna izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.5f, -6.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_A.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.2f, -6.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_A.RenderModel();

		// Brazo izquierdo (swing hacia adelante)
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.0f, 6.8f, 0.0f));
		model = glm::rotate(model, armSwing, glm::vec3(1.0f, 0.0f, 0.0f)); // Oscila hacia adelante y atrás
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_A.RenderModel();

		// Brazo derecho (swing opuesto)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.8f, 6.8f, 0.0f));
		model = glm::rotate(model, -armSwing, glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento opuesto para balance
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_A.RenderModel();

		//*************************************************************************************************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-185.0f, 22.0f, 70.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoTacos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 10.0f, 35.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoAlgodon.RenderModel();

		//******************************** NPC Sam*************************************************************
		model = modelaux;
		model = glm::translate(model, glm::vec3(-15.0f, 1.3f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Sam.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.4f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians(samPiernaAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_Sam.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.4f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians(-samPiernaAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaDer_Sam.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.2f, 2.72f, 0.0f));
		model = glm::rotate(model, glm::radians(samBrazoAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_Sam.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.2f, 2.72f, 0.0f));
		model = glm::rotate(model, glm::radians(-samBrazoAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piel.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_Sam.RenderModel();

		//*********************************************************************************************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 11.0f, -35.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aluminio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoDulces.RenderModel();

		//******************************** NPC Tristeza *************************************************************
		model = modelaux;
		model = glm::translate(model, glm::vec3(-10.0f, -5.5f, 10.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(tristezaBalanceo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tristeza.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.92f, -4.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzq_T.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.1f, -4.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaDer_T.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.0f, 4.9f, 0.0f));
		model = glm::rotate(model, glm::radians(tristezaBrazoAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDer_T.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(5.7f, 4.9f, 0.0f));
		model = glm::rotate(model, glm::radians(tristezaBrazoAngulo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzq_T.RenderModel();

		//*************************************************************************************************


		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();



	}

	//************************************************** SE LIBERA  LA MEMORIA DE LOS SONIDOS *******************************************

	if (musicaFondo) Mix_FreeMusic(musicaFondo);
	if (musicaBoliche) Mix_FreeMusic(musicaBoliche);
	if (musicaHacha) Mix_FreeMusic(musicaHacha);
	if (musicaGlobos) Mix_FreeMusic(musicaGlobos);
	if (musicaBateo) Mix_FreeMusic(musicaBateo);
	if (musicaDados) Mix_FreeMusic(musicaDados);
	if (sonidoAmbiente) Mix_FreeChunk(sonidoAmbiente);
	if (sonnidoCarrusel) Mix_FreeChunk(sonnidoCarrusel);
	if (sonidoMartillo) Mix_FreeChunk(sonidoMartillo);
	if (sonidoMoneda) Mix_FreeChunk(sonidoMoneda);
	if (sonidoDados)Mix_FreeChunk(sonidoDados);
	if (sonidoPanico)Mix_FreeChunk(sonidoPanico);
	if (sonidoHercules)Mix_FreeChunk(sonidoHercules);
	if (sonidoHacha)Mix_FreeChunk(sonidoHacha);
	if (sonidoDanny)Mix_FreeChunk(sonidoDanny);
	if (sonidoTopos)Mix_FreeChunk(sonidoTopos);
	if (sonidoBateo)Mix_FreeChunk(sonidoBateo);



	//************************************************* SALE DE LAS LIBRERIAS DE SONIDO ***************************************************

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}