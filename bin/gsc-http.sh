#!/bin/sh

cd "$(dirname $0)/../server_root"

../build.debug/gsc --docroot ../html --http-address 0.0.0.0 --http-port 9090
