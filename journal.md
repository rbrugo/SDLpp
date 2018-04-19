# The project journal
## Or, better, the project's maker logbook
I think there's no a real need to write something like this. It's more like an experiment or a flavor.
I'm going to write here design changes or ideas I'm having for the SDLpp library, since being my first experience I really do not
know what shall I do and I don't have ideas about write this in a tidier way.
This journal shall be maintained in pair with the roadmap to give me a track to follow... So, let's try.

### `expected` and `optional` components and extension by inheritance
#### 20/04/2018
- [ ] `expected` and `optional` components.
    In the sense: every component that should return an object must return an `expected` associated with an error code; every component
    that could return an object must return an `optional`.  
    This approach has some benefits over _classical methods_:
    - stack allocation: `expected` and `optional` allocates their content on stack, improving performance (I think?)
	- clearer interface: there's no `nullptr` for invalid objects, nor `-1` or similar for error codes. Every useful information is
	  carried with the returned object
	Actually, there are issues with this idea: at first, there's no `std::expected` (not yet at least). Second, there's no support for
	`std::optional<T&>`, so I should use `std::optional<std::reference_wrapper<T>>`. But that's ugly.
	So I opted to use @TartanLlama's implementation of [optional][1] and [expected][2].
	They provide me an `expected` type, an `optional<T&>` implementation, and they're also monadic! That's just beautiful.
[1]:https://github.com/TartanLlama/optional
[2]:https://github.com/TartanLlama/expected
- [ ] Extension by inheritance
	There was a problem with SDL_Rect: because it has been written for C lang, it doesn't have any special constructor.
	Actually, something like `SDL_Rect{x, y}` would be great, and `SDL_Rect{}` / `SDL_Rect{x,y,w}` aren't so good to me. (Is this correct
	English? T.T)
	At first I tried making a `SDLpp::rectangle`, a structure encapsulating a `SDL_Rect` and the two constructors. And I was fine with
	this, seeming the best solution to my problem, and I continued this way with other structures like `SDL_Surface`.  
	Yesterday I realized how much I must be silly.  
	**INHERITANCE.**  
	An approach like
	```cpp
	struct rect : public SDL_Rect { ... };
	```
	gives me
	- no need to wrap `SDL_Rect` into a class just to give him some constructors and (maybe) some methods
	- an automatic cast for values and references from a `SDLpp::rect` to a `SDL_Rect`, mantaining compatibility with the SDL API.  
	
	That really seems a better approach to the problem.
	This way it could be possible to statically allocate a surface, replacing the `SDL_FreeSurface` with RAII. It will require some work
	to correctly make the changes, but it might be worth it.
	- [ ] `SDL_Rect`
	- [ ] `SDL_Surface`
	- [ ] `SDL_Window` (maybe?)
