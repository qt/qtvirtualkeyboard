#!/bin/bash
#******************************************************************************
#**
#** Copyright (C) 2019 The Qt Company Ltd.
#** Contact: https://www.qt.io/licensing/
#**
#** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
#**
#** $QT_BEGIN_LICENSE:GPL$
#** Commercial License Usage
#** Licensees holding valid commercial Qt licenses may use this file in
#** accordance with the commercial license agreement provided with the
#** Software or, alternatively, in accordance with the terms contained in
#** a written agreement between you and The Qt Company. For licensing terms
#** and conditions see https://www.qt.io/terms-conditions. For further
#** information use the contact form at https://www.qt.io/contact-us.
#**
#** GNU General Public License Usage
#** Alternatively, this file may be used under the terms of the GNU
#** General Public License version 3 or (at your option) any later version
#** approved by the KDE Free Qt Foundation. The licenses are as published by
#** the Free Software Foundation and appearing in the file LICENSE.GPL3
#** included in the packaging of this file. Please review the following
#** information to ensure the GNU General Public License requirements will
#** be met: https://www.gnu.org/licenses/gpl-3.0.html.
#**
#** $QT_END_LICENSE$
#**
#****************************************************************************/

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
