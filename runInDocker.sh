#!/bin/bash
set -ex
docker build -t per-pixel-graphics-image .
docker run --rm -it -e DISPLAY -v $XAUTHORITY:/root/.Xauthority --net=host --name per-pixel-graphics-container per-pixel-graphics-image 
