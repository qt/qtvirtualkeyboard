// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

.pragma library

function findChildByProperty(parent, propertyName, propertyValue, compareCb) {
    var obj = null
    if (parent === null)
        return null
    var children = parent.children
    for (obj of children) {
        if (obj.hasOwnProperty(propertyName)) {
            if (compareCb !== null) {
                if (compareCb(obj[propertyName], propertyValue))
                    break
            } else if (obj[propertyName] === propertyValue) {
                break
            }
        }
        obj = findChildByProperty(obj, propertyName, propertyValue, compareCb)
        if (obj)
            break
    }
    return obj
}

function findChild(parent, param, matchCb) {
    var obj = null
    if (parent === null)
        return null
    var children = parent.children
    for (obj of children) {
        if (matchCb(obj, param))
            break
        obj = findChild(obj, param, matchCb)
        if (obj)
            break
    }
    return obj
}

function toUnicodeHex(str) {
    var result = ''
    for (var i = 0; i < str.length; i++) {
        if (result.length > 0)
            result += ", "
        result += "U+" + ("000" + str.charCodeAt(i).toString(16)).slice(-4)
    }
    return result
}
