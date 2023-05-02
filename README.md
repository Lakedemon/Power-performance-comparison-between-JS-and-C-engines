# BSP-2023-S2-Leonint-Power-performance-comparison-between-JS-and-C-engines
Bachelor project focused on comparing efficiency of 3D engines based on their programming language

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
cmake -S ./ -B ./Build
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

## JavaScript Engine environment setup(Linux)

Install google-chrome-stable for the WebGL context:
```shell
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb
```

Change the instalation in **server.py** file if different from "/usr/bin/google-chrome-stable"
```
ChromePath = "/path/to/your/google-chrome-stable"
```

Test the setup with following:
```
python3 server.py
```
To confirm correct setup programm must: 
1. Launch an html page in a new google chrome window
2. ~30-60 seconds later close the google chrome window
3. Exit the terminal thread

## Benchmarking(perf stat)
