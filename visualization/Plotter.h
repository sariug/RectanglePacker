#ifndef __PLOTTER__H
#define __PLOTTER__H
#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Window.h"
#include <glm/gtc/type_ptr.hpp>

// Vertex Shader
static const char *vShader = R"(shaders/shader.vert)";
static const char *vShader_rect = R"(shaders/shader_rect.vert)";

// Pixel Shader
static const char *fShader = R"(shaders/shader.frag)";
static const char *fShader_rect = R"(shaders/shader_rect.frag)";

class Plotter
{
public:
    Plotter(float edge_length);
    ~Plotter();
    void show();
    void add_rectangle(std::vector<int> corners);

private:
    void init();
    void update_camera_position(std::vector<int> &corners);
    std::vector<Mesh *> meshList;
    Window *mainwindow;
    Shader *_shader;
    Shader *_shader_rect;

    Camera *camera;
    GLuint shader, uniformModel, uniformProjection, uniformView;
    glm::mat4 projection;
    glm::vec4 bbox;
    float edgeLength;
};

#endif