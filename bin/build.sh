#!/bin/sh

cd "${0%/*}"
. ./setup-build-env.sh
cd ..

case "$1" in
    debug)
        cmake_type=Debug
        ;;
    release)
        cmake_type=Release
        ;;
    *)
        echo >&2 "Usage: $0 [ debug | release ] TARGETS..."
        exit 1
        ;;
esac

build_dir=build.$1
shift

cmake -S . -B $build_dir -DCMAKE_BUILD_TYPE=$cmake_type
cmake --build $build_dir --target "$@" -- -j 4
chmod -R a+rX $build_dir
