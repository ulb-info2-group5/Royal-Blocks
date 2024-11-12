#!/bin/bash

for dir in */; do 
  echo $dir
  cd $dir 
  echo *.png
  rm *.png
  plantuml *.plantuml
  cd ..
done
