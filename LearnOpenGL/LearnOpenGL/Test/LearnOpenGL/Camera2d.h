#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Camera2d
{
public:
    // camera Attributes
    glm::vec3 Position;

    // camera options
    //float MovementSpeed;
    //float MouseSensitivity;
    //float Zoom;

    Camera2d(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0));



};

#endif // !CAMERA2D_H