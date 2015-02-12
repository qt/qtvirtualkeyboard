/****************************************************************************
**
** Copyright (C) 2015 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "declarativetrace.h"
#include <QtCore/private/qobject_p.h>

class DeclarativeTracePrivate : public QObjectPrivate
{
public:
    DeclarativeTracePrivate() :
        QObjectPrivate(),
        traceId(0),
        final(false),
        canceled(false)
    { }

    int traceId;
    QVariantList points;
    QMap<QString, QVariantList> channels;
    bool final;
    bool canceled;
};

/*!
    \class DeclarativeTrace
    \inmodule qtvirtualkeyboard
    \since QtQuick.Enterprise.VirtualKeyboard 1.4
    \brief Trace is a data model for touch input data.

    Trace provides the data model for coordinate data and other
    optional data associated with a single stroke.

    A typical use case for the trace object is as follows:
    \list
        \li TraceInputArea or other input device initiates
            the trace event by calling \l {InputEngine::traceBegin()}
            {InputEngine.traceBegin()} method.
        \li If the current input method accepts the event it creates
            a trace object and configures the required data channels
            (if any).
        \li TraceInputArea collects the data for the Trace object.
        \li TraceInputArea calls the \l {InputEngine::traceEnd()}
            {InputEngine.traceEnd()} method to finish the trace and
            passing the trace object back to input method.
        \li The input method processes the data and discards the object
            when it is no longer needed.
    \endlist

    The coordinate data is retrieved using the points() function.

    In addition to coordinate based data, it is possible
    to attach an arbitrary data channel for each data point.

    The data channels must be defined before the points are added.
    The data channels supported by the TraceInputArea are listed below:

    \list
        \li \c "t" Collects time for each data point. The time is
            the number of milliseconds since 1970/01/01:
    \endlist

    For example, to configure the object to collect the times for
    each point:

    \code
        DeclarativeTrace *trace = new DeclarativeTrace(this);
        trace->setChannels(QStringList() << "t");
    \endcode

    The collected data can be accessed using the channelData() function:

    \code
        QVariantList timeData = trace->channelData("t");
    \endcode

    Trace objects are owned by their creator, which is the input method in
    normal case. This means the objects are constructed in
    \l {AbstractInputMethod::traceBegin()} (C++) or \l {InputMethod::traceBegin()}
    {InputMethod.traceBegin()} (QML) method.

    By definition, the trace object can be destroyed at earliest in the
    \l {AbstractInputMethod::traceEnd()} (C++) or \l {InputMethod::traceEnd()}
    {InputMethod.traceEnd()} (QML) method.
*/

/*!
    \qmltype Trace
    \instantiates DeclarativeTrace
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \since QtQuick.Enterprise.VirtualKeyboard 1.4
    \brief Trace is a data model for touch input data.

    Trace provides the data model for coordinate data and other
    optional data associated with a single stroke.

    A typical use case for the trace object is as follows:
    \list
        \li TraceInputArea or other input device initiates
            the trace event by calling \l {InputEngine::traceBegin()}
            {InputEngine.traceBegin()} method.
        \li If the current input method accepts the event it creates
            a trace object and configures the required data channels
            (if any).
        \li TraceInputArea collects the data for the trace object.
        \li TraceInputArea calls the \l {InputEngine::traceEnd()}
            {InputEngine.traceEnd()} method to finish the trace and
            passing the trace object back to input method.
        \li The input method processes the data and discards the object
            when it is no longer needed.
    \endlist

    The coordinate data is retrieved using the points() function.

    In addition to coordinate based data, it is possible
    to attach an arbitrary data channel for each data point.

    The data channels must be defined before the points are added.
    The data channels supported by the TraceInputArea are listed below:

    \list
        \li \c "t" Collects time for each data point. The time is
            the number of milliseconds since 1970/01/01:
    \endlist

    For example, to configure the object to collect the times for
    each point:

    \code
        DeclarativeTrace *trace = new DeclarativeTrace(this);
        trace->setChannels(QStringList() << "t");
    \endcode

    The collected data can be accessed using the channelData() function:

    \code
        QVariantList timeData = trace->channelData("t");
    \endcode

    Trace objects are owned by their creator, which is the input method in
    normal case. This means the objects are constructed in
    \l {AbstractInputMethod::traceBegin()} (C++) or \l {InputMethod::traceBegin()}
    {InputMethod.traceBegin()} (QML) method.

    By definition, the trace object can be destroyed at earliest in the
    \l {AbstractInputMethod::traceEnd()} (C++) or \l {InputMethod::traceEnd()}
    {InputMethod.traceEnd()} (QML) method.
*/

/*! \internal */
DeclarativeTrace::DeclarativeTrace(QObject *parent) :
    QObject(*new DeclarativeTracePrivate(), parent)
{
}

/*! \internal */
DeclarativeTrace::~DeclarativeTrace()
{
}

int DeclarativeTrace::traceId() const
{
    Q_D(const DeclarativeTrace);
    return d->traceId;
}

void DeclarativeTrace::setTraceId(int id)
{
    Q_D(DeclarativeTrace);
    if (d->traceId != id) {
        d->traceId = id;
        emit traceIdChanged(id);
    }
}

QStringList DeclarativeTrace::channels() const
{
    Q_D(const DeclarativeTrace);
    return d->channels.keys();
}

void DeclarativeTrace::setChannels(const QStringList &channels)
{
    Q_D(DeclarativeTrace);
    Q_ASSERT(d->points.isEmpty());
    if (d->points.isEmpty()) {
        d->channels.clear();
        for (QStringList::ConstIterator i = channels.constBegin();
             i != channels.constEnd(); i++) {
            d->channels[*i] = QVariantList();
        }
        emit channelsChanged();
    }
}

int DeclarativeTrace::length() const
{
    Q_D(const DeclarativeTrace);
    return d->points.size();
}

/*! \qmlmethod var Trace::points(int pos, int count)

    Returns list of points. If no parameters are given, the
    function returns all the points.

    If the \a pos parameter is given, the function returns points starting
    at the position. The \a count parameter limits how many points are
    returned.

    The returned list contains \c point types.
*/

/*! Returns list of points. If no parameters are given, the
    method returns all the data.

    If the \a pos parameter is given, the method returns points starting
    at the position. The \a count parameter limits how many points are
    returned.

    The returned list contains QPointF types.
*/

QVariantList DeclarativeTrace::points(int pos, int count) const
{
    Q_D(const DeclarativeTrace);
    return d->points.mid(pos, count);
}

/*! \qmlmethod int Trace::addPoint(point point)

    Adds a \a point to the Trace.

    The method returns index of the point added, or -1 if
    the points cannot be added (i.e. the isFinal is true).

    \note The returned index is required to associate additional
    data with the point using the setChannelData() function.
*/

/*! Adds a \a point to the Trace.

    The method returns index of the point added, or -1 if
    the points cannot be added (i.e. the isFinal is true).

    \note The returned index is required to associate additional
    data with the point using the setChannelData() method.
*/

int DeclarativeTrace::addPoint(const QPointF &point)
{
    Q_D(DeclarativeTrace);
    int index;
    if (!d->final) {
        index = d->points.size();
        d->points.append(point);
        emit lengthChanged(d->points.size());
    } else {
        index = -1;
    }
    return index;
}

/*! \qmlmethod void Trace::setChannelData(int index, string channel, var data)

    Sets \a data for the point at \a index in the given data \a channel.

    If this method is not called for each data point, the channel data
    will be padded with empty values. However, the data cannot be added at
    arbitrary index, i.e., it must be added in synchronously with the point data.
*/

/*! Sets \a data for the point at \a index in the given data \a channel.

    If this method is not called for each data point, the channel data
    will be padded with empty values. However, the data cannot be added at
    arbitrary index, i.e., it must be added in synchronously with the point data.
*/

void DeclarativeTrace::setChannelData(const QString &channel, int index, const QVariant &data)
{
    Q_D(DeclarativeTrace);
    if (!d->final && (index + 1) == d->points.size() && d->channels.contains(channel)) {
        QVariantList &channelData = d->channels[channel];
        while (index > channelData.size())
            channelData.append(QVariant());
        if (index == channelData.size())
            channelData.append(data);
    }
}

/*! \qmlmethod var Trace::channelData(string channel, int pos, int count)

    Returns data from the specified \a channel. If no other parameters
    are given, the function returns all the data.

    If the \a pos parameter is given, the function returns data starting
    at the position. The \a count parameter limits how many items are
    returned.
*/

/*! Returns data from the specified \a channel. If no other parameters
    are given, the method returns all the data.

    If the \a pos parameter is given, the method returns data starting
    at the position. The \a count parameter limits how many items are
    returned.
*/

QVariantList DeclarativeTrace::channelData(const QString &channel, int pos, int count) const
{
    Q_D(const DeclarativeTrace);
    return d->channels.value(channel).mid(pos, count);
}

bool DeclarativeTrace::isFinal() const
{
    Q_D(const DeclarativeTrace);
    return d->final;
}

void DeclarativeTrace::setFinal(bool final)
{
    Q_D(DeclarativeTrace);
    if (d->final != final) {
        d->final = final;
        emit finalChanged(final);
    }
}

bool DeclarativeTrace::isCanceled() const
{
    Q_D(const DeclarativeTrace);
    return d->canceled;
}

void DeclarativeTrace::setCanceled(bool canceled)
{
    Q_D(DeclarativeTrace);
    if (d->canceled != canceled) {
        d->canceled = canceled;
        emit canceledChanged(canceled);
    }
}

/*! \qmlproperty int Trace::traceId

    Unique id of this Trace.
*/

/*! \property DeclarativeTrace::traceId
    \brief unique id of this Trace.
*/

/*! \qmlproperty list<strings> Trace::channels

    List of additional data channels in the Trace.
    This property must be initialized before the data
    is added.
*/

/*! \property DeclarativeTrace::channels
    \brief list of data channels in the Trace.

    This property must be initialized before the data
    is added.
*/

/*! \qmlproperty int Trace::length

    The number of points in the Trace.
*/

/*! \property DeclarativeTrace::length
    \brief the number of of points in the Trace.
*/

/*! \qmlproperty bool Trace::isFinal

    This property defines whether the Trace can accept more data.
    If the value is true, no more data is accepted.
*/

/*! \property DeclarativeTrace::isFinal
    \brief defines whether the Trace can accept more data.
    If the value is true, no more data is accepted.
*/

/*! \qmlproperty bool Trace::isCanceled

    This property defines whether the Trace is canceled.
    The input data should not be processed from the Traces
    whose isCanceled property set to true.
*/

/*! \property DeclarativeTrace::isCanceled
    \brief defines whether the Trace is canceled.

    The input data should not be processed from the Traces
    whose isCanceled property set to true.
*/
