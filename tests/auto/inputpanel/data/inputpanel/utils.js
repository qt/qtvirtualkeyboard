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

.pragma library

function findChildByProperty(parent, propertyName, propertyValue, compareCb) {
    var obj = null
    if (parent === null)
        return null
    var children = parent.children
    for (var i = 0; i < children.length; i++) {
        obj = children[i]
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
    for (var i = 0; i < children.length; i++) {
        obj = children[i]
        if (matchCb(obj, param))
            break
        obj = findChild(obj, param, matchCb)
        if (obj)
            break
    }
    return obj
}
