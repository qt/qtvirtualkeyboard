/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

import QtQuick 2.0

/*!
    Style definitions for the Virtual Keyboard.
*/

QtObject {
    /*! Actual keyboard height set by keyboard when style is loaded. */
    property real keyboardHeight
    /*! Design width of this keyboard style. */
    property real keyboardDesignWidth
    /*! Design height of this keyboard style. */
    property real keyboardDesignHeight
    /*! Scale hint for keyboard style. All sizable elements should be scaled according to this value. */
    readonly property real scaleHint: keyboardHeight / keyboardDesignHeight
    /*! Left margin for keyboard. */
    property real keyboardRelativeLeftMargin: 0
    /*! Right margin for keyboard. */
    property real keyboardRelativeRightMargin: 0
    /*! Top margin for keyboard. */
    property real keyboardRelativeTopMargin: 0
    /*! Bottom margin for keyboard. */
    property real keyboardRelativeBottomMargin: 0
    /*! Delegate for keyboard background. */
    property Component keyboardBackground: null
    /*! Delegate for regular key. */
    property Component keyPanel: null
    /*! Delegate for backspace key. */
    property Component backspaceKeyPanel: null
    /*! Delegate for language key. */
    property Component languageKeyPanel: null
    /*! Delegate for enter key. */
    property Component enterKeyPanel: null
    /*! Delegate for hide key. */
    property Component hideKeyPanel: null
    /*! Delegate for shift key. */
    property Component shiftKeyPanel: null
    /*! Delegate for space key. */
    property Component spaceKeyPanel: null
    /*! Delegate for symbol key. */
    property Component symbolKeyPanel: null
    /*! Margin between key and character preview panel. */
    property real characterPreviewMargin: 0
    /*! Delegate for character preview popup. */
    property Component characterPreviewDelegate: null
    /*! Width of the alternate keys list item. */
    property real alternateKeysListItemWidth: 0
    /*! Height of the alternate keys list item. */
    property real alternateKeysListItemHeight: 0
    /*! Top margin alternate keys list panel. */
    property real alternateKeysListTopMargin: 0
    /*! Bottom margin alternate keys list panel. */
    property real alternateKeysListBottomMargin: 0
    /*! Left margin for alternate keys list panel. */
    property real alternateKeysListLeftMargin: 0
    /*! Right margin for alternate keys list panel. */
    property real alternateKeysListRightMargin: 0
    /*! Delegate for alternate keys list item. */
    property Component alternateKeysListDelegate: null
    /*! Delegate for alternate keys list highlight. */
    property Component alternateKeysListHighlight: null
    /*! Delegate for alternate keys list background. */
    property Component alternateKeysListBackground: null
    /*! Selection list height. */
    property real selectionListHeight: 0
    /*! Delegate for selection list item. */
    property Component selectionListDelegate: null
    /*! Delegate for selection list highlight. */
    property Component selectionListHighlight: null
    /*! Delegate for selection list background. */
    property Component selectionListBackground: null
}
