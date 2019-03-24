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

#ifndef QGOOGLEASSISTANTRESPONSE_H
#define QGOOGLEASSISTANTRESPONSE_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdebug.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qlist.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qshareddata.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>
#include <memory>

namespace google::assistant::embedded::v1alpha2 {
    class AudioOut;
    class DebugInfo;
    class DeviceAction;
    class DialogStateOut;
    class ScreenOut;
    class SpeechRecognitionResult;
    class AssistResponse;
}

QT_BEGIN_NAMESPACE

namespace assistant = google::assistant::embedded::v1alpha2;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudioOut
{
    Q_GADGET
    Q_PROPERTY(QByteArray audioData READ audioData WRITE setAudioData)

public:
    QGoogleAssistantAudioOut();
    QGoogleAssistantAudioOut(std::shared_ptr<assistant::AudioOut> audio_out);

    QByteArray audioData() const;
    void setAudioData(const QByteArray &audioData);

    std::shared_ptr<assistant::AudioOut> get() const;

private:
    std::shared_ptr<assistant::AudioOut> audio_out;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDebugInfo
{
    Q_GADGET
    Q_PROPERTY(QJsonObject actionOnGoogleAgentToAssistant READ actionOnGoogleAgentToAssistant WRITE setActionOnGoogleAgentToAssistant)

public:
    QGoogleAssistantDebugInfo();
    QGoogleAssistantDebugInfo(std::shared_ptr<assistant::DebugInfo> debug_info);

    QJsonObject actionOnGoogleAgentToAssistant() const;
    void setActionOnGoogleAgentToAssistant(const QJsonObject &actionOnGoogleAgentToAssistant);

    std::shared_ptr<assistant::DebugInfo> get() const;

private:
    std::shared_ptr<assistant::DebugInfo> debug_info;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDeviceAction
{
    Q_GADGET
    Q_PROPERTY(QJsonObject deviceRequest READ deviceRequest WRITE setDeviceRequest)

public:
    QGoogleAssistantDeviceAction();
    QGoogleAssistantDeviceAction(std::shared_ptr<assistant::DeviceAction> device_action);

    QJsonObject deviceRequest() const;
    void setDeviceRequest(const QJsonObject &deviceRequest);

    std::shared_ptr<assistant::DeviceAction> get() const;

private:
    std::shared_ptr<assistant::DeviceAction> device_action;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDialogStateOut
{
    Q_GADGET
    Q_PROPERTY(QString supplementalDisplayText READ supplementalDisplayText WRITE setSupplementalDisplayText)
    Q_PROPERTY(QByteArray conversationState READ conversationState WRITE setConversationState)
    Q_PROPERTY(bool shouldCloseMicrophone READ shouldCloseMicrophone)
    Q_PROPERTY(bool shouldDialogFollowOn READ shouldDialogFollowOn)
    Q_PROPERTY(MicrophoneMode microphoneMode READ microphoneMode WRITE setMicrophoneMode)
    Q_PROPERTY(qint32 volumePercentage READ volumePercentage WRITE setVolumePercentage)

public:
    QGoogleAssistantDialogStateOut();
    QGoogleAssistantDialogStateOut(std::shared_ptr<assistant::DialogStateOut> dialog_state_out);

    QString supplementalDisplayText() const;
    void setSupplementalDisplayText(const QString &supplementalDisplayText);

    QByteArray conversationState() const;
    void setConversationState(const QByteArray &conversationState);

    enum MicrophoneMode { Unspecified = 0, CloseMicrophone = 1, DialogFollowOn = 2 };
    Q_ENUM(MicrophoneMode)

    bool shouldCloseMicrophone() const;
    bool shouldDialogFollowOn() const;
    MicrophoneMode microphoneMode() const;
    void setMicrophoneMode(MicrophoneMode microphoneMode);

    qint32 volumePercentage() const;
    void setVolumePercentage(qint32 volumePercentage);

    std::shared_ptr<assistant::DialogStateOut> get() const;

private:
    std::shared_ptr<assistant::DialogStateOut> dialog_state_out;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantScreenOut
{
    Q_GADGET
    Q_PROPERTY(Format format READ format WRITE setFormat)
    Q_PROPERTY(QByteArray data READ data WRITE setData)

public:
    QGoogleAssistantScreenOut();
    QGoogleAssistantScreenOut(std::shared_ptr<assistant::ScreenOut> screen_out);

    enum Format { Unspecified = 0, Html = 1 };
    Q_ENUM(Format)

    Format format() const;
    void setFormat(Format format);

    QByteArray data() const;
    void setData(const QByteArray &data);

    std::shared_ptr<assistant::ScreenOut> get() const;

private:
    std::shared_ptr<assistant::ScreenOut> screen_out;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantSpeechRecognitionResult
{
    Q_GADGET
    Q_PROPERTY(QString transcript READ transcript WRITE setTranscript)
    Q_PROPERTY(qreal stability READ stability WRITE setStability)

public:
    QGoogleAssistantSpeechRecognitionResult();
    QGoogleAssistantSpeechRecognitionResult(std::shared_ptr<assistant::SpeechRecognitionResult> speech_result);

    QString transcript() const;
    void setTranscript(const QString &transcript);

    qreal stability() const;
    void setStability(qreal stability);

    std::shared_ptr<assistant::SpeechRecognitionResult> get() const;

private:
    std::shared_ptr<assistant::SpeechRecognitionResult> speech_result;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantResponse
{
    Q_GADGET
    Q_PROPERTY(bool endOfUtterance READ endOfUtterance)
    Q_PROPERTY(EventType eventType READ eventType WRITE setEventType)
    Q_PROPERTY(bool hasAudioOut READ hasAudioOut)
    Q_PROPERTY(QGoogleAssistantAudioOut audioOut READ audioOut WRITE setAudioOut)
    Q_PROPERTY(bool hasScreenOut READ hasScreenOut)
    Q_PROPERTY(QGoogleAssistantScreenOut screenOut READ screenOut WRITE setScreenOut)
    Q_PROPERTY(bool hasDeviceAction READ hasDeviceAction)
    Q_PROPERTY(QGoogleAssistantDeviceAction deviceAction READ deviceAction WRITE setDeviceAction)
    Q_PROPERTY(int speechResultCount READ speechResultCount)
    Q_PROPERTY(QList<QGoogleAssistantSpeechRecognitionResult> speechResults READ speechResults RESET clearSpeechResults)
    Q_PROPERTY(bool hasDialogStateOut READ hasDialogStateOut)
    Q_PROPERTY(QGoogleAssistantDialogStateOut dialogStateOut READ dialogStateOut WRITE setDialogStateOut)
    Q_PROPERTY(bool hasDebugInfo READ hasDebugInfo)
    Q_PROPERTY(QGoogleAssistantDebugInfo debugInfo READ debugInfo WRITE setDebugInfo)

public:
    QGoogleAssistantResponse();
    QGoogleAssistantResponse(std::shared_ptr<assistant::AssistResponse> assist_response);

    enum EventType { Unspecified = 0, EndOfUtterance = 1 };
    Q_ENUM(EventType)

    bool endOfUtterance() const;
    EventType eventType() const;
    void setEventType(EventType eventType);

    bool hasAudioOut() const;
    QGoogleAssistantAudioOut audioOut() const;
    void setAudioOut(const QGoogleAssistantAudioOut &audioOut);

    bool hasScreenOut() const;
    QGoogleAssistantScreenOut screenOut() const;
    void setScreenOut(const QGoogleAssistantScreenOut &screenOut);

    bool hasDeviceAction() const;
    QGoogleAssistantDeviceAction deviceAction() const;
    void setDeviceAction(const QGoogleAssistantDeviceAction &deviceAction);

    int speechResultCount() const;
    QList<QGoogleAssistantSpeechRecognitionResult> speechResults() const;
    Q_INVOKABLE QGoogleAssistantSpeechRecognitionResult speechResult(int index) const;
    Q_INVOKABLE void addSpeechResult(const QGoogleAssistantSpeechRecognitionResult &speechResult);
    Q_INVOKABLE void clearSpeechResults();

    bool hasDialogStateOut() const;
    QGoogleAssistantDialogStateOut dialogStateOut() const;
    void setDialogStateOut(const QGoogleAssistantDialogStateOut &dialogStateOut);

    bool hasDebugInfo() const;
    QGoogleAssistantDebugInfo debugInfo() const;
    void setDebugInfo(const QGoogleAssistantDebugInfo &debugInfo);

    std::shared_ptr<assistant::AssistResponse> get() const;

private:
    std::shared_ptr<assistant::AssistResponse> assist_response;
};

#ifndef QT_NO_DEBUG_STREAM
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantAudioOut &audioOut);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDebugInfo &debugInfo);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDeviceAction &deviceAction);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDialogStateOut &stateOut);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantScreenOut &screenOut);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantSpeechRecognitionResult &speechResult);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantResponse &response);
#endif

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QGoogleAssistantAudioOut)
Q_DECLARE_METATYPE(QGoogleAssistantDebugInfo)
Q_DECLARE_METATYPE(QGoogleAssistantDeviceAction)
Q_DECLARE_METATYPE(QGoogleAssistantDialogStateOut)
Q_DECLARE_METATYPE(QGoogleAssistantScreenOut)
Q_DECLARE_METATYPE(QGoogleAssistantSpeechRecognitionResult)
Q_DECLARE_METATYPE(QGoogleAssistantResponse)

#endif // QGOOGLEASSISTANTRESPONSE_H
