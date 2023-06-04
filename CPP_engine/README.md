## C++ Engine environment setup(Linux)

Get libraries and tools(cmake, g++ compiler, package manager and OpenGL dependecies):

```sh
sudo apt-get update
sudo apt-get install cmake pkg-config build-essential libglew-dev libglfw3-dev libglm-dev libao-dev libmpg123-dev libxinerama-dev libxcursor-dev libxi-dev
```

Get open source OpenGL implementation(GLFW) and configure the cmake:

```sh
cd /usr/local/lib/
sudo git clone https://github.com/glfw/glfw.git
cd glfw
sudo cmake .
sudo make
sudo make install
```

Get GLAD configuration from [GLAD](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.6&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on) and add it to the include folder:

Configuration for glad  is following:

1. Languafe - c/C++
2. Api(gl) - Version 4.6
3. Specification - OpenGL
4. Profile - Core

```sh
wget !!! Get the glad zip url from the provided url by clicking generate !!!
unzip glad.zip
cp -R include/* /usr/include/
```

Test the setup with following:

```sh
cd {your project dirrectory}
g++ hello_triangle.cpp glad.c -ldl -lglfw
```

Compile the repository:
```shell
mkdir ./Build
sudo cmake -S ./ -B ./Build
cd ./Build
make
```

Test the compiled project:
```shell
./OpenGLEngine
```
To confirm correct setup programm must: 
1. Launch a new window
2. ~30-60 seconds later close the window
3. Exit the terminal thread
