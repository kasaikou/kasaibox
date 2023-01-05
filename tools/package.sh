#!/bin/sh

cd `dirname $0`/..
mkdir ./kasaibox

# dependency modules
mkdir ./kasaibox/dependencies
cp ./libs/bin/opencv_world460.dll \
    ./libs/bin/ncnn.dll \
    ./kasaibox/dependencies

cp ./Release/kasaibox.dll \
    ./@かさいボックス.anm \
    ./README.md \
    ./kasaibox
