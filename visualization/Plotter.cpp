#include "Plotter.h"

Plotter::Plotter(float edge_length) : edgeLength(edge_length)
{
    this->init();
    std::cout << "Plotter initialized\n";
}
Plotter::~Plotter()
{
}
void Plotter::show()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!mainwindow->shouldWindowClose())
    {
        glfwPollEvents();
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model;
        for (auto &m : meshList)
        {
            _shader_rect->UseShader();
            glUniformMatrix4fv(_shader_rect->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(_shader_rect->GetModelProjection(), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(_shader_rect->GetModelView(), 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));

            m->renderMesh(_shader->GetColorLocation());
            _shader->UseShader();
            glUniformMatrix4fv(_shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(_shader->GetModelProjection(), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(_shader->GetModelView(), 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
            m->renderGlyph(_shader->GetColorLocation());
        }
        glUseProgram(0);

        mainwindow->swapBuffers();
    }
}
void Plotter::add_rectangle(std::vector<int> corners)
{
    unsigned int indices[] = {0, 1, 2,
                              2, 3, 0};
    GLfloat vertices[] = {corners[0], corners[3], 0.0f, 0.0f,
                          corners[2], corners[3], 1.0f, 0.0f,
                          corners[2], corners[1], 1.0f, 1.0f,
                          corners[0], corners[1], 0.0f, 1.0f};

    Mesh *dummy = new Mesh();
    dummy->createMesh(vertices, indices, 16, 6);
    meshList.push_back(dummy);
    update_camera_position(corners);
}

void Plotter::init()
{
    mainwindow = new Window;
    _shader = new Shader;
    _shader_rect = new Shader;
    mainwindow->initialize();
    _shader->CreateFromFile(vShader, fShader);
    _shader_rect->CreateFromFile(vShader_rect, fShader_rect);
    camera = new Camera(glm::vec3(.0f, 1.0f, .0f));
    projection = glm::perspective(45.0f, mainwindow->getBufferWidth() / mainwindow->getBufferHeight(), 0.01f, 1000.0f);
    bbox = glm::vec4(0, 0, 0, 0); // x0,y0,x1,y1
}
void Plotter::update_camera_position(std::vector<int> &corners)
{
    if (corners[0] < bbox[0])
        bbox[0] = corners[0];
    if (corners[1] < bbox[1])
        bbox[1] = corners[1];
    if (corners[2] > bbox[2])
        bbox[2] = corners[2];
    if (corners[3] > bbox[3])
        bbox[3] = corners[3];
    camera->set_position(glm::vec3((bbox[0] + bbox[2]) / 2, (bbox[1] + bbox[3]) / 2, edgeLength));
}
