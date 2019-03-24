/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
**
** This file is part of QtGoogleAssistant.
**
** QtGoogleAssistant is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtGoogleAssistant is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtGoogleAssistant. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef QGOOGLEASSISTANTAUDIOOUTPUT_H
#define QGOOGLEASSISTANTAUDIOOUTPUT_H

#include <QtCore/qobject.h>
#include <QtMultimedia/qaudioformat.h>
#include <QtMultimedia/qaudiodeviceinfo.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantAudioOutputPrivate;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudioOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QAudioFormat format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QAudioDeviceInfo device READ device WRITE setDevice NOTIFY deviceChanged)

public:
    explicit QGoogleAssistantAudioOutput(QObject *parent = nullptr);

    bool isEnabled() const;

    QAudioFormat format() const;
    void setFormat(const QAudioFormat &format);

    QAudioDeviceInfo device() const;
    void setDevice(const QAudioDeviceInfo &device);

public Q_SLOTS:
    void setEnabled(bool enabled);
    void enable();
    void disable();
    void output(const QByteArray &data);

Q_SIGNALS:
    void enabledChanged(bool enabled);
    void formatChanged(const QAudioFormat &format);
    void deviceChanged(const QAudioDeviceInfo &device);

private:
    Q_DISABLE_COPY(QGoogleAssistantAudioOutput)
    Q_DECLARE_PRIVATE(QGoogleAssistantAudioOutput)
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTAUDIOOUTPUT_H
