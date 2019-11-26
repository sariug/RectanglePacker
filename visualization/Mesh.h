#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GlyphLoader.h"
class Mesh
{
public:
    Mesh();
    ~Mesh();
    void renderGlyph(GLuint color_loc);
    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void renderMesh(GLuint color_loc);
    void clearMesh();

private:
    // Attributes
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    glm::vec3 color;
    static int ID;
    GlyphLoader *_glyph;
};