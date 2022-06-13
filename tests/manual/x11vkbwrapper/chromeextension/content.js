// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
