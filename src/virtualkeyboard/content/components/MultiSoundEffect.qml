/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtMultimedia 5.0

Item {
    id: multiSoundEffect
    property url source
    property int maxInstances: 2
    property var __cachedInstances
    property int __currentIndex: 0

    signal playingChanged(url source, bool playing)

    Component {
        id: soundEffectComp
        SoundEffect {
            source: multiSoundEffect.source
            onPlayingChanged: multiSoundEffect.playingChanged(source, playing)
        }
    }

    onSourceChanged: {
        __cachedInstances = []
        __currentIndex = 0
        if (source != Qt.resolvedUrl("")) {
            var i
            for (i = 0; i < maxInstances; i++) {
                var soundEffect = soundEffectComp.createObject(multiSoundEffect)
                if (soundEffect === null)
                    return
                __cachedInstances.push(soundEffect)
            }
        }
    }

    function play() {
        if (__cachedInstances === undefined || __cachedInstances.length === 0)
            return
        if (__cachedInstances[__currentIndex].playing) {
            __cachedInstances[__currentIndex].stop()
            __currentIndex = (__currentIndex + 1) % __cachedInstances.length
        }
        __cachedInstances[__currentIndex].play()
    }
}
