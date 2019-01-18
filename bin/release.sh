#!/bin/sh

cd "$(dirname $0)"/..

# Require password up front
sudo true

bin/build.sh release

sudo install -v -o gsc -m 4555 build.release/gscd-fcgi server_root/gscd.fcgi
sudo service apache2 restart
