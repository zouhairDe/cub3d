#!/bin/bash

for file in *.c *.h; do
  if [ -e "$file" ]; then
    base_name="${file%.*}"
    extension="${file##*.}"
    
    mv "$file" "${base_name}_bonus.$extension"
    echo "Renamed: $file to ${base_name}_bonus.$extension"
  fi
done
