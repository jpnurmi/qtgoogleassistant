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

#include "qgoogleassistantrequest.h"

#include <QtCore/qdebug.h>

#include <google/assistant/embedded/v1alpha2/embedded_assistant.pb.h>

QT_BEGIN_NAMESPACE

static void no_delete(void *ptr) { Q_UNUSED(ptr); }

/// AudioInConfig
QGoogleAssistantAudioInConfig::QGoogleAssistantAudioInConfig() : audio_in_config(std::make_shared<assistant::AudioInConfig>()) { }
QGoogleAssistantAudioInConfig::QGoogleAssistantAudioInConfig(std::shared_ptr<assistant::AudioInConfig> audio_in_config) : audio_in_config(audio_in_config) { }
QGoogleAssistantAudioInConfig::Encoding QGoogleAssistantAudioInConfig::encoding() const { return static_cast<Encoding>(audio_in_config->encoding()); }
void QGoogleAssistantAudioInConfig::setEncoding(QGoogleAssistantAudioInConfig::Encoding encoding) { audio_in_config->set_encoding(static_cast<assistant::AudioInConfig::Encoding>(encoding)); }
qint32 QGoogleAssistantAudioInConfig::sampleRateHertz() const { return audio_in_config->sample_rate_hertz(); }
void QGoogleAssistantAudioInConfig::setSampleRateHertz(qint32 sampleRateHertz) { audio_in_config->set_sample_rate_hertz(sampleRateHertz); }
std::shared_ptr<assistant::AudioInConfig> QGoogleAssistantAudioInConfig::get() const { return audio_in_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantAudioInConfig &audioInConfig)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "audio_in_config " << audioInConfig.encoding() << "@" << audioInConfig.sampleRateHertz() << "hz";
    return dbg;
}
#endif

/// AudioOutConfig
QGoogleAssistantAudioOutConfig::QGoogleAssistantAudioOutConfig() : audio_out_config(std::make_shared<assistant::AudioOutConfig>()) { }
QGoogleAssistantAudioOutConfig::QGoogleAssistantAudioOutConfig(std::shared_ptr<assistant::AudioOutConfig> audio_out_config) : audio_out_config(audio_out_config) { }
QGoogleAssistantAudioOutConfig::Encoding QGoogleAssistantAudioOutConfig::encoding() const { return static_cast<Encoding>(audio_out_config->encoding()); }
void QGoogleAssistantAudioOutConfig::setEncoding(QGoogleAssistantAudioOutConfig::Encoding encoding) { audio_out_config->set_encoding(static_cast<assistant::AudioOutConfig::Encoding>(encoding)); }
qint32 QGoogleAssistantAudioOutConfig::sampleRateHertz() const { return audio_out_config->sample_rate_hertz(); }
void QGoogleAssistantAudioOutConfig::setSampleRateHertz(qint32 sampleRateHertz) { audio_out_config->set_sample_rate_hertz(sampleRateHertz); }
qint32 QGoogleAssistantAudioOutConfig::volumePercentage() const { return audio_out_config->volume_percentage(); }
void QGoogleAssistantAudioOutConfig::setVolumePercentage(qint32 volumePercentage) { audio_out_config->set_volume_percentage(volumePercentage); }
std::shared_ptr<assistant::AudioOutConfig> QGoogleAssistantAudioOutConfig::get() const { return audio_out_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantAudioOutConfig &audioOutConfig)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "audio_out_config " << audioOutConfig.encoding() << "@" << audioOutConfig.sampleRateHertz() << "hz " << audioOutConfig.volumePercentage() << "%";
    return dbg;
}
#endif

/// ScreenOutConfig
QGoogleAssistantScreenOutConfig::QGoogleAssistantScreenOutConfig() : screen_out_config(std::make_shared<assistant::ScreenOutConfig>()) { }
QGoogleAssistantScreenOutConfig::QGoogleAssistantScreenOutConfig(std::shared_ptr<assistant::ScreenOutConfig> screen_out_config) : screen_out_config(screen_out_config) { }
QGoogleAssistantScreenOutConfig::ScreenMode QGoogleAssistantScreenOutConfig::screenMode() const { return static_cast<ScreenMode>(screen_out_config->screen_mode()); }
void QGoogleAssistantScreenOutConfig::setScreenMode(QGoogleAssistantScreenOutConfig::ScreenMode screenMode) { screen_out_config->set_screen_mode(static_cast<assistant::ScreenOutConfig::ScreenMode>(screenMode)); }
std::shared_ptr<assistant::ScreenOutConfig> QGoogleAssistantScreenOutConfig::get() const { return screen_out_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantScreenOutConfig &screenOutConfig)
{
    QDebugStateSaver saver(dbg);
    dbg << "screen_out_config" << screenOutConfig.screenMode();
    return dbg;
}
#endif

/// DeviceLocation
QGoogleAssistantDeviceLocation::QGoogleAssistantDeviceLocation() : device_location(std::make_shared<assistant::DeviceLocation>()) { }
QGoogleAssistantDeviceLocation::QGoogleAssistantDeviceLocation(std::shared_ptr<assistant::DeviceLocation> device_location) : device_location(device_location) { }
qreal QGoogleAssistantDeviceLocation::latitude() const { return device_location->coordinates().latitude(); }
void QGoogleAssistantDeviceLocation::setLatitude(qreal latitude) { device_location->mutable_coordinates()->set_latitude(latitude); }
qreal QGoogleAssistantDeviceLocation::longitude() const { return device_location->coordinates().longitude(); }
void QGoogleAssistantDeviceLocation::setLongitude(qreal longitude) { device_location->mutable_coordinates()->set_longitude(longitude); }
std::shared_ptr<assistant::DeviceLocation> QGoogleAssistantDeviceLocation::get() const { return device_location; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDeviceLocation &deviceLocation)
{
    QDebugStateSaver saver(dbg);
    dbg << "device_location" << deviceLocation.latitude() << "," << deviceLocation.longitude();
    return dbg;
}
#endif

/// DialogStateIn
QGoogleAssistantDialogStateIn::QGoogleAssistantDialogStateIn() : dialog_state_in(std::make_shared<assistant::DialogStateIn>()) { }
QGoogleAssistantDialogStateIn::QGoogleAssistantDialogStateIn(std::shared_ptr<assistant::DialogStateIn> dialog_state_in) : dialog_state_in(dialog_state_in) { }
QByteArray QGoogleAssistantDialogStateIn::conversationState() const { return QByteArray::fromStdString(dialog_state_in->conversation_state()); }
void QGoogleAssistantDialogStateIn::setConversationState(const QByteArray &conversationState) { dialog_state_in->set_conversation_state(conversationState.toStdString()); }
QString QGoogleAssistantDialogStateIn::languageCode() const { return QString::fromStdString(dialog_state_in->language_code()); }
void QGoogleAssistantDialogStateIn::setLanguageCode(const QString &languageCode) { dialog_state_in->set_language_code(languageCode.toStdString()); }
bool QGoogleAssistantDialogStateIn::hasDeviceLocation() const { return dialog_state_in->has_device_location(); }
QGoogleAssistantDeviceLocation QGoogleAssistantDialogStateIn::deviceLocation() const { return QGoogleAssistantDeviceLocation(std::shared_ptr<assistant::DeviceLocation>(dialog_state_in->mutable_device_location(), no_delete)); }
void QGoogleAssistantDialogStateIn::setDeviceLocation(const QGoogleAssistantDeviceLocation &deviceLocation) { *dialog_state_in->mutable_device_location() = *deviceLocation.get(); }
bool QGoogleAssistantDialogStateIn::isNewConversation() const { return dialog_state_in->is_new_conversation(); }
void QGoogleAssistantDialogStateIn::setNewConversation(bool newConversation) { dialog_state_in->set_is_new_conversation(newConversation); }
std::shared_ptr<assistant::DialogStateIn> QGoogleAssistantDialogStateIn::get() const { return dialog_state_in; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDialogStateIn &dialogStateIn)
{
    QDebugStateSaver saver(dbg);
    dbg << "dialog_state_in" << dialogStateIn.languageCode() << dialogStateIn.deviceLocation() << (dialogStateIn.isNewConversation() ? "new" : "");
    return dbg;
}
#endif

/// DeviceConfig
QGoogleAssistantDeviceConfig::QGoogleAssistantDeviceConfig() : device_config(std::make_shared<assistant::DeviceConfig>()) { }
QGoogleAssistantDeviceConfig::QGoogleAssistantDeviceConfig(std::shared_ptr<assistant::DeviceConfig> device_config) : device_config(device_config) { }
QString QGoogleAssistantDeviceConfig::deviceId() const { return QString::fromStdString(device_config->device_id()); }
void QGoogleAssistantDeviceConfig::setDeviceId(const QString &deviceId) { device_config->set_device_id(deviceId.toStdString()); }
QString QGoogleAssistantDeviceConfig::deviceModelId() const { return QString::fromStdString(device_config->device_model_id()); }
void QGoogleAssistantDeviceConfig::setDeviceModelId(const QString &deviceModelId) { device_config->set_device_model_id(deviceModelId.toStdString()); }
std::shared_ptr<assistant::DeviceConfig> QGoogleAssistantDeviceConfig::get() const { return device_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDeviceConfig &deviceConfig)
{
    QDebugStateSaver saver(dbg);
    dbg << "device_config" << deviceConfig.deviceId() << deviceConfig.deviceModelId();
    return dbg;
}
#endif

/// DebugConfig
QGoogleAssistantDebugConfig::QGoogleAssistantDebugConfig() : debug_config(std::make_shared<assistant::DebugConfig>()) { }
QGoogleAssistantDebugConfig::QGoogleAssistantDebugConfig(std::shared_ptr<assistant::DebugConfig> debug_config) : debug_config(debug_config) { }
bool QGoogleAssistantDebugConfig::returnDebugInfo() const { return debug_config->return_debug_info(); }
void QGoogleAssistantDebugConfig::setReturnDebugInfo(bool returnDebugInfo) { debug_config->set_return_debug_info(returnDebugInfo); }
std::shared_ptr<assistant::DebugConfig> QGoogleAssistantDebugConfig::get() const { return debug_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDebugConfig &debugConfig)
{
    QDebugStateSaver saver(dbg);
    dbg << "debug_config" << debugConfig.returnDebugInfo();
    return dbg;
}
#endif

/// AssistConfig
QGoogleAssistantConfig::QGoogleAssistantConfig() : assist_config(std::make_shared<assistant::AssistConfig>()) { }
QGoogleAssistantConfig::QGoogleAssistantConfig(std::shared_ptr<assistant::AssistConfig> assist_config) : assist_config(assist_config) { }
QString QGoogleAssistantConfig::textQuery() const { return QString::fromStdString(assist_config->text_query()); }
void QGoogleAssistantConfig::setTextQuery(const QString &textQuery) { assist_config->set_text_query(textQuery.toStdString()); }
bool QGoogleAssistantConfig::hasAudioInConfig() const { return assist_config->has_audio_in_config(); }
QGoogleAssistantAudioInConfig QGoogleAssistantConfig::audioInConfig() const { return QGoogleAssistantAudioInConfig(std::shared_ptr<assistant::AudioInConfig>(assist_config->mutable_audio_in_config(), no_delete)); }
void QGoogleAssistantConfig::setAudioInConfig(const QGoogleAssistantAudioInConfig &audioInConfig) { *assist_config->mutable_audio_in_config() = *audioInConfig.get(); }
bool QGoogleAssistantConfig::hasAudioOutConfig() const { return assist_config->has_audio_out_config(); }
QGoogleAssistantAudioOutConfig QGoogleAssistantConfig::audioOutConfig() const { return QGoogleAssistantAudioOutConfig(std::shared_ptr<assistant::AudioOutConfig>(assist_config->mutable_audio_out_config(), no_delete)); }
void QGoogleAssistantConfig::setAudioOutConfig(const QGoogleAssistantAudioOutConfig &audioOutConfig) { *assist_config->mutable_audio_out_config() = *audioOutConfig.get(); }
bool QGoogleAssistantConfig::hasScreenOutConfig() const { return assist_config->has_screen_out_config(); }
QGoogleAssistantScreenOutConfig QGoogleAssistantConfig::screenOutConfig() const { return QGoogleAssistantScreenOutConfig(std::shared_ptr<assistant::ScreenOutConfig>(assist_config->mutable_screen_out_config(), no_delete)); }
void QGoogleAssistantConfig::setScreenOutConfig(const QGoogleAssistantScreenOutConfig &screenOutConfig) { *assist_config->mutable_screen_out_config() = *screenOutConfig.get(); }
bool QGoogleAssistantConfig::hasDialogStateIn() const { return assist_config->has_dialog_state_in(); }
QGoogleAssistantDialogStateIn QGoogleAssistantConfig::dialogStateIn() const { return QGoogleAssistantDialogStateIn(std::shared_ptr<assistant::DialogStateIn>(assist_config->mutable_dialog_state_in(), no_delete)); }
void QGoogleAssistantConfig::setDialogStateIn(const QGoogleAssistantDialogStateIn &dialogStateIn) { *assist_config->mutable_dialog_state_in() = *dialogStateIn.get(); }
bool QGoogleAssistantConfig::hasDeviceConfig() const { return assist_config->has_device_config(); }
QGoogleAssistantDeviceConfig QGoogleAssistantConfig::deviceConfig() const { return QGoogleAssistantDeviceConfig(std::shared_ptr<assistant::DeviceConfig>(assist_config->mutable_device_config(), no_delete)); }
void QGoogleAssistantConfig::setDeviceConfig(const QGoogleAssistantDeviceConfig &deviceConfig) { *assist_config->mutable_device_config() = *deviceConfig.get(); }
bool QGoogleAssistantConfig::hasDebugConfig() const { return assist_config->has_debug_config(); }
QGoogleAssistantDebugConfig QGoogleAssistantConfig::debugConfig() const { return QGoogleAssistantDebugConfig(std::shared_ptr<assistant::DebugConfig>(assist_config->mutable_debug_config(), no_delete)); }
void QGoogleAssistantConfig::setDebugConfig(const QGoogleAssistantDebugConfig &debugConfig) { *assist_config->mutable_debug_config() = *debugConfig.get(); }
std::shared_ptr<assistant::AssistConfig> QGoogleAssistantConfig::get() const { return assist_config; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantConfig &config)
{
    QDebugStateSaver saver(dbg);
    dbg << "assist_config" << config.textQuery();
    if (config.hasAudioInConfig())
        dbg << config.audioInConfig();
    if (config.hasAudioOutConfig())
        dbg << config.audioOutConfig();
    if (config.hasScreenOutConfig())
        dbg << config.screenOutConfig();
    if (config.hasDialogStateIn())
        dbg << config.dialogStateIn();
    if (config.hasDeviceConfig())
        dbg << config.deviceConfig();
    if (config.hasDebugConfig())
        dbg << config.debugConfig();
    return dbg;
}
#endif

/// AssistRequest
QGoogleAssistantRequest::QGoogleAssistantRequest() : assist_request(std::make_shared<assistant::AssistRequest>()) { }
QGoogleAssistantRequest::QGoogleAssistantRequest(const QByteArray &audioIn) : QGoogleAssistantRequest() { setAudioIn(audioIn); }
QGoogleAssistantRequest::QGoogleAssistantRequest(const QGoogleAssistantConfig &config) : QGoogleAssistantRequest() { setConfig(config); }
QGoogleAssistantRequest::QGoogleAssistantRequest(std::shared_ptr<assistant::AssistRequest> assist_request) : assist_request(assist_request) { }
QByteArray QGoogleAssistantRequest::audioIn() const { return QByteArray::fromStdString(assist_request->audio_in()); }
void QGoogleAssistantRequest::setAudioIn(const QByteArray &audioIn) { assist_request->set_audio_in(audioIn.toStdString()); }
bool QGoogleAssistantRequest::hasConfig() const { return assist_request->has_config(); }
QGoogleAssistantConfig QGoogleAssistantRequest::config() const { return QGoogleAssistantConfig(std::shared_ptr<assistant::AssistConfig>(assist_request->mutable_config(), no_delete)); }
void QGoogleAssistantRequest::setConfig(const QGoogleAssistantConfig &config) { *assist_request->mutable_config() = *config.get(); }
std::shared_ptr<assistant::AssistRequest> QGoogleAssistantRequest::get() const { return assist_request; }

QT_END_NAMESPACE
