# BSP-2023-S2-Leonint-Power-performance-comparison-between-JS-and-C-engines
This repository is a part of a bachelor project completed in the University of luxembourg. 

The project is focused on conducting energy and time benchmarks, comparing C++ and JavaScript in their performance in graphical applications. The project includes development of the test subjects, benchmarking environment and data analysis. The following are the components of this package:
* JS_engine - JavaScript 3D engine.
* C++_engine - C++ 3D engine.
* Main - Contains the steps needed to be taken to reproduce the experiment, using provided tools as well as [data](experiment_results) produced in the experiment.

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

Benchmarks are recorded with the perf stat tool available on linux distributions.
The following installs the collection of tools, perf is part of if it happends to be missing.
```shell
sudo apt-get install linux-tools-generic
```

The comands run on the C++ and JS engines are respectively following:
```shell
perf stat -a -o <your output file name> -e /power/energy-pkg/,/power/energy-ram/ <C++ engine build path>./OpenGLEngine
perf stat -a -o <your output file name> -e /power/energy-pkg/,/power/energy-ram/ <JS engine build path> python3 server.py --scenario <your selected scenario>
```

The C++ engine must be first built with cmake, in order to produce an executable file, for how refer to [C++ Engine setup](#c-engine-environment-setuplinux)
The JS engine does not need to be build in order to be run and supports flags "--scenaro" that allow the user to select the scene/scenario that is launched from the assets folder

The described process is automated with the following [script](perf_automation.sh).
When using make sure to edit if needed for the experiment:
* n - number of repetitions that script runs for each of the scenario.
* duration_between runs - time that a machine will sleep(to cool down) for in seconds.
* targets - a list of targets perf stat is run on
* new_dir_names - names of the dirrectories test result is stored in, required for data analysis part, the format is following "[JS/CPP]_[low/mid/high]"

Make the script executable and run it with following:
```shell
chmod -x ./perf_automation.sh
./perf_automation.sh
```

## Parsing perf stat data

The following python [script](perf_parser.py) organises the collected in the [experiment](#benchmarkingperf-stat) in a single .csv file, well suited for data analysis.

Set the following parameters if you make changes in the project design:
* data_dir - directory with perf stat files
* parsed_data_name - file name for the resulting .csv file

## Statistical analysis

The following R [script](statistical_analysis.R) contains the following steps:
* lines 1-7 - Loading and orginise data
* lines 10-20 - Kollmogorov-Smirnov goodnes of fit.
* lines 25-48 - Significance t-test.
* lines 52-74 - Bar plot of the data.

R script was run in the R studio. A the script is modular you can chose to only run some of the described above points, only lines 1-7 are required.