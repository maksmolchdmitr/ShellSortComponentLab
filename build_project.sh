#!/usr/bin/env bash
DIR=$(cd "$(dirname "$0")"; pwd)
cd AssemblyFiles/Linux/gcc_7_4_0
bash build.sh
cd "$DIR"