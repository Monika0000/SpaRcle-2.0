#define GLEW_STATIC
#define NOMINMAX

#include "pch.h"
#include "Shader.h"

#include <iostream>
#include <map>

#include <SRHelper.h>
#include "SRGraphics.h"

SpaRcle::Graphics::Shader::Shader(std::string name, Debug* debug) {
    this->name = name;
    this->isLinked = false;
    this->debug = debug;
}

SpaRcle::Graphics::Shader::~Shader() {

}

bool SpaRcle::Graphics::Shader::Compile() {
    std::string path = SRGraphics::Get()->GetResourcesFolder() + "\\Shaders\\";
    std::string vertex_path   = path + name + "_vertex.glsl";
    std::string fragment_path = path + name + "_fragment.glsl";;

    // создаем шейдеры
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // читаем вершинный шейдер из файла
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // читаем фрагментный шейдер из файла
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;
    std::string error;

    // Компилируем вершинный шейдер
    debug->Shader("Compiling vertex shader : " + vertex_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Устанавливаем параметры
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    //?===========================================[ ERRORS ]==============================================
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    ///error = String::FromCharVector(VertexShaderErrorMessage);
    ///if (error.size() == 0) error = "Shader is nullptr!";
    ///debug->Error("Failed compile vertex shader! Reason : " + error);
    //?===================================================================================================

    // Компилируем фрагментный шейдер
    debug->Shader("Compiling fragment shader : " + fragment_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Устанавливаем параметры
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    //?===========================================[ ERRORS ]==============================================
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
   /// error = String::FromCharVector(FragmentShaderErrorMessage);
    ///if (error.size() == 0) error = "Shader is nullptr!";
    ///debug->Error("Failed compile fragment shader! Reason : " + error);
    //?===================================================================================================

    debug->Shader("Linking program...");
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Устанавливаем параметры
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    //?===========================================[ ERRORS ]==============================================
    std::vector<char> ProgramErrorMessage(InfoLogLength);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    error = String::FromCharVector(ProgramErrorMessage);
    if (error.size() != 0) {
        size_t index = error.find("error");
        if (index == Math::size_t_max) {
            debug->Warn("Warning linking program! Reason : " + error);
            isLinked = true;
        }
        else debug->Error("Failed linking program! Reason : " + error);
    }
    else isLinked = true;
    //?===================================================================================================

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

	return isLinked;
}

bool SpaRcle::Graphics::Shader::Use() { //GLuint tex1, GLuint vbo, GLuint uv
    if (isLinked) {
        //glUniform3f(glGetUniformLocation(this->ProgramID, "color"), 0.0, 0.0, 1.0);
        //int index = glGetAttribLocation(this->ProgramID, "atr");
        //glMatrixMode(GL_TEXTURE);

        glUseProgram(this->ProgramID);

        /*
        glBindTexture(GL_TEXTURE_2D, tex1);

        //?======================================[VERTEXES]========================================
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        //?========================================================================================

        //TODO:===================================[TEX COORDS]=====================================
       // glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER, uv);
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);    
        //TODO:====================================================================================
        //!=====================================[SHADER TEXTURE]===================================
        if (true) {
            GLuint texCoordID = glGetAttribLocation(this->ProgramID, "InTexCoords");
            glEnableVertexAttribArray(texCoordID);
           glBindBuffer(GL_ARRAY_BUFFER, uv);
            glVertexAttribPointer(texCoordID, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            //glVertexAttribPointer(texCoordID, 3, GL_FLOAT, GL_TRUE, 0, NULL);
            /// glVertexAttribPointer(texCoordID, !!!2!!!, GL_FLOAT, GL_FALSE, 0, NULL);

            GLuint texID = glGetUniformLocation(this->ProgramID, "img");
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(texID, 0); // This is GL_TEXTURE0
            */

        //!========================================================================================

        return true;
    }
    else return false;
}

bool SpaRcle::Graphics::Shader::Release() {
    glDeleteProgram(this->ProgramID);
	return true;
}
