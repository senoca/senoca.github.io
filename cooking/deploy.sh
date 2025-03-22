#!/bin/bash

# Navigate to the cooking directory
cd "$(dirname "$0")"

echo "Building Hugo site..."
hugo

# Check if the build was successful
if [ $? -ne 0 ]; then
    echo "Hugo build failed! Exiting."
    exit 1
fi

echo "Copying files to parent directory..."
cp -r public/* ../cooking/

echo "Done! Don't forget to commit and push your changes."
