#ifndef POINT_CLOUD_HPP
#define POINT_CLOUD_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <torch/torch.h>

#include <digital_twin/shader.hpp>
#include <digital_twin/drawable.hpp>

#include <glm/glm.hpp>

#include <iostream>

namespace digital_twin {

  /*
   * A point cloud structure for rendering.
   */
  class PointCloud : public Drawable {
  public:
    PointCloud();

    ~PointCloud() {
      shader.cleanup();
      glDeleteBuffers(1, &vbo);
      glDeleteVertexArrays(1, &vao);
    }

    void draw(const glm::mat4& proj, const glm::mat4& view) override;
    void setupMesh();

  private:

    glm::vec3 position;
    // TODO orientation
    
    GLuint vao;
    GLuint vbo;
    Shader shader;    
    
  };

} // namespace digital_twin


#endif // POINT_CLOUD_HPP
