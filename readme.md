# Environment setup

Get libraries and tools(cmake, g++ compiler, package manager and OpenGL dependecies):

```sh
apt-get update
apt-get install cmake pkg-config build-essential libglew-dev libglfw3-dev libglm-dev libao-dev libmpg123-dev libxinerama-dev libxcursor-dev libxi-dev
```

Get open source OpenGL implementation(GLFW) and configure the cmake:

```sh
cd /usr/local/lib/
git clone https://github.com/glfw/glfw.git
cmake .
make
make install
```

Get GLAD configuration from https://glad.dav1d.de/#profile=compatibility&language=c&specification=gl&loader=on&api=gl%3D4.6() and add it to the include folder:

```sh
wget !!! Get the glad zip url from the provided url by clicking generate !!!
unzip glad.zip
cp -R include/* /usr/include/
```

Test the setup with following

```sh
cd {your project dirrectory}
g++ hello_triangle.cpp glad.c -ldl -lglfw
```