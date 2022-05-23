#ifndef SIM_WORLD_HPP
#define SIM_WORLD_HPP

#include <digital_twin/drawable.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>

namespace digital_twin {

  class SimWorld {
  public:
    
    void draw(const glm::mat4& proj, const glm::mat4& view) {
      for (const auto& o : scene) {
	o->draw(proj, view);
      }
    }

    void add(const std::shared_ptr<Drawable>& obj) {
      scene.push_back(obj);
    }
    
  private:
    
    std::vector<std::shared_ptr<Drawable>> scene;
    
  };

}

#endif // SIM_WORLD_HPP
