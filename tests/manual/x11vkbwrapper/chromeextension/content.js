/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

var lastActiveElement = null;
var inputs = ['input', 'textarea'];
var types = ['text', 'password', 'email', 'number', 'search', 'url', 'date', 'tel', 'time'];
var sentValue = 0;

function sendValue(value)
{
    sentValue = value;
    chrome.runtime.sendMessage(sentValue);
}


if (inputs.indexOf(document.activeElement.nodeName.toLowerCase()) !== -1) {
    sendValue(1);
}

function detectBlur()
{
    lastActiveElement = document.activeElement;
    if (sentValue === 1)
    {
        sendValue(0);
    }
}

function isSameActiveElement()
{
    var currentActiveElement = document.activeElement;
    if (lastActiveElement !== currentActiveElement) {
        lastActiveElement = currentActiveElement;
        return false;
    }
    return true;
}

function detectFocus()
{
    if (!isSameActiveElement() &&
      (inputs.indexOf(document.activeElement.nodeName.toLowerCase()) !== -1) &&
      (types.indexOf(document.activeElement.type.toLowerCase()) !== -1))
    {
        sendValue(1);
    }
}

window.onblur = function(e) {
    lastActiveElement = null;
}


function attachEvents()
{
    window.addEventListener ? window.addEventListener('focus', detectFocus, true) : window.attachEvent('onfocusout', detectFocus);
    window.addEventListener ? window.addEventListener('blur', detectBlur, true) : window.attachEvent('onblur', detectBlur);
}

chrome.runtime.onMessage.addListener(function(message) {
    lastActiveElement = null;
    detectFocus();
});

attachEvents();
