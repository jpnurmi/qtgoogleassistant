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

#include "qgoogleassistant.h"
#include "qgoogleassistant_p.h"
#include "qgoogleassistantauth.h"
#include "qgoogleassistantaudioinput.h"
#include "qgoogleassistantaudiooutput.h"
#include "qgoogleassistantchannel_p.h"
#include "qgoogleassistantrequest.h"
#include "qgoogleassistantresponse.h"

#include <QtCore/qthread.h>
#include <QtGui/qdesktopservices.h>

QT_BEGIN_NAMESPACE

QGoogleAssistantConfig QGoogleAssistantPrivate::createConfig() const
{
    QGoogleAssistantDeviceConfig deviceConfig;
    deviceConfig.setDeviceId(deviceIdentifier);
    deviceConfig.setDeviceModelId(deviceModel);

    QGoogleAssistantDialogStateIn dialogStateIn;
    dialogStateIn.setLanguageCode(locale.name());

    QGoogleAssistantAudioInConfig audioInConfig;
    audioInConfig.setSampleRateHertz(audioInput->format().sampleRate());
    audioInConfig.setEncoding(QGoogleAssistantAudioInConfig::Linear16);
    QGoogleAssistantAudioOutConfig audioOutConfig;
    audioOutConfig.setSampleRateHertz(audioOutput->format().sampleRate());
    audioOutConfig.setEncoding(QGoogleAssistantAudioOutConfig::Linear16);

    QGoogleAssistantConfig config;
    config.setDeviceConfig(deviceConfig);
    config.setDialogStateIn(dialogStateIn);
    config.setAudioInConfig(audioInConfig);
    config.setAudioOutConfig(audioOutConfig);
    return config;
}

void QGoogleAssistantPrivate::postRequest(const QGoogleAssistantRequest &request)
{
    QMetaObject::invokeMethod(channel, "request", Qt::QueuedConnection, Q_ARG(QGoogleAssistantRequest, request));
}

void QGoogleAssistantPrivate::receiveResponse(const QGoogleAssistantResponse &response)
{
    Q_Q(QGoogleAssistant);
    if (audioInput->isActive() && (response.hasAudioOut() || response.endOfUtterance()))
        audioInput->disable();
    if (response.hasAudioOut())
        audioOutput->output(response.audioOut().audioData());
    emit q->response(response);
}

void QGoogleAssistantPrivate::finish(QGoogleAssistant::Status newStatus, const QString &newError)
{
    Q_Q(QGoogleAssistant);
    bool statusChange = status != newStatus;
    bool errorChange = lastError != newError;

    status = newStatus;
    lastError = newError;

    if (statusChange)
        emit q->statusChanged(newStatus);
    if (errorChange)
        emit q->lastErrorChanged(newError);
    emit q->finished(newStatus);
}

QGoogleAssistant::QGoogleAssistant(QObject *parent)
    : QObject(*(new QGoogleAssistantPrivate), parent)
{
    Q_D(QGoogleAssistant);
    d->auth = new QGoogleAssistantAuth(this);
    d->audioInput = new QGoogleAssistantAudioInput(this);
    d->audioOutput = new QGoogleAssistantAudioOutput(this);

    connect(d->audioInput, &QGoogleAssistantAudioInput::input, this, &QGoogleAssistant::audioRequest);

    d->channel = new QGoogleAssistantChannel(this);
    connect(d->audioInput, &QGoogleAssistantAudioInput::begin, d->channel, &QGoogleAssistantChannel::beginBatch, Qt::QueuedConnection);
    connect(d->audioInput, &QGoogleAssistantAudioInput::end, d->channel, &QGoogleAssistantChannel::endBatch, Qt::QueuedConnection);
    QObjectPrivate::connect(d->channel, &QGoogleAssistantChannel::finished, d, &QGoogleAssistantPrivate::finish, Qt::QueuedConnection);
    QObjectPrivate::connect(d->channel, &QGoogleAssistantChannel::response, d, &QGoogleAssistantPrivate::receiveResponse, Qt::QueuedConnection);

    QThread *thread = new QThread(this);
    d->channel->moveToThread(thread);
    thread->start();

    qRegisterMetaType<QGoogleAssistantAudioInConfig>();
    qRegisterMetaType<QGoogleAssistantAudioOutConfig>();
    qRegisterMetaType<QGoogleAssistantScreenOutConfig>();
    qRegisterMetaType<QGoogleAssistantDeviceLocation>();
    qRegisterMetaType<QGoogleAssistantDialogStateIn>();
    qRegisterMetaType<QGoogleAssistantDeviceConfig>();
    qRegisterMetaType<QGoogleAssistantDebugConfig>();
    qRegisterMetaType<QGoogleAssistantConfig>();
    qRegisterMetaType<QGoogleAssistantRequest>();

    qRegisterMetaType<QGoogleAssistantAudioOut>();
    qRegisterMetaType<QGoogleAssistantDebugInfo>();
    qRegisterMetaType<QGoogleAssistantDeviceAction>();
    qRegisterMetaType<QGoogleAssistantDialogStateOut>();
    qRegisterMetaType<QGoogleAssistantScreenOut>();
    qRegisterMetaType<QGoogleAssistantSpeechRecognitionResult>();
    qRegisterMetaType<QGoogleAssistantResponse>();
}

QGoogleAssistant::~QGoogleAssistant()
{
    Q_D(QGoogleAssistant);
    if (d->channel) {
        QThread *thread = d->channel->thread();
        thread->quit();
        thread->wait(2000);
        delete d->channel;
    }
}

QGoogleAssistantAuth *QGoogleAssistant::auth() const
{
    Q_D(const QGoogleAssistant);
    return d->auth;
}

QGoogleAssistantAudioInput *QGoogleAssistant::audioInput() const
{
    Q_D(const QGoogleAssistant);
    return d->audioInput;
}

QGoogleAssistantAudioOutput *QGoogleAssistant::audioOutput() const
{
    Q_D(const QGoogleAssistant);
    return d->audioOutput;
}

QLocale QGoogleAssistant::locale() const
{
    Q_D(const QGoogleAssistant);
    return d->locale;
}

void QGoogleAssistant::setLocale(const QLocale &locale)
{
    Q_D(QGoogleAssistant);
    if (d->locale == locale)
        return;

    d->locale = locale;
    emit localeChanged(locale);
}

QString QGoogleAssistant::apiEndpoint() const
{
    Q_D(const QGoogleAssistant);
    return d->apiEndpoint;
}

void QGoogleAssistant::setApiEndpoint(const QString &apiEndpoint)
{
    Q_D(QGoogleAssistant);
    if (d->apiEndpoint == apiEndpoint)
        return;

    d->apiEndpoint = apiEndpoint;
    emit apiEndpointChanged(apiEndpoint);
}

QString QGoogleAssistant::deviceIdentifier() const
{
    Q_D(const QGoogleAssistant);
    return d->deviceIdentifier;
}

void QGoogleAssistant::setDeviceIdentifier(const QString &deviceIdentifier)
{
    Q_D(QGoogleAssistant);
    if (d->deviceIdentifier == deviceIdentifier)
        return;

    d->deviceIdentifier = deviceIdentifier;
    emit deviceIdentifierChanged(deviceIdentifier);
}

QString QGoogleAssistant::deviceModel() const
{
    Q_D(const QGoogleAssistant);
    return d->deviceModel;
}

void QGoogleAssistant::setDeviceModel(const QString &deviceModel)
{
    Q_D(QGoogleAssistant);
    if (d->deviceModel == deviceModel)
        return;

    d->deviceModel = deviceModel;
    emit deviceModelChanged(deviceModel);
}

QGoogleAssistant::Status QGoogleAssistant::status() const
{
    Q_D(const QGoogleAssistant);
    return d->status;
}

QString QGoogleAssistant::lastError() const
{
    Q_D(const QGoogleAssistant);
    return d->lastError;
}

void QGoogleAssistant::textRequest(const QString &text)
{
    Q_D(QGoogleAssistant);
    QGoogleAssistantConfig config = d->createConfig();
    config.setTextQuery(text);
    QGoogleAssistantRequest request;
    request.setConfig(config);
    d->postRequest(request);
}

void QGoogleAssistant::audioRequest(const QByteArray &audio)
{
    Q_D(QGoogleAssistant);
    QGoogleAssistantRequest request;
    request.setAudioIn(audio);
    d->postRequest(request);
}

void QGoogleAssistant::request(const QGoogleAssistantRequest &request)
{
    Q_D(QGoogleAssistant);
    d->postRequest(request);
}

QT_END_NAMESPACE
