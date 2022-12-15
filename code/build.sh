#!/bin/bash
custom/bin/buildsuper_x64-linux.sh custom/custom_layer.cpp
mv ../build/custom_4coder.so ../build/COPYcustom_4coder.so
cp custom_4coder.so ../build/custom_4coder.so
