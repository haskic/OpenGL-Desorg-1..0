// OpenGlStart.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <glew.h>
#include <stdio.h>
#include <stdlib.h>

#include <glfw3.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <vec4.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/string_cast.hpp>
#include <mat4x4.hpp>
#include "Camera.h"



GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
//GLuint loadBMP_custom(const char* imagepath);


int main()
{
    std::cout << "Program starting ..." << std::endl;
    double mouseX, mouseY;

    if (!glfwInit()) {
        std::cout << "GLFW error initialize!" << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Zhakar OpenGl", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "GLFW INIT ERROR");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW INIT ERROR");
        return -1;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    static std::vector<GLfloat> g_vertex_buffer_data{
     -1.5f,-0.5f,-0.5f, // Треугольник 1 : начало
    -1.5f,-0.5f, 0.5f,
    -1.5f, 0.5f, 0.5f, // Треугольник 1 : конец
    -0.5f, 0.5f,-0.5f, // Треугольник 2 : начало
    -1.5f,-0.5f,-0.5f,
    -1.5f, 0.5f,-0.5f, // Треугольник 2 : конец
    -0.5f,-0.5f, 0.5f,
    -1.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -1.5f,-0.5f,-0.5f,
    -1.5f,-0.5f,-0.5f,
    -1.5f, 0.5f, 0.5f,
    -1.5f, 0.5f,-0.5f,
    -0.5f,-0.5f, 0.5f,
    -1.5f,-0.5f, 0.5f,
    -1.5f,-0.5f,-0.5f,
    -1.5f, 0.5f, 0.5f,
    -1.5f,-0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f,-0.5f,
    -1.5f, 0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f,
    -1.5f, 0.5f,-0.5f,
    -1.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -1.5f, 0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f
    };

    static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };


    static std::vector<GLfloat> vertex_line_buffer{
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f,  0.0f, 0.0f,
    };

    static std::vector<GLfloat> g_vertex_buffer_data1{
    -0.3f,-0.3f,-0.3f, // Треугольник 1 : начало
    -0.3f,-0.3f, 0.3f,
    -0.3f, 0.3f, 0.3f, // Треугольник 1 : конец
    0.3f, 0.3f,-0.3f, // Треугольник 2 : начало
    -0.3f,-0.3f,-0.3f,
    -0.3f, 0.3f,-0.3f, // Треугольник 2 : конец
    0.3f,-0.3f, 0.3f,
    -0.3f,-0.3f,-0.3f,
    0.3f,-0.3f,-0.3f,
    0.3f, 0.3f,-0.3f,
    0.3f,-0.3f,-0.3f,
    -0.3f,-0.3f,-0.3f,
    -0.3f,-0.3f,-0.3f,
    -0.3f, 0.3f, 0.3f,
    -0.3f, 0.3f,-0.3f,
    0.3f,-0.3f, 0.3f,
    -0.3f,-0.3f, 0.3f,
    -0.3f,-0.3f,-0.3f,
    -0.3f, 0.3f, 0.3f,
    -0.3f,-0.3f, 0.3f,
    0.3f,-0.3f, 0.3f,
    0.3f, 0.3f, 0.3f,
    0.3f,-0.3f,-0.3f,
    0.3f, 0.3f,-0.3f,
    0.3f,-0.3f,-0.3f,
    0.3f, 0.3f, 0.3f,
    0.3f,-0.3f, 0.3f,
    0.3f, 0.3f, 0.3f,
    0.3f, 0.3f,-0.3f,
    -0.3f, 0.3f,-0.3f,
    0.3f, 0.3f, 0.3f,
    -0.3f, 0.3f,-0.3f,
    -0.3f, 0.3f, 0.3f,
    0.3f, 0.3f, 0.3f,
    -0.3f, 0.3f, 0.3f,
    0.3f,-0.3f, 0.3f
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(GLfloat), &g_vertex_buffer_data.front(), GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint vertexbuffer1;
    glGenBuffers(1, &vertexbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data1.size() * sizeof(GLfloat), &g_vertex_buffer_data1.front(), GL_STATIC_DRAW);

    GLuint vertexbufferline;
    

    GLuint programID = LoadShaders("Vertex.shader", "Fragment.shader");

    glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(1.f, 1.f, 1.f));

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    Camera* mainCamera = new Camera(3,3,3,0,0,0,glm::vec3(0,1,0));
   
    glm::mat4 Model = glm::mat4(1.f);
    Model = glm::rotate(Model, glm::radians(70.0f), glm::vec3(0, 1, 0));
    // Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
    glm::mat4 MVP;
    MVP = Projection * mainCamera->getCameraMatrix() * Model;
    std::cout << glm::to_string(MVP) << std::endl;

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    float z = 1.f;
    float alpha = 0.f;
    float alpha2 = 0.f;

    float radius = 3.f;
    float xCamera = -4.f;
    float yCamera = 3.f;
    float zCamera = 3.f;
    float scaleNumber = .5f;
    bool isClick = false;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    MVP = Projection * mainCamera->getCameraMatrix() * Model;

        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void*)0            // Смещение массива в буфере
            );
        glDrawArrays(GL_TRIANGLES, 0, 36); // Начиная с вершины 0, всего 3 вершины -> один треугольник

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
            3,                                // Размер
            GL_FLOAT,                         // Тип
            GL_FALSE,                         // Нормализован?
            0,                                // Шаг
            (void*)0                          // Смещение
            );

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
        glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void*)0            // Смещение массива в буфере
            );
        // Вывести треугольник!
        glDrawArrays(GL_TRIANGLES, 0, 36); // Начиная с вершины 0, всего 3 вершины -> один треугольник

       
        
        glDisableVertexAttribArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
        /*if (z > 3) {
            z -= 2.f;
        }
        z += 0.01f;*/
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
            glfwGetCursorPos(window, &mouseX, &mouseY);
            std::cout << "Mouse button was pressed x = "<<mouseX<<"  :  y = "<<mouseY << std::endl;
           
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
            std::cout << "Na berlin "<< std::endl;
            alpha += .05;
        }
        if  (glfwGetKey(window, GLFW_KEY_LEFT)) {
            std::cout << "Na berlin " << std::endl;
            alpha -= 0.05;
        }
        if (glfwGetKey(window, GLFW_KEY_UP)) {
            alpha2 += .05;
            mainCamera->toY += 0.05;
            //scaleNumber += .01;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN)) {
            //scaleNumber -= .01;
            alpha2 -= .05;
            mainCamera->toY -= 0.05;


        }
        if (glfwGetKey(window, GLFW_KEY_W)) {
            mainCamera->x += 0.1;
        }
        mainCamera->toX = cos(alpha) * radius + 3.;
        //mainCamera->toY = sin(alpha) * radius;
        mainCamera->toZ = sin(alpha) * radius + 3.;

        /*mainCamera->toY = cos(alpha2) * radius + 3.;
        mainCamera->toZ = sin(alpha2) * radius + 3.;*/


        //mainCamera->toY = cos(alpha) * radius;
    } // Проверяем нажатие клавиши Escape или закрытие окна
    
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);


}
//
//GLuint loadBMP_custom(const char* imagepath) {
//    unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
//    unsigned int dataPos;     // Смещение данных в файле (позиция данных)
//    unsigned int width, height;
//    unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3
//    // RGB-данные, полученные из файла
//    unsigned char* data;
//    FILE* file = fopen(imagepath, "rb");
//    if (!file) {
//        printf("Изображение не может быть открытоn");
//        return 0;
//    }
//    if (fread(header, 1, 54, file) != 54) { // Если мы прочитали меньше 54 байт, значит возникла проблема
//        printf("Некорректный BMP-файлn");
//        return false;
//    }
//    if (header[0] != 'B' || header[1] != 'M') {
//        printf("Некорректный BMP-файлn");
//        return 0;
//    }
//    dataPos = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
//    imageSize = *(int*)&(header[0x22]); // Размер изображения в байтах
//    width = *(int*)&(header[0x12]); // Ширина
//    height = *(int*)&(header[0x16]); // Высота
//    if (imageSize == 0)    imageSize = width * height * 3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
//    if (dataPos == 0)      dataPos = 54; // В таком случае, данные будут следовать сразу за заголовком
//    // Создаем буфер
//    data = new unsigned char[imageSize];
//
//    // Считываем данные из файла в буфер
//    fread(data, 1, imageSize, file);
//
//    // Закрываем файл, так как больше он нам не нужен
//    fclose(file);
//}
