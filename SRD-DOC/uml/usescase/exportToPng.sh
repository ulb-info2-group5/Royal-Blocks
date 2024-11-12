#!/bin/bash

for d in */ ; do 
  java -jar plantum.jar *.plantuml
done 

