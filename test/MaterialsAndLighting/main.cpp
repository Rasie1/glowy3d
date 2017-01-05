#include "Engine.h"
#include <iostream> 
#include <memory>
#include "base/System.h"
#include "base/Config.h"
#include "platforms/Window.h"
#include "platforms/ShaderProgram.h"
#include "platforms/VertexInterleavedBuffer.h"
#include "platforms/IndexBuffer.h"
#include "platforms/UniformMat2.h"
#include "tiny_obj_loader.h"
#include "platforms/Tex2D.h"
#include "platforms/Renderer.h"
#include "math/vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "g2dMath.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glowy3d;

int main()
{
    ShaderProgram*           shaderProgram;

    VertexInterleavedBufferWithNormals* bufferCity;
    IndexBuffer*             indexBufferCity;
    Tex2D*                   bricksTextureCity;
    VertexInterleavedBufferWithNormals* bufferLenin;
    IndexBuffer*             indexBufferLenin;
    Tex2D*                   bricksTextureLenin;
    // UniformMat2*?

    uint citySize;
    uint leninSize;

    std::string inputfile;

    auto init = [&](){
        shaderProgram = new ShaderProgram(System::config->getVertexShaderPath(), 
                                          System::config->getFragmentShaderPath());
        vector<vertexn> data;
        vector<uint> indexData;
        shaderProgram->use();
        {
            inputfile = "lenin.obj";

            auto modelMatrixUniform = new UniformMat2(shaderProgram, "model", 0);
            modelMatrixUniform->bind();
            auto viewMatrixUniform = new UniformMat2(shaderProgram, "camera", 1);
            viewMatrixUniform->bind();

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

            std::string err;
            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

            if (!err.empty()) 
                std::cerr << err << std::endl;

            if (!ret) 
                exit(1);


            for (size_t s = 0; s < shapes.size(); s++) 
            {
                cout << "Shape " << s << endl;
                size_t index_offset = 0;
                for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
                {
                    int fv = shapes[s].mesh.num_face_vertices[f];
                    for (size_t v = 0; v < fv; v++) 
                    {
                        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                        float vx = attrib.vertices[3*idx.vertex_index+0];
                        float vy = attrib.vertices[3*idx.vertex_index+1];
                        float vz = attrib.vertices[3*idx.vertex_index+2];
                        float nx = attrib.normals[3*idx.normal_index+0];
                        float ny = attrib.normals[3*idx.normal_index+1];
                        float nz = attrib.normals[3*idx.normal_index+2];
                        float tx = attrib.texcoords[2*idx.texcoord_index+0];
                        float ty = attrib.texcoords[2*idx.texcoord_index+1];

                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+0*/);
                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+1*/);
                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+2*/);
                        data.push_back(vertexn(vec3(vx, vy, vz), 
                                               vec3(nx, ny, nz),
                                               vec2(tx, ty)));
                    }
                    index_offset += fv;
                    shapes[s].mesh.material_ids[f];

                }
            }


            bufferLenin = new VertexInterleavedBufferWithNormals(data.data(), data.size() * sizeof(vertexn));
            bufferLenin->setLayout();
            bufferLenin->bind();
            indexBufferLenin = new IndexBuffer(indexData.data(), indexData.size() * sizeof(uint));
            indexBufferLenin->bind();

            bricksTextureLenin = new Tex2D("TileStone.png");
            bricksTextureLenin->bind();
            citySize = data.size();
        }
        data.clear();
        indexData.clear();
        {
            // vector<vertexn> data;
            // vector<uint> indexData;
            inputfile = "city.obj";

            auto modelMatrixUniform = new UniformMat2(shaderProgram, "model", 0);
            modelMatrixUniform->bind();
            auto viewMatrixUniform = new UniformMat2(shaderProgram, "camera", 1);
            viewMatrixUniform->bind();

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

            std::string err;
            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

            if (!err.empty()) 
                std::cerr << err << std::endl;

            if (!ret) 
                exit(1);

            for (size_t s = 0; s < shapes.size(); s++) 
            {
                cout << "Shape " << s << endl;
                size_t index_offset = 0;
                for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
                {
                    int fv = shapes[s].mesh.num_face_vertices[f];
                    for (size_t v = 0; v < fv; v++) 
                    {
                        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                        float vx = attrib.vertices[3*idx.vertex_index+0];
                        float vy = attrib.vertices[3*idx.vertex_index+1];
                        float vz = attrib.vertices[3*idx.vertex_index+2];
                        float nx = attrib.normals[3*idx.normal_index+0];
                        float ny = attrib.normals[3*idx.normal_index+1];
                        float nz = attrib.normals[3*idx.normal_index+2];
                        float tx = attrib.texcoords[2*idx.texcoord_index+0];
                        float ty = attrib.texcoords[2*idx.texcoord_index+1];

                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+0*/);
                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+1*/);
                        indexData.push_back(indexData.size()/*3*idx.vertexn_index+2*/);
                        data.push_back(vertexn(vec3(vx, vy, vz), 
                                               vec3(nx, ny, nz),
                                               vec2(tx, ty)));
                    }
                    index_offset += fv;
                    shapes[s].mesh.material_ids[f];

                }
            }


            bufferCity = new VertexInterleavedBufferWithNormals(data.data(), data.size() * sizeof(vertexn));
            bufferCity->setLayout();
            bufferCity->bind();
            indexBufferCity = new IndexBuffer(indexData.data(), indexData.size() * sizeof(uint));
            indexBufferCity->bind();

            bricksTextureCity = new Tex2D("city.png");
            bricksTextureCity->bind();
            leninSize = data.size();
        }
    };

    vec3 position = vec3(0, 0, 5);
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    vec3 lightPosition = vec3(1, 1, 1);
    float fov = 45.0f;
    float speed = 3.0f; 
    float mouseSpeed = 10.0f;
    mat4 modelMatrix = glm::mat4(0.01, 0, 0, 0,
                                 0, 0.01, 0, 0,
                                 0, 0, 0.01, 0,
                                 0, 0, 0,   1);
    // mat4 modelMatrix = glm::mat4(1, 0, 0, 0,
    //                                   0, 1, 0, 0,
    //                                   0, 0, 1, 0,
    //                                   0, 0, 0, 1);


    auto update = [&](){
        float deltaTime = System::getDeltaTime();
        auto window = System::window->getHandle();
        auto windowWidth  = System::window->getSize().x;
        auto windowHeight = System::window->getSize().y;

        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

        horizontalAngle += mouseSpeed * deltaTime * float(windowWidth /2 - cursorX );
        verticalAngle   += mouseSpeed * deltaTime * float(windowHeight/2 - cursorY );


        glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        );

        glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
        );

        glm::vec3 up = glm::cross( right, direction );

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += direction * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= direction * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += right * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= right * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position -= up * deltaTime * speed;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            lightPosition += direction * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            lightPosition -= direction * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            lightPosition += right * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            lightPosition -= right * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
            lightPosition += up * deltaTime * speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
            lightPosition -= up * deltaTime * speed;

        mat4 projectionMatrix = glm::perspective(fov, 4.0f / 3.0f,
                                                 0.1f, 100.0f);
        mat4 viewMatrix = glm::lookAt(
            position,           
            position+direction, 
            up);

        // modelMatrix = rotate(modelMatrix, 2 * deltaTime, vec3(1,1,1));
        glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

        auto mvpUniformLocation = glGetUniformLocation(
            shaderProgram->id, 
            "mvp_matrix");
        glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, (float*)&mvp);

        {
            auto uniformEyePosWLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"eyePosW");
            auto val = vec4(position.x, position.y, position.z, 1);
            glUniform4fv(uniformEyePosWLLocation, 1, (float*)&val);
        }
        {
            auto uniformEyePosWLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"eyeNormalW");
            auto val = vec4(direction.x, direction.y, direction.z, 1);
            glUniform4fv(uniformEyePosWLLocation, 1, (float*)&val);
        }
        {
            auto uniformLightPosWLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"lightPosW");
            auto val = vec4(lightPosition.x, 
                            lightPosition.y, 
                            lightPosition.z, 1);
            glUniform4fv(uniformLightPosWLLocation, 1, (float*)&val);
        }
        {
            auto uniformLightColorLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"lightColor"); 
            auto val = vec4(1, 0.5, 0.5, 1);
            glUniform4fv(uniformLightColorLLocation, 1, (float*)&val);
        }

        {
            auto uniformMaterialEmissiveLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"materialEmissive");
            auto val = vec4(0.5, 0.5, 0.5, 1);
            glUniform4fv(uniformMaterialEmissiveLLocation, 1, (float*)&val);
        }
        {
            auto uniformMaterialDiffuseLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"materialDiffuse");
            auto val = vec4(0.5, 0.5, 0.5, 1);
            glUniform4fv(uniformMaterialDiffuseLLocation, 1, (float*)&val);
        }
        {
            auto uniformMaterialSpecularLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"materialSpecular");
            auto val = vec4(0.5, 0.5, 0.5, 1);
            glUniform4fv(uniformMaterialSpecularLLocation, 1, (float*)&val);
        }
        {
            auto uniformMaterialShininessLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform float */"materialShininess");
            auto val = 0.5;
            glUniform1fv(uniformMaterialShininessLocation, 1, (float*)&val);
        }

        {
            auto uniformAmbientLLocation = glGetUniformLocation(
                shaderProgram->id, 
    /*uniform vec4 */"ambient");
            auto val = vec4(0.3, 0.3, 0.3, 1);
            glUniform4fv(uniformAmbientLLocation, 1, (float*)&val);
        }

        indexBufferCity->bind();
        bufferCity->bind();
        bricksTextureCity->bind();
        glDrawElements(GL_TRIANGLES, citySize / 3, GL_UNSIGNED_INT, 0);
        indexBufferLenin->bind();
        bufferLenin->bind();
        bricksTextureLenin->bind();
        glDrawElements(GL_TRIANGLES, leninSize / 3, GL_UNSIGNED_INT, 0);
    };


    glowy3d::start(init, update);
    delete shaderProgram;
}
