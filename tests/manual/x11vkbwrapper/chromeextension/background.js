// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
