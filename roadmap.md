# Roadmap
Now, this is a roadmap *BUT* since this project is a wrapper, I just do not want to make _n_ squares like
"implement this from SDL", "implement that fro SDL", you know.
So.

## Wrapper implementation
My path follows [LazyFoo SDL2.0 tutorial](http://lazyfoo.net/tutorials/SDL/); I'm implementing wrappers along the way.
At the end of each lesson, someone should be able to write the code only with stuff from `SDLpp` namespace.
- [X] Getting an image on the screen [(!)](http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php)
- [X] Event Driven Programming [(!)](http://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php)
- [X] Key Presses [(!)](http://lazyfoo.net/tutorials/SDL/04_key_presses/index.php)
  - [X] Poll event
  - [X] SDL_Event
- [ ] Optimized Surface Loading and Soft Stretching [(!)](http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php)
- [ ] Extension Libraries and Loading Other Image Formats [(!)](http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
- [ ] Texture loading and rendering [(!)](http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php)
- [ ] Geometry rendering [(!)](http://lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php)
- [ ] The viewport [(!)](http://lazyfoo.net/tutorials/SDL/09_the_viewport/index.php)
- [ ] Color keying [(!)](http://lazyfoo.net/tutorials/SDL/10_color_keying/index.php)
- [ ] Clip rendering and sprite sheets [(!)](http://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php)
- [ ] Color modulation [(!)](http://lazyfoo.net/tutorials/SDL/12_color_modulation/index.php)
- [ ] Alpha blending [(!)](http://lazyfoo.net/tutorials/SDL/13_alpha_blending/index.php)
- [ ] Animated sprites and vsync [(!)](http://lazyfoo.net/tutorials/SDL/14_animated_sprites_and_vsync/index.php)
- [ ] Rotation and flipping [(!)](http://lazyfoo.net/tutorials/SDL/15_rotation_and_flipping/index.php)
- [ ] And other more...

## Design implementation
- [X] Change `std::optional` with `tl::optional`
- [ ] Use `tl::expected` where needed
  - [ ] Make error codes and exceptions
  - [ ] New namespace for throwing | nonthrowing functions
