# SnakeGL
* SnakeGL Game Engine (SGE) is a cross-platform, except for Mac, which I don't own, 2D game engine that uses OpenGL as its backend, though can easily be ported to other graphics APIs.
* This repository comes with the engine itself (sge part), and a few games made on it (snakegame, etc.).

## Compile & Play
```sh
git clone https://github.com/ivkei/snakegl
cd snakegl/<your_desired_game>
premake5 <your_target>
make config=<your_config_target> # If `gmake` as <your_target>, if `vs2022`, then open the .sln file
```
* For `<your_desired_game>` put a directory name with the game your want to compile, `snakegame` for example.
* The premake5 target may be `gmake`, for make, or `vs2022`, or `xcode`. For people on Windows look inside `vendors/premake5`, there's an executable in case you don't have it installed.
* The make config target may either be `debug` or `release`, debug will create `build/bin` and `build/res`, and release, on top of debug's functionality, will add <game_name>release directory with the game ready to be shipped.

## Credits
* [premake5](https://premake.github.io/)
* [Make](https://www.gnu.org/software/make/)
* [GLM](https://github.com/g-truc/glm)
* [GLFW](https://www.glfw.org/)
* [GLEW](https://github.com/nigels-com/glew)
