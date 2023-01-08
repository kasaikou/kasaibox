#!/bin/sh

cd `dirname $0`/..
mkdir ./kasaibox

# dependency modules
mkdir ./kasaibox/dependencies
cp ./libs/bin/opencv_world460.dll \
    ./libs/bin/ncnn.dll \
    ./libs/bin/vulkan-1.dll \
    ./kasaibox/dependencies

cp ./Release/kasaibox.dll \
    ./@かさいボックス.anm \
    ./@かさいボックス.tra \
    ./@かさいボックス.obj \
    ./README.md \
    ./kasaibox

cp -R ./models ./kasaibox
