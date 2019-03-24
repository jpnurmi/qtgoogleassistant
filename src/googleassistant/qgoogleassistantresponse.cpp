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

#include "qgoogleassistantresponse.h"

#include <QtCore/qjsondocument.h>

#include <google/assistant/embedded/v1alpha2/embedded_assistant.pb.h>

QT_BEGIN_NAMESPACE

template <typename T, typename RPF>
static QList<T> toList(RPF repeatedPtrField)
{
    QList<T> list;
    for (int i = 0; i < repeatedPtrField.size(); ++i)
        list += T(std::shared_ptr<assistant::SpeechRecognitionResult>(repeatedPtrField.Mutable(i)));
    return list;
}

static void no_delete(void *ptr) { Q_UNUSED(ptr); }

/// AudioOut
QGoogleAssistantAudioOut::QGoogleAssistantAudioOut() : audio_out(std::make_shared<assistant::AudioOut>()) { }
QGoogleAssistantAudioOut::QGoogleAssistantAudioOut(std::shared_ptr<assistant::AudioOut> audio_out) : audio_out(audio_out) { }
QByteArray QGoogleAssistantAudioOut::audioData() const { return QByteArray::fromStdString(audio_out->audio_data()); }
void QGoogleAssistantAudioOut::setAudioData(const QByteArray &audioData) { audio_out->set_audio_data(audioData.toStdString()); }
std::shared_ptr<assistant::AudioOut> QGoogleAssistantAudioOut::get() const { return audio_out; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantAudioOut &audioOut)
{
    QDebugStateSaver saver(dbg);
    dbg << "audio_out" << audioOut.audioData().size() << "bytes";
    return dbg;
}
#endif

/// DebugInfo
QGoogleAssistantDebugInfo::QGoogleAssistantDebugInfo() : debug_info(std::make_shared<assistant::DebugInfo>()) { }
QGoogleAssistantDebugInfo::QGoogleAssistantDebugInfo(std::shared_ptr<assistant::DebugInfo> debug_info) : debug_info(debug_info) { }
QJsonObject QGoogleAssistantDebugInfo::actionOnGoogleAgentToAssistant() const { return QJsonDocument::fromJson(QByteArray::fromStdString(debug_info->aog_agent_to_assistant_json())).object(); }
void QGoogleAssistantDebugInfo::setActionOnGoogleAgentToAssistant(const QJsonObject &actionOnGoogleAgentToAssistant) { debug_info->set_aog_agent_to_assistant_json(QJsonDocument(actionOnGoogleAgentToAssistant).toJson().toStdString()); }
std::shared_ptr<assistant::DebugInfo> QGoogleAssistantDebugInfo::get() const { return debug_info; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDebugInfo &debugInfo)
{
    QDebugStateSaver saver(dbg);
    dbg << "debug_info" << QJsonDocument(debugInfo.actionOnGoogleAgentToAssistant()).toJson();
    return dbg;
}
#endif

/// DeviceAction
QGoogleAssistantDeviceAction::QGoogleAssistantDeviceAction() : device_action(std::make_shared<assistant::DeviceAction>()) { }
QGoogleAssistantDeviceAction::QGoogleAssistantDeviceAction(std::shared_ptr<assistant::DeviceAction> device_action) : device_action(device_action) { }
QJsonObject QGoogleAssistantDeviceAction::deviceRequest() const { return QJsonDocument::fromJson(QByteArray::fromStdString(device_action->device_request_json())).object(); }
void QGoogleAssistantDeviceAction::setDeviceRequest(const QJsonObject &deviceRequest) { device_action->set_device_request_json(QJsonDocument(deviceRequest).toJson().toStdString()); }
std::shared_ptr<assistant::DeviceAction> QGoogleAssistantDeviceAction::get() const { return device_action; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDeviceAction &deviceAction)
{
    QDebugStateSaver saver(dbg);
    dbg << "device_action" << QJsonDocument(deviceAction.deviceRequest()).toJson();
    return dbg;
}
#endif

/// DialogStateOut
QGoogleAssistantDialogStateOut::QGoogleAssistantDialogStateOut() : dialog_state_out(std::make_shared<assistant::DialogStateOut>()) { }
QGoogleAssistantDialogStateOut::QGoogleAssistantDialogStateOut(std::shared_ptr<assistant::DialogStateOut> dialog_state_out) : dialog_state_out(dialog_state_out) { }
QString QGoogleAssistantDialogStateOut::supplementalDisplayText() const { return QString::fromStdString(dialog_state_out->supplemental_display_text()); }
void QGoogleAssistantDialogStateOut::setSupplementalDisplayText(const QString &supplementalDisplayText) { dialog_state_out->set_supplemental_display_text(supplementalDisplayText.toStdString()); }
QByteArray QGoogleAssistantDialogStateOut::conversationState() const { return QByteArray::fromStdString(dialog_state_out->conversation_state()); }
void QGoogleAssistantDialogStateOut::setConversationState(const QByteArray &conversationState) { dialog_state_out->set_conversation_state(conversationState.toStdString()); }
bool QGoogleAssistantDialogStateOut::shouldCloseMicrophone() const { return microphoneMode() == QGoogleAssistantDialogStateOut::CloseMicrophone; }
bool QGoogleAssistantDialogStateOut::shouldDialogFollowOn() const { return microphoneMode() == QGoogleAssistantDialogStateOut::DialogFollowOn; }
QGoogleAssistantDialogStateOut::MicrophoneMode QGoogleAssistantDialogStateOut::microphoneMode() const { return static_cast<MicrophoneMode>(dialog_state_out->microphone_mode()); }
void QGoogleAssistantDialogStateOut::setMicrophoneMode(MicrophoneMode microphoneMode) { dialog_state_out->set_microphone_mode(static_cast<assistant::DialogStateOut::MicrophoneMode>(microphoneMode)); }
qint32 QGoogleAssistantDialogStateOut::volumePercentage() const { return dialog_state_out->volume_percentage(); }
void QGoogleAssistantDialogStateOut::setVolumePercentage(qint32 volumePercentage) { dialog_state_out->set_volume_percentage(volumePercentage); }
std::shared_ptr<assistant::DialogStateOut> QGoogleAssistantDialogStateOut::get() const { return dialog_state_out; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantDialogStateOut &dialogStateOut)
{
    QDebugStateSaver saver(dbg);
    dbg << "dialog_state_out" << dialogStateOut.supplementalDisplayText();
    return dbg;
}
#endif

/// ScreenOut
QGoogleAssistantScreenOut::QGoogleAssistantScreenOut() : screen_out(std::make_shared<assistant::ScreenOut>()) { }
QGoogleAssistantScreenOut::QGoogleAssistantScreenOut(std::shared_ptr<assistant::ScreenOut> screen_out) : screen_out(screen_out) { }
QGoogleAssistantScreenOut::Format QGoogleAssistantScreenOut::format() const { return static_cast<Format>(screen_out->format()); }
void QGoogleAssistantScreenOut::setFormat(QGoogleAssistantScreenOut::Format format) { screen_out->set_format(static_cast<assistant::ScreenOut::Format>(format)); }
QByteArray QGoogleAssistantScreenOut::data() const { return QByteArray::fromStdString(screen_out->data()); }
void QGoogleAssistantScreenOut::setData(const QByteArray &data) { screen_out->set_data(data.toStdString()); }
std::shared_ptr<assistant::ScreenOut> QGoogleAssistantScreenOut::get() const { return screen_out; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantScreenOut &screenOut)
{
    QDebugStateSaver saver(dbg);
    dbg << "screen_out" << screenOut.data().size() << "bytes";
    return dbg;
}
#endif

/// SpeechRecognitionResult
QGoogleAssistantSpeechRecognitionResult::QGoogleAssistantSpeechRecognitionResult() : speech_result(std::make_shared<assistant::SpeechRecognitionResult>()) { }
QGoogleAssistantSpeechRecognitionResult::QGoogleAssistantSpeechRecognitionResult(std::shared_ptr<assistant::SpeechRecognitionResult> speech_result) : speech_result(speech_result) { }
QString QGoogleAssistantSpeechRecognitionResult::transcript() const { return QString::fromStdString(speech_result->transcript()); }
void QGoogleAssistantSpeechRecognitionResult::setTranscript(const QString &transcript) { speech_result->set_transcript(transcript.toStdString()); }
qreal QGoogleAssistantSpeechRecognitionResult::stability() const { return speech_result->stability(); }
void QGoogleAssistantSpeechRecognitionResult::setStability(qreal stability) { speech_result->set_stability(stability); }
std::shared_ptr<assistant::SpeechRecognitionResult> QGoogleAssistantSpeechRecognitionResult::get() const { return speech_result; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantSpeechRecognitionResult &speechResult)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "speech_result " << speechResult.transcript() << " (" << speechResult.stability() << ")";
    return dbg;
}
#endif

/// AssistantResponse
QGoogleAssistantResponse::QGoogleAssistantResponse() : assist_response(std::make_shared<assistant::AssistResponse>()) { }
QGoogleAssistantResponse::QGoogleAssistantResponse(std::shared_ptr<assistant::AssistResponse> assist_response) : assist_response(assist_response) { }
bool QGoogleAssistantResponse::endOfUtterance() const { return eventType() == EndOfUtterance; }
QGoogleAssistantResponse::EventType QGoogleAssistantResponse::eventType() const { return static_cast<EventType>(assist_response->event_type()); }
void QGoogleAssistantResponse::setEventType(EventType eventType) { assist_response->set_event_type(static_cast<assistant::AssistResponse::EventType>(eventType)); }
bool QGoogleAssistantResponse::hasAudioOut() const { return assist_response->has_audio_out(); }
QGoogleAssistantAudioOut QGoogleAssistantResponse::audioOut() const { return QGoogleAssistantAudioOut(std::shared_ptr<assistant::AudioOut>(assist_response->mutable_audio_out(), no_delete)); }
void QGoogleAssistantResponse::setAudioOut(const QGoogleAssistantAudioOut &audioOut) { *assist_response->mutable_audio_out() = *audioOut.get(); }
bool QGoogleAssistantResponse::hasScreenOut() const { return assist_response->has_screen_out(); }
QGoogleAssistantScreenOut QGoogleAssistantResponse::screenOut() const { return QGoogleAssistantScreenOut(std::shared_ptr<assistant::ScreenOut>(assist_response->mutable_screen_out(), no_delete)); }
void QGoogleAssistantResponse::setScreenOut(const QGoogleAssistantScreenOut &screenOut) { *assist_response->mutable_screen_out() = *screenOut.get(); }
bool QGoogleAssistantResponse::hasDeviceAction() const { return assist_response->has_device_action(); }
QGoogleAssistantDeviceAction QGoogleAssistantResponse::deviceAction() const { return QGoogleAssistantDeviceAction(std::shared_ptr<assistant::DeviceAction>(assist_response->mutable_device_action(), no_delete)); }
void QGoogleAssistantResponse::setDeviceAction(const QGoogleAssistantDeviceAction &deviceAction) { *assist_response->mutable_device_action() = *deviceAction.get(); }
int QGoogleAssistantResponse::speechResultCount() const { return assist_response->speech_results_size(); }
QList<QGoogleAssistantSpeechRecognitionResult> QGoogleAssistantResponse::speechResults() const { return toList<QGoogleAssistantSpeechRecognitionResult>(assist_response->speech_results()); }
QGoogleAssistantSpeechRecognitionResult QGoogleAssistantResponse::speechResult(int index) const { return QGoogleAssistantSpeechRecognitionResult(std::shared_ptr<assistant::SpeechRecognitionResult>(assist_response->mutable_speech_results(index), no_delete)); }
void QGoogleAssistantResponse::addSpeechResult(const QGoogleAssistantSpeechRecognitionResult &speechResult) { *assist_response->add_speech_results() = *speechResult.get(); }
void QGoogleAssistantResponse::clearSpeechResults() { assist_response->clear_speech_results(); }
bool QGoogleAssistantResponse::hasDialogStateOut() const { return assist_response->has_dialog_state_out(); }
QGoogleAssistantDialogStateOut QGoogleAssistantResponse::dialogStateOut() const { return QGoogleAssistantDialogStateOut(std::shared_ptr<assistant::DialogStateOut>(assist_response->mutable_dialog_state_out(), no_delete)); }
void QGoogleAssistantResponse::setDialogStateOut(const QGoogleAssistantDialogStateOut &dialogStateOut) { *assist_response->mutable_dialog_state_out() = *dialogStateOut.get(); }
bool QGoogleAssistantResponse::hasDebugInfo() const { return assist_response->has_debug_info(); }
QGoogleAssistantDebugInfo QGoogleAssistantResponse::debugInfo() const { return QGoogleAssistantDebugInfo(std::shared_ptr<assistant::DebugInfo>(assist_response->mutable_debug_info(), no_delete)); }
void QGoogleAssistantResponse::setDebugInfo(const QGoogleAssistantDebugInfo &debugInfo) { *assist_response->mutable_debug_info() = *debugInfo.get(); }
std::shared_ptr<assistant::AssistResponse> QGoogleAssistantResponse::get() const { return assist_response; }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGoogleAssistantResponse &response)
{
    QDebugStateSaver saver(dbg);
    dbg << "assist_response";
    if (response.hasAudioOut())
        dbg << "\t" << response.audioOut();
    if (response.hasScreenOut())
        dbg << "\t" << response.screenOut();
    if (response.hasDeviceAction())
        dbg << "\t" << response.deviceAction();
    if (response.speechResultCount())
        dbg << "\t" << response.speechResults();
    if (response.hasDialogStateOut())
        dbg << "\t" << response.dialogStateOut();
    if (response.hasDebugInfo())
        dbg << "\t" << response.debugInfo();
    return dbg;
}
#endif

QT_END_NAMESPACE

#include "moc_qgoogleassistantresponse.cpp"
