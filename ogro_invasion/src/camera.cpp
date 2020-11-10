#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "camera.h"
#include "entity.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera():
m_position(Vector3(0.0f, 0.0f, 0.0f)),
m_up(Vector3(0.0f, 1.0f, 0.0f)),
m_right(Vector3(1.0f, 0.0f, 0.0f)),
m_forward(Vector3(0.0f, 0.0f, 1.0f)),
m_yaw(0.0f),
m_pitch(0.0f),
m_attachedEntity(NULL),
m_lookAt(Vector3(0.0f, 0.0f, 1.0f))
{
}

Camera::Camera(const Vector3& position):
m_position(position),
m_up(Vector3(0.0f, 1.0f, 0.0f)),
m_right(Vector3(1.0f, 0.0f, 0.0f)),
m_forward(Vector3(0.0f, 0.0f, 1.0f)),
m_yaw(0.0f),
m_pitch(0.0f),
m_attachedEntity(NULL),
m_lookAt(Vector3(0.0f, 0.0f, 1.0f))
{
}

void Camera::setPosition(const Vector3& position)
{
    m_position = position;
}

void Camera::yaw(const float degrees)
{
    m_yaw += degrees;

    if (m_yaw >= 360.0f) m_yaw -=360.0f;
    if (m_yaw < 0.0f) m_yaw += 360.0f;

    float radians = degreesToRadians(m_yaw);

	float sine = sinf(radians);
	float cosine = cosf(radians);

	m_right.x = cosine * m_right.length();
	m_right.z = sine * m_right.length();

	m_forward.x = -sine * m_forward.length();
	m_forward.z = cosine * m_forward.length();
}

void Camera::pitch(const float degrees)
{

}

float* Camera::GetMVPMatrix()
{
    apply();
    float proj[16]= {0.0};
    
    
    glm::mat4 View = glm::lookAt(
                                 glm::vec3(m_position.x,m_position.y,m_position.z), // Camera is at (4,3,3), in World Space
                                 glm::vec3(m_lookAt.x,m_lookAt.y,m_lookAt.z),
                                 glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                 
                                 );
     
    
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 mv = model * View;
    m_mvp = (float*)glm::value_ptr(mv);
    for (int i = 0; i < 16; ++i)
        proj[i] = m_mvp[i];
    
    return m_mvp;
}

void Camera::apply()
{
    if (m_attachedEntity != NULL) {
        setPosition(m_attachedEntity->getPosition());
        m_yaw = m_attachedEntity->getYaw();
        m_pitch = m_attachedEntity->getPitch();
    }

    float cosYaw = cosf(degreesToRadians(m_yaw));
    float sinYaw = sinf(degreesToRadians(m_yaw));
    float sinPitch = sinf(degreesToRadians(m_pitch));

    // calculate lookAt based on new position
    m_lookAt.x = m_position.x + cosYaw;
    m_lookAt.y = m_position.y + sinPitch;
    m_lookAt.z = m_position.z + sinYaw;
    
    //the glulookat does not work, have to construct model viemodel matrixes accordingly
    // set the camera
	gluLookAt(m_position.x, m_position.y, m_position.z,
              m_lookAt.x, m_lookAt.y, m_lookAt.z,
              m_up.x, m_up.y, m_up.z);
}
