#pragma once

#include "CommonValues.h"
#include <vector>
#include <string>
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Shader_light.h"
// — Skybox.h —



/// Clase Skybox con transición día?noche
class Skybox {
public:
    // Constructor que recibe las rutas de las 6 caras para día y noche
    Skybox(const std::vector<std::string>& dayFaces,
        const std::vector<std::string>& nightFaces);
    ~Skybox();

    // Si quieres recargar las texturas en runtime
    void updateFaces(const std::vector<std::string>& dayFaces,
        const std::vector<std::string>& nightFaces);

    // Dibuja el skybox mezclando día/noche según blendFactor [0.0?1.0]
    void DrawSkybox(const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix,
        float blendFactor);

private:
    GLuint textureIdDay;    // cubemap día
    GLuint textureIdNight;  // cubemap noche
    GLuint uniformProjection;
    GLuint uniformView;
    GLuint uniformBlend;     // ubicación de blendFactor

    Shader* skyShader;
    Mesh* skyMesh;

    // Helper que carga 6 imágenes en el cubemap texID
    void loadCubemap(const std::vector<std::string>& faces, GLuint texID);
};