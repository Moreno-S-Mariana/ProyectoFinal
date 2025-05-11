

// — Skybox.cpp —
#include "Skybox.h"


Skybox::Skybox(const std::vector<std::string>& dayFaces,
    const std::vector<std::string>& nightFaces) {
    // Inicialización del shader
    skyShader = new Shader();
    skyShader->CreateFromFiles("shaders/skybox.vert", "shaders/skybox.frag");
    skyShader->UseShader();

    // Asignamos samplers (solo una vez)
    GLuint prog = skyShader->GetShaderID();
    glUniform1i(glGetUniformLocation(prog, "skybox1"), 0);
    glUniform1i(glGetUniformLocation(prog, "skybox2"), 1);

    // Obtenemos ubicaciones de matrices
    uniformProjection = skyShader->GetProjectionLocation();
    uniformView = skyShader->GetViewLocation();

    // Generamos las texturas de cubemap
    glGenTextures(1, &textureIdDay);
    glGenTextures(1, &textureIdNight);

    // Cargamos día y noche
    loadCubemap(dayFaces, textureIdDay);
    loadCubemap(nightFaces, textureIdNight);

    // Setup de VAO/VBO para el cube
    unsigned int skyboxIndices[] = {
        0, 1, 2, 2, 1, 3, // front
        2, 3, 5, 5, 3, 7, // right
        5, 7, 4, 4, 7, 6, // back
        4, 6, 0, 0, 6, 1, // left
        4, 0, 5, 5, 0, 2, // top
        1, 6, 3, 3, 6, 7  // bottom
    };

    float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f, 0,0, 0,0,0,  // 0
        -1.0f, -1.0f, -1.0f, 0,0, 0,0,0,  // 1
         1.0f,  1.0f, -1.0f, 0,0, 0,0,0,  // 2
         1.0f, -1.0f, -1.0f, 0,0, 0,0,0,  // 3
        -1.0f,  1.0f,  1.0f, 0,0, 0,0,0,  // 4
         1.0f,  1.0f,  1.0f, 0,0, 0,0,0,  // 5
        -1.0f, -1.0f,  1.0f, 0,0, 0,0,0,  // 6
         1.0f, -1.0f,  1.0f, 0,0, 0,0,0   // 7
    };

    skyMesh = new Mesh();
    skyMesh->CreateMesh(skyboxVertices, skyboxIndices,
        sizeof(skyboxVertices),
        sizeof(skyboxIndices));
}

Skybox::~Skybox() {
    glDeleteTextures(1, &textureIdDay);
    glDeleteTextures(1, &textureIdNight);
    delete skyShader;
    delete skyMesh;
}

void Skybox::loadCubemap(const std::vector<std::string>& faces, GLuint textureId) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    int width, height, bitDepth;

    for (size_t i = 0; i < faces.size(); ++i) {
        unsigned char* texData = stbi_load(faces[i].c_str(), &width, &height, &bitDepth, 0);
        if (!texData) {
            std::cerr << "No se encontró: " << faces[i] << std::endl;
            continue;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        stbi_image_free(texData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Skybox::updateFaces(const std::vector<std::string>& dayFaces,
    const std::vector<std::string>& nightFaces) {
    loadCubemap(dayFaces, textureIdDay);
    loadCubemap(nightFaces, textureIdNight);
}

void Skybox::DrawSkybox(const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix,
    float blendFactor) {
    glm::mat4 viewNoTrans = glm::mat4(glm::mat3(viewMatrix));

    glDepthMask(GL_FALSE);
    skyShader->UseShader();

    // MVP matrices
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewNoTrans));

    // Reasignar texturas cada frame
    glUniform1i(glGetUniformLocation(skyShader->GetShaderID(), "skybox1"), 0);
    glUniform1i(glGetUniformLocation(skyShader->GetShaderID(), "skybox2"), 1);
    glUniform1f(glGetUniformLocation(skyShader->GetShaderID(), "blendFactor"), blendFactor);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureIdDay);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureIdNight);

    skyMesh->RenderMesh();
    glDepthMask(GL_TRUE);
}


