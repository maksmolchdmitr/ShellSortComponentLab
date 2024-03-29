#!/usr/bin/env bash
echo "Build Eco.Lab1"
DIR=$(cd "$(dirname "$0")"; pwd)
echo $DIR

# Добавляем цель "clean" перед билдингом
make -f Makefile clean
make -f MakefileExe clean

export TARGET=0
export DEBUG=0
make -f Makefile
export TARGET=0
export DEBUG=1
make -f Makefile
export TARGET=1
export DEBUG=0
make -f Makefile
export TARGET=1
export DEBUG=1
make -f Makefile
make -f MakefileExe
