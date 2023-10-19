// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// ![popup]
Dialog {
    id: languageDialog
    title: "Select Input Language"
    modality: Qt.ApplicationModal

    function show(localeList, currentIndex) {
        languageListModel.clear()
        for (var i = 0; i < localeList.length; i++) {
            languageListModel.append({localeName: localeList[i], displayName: Qt.locale(localeList[i]).nativeLanguageName})
        }
        languageListView.currentIndex = currentIndex
        languageListView.positionViewAtIndex(currentIndex, ListView.Center)
        languageDialog.visible = true
    }

    contentItem: ListView {
        id: languageListView
        model: ListModel {
            id: languageListModel
            function selectItem(index) {
                VirtualKeyboardSettings.locale = languageListModel.get(index).localeName
                languageDialog.visible = false
            }
        }
        delegate: Item {
            id: languageListItem
            width: languageNameTextMetrics.width * 17
            height: languageNameTextMetrics.height + languageListLabel.anchors.topMargin + languageListLabel.anchors.bottomMargin
            Text {
                id: languageListLabel
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: languageNameTextMetrics.height / 2
                anchors.rightMargin: anchors.leftMargin
                anchors.topMargin: languageNameTextMetrics.height / 3
                anchors.bottomMargin: anchors.topMargin
                text: languageNameFormatter.elidedText
                color: "#5CAA15"
                font {
                    weight: Font.Normal
                    pixelSize: 28
                }
            }
            TextMetrics {
                id: languageNameTextMetrics
                font {
                    weight: Font.Normal
                    pixelSize: 28
                }
                text: "X"
            }
            TextMetrics {
                id: languageNameFormatter
                font {
                    weight: Font.Normal
                    pixelSize: 28
                }
                elide: Text.ElideRight
                elideWidth: languageListItem.width - languageListLabel.anchors.leftMargin - languageListLabel.anchors.rightMargin
                text: displayName
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if (index === -1)
                        return
                    parent.ListView.view.currentIndex = index
                    parent.ListView.view.model.selectItem(index)
                }
            }
            states: State {
                name: "current"
                when: languageListItem.ListView.isCurrentItem
                PropertyChanges {
                    target: languageListLabel
                    color: "black"
                }
            }
        }
    }
}
// ![popup]

// ![declaring]
LanguageDialog {
    id: languageDialog
    width: 400
    height: 400
}
// ![declaring]

// ![using]
InputPanel {
    id: inputPanel
    externalLanguageSwitchEnabled: true
    onExternalLanguageSwitch: languageDialog.show(localeList, currentIndex)
    // ...
}
// ![using]
