#pragma once

#include "commonenums.hpp"
#include <memory>
#include "glm.hpp"
#include "gtx/quaternion.hpp"

namespace basegame {
	typedef glm::detail::tquat<float> FQuaternion;	
	//Perspective projection camera
class Camera
{
public:
	
	Camera(void);

	virtual ~Camera(void);

	void setPosition(const glm::vec3 &pos_);

	//
	void setLookAt(const glm::vec3 &vec_, const glm::vec3 &up_);
	
	//Move the view by rotation according to the provided view space vector
	void setViewRotation(float yaw_, float pitch_, float roll_);

	void addViewRotation(float yaw_, float pitch_, float roll_);

	void setOrientation(const glm::quat &orientation_);

	void rotate(float angle_, const glm::vec3 &vec_);

	void translate(const glm::vec3 &translation_);

	void setNear(float near_);

	void setFar(float near_);
	
	void setHFov(float hfov_);

	void setViewPort(int width_, int height_);

	inline const glm::mat4 &getProjectionMatrix() const;

	inline const glm::mat4 &getViewMatrix() const;

	void translateInLookAt(float dist_);

private:

	void calcView();

	void calcProjection();

	glm::mat4 m_projectionMatrix;

	glm::mat4 m_viewMatrix;

	FQuaternion m_orientation;

	FQuaternion m_qroll;

	FQuaternion m_qyaw;

	FQuaternion m_qpitch;

	float m_near;

	float m_far;

	float m_hFov;

	int m_width;

	int m_height;

	glm::vec3 m_position;

	//Current values, should not be transformed, only set
	glm::mat4 m_posTransform;	
	glm::mat4 m_rotationTransform;
};

typedef std::shared_ptr<Camera> CameraPtr;


inline const glm::mat4 &Camera::getProjectionMatrix() const {
	return m_projectionMatrix;
}

inline const glm::mat4 &Camera::getViewMatrix() const {
	return m_viewMatrix;
}

}