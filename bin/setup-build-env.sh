#!/bin/sh

unset CC
unset CXX
unset CFLAGS
unset CXXFLAGS
unset LDFLAGS

case "$(hostname)" in
    stewie)
        CC=clang-8
        CXX=clang++-8
        CXXFLAGS=-stdlib=libstdc++
        LDFLAGS="-lstdc++ -lstdc++fs"
        ;;
esac

export CC
export CXX
export CFLAGS
export CXXFLAGS
export LDFLAGS
