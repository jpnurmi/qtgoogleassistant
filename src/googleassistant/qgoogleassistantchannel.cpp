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

#include "qgoogleassistantchannel_p.h"
#include "qgoogleassistant_p.h"
#include "qgoogleassistantauth.h"
#include "qgoogleassistantrequest.h"
#include "qgoogleassistantresponse.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qloggingcategory.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/private/qobject_p.h>

#include <grpc++/grpc++.h>
#include <google/assistant/embedded/v1alpha2/embedded_assistant.pb.h>
#include <google/assistant/embedded/v1alpha2/embedded_assistant.grpc.pb.h>

QT_BEGIN_NAMESPACE

namespace assistant = google::assistant::embedded::v1alpha2;

#define GRPC_ENUM_STATIC_ASSERT(Enum, Status) \
    static_assert(static_cast<grpc::StatusCode>(Enum) == Status, "QGoogleAssistant::Status mismatch");

GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Ok, grpc::OK)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Cancelled, grpc::CANCELLED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Unknown, grpc::UNKNOWN)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::InvalidArgument, grpc::INVALID_ARGUMENT)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::DeadlineExceeded, grpc::DEADLINE_EXCEEDED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::NotFound, grpc::NOT_FOUND)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::AlreadyExists, grpc::ALREADY_EXISTS)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::PermissionDenied, grpc::PERMISSION_DENIED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Unauthenticated, grpc::UNAUTHENTICATED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::ResourceExhausted, grpc::RESOURCE_EXHAUSTED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::FailedPrecondition, grpc::FAILED_PRECONDITION)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Aborted, grpc::ABORTED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::OutOfRange, grpc::OUT_OF_RANGE)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Unimplemented, grpc::UNIMPLEMENTED)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Internal, grpc::INTERNAL)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::Unavailable, grpc::UNAVAILABLE)
GRPC_ENUM_STATIC_ASSERT(QGoogleAssistant::DataLoss, grpc::DATA_LOSS)

Q_LOGGING_CATEGORY(lcChannel, "qt.googleassistant.channel")

class QGoogleAssistantChannelPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QGoogleAssistantChannel)

public:
    void init();
    void reset();

    void readResponse();
    void writeRequest(std::shared_ptr<assistant::AssistRequest> request);
    void writesDone();

    bool batch = false;
    QGoogleAssistant *assistant = nullptr;
    std::shared_ptr<grpc::Channel> channel;
    std::shared_ptr<grpc::ClientContext> context;
    std::unique_ptr<assistant::EmbeddedAssistant::Stub> stub;
    std::unique_ptr<grpc::ClientReaderWriter<assistant::AssistRequest, assistant::AssistResponse>> stream;
};

static std::shared_ptr<grpc::Channel> createChannel(QGoogleAssistant *assistant)
{
    std::shared_ptr<grpc::ChannelCredentials> creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
    return grpc::CreateCustomChannel(assistant->apiEndpoint().toStdString() + ":443", creds, grpc::ChannelArguments());
}

static std::shared_ptr<grpc::ClientContext> createContext(QGoogleAssistant *assistant)
{
    std::string json = QJsonDocument(assistant->auth()->credentials()).toJson().toStdString();
    std::shared_ptr<grpc::CallCredentials> creds = grpc::GoogleRefreshTokenCredentials(json);
    if (!creds) {
        qCritical() << "QGoogleAssistant: the credentials are invalid. "
                    << "Check README for how to get valid credentials";
    }

    std::shared_ptr<grpc::ClientContext> context = std::make_shared<grpc::ClientContext>();
    context->set_wait_for_ready(true);
    context->set_credentials(creds);
    return context;
}

void QGoogleAssistantChannelPrivate::init()
{
    qCDebug(lcChannel) << "init" << assistant->apiEndpoint();
    channel = createChannel(assistant);
    context = createContext(assistant);
    stub = assistant::EmbeddedAssistant::NewStub(channel);
    stream = stub->Assist(context.get());
}

void QGoogleAssistantChannelPrivate::reset()
{
    qCDebug(lcChannel) << "reset" << assistant->apiEndpoint();
    stream.reset();
    stub.reset();
    context.reset();
    channel.reset();
}

void QGoogleAssistantChannelPrivate::readResponse()
{
    Q_Q(QGoogleAssistantChannel);
    assistant::AssistResponse response;
    qCDebug(lcChannel) << "read response";
    while (stream->Read(&response)) {
        if (response.has_audio_out())
            qCDebug(lcChannel) << "response audio_out" << response.audio_out().audio_data().size() << "bytes";
        else
            qCDebug(lcChannel) << "response" << response.ShortDebugString().c_str();
        emit q->response(QGoogleAssistantResponse(std::make_shared<assistant::AssistResponse>(response)));
    }

    grpc::Status status = stream->Finish();
    qCDebug(lcChannel) << "finished" << status.error_code();
    if (status.error_code() != grpc::OK)
        qCDebug(lcChannel) << "error" << QString::fromStdString(status.error_message()) << QString::fromStdString(status.error_details());

    reset();

    emit q->finished(static_cast<QGoogleAssistant::Status>(status.error_code()), QString::fromStdString(status.error_message()));
}

void QGoogleAssistantChannelPrivate::writeRequest(std::shared_ptr<assistant::AssistRequest> request)
{
    if (!stream)
        init();

    // ### TODO: qCDebug(lcChannel) << "request" << request;
    if (!request->audio_in().empty())
        qCDebug(lcChannel) << "request audio_in" << request->audio_in().size() << "bytes";
    else
        qCDebug(lcChannel) << "request" << request->ShortDebugString().c_str();

    stream->Write(*request);

    if (!batch)
        readResponse();
}

void QGoogleAssistantChannelPrivate::writesDone()
{
    if (!stream)
        return;

    stream->WritesDone();
    readResponse();
}

// don't set a QObject parent - the channel is moved to a worker thread
QGoogleAssistantChannel::QGoogleAssistantChannel(QGoogleAssistant *assistant)
    : QObject(*(new QGoogleAssistantChannelPrivate))
{
    Q_D(QGoogleAssistantChannel);
    d->assistant = assistant;

    static bool init = false;
    if (!init) { // ### TODO: switch to grpc_is_initialized() when available
        grpc_init();
        qAddPostRoutine(grpc_shutdown);
        init = true;
    }
}

void QGoogleAssistantChannel::request(const QGoogleAssistantRequest &request)
{
    Q_D(QGoogleAssistantChannel);
    d->writeRequest(request.get());
}

void QGoogleAssistantChannel::beginBatch()
{
    Q_D(QGoogleAssistantChannel);
    qCDebug(lcChannel) << "audio begin";
    d->batch = true;
    request(QGoogleAssistantPrivate::get(d->assistant)->createConfig());
}

void QGoogleAssistantChannel::endBatch()
{
    Q_D(QGoogleAssistantChannel);
    qCDebug(lcChannel) << "audio end";
    d->batch = false;
    d->writesDone();
}

QT_END_NAMESPACE
