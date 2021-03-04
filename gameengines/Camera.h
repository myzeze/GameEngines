#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE {

	class Camera {
	public: Camera(glm::vec3 cam_pos, glm::vec3 cam_upDir, float fov, float ar, float near, float far) {
		pos = cam_pos;
		target = cam_target;
		up = cam_dir;

		fovy = fov;
		aspectR = ar;
		nearClip = near;
		farClip = far;

		updateCamMatricies();
	}

		  ~Camera(){}

		  float getPosX() {
			  return pos.x;
		  }

		  float getPosY() {
			  return pos.y;
		  }

		  float getPosZ() {
			  return pos.z;
		  }


	};
}