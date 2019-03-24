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

#ifndef QGOOGLEASSISTANTREQUEST_H
#define QGOOGLEASSISTANTREQUEST_H

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qstring.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>
#include <memory>

namespace google::assistant::embedded::v1alpha2 {
    class AudioInConfig;
    class AudioOutConfig;
    class ScreenOutConfig;
    class DeviceLocation;
    class DialogStateIn;
    class DeviceConfig;
    class DebugConfig;
    class AssistConfig;
    class AssistRequest;
}

QT_BEGIN_NAMESPACE

namespace assistant = google::assistant::embedded::v1alpha2;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudioInConfig
{
    Q_GADGET
    Q_PROPERTY(Encoding encoding READ encoding WRITE setEncoding)
    Q_PROPERTY(qint32 sampleRateHertz READ sampleRateHertz WRITE setSampleRateHertz)

public:
    QGoogleAssistantAudioInConfig();
    QGoogleAssistantAudioInConfig(std::shared_ptr<assistant::AudioInConfig> audio_in_config);

    enum Encoding { Unspecified = 0, Linear16 = 1, Flac = 2 };
    Q_ENUM(Encoding)

    Encoding encoding() const;
    void setEncoding(Encoding encoding);

    qint32 sampleRateHertz() const;
    void setSampleRateHertz(qint32 sampleRateHertz);

    std::shared_ptr<assistant::AudioInConfig> get() const;

private:
    std::shared_ptr<assistant::AudioInConfig> audio_in_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudioOutConfig
{
    Q_GADGET
    Q_PROPERTY(Encoding encoding READ encoding WRITE setEncoding)
    Q_PROPERTY(qint32 sampleRateHertz READ sampleRateHertz WRITE setSampleRateHertz)
    Q_PROPERTY(qint32 volumePercentage READ volumePercentage WRITE setVolumePercentage)

public:
    QGoogleAssistantAudioOutConfig();
    QGoogleAssistantAudioOutConfig(std::shared_ptr<assistant::AudioOutConfig> audio_out_config);

    enum Encoding { Unspecified = 0, Linear16 = 1, Mp3 = 2, OpusInOgg = 3 };
    Q_ENUM(Encoding)

    Encoding encoding() const;
    void setEncoding(Encoding encoding);

    qint32 sampleRateHertz() const;
    void setSampleRateHertz(qint32 sampleRateHertz);

    qint32 volumePercentage() const;
    void setVolumePercentage(qint32 volumePercentage);

    std::shared_ptr<assistant::AudioOutConfig> get() const;

private:
    std::shared_ptr<assistant::AudioOutConfig> audio_out_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantScreenOutConfig
{
    Q_GADGET
    Q_PROPERTY(ScreenMode screenMode READ screenMode WRITE setScreenMode)

public:
    QGoogleAssistantScreenOutConfig();
    QGoogleAssistantScreenOutConfig(std::shared_ptr<assistant::ScreenOutConfig> screen_out_config);

    enum ScreenMode { Unspecified = 0, Off = 1, Playing = 3 };
    Q_ENUM(ScreenMode)

    ScreenMode screenMode() const;
    void setScreenMode(ScreenMode screenMode);

    std::shared_ptr<assistant::ScreenOutConfig> get() const;

private:
    std::shared_ptr<assistant::ScreenOutConfig> screen_out_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDeviceLocation
{
    Q_GADGET
    Q_PROPERTY(qreal latitude READ latitude WRITE setLatitude)
    Q_PROPERTY(qreal longitude READ longitude WRITE setLongitude)

public:
    QGoogleAssistantDeviceLocation();
    QGoogleAssistantDeviceLocation(std::shared_ptr<assistant::DeviceLocation> device_location);

    qreal latitude() const;
    void setLatitude(qreal latitude);

    qreal longitude() const;
    void setLongitude(qreal longitude);

    std::shared_ptr<assistant::DeviceLocation> get() const;

private:
    std::shared_ptr<assistant::DeviceLocation> device_location;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDialogStateIn
{
    Q_GADGET
    Q_PROPERTY(QByteArray conversationState READ conversationState WRITE setConversationState)
    Q_PROPERTY(QString languageCode READ languageCode WRITE setLanguageCode)
    Q_PROPERTY(bool hasDeviceLocation READ hasDeviceLocation)
    Q_PROPERTY(QGoogleAssistantDeviceLocation deviceLocation READ deviceLocation WRITE setDeviceLocation)
    Q_PROPERTY(bool isNnewConversation READ isNewConversation WRITE setNewConversation)

public:
    QGoogleAssistantDialogStateIn();
    QGoogleAssistantDialogStateIn(std::shared_ptr<assistant::DialogStateIn> dialog_state_in);

    QByteArray conversationState() const;
    void setConversationState(const QByteArray &conversationState);

    QString languageCode() const;
    void setLanguageCode(const QString &languageCode);

    bool hasDeviceLocation() const;
    QGoogleAssistantDeviceLocation deviceLocation() const;
    void setDeviceLocation(const QGoogleAssistantDeviceLocation &deviceLocation);

    bool isNewConversation() const;
    void setNewConversation(bool newConversation);

    std::shared_ptr<assistant::DialogStateIn> get() const;

private:
    std::shared_ptr<assistant::DialogStateIn> dialog_state_in;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDeviceConfig
{
    Q_GADGET
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId)
    Q_PROPERTY(QString deviceModelId READ deviceModelId WRITE setDeviceModelId)

public:
    QGoogleAssistantDeviceConfig();
    QGoogleAssistantDeviceConfig(std::shared_ptr<assistant::DeviceConfig> device_config);

    QString deviceId() const;
    void setDeviceId(const QString &deviceId);

    QString deviceModelId() const;
    void setDeviceModelId(const QString &deviceModelId);

    std::shared_ptr<assistant::DeviceConfig> get() const;

private:
    std::shared_ptr<assistant::DeviceConfig> device_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantDebugConfig
{
    Q_GADGET
    Q_PROPERTY(bool returnDebugInfo READ returnDebugInfo WRITE setReturnDebugInfo)

public:
    QGoogleAssistantDebugConfig();
    QGoogleAssistantDebugConfig(std::shared_ptr<assistant::DebugConfig> debug_config);

    bool returnDebugInfo() const;
    void setReturnDebugInfo(bool returnDebugInfo);

    std::shared_ptr<assistant::DebugConfig> get() const;

private:
    std::shared_ptr<assistant::DebugConfig> debug_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantConfig
{
    Q_GADGET
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery)
    Q_PROPERTY(bool hasAudioInConfig READ hasAudioInConfig)
    Q_PROPERTY(QGoogleAssistantAudioInConfig audioInConfig READ audioInConfig WRITE setAudioInConfig)
    Q_PROPERTY(bool hasAudioOutConfig READ hasAudioOutConfig)
    Q_PROPERTY(QGoogleAssistantAudioOutConfig audioOutConfig READ audioOutConfig WRITE setAudioOutConfig)
    Q_PROPERTY(bool hasScreenOutConfig READ hasScreenOutConfig)
    Q_PROPERTY(QGoogleAssistantScreenOutConfig screenOutConfig READ screenOutConfig WRITE setScreenOutConfig)
    Q_PROPERTY(bool hasDialogStateIn READ hasDialogStateIn)
    Q_PROPERTY(QGoogleAssistantDialogStateIn dialogStateIn READ dialogStateIn WRITE setDialogStateIn)
    Q_PROPERTY(bool hasDeviceConfig READ hasDeviceConfig)
    Q_PROPERTY(QGoogleAssistantDeviceConfig deviceConfig READ deviceConfig WRITE setDeviceConfig)
    Q_PROPERTY(bool hasDebugConfig READ hasDebugConfig)
    Q_PROPERTY(QGoogleAssistantDebugConfig debugConfig READ debugConfig WRITE setDebugConfig)

public:
    QGoogleAssistantConfig();
    QGoogleAssistantConfig(std::shared_ptr<assistant::AssistConfig> assist_config);

    QString textQuery() const;
    void setTextQuery(const QString &textQuery);

    bool hasAudioInConfig() const;
    QGoogleAssistantAudioInConfig audioInConfig() const;
    void setAudioInConfig(const QGoogleAssistantAudioInConfig &audioInConfig);

    bool hasAudioOutConfig() const;
    QGoogleAssistantAudioOutConfig audioOutConfig() const;
    void setAudioOutConfig(const QGoogleAssistantAudioOutConfig &audioOutConfig);

    bool hasScreenOutConfig() const;
    QGoogleAssistantScreenOutConfig screenOutConfig() const;
    void setScreenOutConfig(const QGoogleAssistantScreenOutConfig &screenOutConfig);

    bool hasDialogStateIn() const;
    QGoogleAssistantDialogStateIn dialogStateIn() const;
    void setDialogStateIn(const QGoogleAssistantDialogStateIn &dialogStateIn);

    bool hasDeviceConfig() const;
    QGoogleAssistantDeviceConfig deviceConfig() const;
    void setDeviceConfig(const QGoogleAssistantDeviceConfig &deviceConfig);

    bool hasDebugConfig() const;
    QGoogleAssistantDebugConfig debugConfig() const;
    void setDebugConfig(const QGoogleAssistantDebugConfig &debugConfig);

    std::shared_ptr<assistant::AssistConfig> get() const;

private:
    std::shared_ptr<assistant::AssistConfig> assist_config;
};

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantRequest
{
    Q_GADGET
    Q_PROPERTY(QByteArray audioIn READ audioIn WRITE setAudioIn)
    Q_PROPERTY(bool hasConfig READ hasConfig)
    Q_PROPERTY(QGoogleAssistantConfig config READ config WRITE setConfig)

public:
    QGoogleAssistantRequest();
    QGoogleAssistantRequest(const QByteArray &audioIn);
    QGoogleAssistantRequest(const QGoogleAssistantConfig &config);
    QGoogleAssistantRequest(std::shared_ptr<assistant::AssistRequest> assist_request);

    QByteArray audioIn() const;
    void setAudioIn(const QByteArray &audioIn);

    bool hasConfig() const;
    QGoogleAssistantConfig config() const;
    void setConfig(const QGoogleAssistantConfig &config);

    std::shared_ptr<assistant::AssistRequest> get() const;

private:
    std::shared_ptr<assistant::AssistRequest> assist_request;
};

#ifndef QT_NO_DEBUG_STREAM
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantAudioInConfig &audioInConfig);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantAudioOutConfig &audioOutConfig);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantScreenOutConfig &screenOutConfig);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDeviceLocation &deviceLocation);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDialogStateIn &dialogStateIn);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDeviceConfig &deviceConfig);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantDebugConfig &debugConfig);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantConfig &config);
Q_GOOGLEASSISTANT_EXPORT QDebug operator<<(QDebug, const QGoogleAssistantRequest &request);
#endif

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QGoogleAssistantAudioInConfig)
Q_DECLARE_METATYPE(QGoogleAssistantAudioOutConfig)
Q_DECLARE_METATYPE(QGoogleAssistantScreenOutConfig)
Q_DECLARE_METATYPE(QGoogleAssistantDeviceLocation)
Q_DECLARE_METATYPE(QGoogleAssistantDialogStateIn)
Q_DECLARE_METATYPE(QGoogleAssistantDeviceConfig)
Q_DECLARE_METATYPE(QGoogleAssistantDebugConfig)
Q_DECLARE_METATYPE(QGoogleAssistantConfig)
Q_DECLARE_METATYPE(QGoogleAssistantRequest)

#endif // QGOOGLEASSISTANTREQUEST_H
