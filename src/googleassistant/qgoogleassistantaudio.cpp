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

#include "qgoogleassistantaudio.h"
#include "qgoogleassistantaudio_p.h"

QT_BEGIN_NAMESPACE

static const int DefaultSampleRate = 16000;

QAudioFormat QGoogleAssistantAudio::defaultFormat()
{
    QAudioFormat format;
    format.setSampleSize(16);
    format.setSampleRate(DefaultSampleRate);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec(QStringLiteral("audio/pcm"));
    format.setChannelCount(1);
    return format;
}

class QGoogleAssistantAudioBuffer : public QIODevice
{
    Q_OBJECT

public:
    explicit QGoogleAssistantAudioBuffer(QObject *parent = nullptr)
        : QIODevice(parent) { }

    bool isSequential() const override { return true; }
    qint64 bytesAvailable() const override { return m_data.size(); }
    bool open(OpenMode mode) override { return QIODevice::open(mode | Unbuffered); }

protected:
    qint64 readData(char *data, qint64 len) override
    {
        if ((len = qMin(len, qint64(m_data.size()))) <= 0)
            return qint64(0);
        memcpy(data, m_data.constData(), len);
        m_data.remove(0, len);
        return len;
    }
    qint64 writeData(const char *data, qint64 len) override
    {
        int size = m_data.size();
        m_data.resize(size + int(len));
        memcpy(m_data.data() + size, data, int(len));
        emit bytesWritten(len);
        emit readyRead();
        return len;
    }

private:
    QByteArray m_data;
};

QIODevice *QGoogleAssistantAudioPrivate::createBuffer(QObject *parent)
{
    return new QGoogleAssistantAudioBuffer(parent);
}

QT_END_NAMESPACE

#include "qgoogleassistantaudio.moc"
