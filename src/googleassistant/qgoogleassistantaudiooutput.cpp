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

#include "qgoogleassistantaudiooutput.h"
#include "qgoogleassistantaudiooutput_p.h"
#include "qgoogleassistantaudio.h"
#include "qgoogleassistantaudio_p.h"

#include <QtCore/qloggingcategory.h>
#include <QtMultimedia/qaudiooutput.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcAudioOutput, "qt.googleassistant.audio.output")

void QGoogleAssistantAudioOutputPrivate::reset()
{
    Q_Q(QGoogleAssistantAudioOutput);
    if (audio)
        audio->deleteLater();
    if (!buffer) {
        buffer = QGoogleAssistantAudioPrivate::createBuffer(q);
        buffer->open(QIODevice::ReadWrite);
    }
    if (!device.isNull()) {
        if (!device.isFormatSupported(format)) {
            QAudioFormat unsupported = format;
            format = device.nearestFormat(format);
            qCWarning(lcAudioOutput) << "unsupported format" << unsupported << "- fallback:" << format;
        }
        qCDebug(lcAudioOutput) << "supported codecs:" << device.supportedCodecs();
    }
    audio = new QAudioOutput(device, format, q);
    QObject::connect(audio, &QAudioOutput::stateChanged, [](QAudio::State state) {
        qCDebug(lcAudioOutput) << "state" << state;
    });
}

QGoogleAssistantAudioOutput::QGoogleAssistantAudioOutput(QObject *parent)
    : QObject(*(new QGoogleAssistantAudioOutputPrivate), parent)
{
    setFormat(QGoogleAssistantAudio::defaultFormat());
    setDevice(QAudioDeviceInfo::defaultOutputDevice());
}

bool QGoogleAssistantAudioOutput::isEnabled() const
{
    Q_D(const QGoogleAssistantAudioOutput);
    return d->enabled;
}

void QGoogleAssistantAudioOutput::setEnabled(bool enabled)
{
    Q_D(QGoogleAssistantAudioOutput);
    if (d->enabled == enabled)
        return;

    d->enabled = enabled;
    if (!enabled && d->audio->state() != QAudio::StoppedState)
        d->audio->stop();
    emit enabledChanged(enabled);
}

void QGoogleAssistantAudioOutput::enable()
{
    setEnabled(true);
}

void QGoogleAssistantAudioOutput::disable()
{
    setEnabled(false);
}

void QGoogleAssistantAudioOutput::output(const QByteArray &data)
{
    Q_D(QGoogleAssistantAudioOutput);
    if (!d->enabled)
        return;

    if (d->audio->state() == QAudio::StoppedState)
        d->audio->start(d->buffer);

    qCDebug(lcAudioOutput) << "output" << data.size() << "bytes";
    d->buffer->write(data);
}

QAudioFormat QGoogleAssistantAudioOutput::format() const
{
    Q_D(const QGoogleAssistantAudioOutput);
    return d->format;
}

void QGoogleAssistantAudioOutput::setFormat(const QAudioFormat &format)
{
    Q_D(QGoogleAssistantAudioOutput);
    if (d->format == format)
        return;

    d->format = format;
    d->reset();
    emit formatChanged(format);
}

QAudioDeviceInfo QGoogleAssistantAudioOutput::device() const
{
    Q_D(const QGoogleAssistantAudioOutput);
    return d->device;
}

void QGoogleAssistantAudioOutput::setDevice(const QAudioDeviceInfo &device)
{
    Q_D(QGoogleAssistantAudioOutput);
    if (d->device == device)
        return;

    d->device = device;
    d->reset();
    emit deviceChanged(device);
}

QT_END_NAMESPACE

#include "moc_qgoogleassistantaudiooutput.cpp"
