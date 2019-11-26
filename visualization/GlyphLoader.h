#pragma once
#include <GL/glew.h>
#include <map>
#include<iostream>
#include <vector>
#include<glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class GlyphLoader
{
public:
    GlyphLoader();
    GlyphLoader(char *fileloc);
    ~GlyphLoader();

    void LoadGlyphs(std::string,std::vector<float>);
    void ClearGlyph();
    void UseGlyph(GLuint);
    void ReleaseGlyph();

private:
    GLuint GlyphID;
    std::vector<float>  Bbox;
    int width, height, bitDepth;
    GLuint VAO, VBO, IBO;

    char *FileLocation;
    std::string text;

    FT_Library ft;
    FT_Face face;
    std::map<GLchar, Character> Characters;

};