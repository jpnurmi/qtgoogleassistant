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

#ifndef QGOOGLEASSISTANTAUDIOINPUT_P_H
#define QGOOGLEASSISTANTAUDIOINPUT_P_H

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

#include <QtCore/qelapsedtimer.h>
#include <QtCore/private/qobject_p.h>
#include <QtMultimedia/qaudioformat.h>
#include <QtMultimedia/qaudiodeviceinfo.h>
#include <QtGoogleAssistant/qgoogleassistantaudioinput.h>

QT_BEGIN_NAMESPACE

class QIODevice;
class QAudioInput;

class QGoogleAssistantAudioInputPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QGoogleAssistantAudioInput)

public:
    static QGoogleAssistantAudioInputPrivate *get(QGoogleAssistantAudioInput *audioInput)
    {
        return audioInput->d_func();
    }

    void reset();
    void probe();
    void updateVolume(qreal volume);
    void activate(bool on, bool force = false);

    bool active = false;
    bool enabled = false;
    qreal volume = 0.0;
    QGoogleAssistantAudioInput::Level level = QGoogleAssistantAudioInput::Low;
    int timeout = 2000;
    qreal threshold = 0.4;
    quint32 maxAmplitude = 0;
    QElapsedTimer timer;
    QAudioFormat format;
    QAudioDeviceInfo device;
    QIODevice *buffer = nullptr;
    QAudioInput *audio = nullptr;
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTAUDIOINPUT_P_H
