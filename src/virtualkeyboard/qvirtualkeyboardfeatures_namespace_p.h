// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDFEATURES_NAMESPACE_P_H
#define QVIRTUALKEYBOARDFEATURES_NAMESPACE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QMetaEnum>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/private/qtvirtualkeyboardexports_p.h>
#include <QtVirtualKeyboard/private/qtvirtualkeyboard-config_p.h>

QT_BEGIN_NAMESPACE

namespace QVirtualKeyboardFeatures {

Q_VIRTUALKEYBOARD_PRIVATE_EXPORT Q_NAMESPACE
QML_NAMED_ELEMENT(VirtualKeyboardFeatures)
QML_ADDED_IN_VERSION(6, 4)

enum Feature {
    Handwriting =
#if QT_CONFIG(cerence_hwr) || QT_CONFIG(myscript) || QT_CONFIG(example_hwr)
         1
#else
         0
#endif
     // possibly extend for other things you may want to detect in the future
};
Q_ENUM_NS(Feature)

} // namespace QVirtualKeyboardFeatures

QT_END_NAMESPACE

#endif // QVIRTUALKEYBOARDFEATURES_NAMESPACE_P_H
