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

    VertexInterleavedBuffer* buffer;
    IndexBuffer*             indexBuffer;
    ShaderProgram*           shaderProgram;
    Tex2D*                   bricksTexture;
    // UniformMat2*?

    std::string inputfile = "cube.obj";

    auto init = [&](){


        shaderProgram = new ShaderProgram(System::config->getVertexShaderPath(), 
                                          System::config->getFragmentShaderPath());
        shaderProgram->use();

        // auto modelMatrixUniform = new UniformMat2(shaderProgram, "model", 0);
        // modelMatrixUniform->bind();
        // auto viewMatrixUniform = new UniformMat2(shaderProgram, "camera", 1);
        // viewMatrixUniform->bind();

        // tinyobj::attrib_t attrib;
        // std::vector<tinyobj::shape_t> shapes;
        // std::vector<tinyobj::material_t> materials;

        // std::string err;
        // bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

        // if (!err.empty()) 
        // { 
        //     std::cerr << err << std::endl;
        // }

        // if (!ret) 
        // {
        //     exit(1);
        // }

        // vector<vertex> data;
        // vector<uint> indexData;

        // for (size_t s = 0; s < shapes.size(); s++) 
        // {
        //     size_t index_offset = 0;
        //     for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
        //     {
        //         int fv = shapes[s].mesh.num_face_vertices[f];
        //         for (size_t v = 0; v < fv; v++) 
        //         {
        //             tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        //             float vx = attrib.vertices[3*idx.vertex_index+0];
        //             float vy = attrib.vertices[3*idx.vertex_index+1];
        //             float vz = attrib.vertices[3*idx.vertex_index+2];
        //             float nx = attrib.normals[3*idx.normal_index+0];
        //             float ny = attrib.normals[3*idx.normal_index+1];
        //             float nz = attrib.normals[3*idx.normal_index+2];
        //             float tx = attrib.texcoords[2*idx.texcoord_index+0];
        //             float ty = attrib.texcoords[2*idx.texcoord_index+1];

        //             data.push_back(vertex(vec3(vx, vy, vz), 
        //                                   vec2(tx, ty)));
        //             indexData.push_back(indexData.size());
        //             indexData.push_back(indexData.size());
        //             indexData.push_back(indexData.size());
        //         }
        //         index_offset += fv;
        //         shapes[s].mesh.material_ids[f];
        //     }
        // }

        auto data = vector<vertex>({
        // Vertex data for face 0
            {vec3(-1.0f, -1.0f,  1.0f), vec2(0.0f, 0.0f)},  // v0
            {vec3( 1.0f, -1.0f,  1.0f), vec2(0.33f, 0.0f)}, // v1
            {vec3(-1.0f,  1.0f,  1.0f), vec2(0.0f, 0.5f)},  // v2
            {vec3( 1.0f,  1.0f,  1.0f), vec2(0.33f, 0.5f)}, // v3

            // Vertex data for face 1
            {vec3( 1.0f, -1.0f,  1.0f), vec2( 0.0f, 0.5f)}, // v4
            {vec3( 1.0f, -1.0f, -1.0f), vec2(0.33f, 0.5f)}, // v5
            {vec3( 1.0f,  1.0f,  1.0f), vec2(0.0f, 1.0f)},  // v6
            {vec3( 1.0f,  1.0f, -1.0f), vec2(0.33f, 1.0f)}, // v7

            // Vertex data for face 2
            {vec3( 1.0f, -1.0f, -1.0f), vec2(0.66f, 0.5f)}, // v8
            {vec3(-1.0f, -1.0f, -1.0f), vec2(1.0f, 0.5f)},  // v9
            {vec3( 1.0f,  1.0f, -1.0f), vec2(0.66f, 1.0f)}, // v10
            {vec3(-1.0f,  1.0f, -1.0f), vec2(1.0f, 1.0f)},  // v11

            // Vertex data for face 3
            {vec3(-1.0f, -1.0f, -1.0f), vec2(0.66f, 0.0f)}, // v12
            {vec3(-1.0f, -1.0f,  1.0f), vec2(1.0f, 0.0f)},  // v13
            {vec3(-1.0f,  1.0f, -1.0f), vec2(0.66f, 0.5f)}, // v14
            {vec3(-1.0f,  1.0f,  1.0f), vec2(1.0f, 0.5f)},  // v15

            // Vertex data for face 4
            {vec3(-1.0f, -1.0f, -1.0f), vec2(0.33f, 0.0f)}, // v16
            {vec3( 1.0f, -1.0f, -1.0f), vec2(0.66f, 0.0f)}, // v17
            {vec3(-1.0f, -1.0f,  1.0f), vec2(0.33f, 0.5f)}, // v18
            {vec3( 1.0f, -1.0f,  1.0f), vec2(0.66f, 0.5f)}, // v19

            // Vertex data for face 5
            {vec3(-1.0f,  1.0f,  1.0f), vec2(0.33f, 0.5f)}, // v20
            {vec3( 1.0f,  1.0f,  1.0f), vec2(0.66f, 0.5f)}, // v21
            {vec3(-1.0f,  1.0f, -1.0f), vec2(0.33f, 1.0f)}, // v22
            {vec3( 1.0f,  1.0f, -1.0f), vec2(0.66f, 1.0f)}  // v23
        });

        auto indexData = vector<uint>{
             0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
             4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
             8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
            12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
            16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
            20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
        };

        buffer = new VertexInterleavedBuffer(data.data(), data.size() * sizeof(vertex));
        buffer->setLayout();
        buffer->bind();
        // int positionLocation = program->attributeLocation("position");
        // int texcoordLocation = program->attributeLocation("texcoord");
        indexBuffer = new IndexBuffer(indexData.data(), indexData.size() * sizeof(uint));
        indexBuffer->bind();

        bricksTexture = new Tex2D("TileStone.png");
        bricksTexture->bind();
    };

    auto update = [&](){

        glm::vec3 position = glm::vec3( 0, 0, 5 );
        float horizontalAngle = 3.14f;
        float verticalAngle = 0.0f;
        float initialFoV = 45.0f;

        float speed = 3.0f; 
        float mouseSpeed = 0.005f;
        double xpos, ypos;
        float deltaTime = System::getDeltaTime();

        // double currentTime = glfwGetTime();
        // float deltaTime = float(currentTime - lastTime);

        auto window = System::window->getHandle();

        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetCursorPos(window, 1024/2, 768/2);

        horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
        verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );


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

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            position += direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            position -= direction * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            position += right * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            position -= right * deltaTime * speed;
        }

        float FoV = initialFoV;// - 5 * glfwGetMouseWheel();

        mat4 ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
        mat4 ViewMatrix       = glm::lookAt(
            position,           // Camera is here
            position+direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
        );


        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        auto mvpUniformLocation = glGetUniformLocation(
            shaderProgram->id, 
            "mvp_matrix");

        glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, (float*)&MVP);


        indexBuffer->bind();
        buffer->bind();
        bricksTexture->bind();
        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, 0);
    };


    glowy3d::start(init, update);
    delete buffer;
    delete shaderProgram;
}
