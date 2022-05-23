#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <digital_twin/sim_focus.hpp>
#include <digital_twin/sim_world.hpp>
#include <digital_twin/camera.hpp>
#include <digital_twin/shader.hpp>

#include <iostream>
#include <map>
#include <string>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace digital_twin {

  class RenderSystem {
  public:

    RenderSystem() = default;
    
    RenderSystem(Camera follow, Camera overhead)
      : follow_camera{follow}
      , overhead_camera{overhead} { }
    
    bool init();
    void resize();
    void render(SimWorld& w);
    void shutdown();

    inline float get_width() const {
      return screen_width;
    }

    inline float get_height() const {
      return screen_height;
    }

    inline SimFocus get_focus() const {
      return focus;
    }

    inline void toggle_camera() {
      if (current_camera == &follow_camera) {
	current_camera = &overhead_camera;
      } else {
	current_camera = &follow_camera;
      }
    }    
    
    Camera follow_camera;
    Camera overhead_camera;
    Camera *current_camera = &follow_camera;
    
  private:
    FT_Library ft;
    FT_Face face;
    
    SDL_Window *main_window;
    SDL_GLContext gl_context;
    
    float screen_width;
    float screen_height;

    // framebuffer variables
    GLuint screen_fbo;
    GLuint color_texture_attachment;
    GLuint screen_rbo;
    GLuint depth_stencil_attachment;

    // screen variables
    Shader screen_shader;
    GLuint screen_vao;
    
    SimFocus focus = SimFocus::SIMWORLD;
    
  };
  
}

#endif // RENDER_SYSTEM_HPP
