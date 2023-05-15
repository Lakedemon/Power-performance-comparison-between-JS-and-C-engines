#!/bin/bash

sudo sysctl -w kernel.perf_event_paranoid=0
cat /proc/sys/kernel/perf_event_paranoid

n=100
duration_between_runs=60


targets=(
  "/home/leonint.amarantos/Documents/JS_engine/python3 server.py --scenario Scenario1"
  "/home/leonint.amarantos/Documents/JS_engine/python3 server.py --scenario Scenario2"
  "/home/leonint.amarantos/Documents/JS_engine/python3 server.py --scenario Scenario3"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario1_build/./OpenGLEngine"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario2_build/./OpenGLEngine"
  "/home/leonint.amarantos/Documents/C++_engine/Scenario3_build/./OpenGLEngine"
)

new_dir_names=(
  "JS_low"
  "JS_mid"
  "JS_high"
  "CPP_low"
  "CPP_mid"
  "CPP_high"
)

data_dir="/home/leonint.amarantos/Documents/LA_BSPS2_Data_Collection"


for j in "${!targets[@]}"; do
  mkdir -p $data_dir/${new_dir_names[$j]}

  target="${targets[$j]}"
  target_dir="${target_directories[$j]}"
  
  echo "Running perf stat on $target_dir/$target..."
  cd $target_dir

  for (( i=1; i<=n; i++ )); do
    perf stat -a -o $data_dir/${new_dir_names[$j]}/"perf_output_${i}.txt" -e /power/energy-pkg/,/power/energy-ram/ $target
    sleep $duration_between_runs
  done
done
