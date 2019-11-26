#include "GlyphLoader.h"

GlyphLoader::GlyphLoader(char *fileloc)
{
    GlyphID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    FileLocation = fileloc;
}

GlyphLoader::GlyphLoader()
{
    GlyphID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
}

void GlyphLoader::LoadGlyphs(std::string Number, std::vector<float> corners)
{
    text = Number;
    Bbox = corners;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        glGenTextures(1, &GlyphID);
        glBindTexture(GL_TEXTURE_2D, GlyphID);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            GlyphID,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void GlyphLoader::UseGlyph(GLuint color_loc)
{
    glUniform4f(color_loc, .0f, .0f, 0.f, 1.f); // Color

    //  glActiveTexture(GL_TEXTURE0);
    std::string::const_iterator c;
    auto scale = .15f;

    GLfloat offsetx = -(Bbox[0]-Bbox[2])/4;
    GLfloat offsety = -(Bbox[1]-Bbox[3])/4;

    GLfloat x = (Bbox[0]+Bbox[2])/2;
    GLfloat y = (Bbox[1]+Bbox[3])/2;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        unsigned int indices[] = {0, 1, 2,
                                  2, 3, 0};
        GLfloat vertices[] = {
            xpos, ypos + h,       0.0, 0.0,
            xpos + w, ypos + h,   1.0, 0.0,
            xpos + w, ypos,       1.0, 1.0,
            xpos, ypos,           0.0, 1.0};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * 6, indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 16, vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 4, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 4, (void *)(sizeof(vertices[0]) * 2));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        // Unbind Buffers

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        // Render quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
        glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(0);
}
void GlyphLoader::ReleaseGlyph()
{
}
void GlyphLoader::ClearGlyph()
{
    glDeleteTextures(1, &GlyphID);

    GlyphID = 0;
    width = height = bitDepth = 0;
    FileLocation = "";
}

GlyphLoader::~GlyphLoader() { ClearGlyph(); }