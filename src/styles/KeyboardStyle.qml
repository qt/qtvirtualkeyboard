/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick

/*!
    \qmltype KeyboardStyle
    \inqmlmodule QtQuick.VirtualKeyboard.Styles
    \brief Provides a styling interface for the Virtual Keyboard.
    \ingroup qtvirtualkeyboard-styles-qml

    The style type provides the style definitions that are used by
    the InputPanel to decorate the virtual keyboard.

    The design size specifies the aspect ratio of the virtual keyboard.
    Styles are scalable according to \l scaleHint, which is
    calculated from the keyboard's actual height and design height.
*/

QtObject {
    /*! The current height of the keyboard. */
    property real keyboardHeight

    /*! The design width of the keyboard. */
    property real keyboardDesignWidth

    /*! The design height of the keyboard. */
    property real keyboardDesignHeight

    /*! The keyboard style scale hint. This value is determined by dividing
        \l keyboardHeight by \l keyboardDesignHeight. All pixel
        dimensions must be proportional to this value.
    */
    readonly property real scaleHint: keyboardHeight / keyboardDesignHeight

    /*!
        The distance between the left-most keys and the left edge of the
        keyboard, expressed as a percentage (\c 0.0 - \c 1.0) of the keyboard's
        width.
    */
    property real keyboardRelativeLeftMargin: 0

    /*!
        The distance between the right-most keys and the right edge of the
        keyboard, expressed as a percentage (\c 0.0 - \c 1.0) of the keyboard's
        width.

        This value is proportional to the keyboard's width.
    */
    property real keyboardRelativeRightMargin: 0

    /*!
        The distance between the top-most keys and the top edge of the
        keyboard, expressed as a percentage (\c 0.0 - \c 1.0) of the keyboard's
        height.
    */
    property real keyboardRelativeTopMargin: 0

    /*!
        The distance between the bottom-most keys and the bottom edge of the
        keyboard container, expressed as a percentage (\c 0.0 - \c 1.0) of the
        keyboard's height.
    */
    property real keyboardRelativeBottomMargin: 0

    /*! Template for the keyboard background.

        Example:
        \code
        keyboardBackground: Rectangle {
            color: "black"
        }
        \endcode
    */
    property Component keyboardBackground: null

    /*! Template for the regular keys.

        \note The delegate must be based on the KeyPanel type.

        Example:
        \code
        keyPanel: KeyPanel {
            Rectangle {
                anchors.fill: parent
                ...
                Text {
                    anchors.fill: parent
                    text: control.displayText
                    ...
                }
            }
        }
        \endcode
    */
    property Component keyPanel: null

    /*! Template for the backspace key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component backspaceKeyPanel: null

    /*! Template for the language key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component languageKeyPanel: null

    /*! Template for the enter key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component enterKeyPanel: null

    /*! Template for the hide key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component hideKeyPanel: null

    /*! Template for the shift key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component shiftKeyPanel: null

    /*! Template for the space key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component spaceKeyPanel: null

    /*! Template for the symbol mode key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component symbolKeyPanel: null

    /*! Template for the generic mode key.

        This template provides a visualization of the key in which the state
        can be on or off. This template is used in situations where the key label
        will remain the same regardless of status.

        The current state is available in the \c control.mode property.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component modeKeyPanel: null

    /*! Template for the handwriting mode key.

        \note The delegate must be based on the KeyPanel type.
    */
    property Component handwritingKeyPanel: null

    /*!
        Number of pixels between the top of each key and the bottom of the
        characterPreviewDelegate.
    */
    property real characterPreviewMargin: 0

    /*! Template for the character preview popup.

        If the delegate contains the \c text property, the property is updated
        with the display text when the component becomes active.

        \code
        property string text
        \endcode

        Example:
        \code
        characterPreviewDelegate: Item {
            property string text
            id: characterPreview
            Rectangle {
                id: characterPreviewBackground
                anchors.fill: parent
                ...
                Text {
                    text: characterPreview.text
                    anchors.fill: parent
                    ...
                }
            }
        }
        \endcode
    */
    property Component characterPreviewDelegate: null

    /*! Width of the alternate keys list item. */
    property real alternateKeysListItemWidth: 0

    /*! Height of the alternate keys list item. */
    property real alternateKeysListItemHeight: 0

    /*! Top margin for the alternate keys list panel. */
    property real alternateKeysListTopMargin: 0

    /*! Bottom margin for the alternate keys list panel. */
    property real alternateKeysListBottomMargin: 0

    /*! Left margin for the alternate keys list panel. */
    property real alternateKeysListLeftMargin: 0

    /*! Right margin for the alternate keys list panel. */
    property real alternateKeysListRightMargin: 0

    /*! Template for the alternative keys list item.

        \note The delegate is used in a \l ListView.
    */
    property Component alternateKeysListDelegate: null

    /*! Template for the alternative keys list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component alternateKeysListHighlight: null

    /*! Template for the alternative keys list background. */
    property Component alternateKeysListBackground: null

    /*! Selection list height. */
    property real selectionListHeight: 0

    /*! Template for the selection list item.

        \note The delegate is used in a \l ListView.
        \note The delegate must be based on the \l SelectionListItem type.

        The following properties are available to the item:
        \list
            \li \c display Display text for the current item.
            \li \c wordCompletionLength Word completion length measured from the end of the display text.
            \li \c dictionary Dictionary type of the word, see QVirtualKeyboardSelectionListModel::DictionaryType.
            \li \c canRemoveSuggestion A boolean indicating if the word can be removed from dictionary.
        \endlist
    */
    property Component selectionListDelegate: null

    /*! Template for the selection list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component selectionListHighlight: null

    /*! Template for the selection list background. */
    property Component selectionListBackground: null

    /*! \since QtQuick.VirtualKeyboard.Styles 1.3

        This property holds the transition to apply to items that
        are added to the selection list view.
    */
    property Transition selectionListAdd

    /*! \since QtQuick.VirtualKeyboard.Styles 1.3

        This property holds the transition to apply to items that
        are removed from the selection list view.
    */
    property Transition selectionListRemove

    /*!
        \since QtQuick.VirtualKeyboard.Styles 1.1

        Template for the navigation highlight item.

        This item is used in \l {Configuration Options}{arrow-key-navigation}
        mode to highlight the navigation focus on the keyboard.

        The item is typically a transparent rectangle with a
        high contrast border.
    */
    property Component navigationHighlight: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the trace input key.

        \note The delegate must be based on the TraceInputKeyPanel type.
    */
    property Component traceInputKeyPanelDelegate: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for rendering a Trace object.

        \note The delegate must be based on the TraceCanvas type.
    */
    property Component traceCanvasDelegate: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the popup list item.

        \note The delegate is used in a \l ListView.
        \note The delegate must be based on the \l SelectionListItem type.

        The following properties are available to the item:
        \list
            \li \c display Display text for the current item.
            \li \c wordCompletionLength Word completion length measured from the end of the display text.
            \li \c dictionary Dictionary type of the word, see QVirtualKeyboardSelectionListModel::DictionaryType.
            \li \c canRemoveSuggestion A boolean indicating if the word can be removed from dictionary.
        \endlist
    */
    property Component popupListDelegate: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the popup list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component popupListHighlight: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the popup list background.
    */
    property Component popupListBackground: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        This property holds the transition to apply to items that
        are added to the popup list view.
    */
    property Transition popupListAdd

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        This property holds the transition to apply to items that
        are removed from the popup list view.
    */
    property Transition popupListRemove

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        This property determines whether a popup list will be shown when the
        language key is clicked. If this property is \c false, clicking the
        language key cycles through the available languages one at a time.

        The default value is \c false.
    */
    property bool languagePopupListEnabled: false

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the language list item.

        \note The delegate is used in a \l ListView.
        \note The delegate must be based on the \l SelectionListItem type.

        The following properties are available to the item:
        \list
            \li \c displayName Display name of the language.
        \endlist
    */
    property Component languageListDelegate: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the language list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component languageListHighlight: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        Template for the language list background.
    */
    property Component languageListBackground: null

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        This property holds the transition to apply to items that
        are added to the language list view.
    */
    property Transition languageListAdd

    /*! \since QtQuick.VirtualKeyboard.Styles 2.1

        This property holds the transition to apply to items that
        are removed from the language list view.
    */
    property Transition languageListRemove

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.1

        This item is used to indicate where the bounds of the text selection is
        and to be able to interactively move the start or end of the selection.
        The same item is used for both start and end selection.

        Selection handles are currently only supported for the
        \l {Integration Method}{application-based integration method}.
    */
    property Component selectionHandle: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the delegate for the background of the full screen
        input container.
    */
    property Component fullScreenInputContainerBackground: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the delegate for the background of the full screen
        input.
    */
    property Component fullScreenInputBackground: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the margins around the full screen input field.

        The default value is \c 0.
    */
    property real fullScreenInputMargins: 0

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the padding around the full screen input content.

        The default value is \c 0.
    */
    property real fullScreenInputPadding: 0

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the delegate for the cursor in the full screen input
        field.

        The delegate should toggle the visibility of the cursor according to
        the \c {parent.blinkStatus} property defined for the full screen input
        field. For example:

        \code
        fullScreenInputCursor: Rectangle {
            width: 1
            color: "#000"
            visible: parent.blinkStatus
        }
        \endcode
    */
    property Component fullScreenInputCursor: null

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the \c font for the full screen input field.
    */
    property font fullScreenInputFont

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the password mask character for the full screen
        input field.
    */
    property string fullScreenInputPasswordCharacter: "\u2022"

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the text color for the full screen input field.

        The default color is black.
    */
    property color fullScreenInputColor: "#000"

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the selection color for the full screen input
        field.

        The default color is semi-transparent black.
    */
    property color fullScreenInputSelectionColor: Qt.rgba(0, 0, 0, 0.15)

    /*!
        \since QtQuick.VirtualKeyboard.Styles 2.2

        This property holds the selected text color for the full screen input
        field.

        The default color is set to \c fullScreenInputColor.
    */
    property color fullScreenInputSelectedTextColor: fullScreenInputColor

    /*! \since QtQuick.VirtualKeyboard.Styles 6.2

        Template for the function list item.

        \note The delegate is used in a \l ListView.

        The following properties are available to the item:
        \list
            \li \c keyboardFunction - Keyboard function of the current item.
        \endlist
    */
    property Component functionPopupListDelegate: null

    /*! \since QtQuick.VirtualKeyboard.Styles 6.2

        Template for the function popup list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component functionPopupListHighlight: null

    /*! \since QtQuick.VirtualKeyboard.Styles 6.2

        Template for the function popup list background.
    */
    property Component functionPopupListBackground: null
}
