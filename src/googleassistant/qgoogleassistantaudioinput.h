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

#ifndef QGOOGLEASSISTANTAUDIOINPUT_H
#define QGOOGLEASSISTANTAUDIOINPUT_H

#include <QtCore/qobject.h>
#include <QtMultimedia/qaudioformat.h>
#include <QtMultimedia/qaudiodeviceinfo.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantAudioInputPrivate;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudioInput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(Level level READ level NOTIFY levelChanged)
    Q_PROPERTY(qreal volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(qreal threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged)
    Q_PROPERTY(QAudioFormat format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QAudioDeviceInfo device READ device WRITE setDevice NOTIFY deviceChanged)

public:
    explicit QGoogleAssistantAudioInput(QObject *parent = nullptr);

    bool isActive() const;
    bool isEnabled() const;

    enum Level { Low, High };
    Q_ENUM(Level)

    Level level() const;
    qreal volume() const;

    int timeout() const;
    void setTimeout(int timeout);

    qreal threshold() const;
    void setThreshold(qreal threshold);

    QAudioFormat format() const;
    void setFormat(const QAudioFormat &format);

    QAudioDeviceInfo device() const;
    void setDevice(const QAudioDeviceInfo &device);

public Q_SLOTS:
    void setEnabled(bool enabled);
    void enable();
    void disable();

Q_SIGNALS:
    void begin();
    void end();
    void input(const QByteArray &data);
    void activeChanged(bool active);
    void enabledChanged(bool enabled);
    void levelChanged(Level level);
    void volumeChanged(qreal volume);
    void timeoutChanged(int timeout);
    void thresholdChanged(qreal threshold);
    void formatChanged(const QAudioFormat &format);
    void deviceChanged(const QAudioDeviceInfo &device);

private:
    Q_DISABLE_COPY(QGoogleAssistantAudioInput)
    Q_DECLARE_PRIVATE(QGoogleAssistantAudioInput)
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTAUDIOINPUT_H
