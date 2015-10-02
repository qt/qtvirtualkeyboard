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

import QtQuick 2.0

/*!
    \qmltype KeyboardStyle
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Styles
    \brief Provides a styling interface for the Virtual Keyboard.
    \ingroup qtvirtualkeyboard-styles-qml

    The style type provides the style definitions that are used by
    the InputPanel to decorate the virtual keyboard.

    The design size specifies the aspect ratio of the virtual keyboard.
    Styles are scalable according to KeyboardStyle.scaleHint, which is
    calculated from the keyboard's actual height and design height.
*/

QtObject {
    /*! The current size of the keyboard. */
    property real keyboardHeight

    /*! The design width of the keyboard. */
    property real keyboardDesignWidth

    /*! The design height of the keyboard. */
    property real keyboardDesignHeight

    /*! The keyboard style scale hint. This value is determined by the
        physical size and the design size of the keyboard. All pixel
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

        \note The delegate is used as \c ListView.delegate.
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

        \note The delegate is used as \c ListView.delegate.
        \note The delegate must be based on the SelectionListItem type.

        The following properties are available to the item:
        \list
            \li \c display Display text for the current item.
            \li \c wordCompletionLength Word completion length measured from the end of the display text.
        \endlist
    */
    property Component selectionListDelegate: null

    /*! Template for the selection list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component selectionListHighlight: null

    /*! Template for the selection list background. */
    property Component selectionListBackground: null

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 1.3

        This property holds the transition to apply to items that
        are added to the selection list view.
    */
    property Transition selectionListAdd

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 1.3

        This property holds the transition to apply to items that
        are removed from the selection list view.
    */
    property Transition selectionListRemove

    /*!
        \since QtQuick.Enterprise.VirtualKeyboard.Styles 1.1

        Template for the navigation highlight item.

        This item is used in \l {Configuration Options}{arrow-key-navigation}
        mode to highlight the navigation focus on the keyboard.

        The item is typically a transparent rectangle with a
        high contrast border.
    */
    property Component navigationHighlight: null

    /*!
        \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        Template for the trace input key.

        \note The delegate must be based on the TraceInputKeyPanel type.
    */
    property Component traceInputKeyPanelDelegate: null

    /*!
        \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        Template for rendering a Trace object.

        \note The delegate must be based on the TraceCanvas type.
    */
    property Component traceCanvasDelegate: null

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        Template for the popup list item.

        \note The delegate is used as \c ListView.delegate.
        \note The delegate must be based on the SelectionListItem type.

        The following properties are available to the item:
        \list
            \li \c display Display text for the current item.
            \li \c wordCompletionLength Word completion length measured from the end of the display text.
        \endlist
    */
    property Component popupListDelegate: null

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        Template for the popup list highlight.

        \note The delegate is used as \c ListView.highlight.
    */
    property Component popupListHighlight: null

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        Template for the popup list background.
    */
    property Component popupListBackground: null

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        This property holds the transition to apply to items that
        are added to the popup list view.
    */
    property Transition popupListAdd

    /*! \since QtQuick.Enterprise.VirtualKeyboard.Styles 2.0

        This property holds the transition to apply to items that
        are removed from the popup list view.
    */
    property Transition popupListRemove
}
