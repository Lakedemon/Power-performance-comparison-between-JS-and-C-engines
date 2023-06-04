# BSP-2023-S2-Leonint-Power-performance-comparison-between-JS-and-C-engines
This repository is a part of a bachelor project completed in the University of luxembourg. 

The project is focused on conducting energy and time benchmarks, comparing C++ and JavaScript in their performance in graphical applications. The project includes development of the test subjects, benchmarking environment and data analysis. The following are the components of this package:
* JavaScript 3D engine (with a hands on demo, see [demo](#demo)).
* C++ 3D engine.
* [Scripts](perf_automation.sh) automating the benchmarking process.
* [Statystical tests](statistical_analysis.R) on collected data.
* [Sample results](experiment_results)
* [Step by step](README.md) replication process of the experiment.
* [SnT report](bics_bsp_s2_2022_leonint_amarantos_overleaf_bsp_SnT_report.pdf) produced with the experiment, that details the design, production and motivation behind the project.

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

The following python [script](perf_parser.py) organises the collected in the [experiment](#benchmarkingperf-stat) results in a single .csv file, well suited for data analysis.

Set the following parameters if you make changes in the project design:
* data_dir - directory with perf stat files
* parsed_data_name - file name for the resulting .csv file

If you would like to skip the data collection yourself samples collected in the original experiment are available in the experiment results [folder](experiment_results).

## Statistical analysis

The following R [script](statistical_analysis.R) contains the following steps:
* lines 1-7 - Loading and orginise data
* lines 12-32 - Shapiro-Wilk goodnes of fit test.
* lines 37-66 - Significance test.
* lines 79-92 - Bar plot of the data.

R script was run in the RStudio. A the script is modular you can chose to only run some of the described above points, only lines 1-7 are required.

## Demo

For a demonstration of the real use case of the engines follow [The JavaScript environment sutup](#javascript-engine-environment-setuplinux). Then launch the application with the following comand and flag:
``` shell
python3 server.py --scenario ShapeMuseum
```

Then use ```WASD``` keys and a mouse to navigate around the screen.