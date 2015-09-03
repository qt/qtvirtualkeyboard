/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
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

