#include "Mesh.h"
int Mesh::ID = 0;
Mesh::Mesh()
{

    VAO=VBO=IBO=indexCount=0;
    color = glm::vec3(  ( std::rand()) / static_cast <float> (RAND_MAX),
                            std::rand()/ static_cast <float> (RAND_MAX),
                            std::rand() / static_cast <float> (RAND_MAX));
    
    _glyph = new GlyphLoader;
    ID++;
    }

    
void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*numOfIndices, indices, GL_STATIC_DRAW);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numOfVertices, vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*4, 0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*4, (void*)(sizeof(vertices[0])*2));
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
    // Unbind Buffers

	        glBindBuffer(GL_ARRAY_BUFFER, 0);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
            _glyph->LoadGlyphs (std::to_string(ID),{vertices[12],vertices[13],vertices[4],vertices[5]});
}
void Mesh::renderMesh(GLuint color_loc)
{
    glUniform4f(color_loc, color.x, color.y, color.z,1.0f); // Color
    glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUniform4f(color_loc, 1.0f, 0.0f, 0.0f,1.0f); // Color
    glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0); 

}
void Mesh::renderGlyph(GLuint color_loc){    this->_glyph->UseGlyph(color_loc);}
void Mesh::clearMesh()
{
    if(IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if(VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;        
    }
    if(VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    indexCount = 0;
}

Mesh::~Mesh(){}