#!/usr/bin/bash

exname=""
if [ "$1" == "" ]; then
    echo "Name of example, preferrably without whitespace: "
    read exname
else
    exname="$1"
fi

if [ -d "${exname}" ]; then
    echo "Folder with name '${exname}' already exists! Aborting..."
    exit 1
fi

echo "Generating new folder for example called '${exname}'"
mkdir -p ${exname}

echo "Copying template files over..."
cp templates/* "${exname}/"

echo "Setting up environment..."
cd ${exname}
make mkdir
cd ..

echo "Done!"
exit 1
