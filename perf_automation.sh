#!/bin/bash

sudo sysctl -w kernel.perf_event_paranoid=0
cat /proc/sys/kernel/perf_event_paranoid

n=2
duration_between_runs=10

target_directories=(
  "/home/leonint.amarantos/Documents/JS_engine"
  "/home/leonint.amarantos/Documents/JS_engine"
  "/home/leonint.amarantos/Documents/JS_engine"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario1_build"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario2_build"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario3_build"
)

targets=(
  "python3 server.py --scenario Scenario1"
  "python3 server.py --scenario Scenario2"
  "python3 server.py --scenario Scenario3"
  "./OpenGLEngine"
  "./OpenGLEngine"
  "./OpenGLEngine"
)

data_dir="/home/leonint.amarantos/Documents/LA_BSPS2_Data_Collection"


for j in "${!targets[@]}"; do
  mkdir -p $data_dir/target_$j

  target="${targets[$j]}"
  target_dir="${target_directories[$j]}"
  
  echo "Running perf stat on $target_dir/$target..."
  cd $target_dir

  for (( i=1; i<=n; i++ )); do

    perf stat -a -o $data_dir/target_$j/"perf_output_${i}.txt" -e /power/energy-pkg/,/power/energy-ram/ $target
    sleep $duration_between_runs
  done
done
