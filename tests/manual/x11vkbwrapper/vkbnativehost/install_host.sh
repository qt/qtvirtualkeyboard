#!/bin/bash
# Copyright (C) 2019 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

set -e
BROWSER=$1
HOST_PATH=$2
HOST_APP_NAME=x11vkbnativehost
HOST_JSON_NAME=x11vkb.host.json

function echo_error_and_exit {
    echo $1
    echo "Use case: ./install_host.sh chromium [or chrome] /full/path/to/executable"
    exit 1
}

if [ "$BROWSER" != "chromium" ]  && [ "$BROWSER" != "chrome" ]; then
    echo_error_and_exit "use chromium or chrome as the first parameter"
fi

if [ ! -f "$HOST_PATH/$HOST_APP_NAME" ]; then
    if [ ! -f "$HOST_PATH" ]; then
        echo_error_and_exit "executable at path $HOST_PATH not found"
    else
        if [ $HOST_APP_NAME == "${HOST_PATH##*/}" ]; then
            HOST_PATH=$(echo $HOST_PATH | rev | cut -d'/' -f2- | rev)
        else
            echo_error_and_exit "executable at path $HOST_PATH/$HOST_APP_NAME not found"
        fi
    fi
fi
HOST_PATH=$(echo $HOST_PATH | sed 's:/*$::')

DIR=$PWD

if [ $BROWSER == "chromium" ]; then
    TARGET_DIR="$HOME/.config/chromium/NativeMessagingHosts"
else
    TARGET_DIR="$HOME/.config/google-chrome/NativeMessagingHosts"
fi

# Create directory to store native messaging host.
mkdir -p "$TARGET_DIR"

# Copy native messaging host manifest.
cp "$DIR/$HOST_JSON_NAME" "$TARGET_DIR"

# Update host path in the manifest.
ESCAPED_HOST_PATH=${HOST_PATH////\\/}

sed -i -e "s/HOST_PATH/$ESCAPED_HOST_PATH/" "$TARGET_DIR/$HOST_JSON_NAME"

# Set permissions for the manifest so that all users can read it.
chmod o+r "$TARGET_DIR/$HOST_JSON_NAME"

echo $HOST_JSON_NAME has been installed.
