#include "camera.h"
#include "gtc/quaternion.hpp"
#include "gtx/transform.hpp"

using namespace basegame;

Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}


void Camera::setPosition(const glm::vec3 &pos_) {
	//simple set position and update view matrix
	m_position = pos_;
	calcView();
}

void Camera::setLookAt(const glm::vec3 &vec_, const glm::vec3 &up_) {
	//simple set look at and update view matrix
	m_viewMatrix = glm::lookAt(m_position, vec_, up_);
}

void Camera::setViewRotation(float yaw_, float pitch_, float roll_) {
	m_orientation = glm::angleAxis(0.0f, 0.0f, 1.0f, 0.0f);
	addViewRotation(yaw_, pitch_, roll_);
}

void Camera::addViewRotation(float yaw_, float pitch_, float roll_) {
	
	//Get a quarternion rotation from the provided view vector
	m_qyaw = m_qyaw * glm::angleAxis(yaw_, 0.0f, 1.0f, 0.0f); //rotate around local y
	m_qpitch = m_qpitch * glm::angleAxis(pitch_, 1.0f, 0.0f, 0.0f); //rotate around local x
	m_qroll = m_qroll * glm::angleAxis(roll_, 0.0f, 0.0f, 1.0f); //rotate around local z
	
	m_orientation = m_qyaw * m_qpitch * m_qroll;
	
	calcView();
}

void Camera::setOrientation(const glm::quat &orientation_) {
	m_orientation = orientation_;
}

void Camera::calcView() {	
	m_posTransform = glm::translate(m_position);
	m_viewMatrix = glm::mat4_cast(m_orientation) * m_posTransform; 
}

void Camera::calcProjection() {
	m_projectionMatrix = glm::perspectiveFov(m_hFov, (float)m_width, (float)m_height, m_near, m_far);
}

void Camera::translate(const glm::vec3 &translation_) {
	m_position += translation_;
	calcView();
}

void Camera::translateInLookAt(float dist_) {
	//need world orientation
	glm::vec4 translation = glm::mat4_cast(m_orientation) * glm::vec4(0,0,dist_,1.0f);
	translate(glm::vec3(translation));
}

void Camera::setNear(float near_) {
	m_near = near_;
	calcProjection();
}

void Camera::setFar(float far_) {
	m_far = far_;
	calcProjection();
}

void Camera::setHFov(float hfov_) {
	m_hFov = hfov_;
	calcProjection();
}

void Camera::setViewPort(int width_, int height_) {
	m_width = width_;
	m_height = height_;
	calcProjection();
}