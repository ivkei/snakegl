# SnakeGameLibrary
A cross platform, snake game, which is implemented via OpenGL for now, and has a really simple way to port it to other graphics APIs.  
Also implements a really primitive game engine, that's why it's called GameLibrary.  
It runs on Linux and Windows, for Mac premake5.lua's have to to be changed to compile right, and potentially some platform specific source code, I'll appreciate pull requests.  

## Compile & Play
```sh
git clone https://github.com/ivkei/snakegl
cd snakegl
premake5 <your_target>
make config=<your_config_target> # If `gmake` as <your_target>, if `vs2022`, then open the .sln file
```
* The premake5 target may be `gmake`, for make, or `vs2022`, or `xcode`. For people on Windows look inside `vendors/premake5`, there's an executable in case you don't have it installed.
* The make config target may either be `debug` or `release`, debug will create `build/bin` and `build/res`, and release, on top of debug's functionality, will add `build/snakegl/`, which will be directory with the game ready to be shipped.

## Credits
* [premake5](https://premake.github.io/)
* [Make](https://www.gnu.org/software/make/)
* [GLM](https://github.com/g-truc/glm)
* [GLFW](https://www.glfw.org/)
* [GLEW](https://github.com/nigels-com/glew)
