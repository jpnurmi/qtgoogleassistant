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

/****************************************************************************
**
** This file contains source code that was copied from, or is inspired by,
** the Audio Input example in Qt Multimedia
** (http://doc.qt.io/qt-5/qtmultimedia-multimedia-audioinput-example.html)
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
This file contains source code that was copied from, or is inspired by,
the Google Assistant C++ SDK (https://github.com/googlesamples/assistant-sdk-cpp)

Copyright 2017 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "qgoogleassistantaudioinput.h"
#include "qgoogleassistantaudioinput_p.h"
#include "qgoogleassistantaudio.h"
#include "qgoogleassistantaudio_p.h"

#include <QtCore/qmath.h>
#include <QtCore/qendian.h>
#include <QtCore/qloggingcategory.h>
#include <QtMultimedia/qaudioinput.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcAudioInput, "qt.googleassistant.audio.input")

// For 16000Hz, it's about 0.1 second.
static constexpr int kFramesPerPacket = 1600;
// 1 channel, S16LE, so 2 bytes each frame.
static constexpr int kBytesPerFrame = 2;

void QGoogleAssistantAudioInputPrivate::reset()
{
    Q_Q(QGoogleAssistantAudioInput);
    if (audio)
        audio->deleteLater();
    if (!buffer) {
        buffer = QGoogleAssistantAudioPrivate::createBuffer(q);
        buffer->open(QIODevice::ReadWrite);
        connect(buffer, &QIODevice::readyRead, this, &QGoogleAssistantAudioInputPrivate::probe);
    }
    if (!device.isNull()) {
        if (!device.isFormatSupported(format)) {
            QAudioFormat unsupported = format;
            format = device.nearestFormat(format);
            qCWarning(lcAudioInput) << "unsupported format" << unsupported << "- fallback:" << format;
        }
        qCDebug(lcAudioInput) << "supported codecs:" << device.supportedCodecs();
    }
    audio = new QAudioInput(device, format, q);
    QObject::connect(audio, &QAudioInput::stateChanged, [](QAudio::State state) {
        qCDebug(lcAudioInput) << "state" << state;
    });
}

void QGoogleAssistantAudioInputPrivate::probe()
{
    Q_Q(QGoogleAssistantAudioInput);
    while (buffer->bytesAvailable() >= kBytesPerFrame * kFramesPerPacket) {
        QByteArray data = buffer->read(kBytesPerFrame * kFramesPerPacket);

        if (!enabled || maxAmplitude <= 0)
            return;

        Q_ASSERT(format.sampleSize() % 8 == 0);
        const int channelBytes = format.sampleSize() / 8;
        const int sampleBytes = format.channelCount() * channelBytes;
        const int len = data.length();
        Q_ASSERT(len % sampleBytes == 0);
        const int numSamples = len / sampleBytes;

        quint32 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data.constData());

        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < format.channelCount(); ++j) {
                quint32 value = 0;

                if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
                    value = *reinterpret_cast<const quint8 *>(ptr);
                } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
                    value = qAbs(*reinterpret_cast<const qint8 *>(ptr));
                } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint16>(ptr);
                    else
                        value = qFromBigEndian<quint16>(ptr);
                } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint16>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint16>(ptr));
                } else if (format.sampleSize() == 32 && format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint32>(ptr);
                    else
                        value = qFromBigEndian<quint32>(ptr);
                } else if (format.sampleSize() == 32 && format.sampleType() == QAudioFormat::SignedInt) {
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint32>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint32>(ptr));
                } else if (format.sampleSize() == 32 && format.sampleType() == QAudioFormat::Float) {
                    value = qAbs(*reinterpret_cast<const float *>(ptr) * 0x7fffffff); // assumes 0-1.0
                }

                maxValue = qMax(value, maxValue);
                ptr += channelBytes;
            }
        }

        maxValue = qMin(maxValue, maxAmplitude);

        updateVolume(qreal(maxValue) / maxAmplitude);

        if (active)
            emit q->input(data);
    }
}

static QGoogleAssistantAudioInput::Level volumeLevel(qreal volume, qreal threshold)
{
    return volume > threshold ? QGoogleAssistantAudioInput::High : QGoogleAssistantAudioInput::Low;
}

void QGoogleAssistantAudioInputPrivate::updateVolume(qreal currentVolume)
{
    Q_Q(QGoogleAssistantAudioInput);
    QGoogleAssistantAudioInput::Level currentLevel = volumeLevel(currentVolume, threshold);

    bool levelChange = level != currentLevel;
    bool volumeChange = !qFuzzyCompare(volume, currentVolume);

    level = currentLevel;
    volume = currentVolume;

    if (volumeChange)
        emit q->volumeChanged(currentVolume);

    if (levelChange)
        emit q->levelChanged(currentLevel);

    activate(currentLevel);
}

void QGoogleAssistantAudioInputPrivate::activate(bool on, bool force)
{
    Q_Q(QGoogleAssistantAudioInput);
    if (on) {
        timer.start();
    } else if (active) {
        if (!force && timer.elapsed() < timeout)
            return;
        timer.invalidate();
    }

    if (active == on)
        return;

    if (on)
        emit q->begin();

    active = on;
    emit q->activeChanged(on);

    if (!on)
        emit q->end();
}

QGoogleAssistantAudioInput::QGoogleAssistantAudioInput(QObject *parent)
    : QObject(*(new QGoogleAssistantAudioInputPrivate), parent)
{
    setFormat(QGoogleAssistantAudio::defaultFormat());
    setDevice(QAudioDeviceInfo::defaultInputDevice());
}

bool QGoogleAssistantAudioInput::isActive() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->active;
}

bool QGoogleAssistantAudioInput::isEnabled() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->enabled;
}

void QGoogleAssistantAudioInput::setEnabled(bool enabled)
{
    Q_D(QGoogleAssistantAudioInput);
    if (d->enabled == enabled)
        return;

    d->enabled = enabled;
    if (enabled) {
        if (d->audio->state() == QAudio::StoppedState)
            d->audio->start(d->buffer);
    } else {
        if (d->audio->state() != QAudio::StoppedState)
            d->audio->stop();
        d->activate(false, true);
    }
    emit enabledChanged(enabled);
}

void QGoogleAssistantAudioInput::enable()
{
    setEnabled(true);
}

void QGoogleAssistantAudioInput::disable()
{
    setEnabled(false);
}

QGoogleAssistantAudioInput::Level QGoogleAssistantAudioInput::level() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->level;
}

qreal QGoogleAssistantAudioInput::volume() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->volume;
}

int QGoogleAssistantAudioInput::timeout() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->timeout;
}

void QGoogleAssistantAudioInput::setTimeout(int timeout)
{
    Q_D(QGoogleAssistantAudioInput);
    if (d->timeout == timeout)
        return;

    d->timeout = timeout;
    emit timeoutChanged(timeout);
}

qreal QGoogleAssistantAudioInput::threshold() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->threshold;
}

void QGoogleAssistantAudioInput::setThreshold(qreal threshold)
{
    Q_D(QGoogleAssistantAudioInput);
    if (qFuzzyCompare(d->threshold, threshold))
        return;

    d->threshold = threshold;
    emit thresholdChanged(threshold);
}

QAudioFormat QGoogleAssistantAudioInput::format() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->format;
}

static quint32 maxAmplitude(const QAudioFormat &format)
{
    switch (format.sampleSize()) {
    case 8:
        switch (format.sampleType()) {
        case QAudioFormat::UnSignedInt: return 255;
        case QAudioFormat::SignedInt: return 127;
        default: break;
        }
        break;
    case 16:
        switch (format.sampleType()) {
        case QAudioFormat::UnSignedInt: return 65535;
        case QAudioFormat::SignedInt: return 32767;
        default: break;
        }
        break;
    case 32:
        switch (format.sampleType()) {
        case QAudioFormat::UnSignedInt: return 0xffffffff;
        case QAudioFormat::SignedInt: return 0x7fffffff;
        case QAudioFormat::Float: return 0x7fffffff; // Kind of
        default: break;
        }
        break;
    default: break;
    }
    return 0;
}


void QGoogleAssistantAudioInput::setFormat(const QAudioFormat &format)
{
    Q_D(QGoogleAssistantAudioInput);
    if (d->format == format)
        return;

    d->format = format;
    d->maxAmplitude = maxAmplitude(format);
    d->reset();
    emit formatChanged(format);
}

QAudioDeviceInfo QGoogleAssistantAudioInput::device() const
{
    Q_D(const QGoogleAssistantAudioInput);
    return d->device;
}

void QGoogleAssistantAudioInput::setDevice(const QAudioDeviceInfo &device)
{
    Q_D(QGoogleAssistantAudioInput);
    if (d->device == device)
        return;

    d->device = device;
    d->reset();
    emit deviceChanged(device);
}

QT_END_NAMESPACE
