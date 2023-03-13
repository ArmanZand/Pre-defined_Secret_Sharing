#!/bin/bash

paste_path=../networking/

protoc -I=. --cpp_out=. *.proto --experimental_allow_proto3_optional

for cc_file in *.cc
do
    echo Copying $cc_file to $paste_path$cc_file
    cp $cc_file $paste_path$cc_file
done

for h_file in *.h
do
    echo Copying $h_file to $paste_path$h_file
    cp $h_file $paste_path$h_file
done
read -p "Press Enter to end."