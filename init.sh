#!/bin/sh

SCR_SERVER_PATH=/var/www/json-docs
if [[ ! -z "${SERVER_PATH}" ]]; then
    SCR_SERVER_PATH="$SERVER_PATH"
fi
echo "Creating the server root directory ($SCR_SERVER_PATH)..."
mkdir -p "$SCR_SERVER_PATH"
mkdir -p "$SCR_SERVER_PATH/jsons"
mkdir -p "$SCR_SERVER_PATH/fcgi"
echo "Copying the script.fcgi to $SCR_SERVER_PATH/fcgi..."
cp build/script.fcgi "$SCR_SERVER_PATH/fcgi"

echo "Creating the user www and adding the current user to www group..."
useradd www
usermod -a -G www $(id -un)

echo "chown'ing and chmod'ing the server root..."
chown -R www:www "$SCR_SERVER_PATH"
chmod -R 0770 "$SCR_SERVER_PATH"

echo "All done!"
