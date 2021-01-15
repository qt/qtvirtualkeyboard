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

const hostName = "x11vkb.host";
var port = null;
var currentTabId = 0;
var context_id = -1;

chrome.input.ime.onFocus.addListener(function(context) {
  context_id = context.contextID;
});

function sendNativeMessage(message, sender)
{
  if (port) {
    port.postMessage(message);
  }
}

function onDisconnected()
{
  port = null;
}

function connect()
{
  port = chrome.runtime.connectNative(hostName);
  port.onDisconnect.addListener(onDisconnected);
}

chrome.runtime.onStartup.addListener(function() {
  connect();
})

chrome.runtime.onMessage.addListener(sendNativeMessage);

chrome.tabs.onCreated.addListener(function (props) {
//  console.log("onCreated, props.url", props.url)
 });

chrome.tabs.onActiveChanged.addListener(function (props, changeInfo, tab) {
  chrome.tabs.sendMessage(props, "onActive");
 });

chrome.tabs.onUpdated.addListener(function (tabId, changeInfo, tab) {
  if (changeInfo.status == 'complete' && tab.active)
  {
    chrome.tabs.sendMessage(tabId, "onActiveChanged");
  }
 });
