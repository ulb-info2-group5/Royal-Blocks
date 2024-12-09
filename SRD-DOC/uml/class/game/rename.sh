#!/bin/bash

new_word='Class'

for file in *.plantuml; do 
  new_name="${file/$old_word/$old_world+$new_word}"
  echo "$file" "$new_name"
done


