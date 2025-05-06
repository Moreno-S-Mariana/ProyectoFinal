/*PROYECTO COMPUTACIÓN GRÁFICA*/
//*****************************************FERIA PULQUE**********************************************
/*GARCÍA SOTO JEAN CARLO
  MINO GUZMÁN YARA AMAIRANI
  MORENO SANTOYO MARIANA

  Materia: CGEIHC
  Grupo:
  Fecha:
  hola
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
//***************************************** Variable animación de Panico*****************************************
GLfloat anguloBrazoP = 0.0f;
GLfloat mueveCuerpoPanico = 0.0f;


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

//***************************************** COMIDA *****************************************

Model PuestoElotes;
Model PuestoComida;
Model PuestoTacos;
Model PuestoAlgodon;
Model PuestoDulces;
Model Taco;

//materiales
Material Material_brillante;
Material Material_opaco;


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
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

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

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

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

	//Skybox actual inicial: día

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.03f, 0.03f,
		0.0f, 0.0f, -1.0f);

	//*************************************************************************************************************************************************
	unsigned int pointLightCount_ARRAY1 = 0;
	// Luz 1
	pointLights1[0] = PointLight(
		1.0f, 1.0f, 1.0f,   // color blanco
		4.0f, 30.0f,        // ambientIntensity = 1.5f, diffuseIntensity = 6.0f
		160.0f, 60.0f, -185.0f,
		0.0f, 0.05f, 0.3f   // atenuación más lenta para que llegue más lejos
	);
	pointLightCount_ARRAY1++;

	// Luz 2
	pointLights1[1] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,                 // ambientIntensity = 1.5f, diffuseIntensity = 8.0f
		160.0f, 60.0f, 185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	// Luz 3
	pointLights1[2] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,                 // ambientIntensity = 1.5f, diffuseIntensity = 6.0f
		-160.0f, 60.0f, -185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	// Luz 4
	pointLights1[3] = PointLight(
		1.0f, 1.0f, 1.0f,
		4.0f, 30.0f,                 // ambientIntensity = 1.5f, diffuseIntensity = 8.0f
		-160.0f, 60.0f, 185.0f,
		0.0f, 0.05f, 0.3f
	);
	pointLightCount_ARRAY1++;

	unsigned int pointLightCount_ARRAY2 = 0;
	pointLights2[0] = PointLight(1.0f, 0.0f, 0.0f,   // color blanco
		4.0f, 30.0f,				// ambientIntensity = 1.5f, diffuseIntensity = 6.0f
		0.0f, 20.0f, 0.0f,
		0.0f, 0.05f, 0.3f			// atenuación más lenta para que llegue más lejos
	);
	pointLightCount_ARRAY2++;
	//*************************************************************************************************************************************************

	unsigned int spotLightCount = 0;
	// Lámpara izquierda
	spotLights[0] = SpotLight(1.0f, 0.843f, 0.6f,
		10.0f, 80.0f,			// aIntensity y dIntensity
		-28.0f, 9.0f, 93.0f,   // Posición
		1.0f, 0.0f, 1.0f,      // Dirección
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
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		0.0f, 40.0f, 60.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		75.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount++;

	//Dardo y globos
	spotLights[3] = SpotLight(0.529f, 0.808f, 0.922f, //azul
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		-80.0f, 40.0f, 108.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		90.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount++;

	unsigned int spotLightCount2 = 0;
	//Martillo
	spotLights2[0] = SpotLight(1.0f, 0.843f, 0.6f,  //amarillo cálido
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		0.0f, 60.0f, -50.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		80.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount2++;
	
	//Hachas
	spotLights2[1] = SpotLight(0.133f, 0.545f, 0.133f,  //verde
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		70.0f, 45.0f, -90.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		80.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount2++;

	//Topo
	spotLights2[2] = SpotLight(0.502f, 0.0f, 0.502f,  //morado
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		-55.0f, 50.0f, -90.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		80.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount2++;

	//Puesto
	spotLights2[3] = SpotLight(1.0f, 0.843f, 0.6f,  
		10.0f, 80.0f,             // Intensidades: ambiente y difusa
		-55.0f, 50.0f, -65.0f,
		0.0f, -1.0f, 0.0f,       // Dirección (apunta hacia abajo)
		1.0f, 0.09f, 0.032f,     // Atenuación
		60.0f                    // Ángulo de corte (grado de apertura)
	);
	spotLightCount2++;

	
	float intensidad = 0.0f;
	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 0.3f * deltaTime;

		// Movimiento alternante del martillo
		// Movimiento alternante del martillo (gira de -90° a +90° suavemente)
		if (direccionDerecha) {
			anguloMartillo += velocidadOscilacion * deltaTime;
			if (anguloMartillo >= 135.0f) {
				anguloMartillo = 135.0f;
				direccionDerecha = false;
			}
		}
		else {
			anguloMartillo -= velocidadOscilacion * deltaTime;
			if (anguloMartillo <= -45.0f) {
				anguloMartillo = -45.0;
				direccionDerecha = true;
			}
		}

		const float dayDuration = 20.0f;
		const float nightDuration = 20.0f;
		const float fadeDuration = 13.0f;
		const float cycleTime = dayDuration + nightDuration + 2 * fadeDuration;

		float t = fmod(glfwGetTime(), cycleTime);
		float blendFactor = 0.0f;

		//0.3->Dia		0.1->Noche
		/**/
		intensidad = 0.1f + 0.2f * (0.5f + 0.5f * sin(lastTime * velocidadDN));
		mainLight.UpdateLightIntensity(intensidad, intensidad);
		//mainLight.UpdateLightIntensity(0.3, 0.3);	//Cambiar al final 

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
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
		float sunAngleDeg = (t / cycleTime) * 360.0f - 90.0f;
		float sunRad = glm::radians(sunAngleDeg);

		// 3) Vector dirección del sol: barrido en el plano X–Y (Z fijo o pequeño para inclinar)
		glm::vec3 sunDir = glm::normalize(glm::vec3(
			cosf(sunRad),      // componente X: este?oeste
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

		// luz ligada a a cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		//glm::vec3 lowerLight = camera.getCameraPosition();
		//lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, 0.1f) * (a1 + a2);

		shaderList[0].SetDirectionalLight(&mainLight);							//Habilita luz principal
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);				//Habilita las luces del spotlight
		shaderList[0].SetSpotLights(spotLights2, spotLightCount2);
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
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//****************************************** EDIFICIOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -245.0f));
		model = glm::scale(model, glm::vec3(14.0f, 14.0f, 14.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Iglesia.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-230.0f, -6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Portales.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(230.0f, -6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Portales.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -6.0f, 235.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		chaparrin.RenderModel();

		//************************Boliche**********************************************************
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Boliche.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.0f, 1.5f, -3.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -3.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.2f, 1.5f, -3.55f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -3.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 1.5f, -3.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolaboliche.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 1.5f, -3.4f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolaboliche.RenderModel();

		//************************Mesa cobro moneda boliche************************************************ 
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.7f, 1.2f, -1.5f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.005f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.72f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//*****************************************************************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, -7.0f, -215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rojita.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, -7.0f, -215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		verde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, -7.0f, 215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rosa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, -7.0f, 215.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aqua.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -7.0f, 15.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 17.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banqueta.RenderModel();

		//***************************************** DECORACIONES DE CALLE *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, 3.0f, -39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 3.0f, -39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 3.0f, 39.0f));
		model = glm::scale(model, glm::vec3(24.0f, 24.0f, 24.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-155.0f, 3.0f, 160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, -160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, 160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, -160.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraVerde.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraAzul.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 3.0f, -55.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BoteBasuraAzul.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, -185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, -50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, 50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.0f, 185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, -185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, -50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, 50.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.0f, 185.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamparas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Quiosco_modelo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, 115.0f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-24.0f, -2.3f, -25.0f));
		model = glm::scale(model, glm::vec3(3.0f, -3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LamparaSuelo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(28.0f, -2.3f, -25.0f));
		model = glm::scale(model, glm::vec3(3.0f, -3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LamparaSuelo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-158.0f, 3.0f, 100.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Parquimetro.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(158.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
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
		Carrousel.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), 3.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Caballo1.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), 0.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Caballo2.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.15f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), -3.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Caballo3.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(3.2f, 1.0f + 0.5 * sin(glm::radians(angulovaria * 3)), -0.2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Caballo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -50.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Martillo.RenderModel();

		// Parte Frontal: rota en dirección opuesta a la trasera
		// Martillo frontal - rota hacia un lado
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.6f, 7.1f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloMartillo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MartilloFrontal.RenderModel();

		// Parte Trasera: rota en dirección contraria
		// Martillo trasero - rota al lado opuesto
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.9f, 7.1f, 0.0f));
		model = glm::rotate(model, glm::radians(-anguloMartillo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MartilloTrasero.RenderModel();

		//***************************************** JUEGOS DE LA FERIA *****************************************
		//***************************************** DADOS  *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 3.0f, 100.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa_dado.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 10.85f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Pock.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, 1.3f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dados.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.0f, 1.3f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dados.RenderModel();

		//************************cobro moneda dados************************************************ 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-10.0f, 10.9f, 0.0f));
		modelaux2 = model;
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//***************************************** GLOBOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 3.0f, 105.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GlobosP.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 23.0f, -6.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 17.0f, -6.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, -6.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, -6.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, 23.0f, -14.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, 17.0f, -14.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, 11.0f, -14.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, 5.0f, -14.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(8.0f, 23.0f, 2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(8.0f, 17.0f, 2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(8.0f, 11.0f, 2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(8.0f, 5.0f, 2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Globos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 4.0f, 83.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dardos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 4.0f, 83.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(-135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dardos.RenderModel();

		//************************ Mesa cobro moneda Dardos ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(25.0f, -1.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//***************************************** TOPOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 3.0f, -90.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, 11.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Monito_TOPO.RenderModel();		//Primer topo

		model = modelaux;
		model = glm::translate(model, glm::vec3(4.5f, 11.0f, 2.5f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Monito_TOPO.RenderModel();		//Segundo topo

		model = modelaux;
		model = glm::translate(model, glm::vec3(4.5f, 11.0f, -2.5f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Monito_TOPO.RenderModel();		//Tercer topo

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, -10.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo.RenderModel();

		//************************ Mesa cobro moneda topos ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 20.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//***************************************** HACHAS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 11.0f, -90.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(8.0f, 5.0f, 8.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HachasP.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(10.0f, -0.5f, 10.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, -0.5f, -8.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Centro.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(7.9f, 3.3f, 12.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hacha.RenderModel();

		//************************ Mesa cobro moneda hachas ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-20.0f, -9.0f, -5.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.15f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 11.f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//***************************************** JAULA BATEO *****************************************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -110.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 2.0f));
		model = glm::rotate(model, glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jaula.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 6.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -90.0f));
		model = glm::scale(model, glm::vec3(5.0f, 6.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bat.RenderModel();

		//************************ Mesa cobro moneda Baseball ********************************************** 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-35.0f, 0.0f, 25.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.10f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 7.3f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuenco.RenderModel();

		//Moneda - Utilizar en los casos necesarios 
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coin.RenderModel();

		//***************************************** PERSONAJES *****************************************
		/********************************************Panico****************************************************/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(93.0f, 10.0f, 100.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		if (mainWindow.getAnimacion_Simp1_P()) {	//Activa animación
			mueveCuerpoPanico += 0.3f * deltaTime;
			model = glm::translate(model, glm::vec3(0.0f + 2 * sin(glm::radians(3 * mueveCuerpoPanico)),
				0.0f,
				0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			mueveCuerpoPanico = 0.0f;		//Reinicia el recorrido de la animación
		}

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Panico_Mar.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.6f, -1.3f, -0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PanicoPDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, -1.3f, -0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PanicoPIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.835f, 2.15f, 0.1f));
		if (mainWindow.getAnimacion_Simp1_P()) {	//Activa animación
			anguloBrazoP += 0.3f * deltaTime;
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(25 * sin(glm::radians(10 * anguloBrazoP))), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			anguloBrazoP = 0.0f;		//Reinicia el recorrido de la animación
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PanicoBDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, 1.85f, -0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PanicoBizq.RenderModel();
		/********************************************Furia****************************************************/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-185.0f, 11.0f, 45.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if (mainWindow.getAnimacion_Simp1_F()) {	//Activa animación
			saltoFuria += 0.1f * deltaTime;
			desplazamientoY_F = fabs(sin(saltoFuria)) * 0.7f;		//Valor abs para no desplazarse hacia abajo
			model = glm::translate(model, glm::vec3(0.0f,
				0.0f + desplazamientoY_F,
				0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			saltoFuria = 0.0f;		//Reinicia el recorrido de la animación
		}

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Furia_cuerpo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.145f, -0.125f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Furia_PiernaIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.143f, -0.128f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Furia_PiernaDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.275f, 0.085f, 0.0f));
		if (mainWindow.getAnimacion_Simp1_F()) {	//Activa animación
			anguloBrazoF += 0.7f * deltaTime;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.05f));
			model = glm::rotate(model, glm::radians(-130.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(50 * sin(glm::radians(10 * anguloBrazoF))), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			anguloBrazoF = 0.0f;
		}
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Furia_BrazoIzq.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.06f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Taco.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.26f, 0.088f, 0.0f));
		if (mainWindow.getAnimacion_Simp1_F()) {	//Activa animación
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.05f));
			model = glm::rotate(model, glm::radians(-130.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(50 * sin(glm::radians(10 * anguloBrazoF))), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Furia_BrazoDer.RenderModel();
		/********************************************Danny Phantom****************************************************/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(81.0f, 16.0f, -67.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if (mainWindow.getAnimacion_Simp1_DP()) {	//Activa animación
			vueloDP += 0.3f * deltaTime;
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f + 2 * sin(glm::radians(3 * vueloDP + 90.0f)),
				5.0f + 3 * sin(glm::radians(3 * vueloDP)),
				0.0f));
		}
		else if (mainWindow.getAnimacion_Simp1_DP() == false) {
			vueloDP = 0.0f;		//Reinicia el recorrido de la animación
		}
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DannyP_cuerpo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.19f, -1.57f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DannyP_PiernaIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.19f, -1.56f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DannyP_PiernaDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.78f, 0.57f, -0.255f));
		if (mainWindow.getAnimacion_Simp1_DP()) {	//Rota arriba brazo izquierdo
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DannyP_BrazoIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.84f, 0.52f, -0.23f));
		if (mainWindow.getAnimacion_Simp1_DP()) {	//Rota arriba brazo derecho
			model = glm::rotate(model, glm::radians(-140.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DannyP_BrazoDer.RenderModel();


		//***************************************** PUESTOS *****************************************

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-93.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(19.0f, 19.0f, 19.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoComida.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.0f, 3.0f, 35.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoElotes.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-185.0f, 22.0f, 70.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoTacos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 10.0f, 35.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoAlgodon.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 11.0f, -35.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoDulces.RenderModel();

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}