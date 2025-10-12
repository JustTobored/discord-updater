#!/usr/bin/env bash

set -e
echo "Compiling..."
g++ updater.cpp -o disup
echo "Built complete, run ./disup to run the program"
