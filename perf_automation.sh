#!/bin/bash

sudo sysctl -w kernel.perf_event_paranoid=0
cat /proc/sys/kernel/perf_event_paranoid

n=100
duration_between_runs=60
BASEDIR="$( cd "$( dirname "$0" )" && pwd )"

target_directories=(
  "$BASEDIR/CPP_engine/Scenario1_build"
  "$BASEDIR/CPP_engine/Scenario2_build"
  "$BASEDIR/CPP_engine/Scenario3_build"
)

targets=(
  "./OpenGLEngine"
  "./OpenGLEngine"
  "./OpenGLEngine"
)

new_dir_names=(
  "CPP_low"
  "CPP_mid"
  "CPP_high"
)

data_dir="$BASEDIR/data_dir"

for j in "${!targets[@]}"; do
  dir_path=$data_dir/${new_dir_names[$j]}
  mkdir -p "${dir_path}"

  target="${targets[$j]}"
  target_dir="${target_directories[$j]}"
  
  echo "Running perf stat on $target_dir/$target..."
  cd $target_dir

  for (( i=1; i<=n; i++ )); do

    perf stat -a -o $dir_path/"perf_output_${i}.txt" -e /power/energy-pkg/,/power/energy-ram/ $target
    sleep $duration_between_runs
  done
done
