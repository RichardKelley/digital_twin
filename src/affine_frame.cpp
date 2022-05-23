#include <digital_twin/affine_frame.hpp>
#include <digital_twin/shader.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace digital_twin {

  void AffineFrame::draw(const glm::mat4& proj, const glm::mat4& view) {

    frame_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
    model = model * orientation.rotation_matrix();

    frame_shader.setMat4("projection", proj);
    frame_shader.setMat4("view", view);
    frame_shader.setMat4("model", model);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);    
  }

  void AffineFrame::setupMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float axes[] = {
		    0.0, 0.0, 0.0,
		    1.0, 0.0, 0.0,
		    0.0, 0.0, 0.0,
		    0.0, 1.0, 0.0,
		    0.0, 0.0, 0.0,
		    0.0, 0.0, 1.0
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(axes), &axes[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }


} // namespace digital_twin
