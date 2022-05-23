#include <digital_twin/input_system.hpp>
#include <digital_twin/render_system.hpp>
#include <digital_twin/sim_world.hpp>
#include <digital_twin/affine_frame.hpp>
#include <digital_twin/bag_loader.hpp>

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <GL/gl.h>

int main(int argc, char **argv) {
  std::cerr << "Digital Twin." << std::endl;

  if (argc != 2) {
    std::cerr << "Need a bagfile to load." << std::endl;
    return 1;
  }

  digital_twin::ROSBagLoader loader{argv[1]};
  
  Camera follow{glm::vec3(0.0f, -3.0f, 0.0f)};
  follow.type = CameraType::FOLLOW;
  
  Camera overhead{glm::vec3(0.0f, 0.0f, 10.0f),
		  glm::vec3(0.0f, 1.0f, 0.0f),
		  glm::vec3(0.0f, 0.0f, 1.0f)};
  overhead.type = CameraType::OVERHEAD;
  
  digital_twin::InputSystem input_system;
  digital_twin::RenderSystem render_system{follow, overhead};
  if (!render_system.init()) {
    std::cerr << "RenderSystem initialization failed." << std::endl;
    return 1;
  }
  
  input_system.init(render_system);
  
  digital_twin::SimWorld world;

  auto fr = std::make_shared<digital_twin::AffineFrame>();
  world.add(fr);
  
  bool done = false;
  float dt = 0.0;
  
  using namespace std::literals::chrono_literals;

  while (!done) {
    auto start_time = std::chrono::system_clock::now();

    // process inputs
    done = input_system.update(render_system, dt);

    // TODO perform any simulation

    // draw
    render_system.render(world);

    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    dt = elapsed_seconds.count();

    if (elapsed_seconds < 8ms) {
      std::this_thread::sleep_for(8ms - elapsed_seconds);
    }
  }

  // TODO finalize writes to disk

  // TODO shut down everything
  render_system.shutdown();
  
}
