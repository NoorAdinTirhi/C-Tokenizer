#!/bin/bash

# Define directory
directory="test"
ref_dir="$directory/ref"
tmp_dir="$directory/tmp"
diff_dir="$directory/diff"
bin_path="bin/run"
if [ ! -f "$bin_path" ]; then
    echo "binary file does not exits, build before running regression" 
    exit 1
fi


mkdir "$tmp_dir"

if [ ! -d "$diff_dir" ]; then
    mkdir "$diff_dir"
fi

rm -rf $diff_dir/*

bad_tests=();

# Loop through files
for file in "$directory"/*; do
    if [ -f "$file" ]; then
        real_path="$(realpath --relative-to="$directory" "$file")"
        $("$bin_path" -i "$file" -o "$tmp_dir/$real_path.log")
        difference=$(diff "$ref_dir/$real_path.log" "$tmp_dir/$real_path.log")   
        if [ ! -z "$difference" ]; then
            bad_tests+=("$file")
            echo "$difference" > "$diff_dir/$real_path.log"
        fi
    fi
done

if [ ! -z $bad_tests ]; then
    echo "faling lists : "
    for item in "${bad_tests[@]}"; do
        echo "$item"
    done
else
    echo "all tests passed succesfully!!!!"
fi




rm -rf "$tmp_dir"