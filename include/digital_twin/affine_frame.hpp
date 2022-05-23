#ifndef AFFINE_FRAME_HPP
#define AFFINE_FRAME_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <digital_twin/shader.hpp>
#include <digital_twin/drawable.hpp>
#include <digital_twin/quaternion.hpp>

#include <glm/glm.hpp>

namespace digital_twin {

struct AffineFrame : public Drawable {

  AffineFrame(const glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0),
	      const glm::vec3 angles = glm::vec3(0.0, 0.0, 0.0))
    : frame_shader{"../src/shaders/frame.vs", "../src/shaders/frame.fs"}
    , position{pos}
    , orientation{glm::vec3(0.0, 0.0, 1.0), 0.5} {
      setupMesh();
    }

  ~AffineFrame() {
    frame_shader.cleanup();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
  }

  void draw(const glm::mat4& proj, const glm::mat4& view) override;
  void setupMesh();

  glm::vec3 position;
  quaternion<float> orientation;

  GLuint vao;
  GLuint vbo;
  Shader frame_shader;
  
};

} // namespace digital_twin


#endif // AFFINE_FRAME_HPP
