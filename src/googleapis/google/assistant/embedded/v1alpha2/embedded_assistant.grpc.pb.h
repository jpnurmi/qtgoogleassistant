// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: google/assistant/embedded/v1alpha2/embedded_assistant.proto
// Original file comments:
// Copyright 2018 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_google_2fassistant_2fembedded_2fv1alpha2_2fembedded_5fassistant_2eproto__INCLUDED
#define GRPC_google_2fassistant_2fembedded_2fv1alpha2_2fembedded_5fassistant_2eproto__INCLUDED

#include "google/assistant/embedded/v1alpha2/embedded_assistant.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace google {
namespace assistant {
namespace embedded {
namespace v1alpha2 {

// Service that implements the Google Assistant API.
class EmbeddedAssistant final {
 public:
  static constexpr char const* service_full_name() {
    return "google.assistant.embedded.v1alpha2.EmbeddedAssistant";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Initiates or continues a conversation with the embedded Assistant Service.
    // Each call performs one round-trip, sending an audio request to the service
    // and receiving the audio response. Uses bidirectional streaming to receive
    // results, such as the `END_OF_UTTERANCE` event, while sending audio.
    //
    // A conversation is one or more gRPC connections, each consisting of several
    // streamed requests and responses.
    // For example, the user says *Add to my shopping list* and the Assistant
    // responds *What do you want to add?*. The sequence of streamed requests and
    // responses in the first gRPC message could be:
    //
    // *   AssistRequest.config
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistResponse.event_type.END_OF_UTTERANCE
    // *   AssistResponse.speech_results.transcript "add to my shopping list"
    // *   AssistResponse.dialog_state_out.microphone_mode.DIALOG_FOLLOW_ON
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    //
    //
    // The user then says *bagels* and the Assistant responds
    // *OK, I've added bagels to your shopping list*. This is sent as another gRPC
    // connection call to the `Assist` method, again with streamed requests and
    // responses, such as:
    //
    // *   AssistRequest.config
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistResponse.event_type.END_OF_UTTERANCE
    // *   AssistResponse.dialog_state_out.microphone_mode.CLOSE_MICROPHONE
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    //
    // Although the precise order of responses is not guaranteed, sequential
    // `AssistResponse.audio_out` messages will always contain sequential portions
    // of audio.
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> Assist(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(AssistRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> AsyncAssist(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(AsyncAssistRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> PrepareAsyncAssist(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(PrepareAsyncAssistRaw(context, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Initiates or continues a conversation with the embedded Assistant Service.
      // Each call performs one round-trip, sending an audio request to the service
      // and receiving the audio response. Uses bidirectional streaming to receive
      // results, such as the `END_OF_UTTERANCE` event, while sending audio.
      //
      // A conversation is one or more gRPC connections, each consisting of several
      // streamed requests and responses.
      // For example, the user says *Add to my shopping list* and the Assistant
      // responds *What do you want to add?*. The sequence of streamed requests and
      // responses in the first gRPC message could be:
      //
      // *   AssistRequest.config
      // *   AssistRequest.audio_in
      // *   AssistRequest.audio_in
      // *   AssistRequest.audio_in
      // *   AssistRequest.audio_in
      // *   AssistResponse.event_type.END_OF_UTTERANCE
      // *   AssistResponse.speech_results.transcript "add to my shopping list"
      // *   AssistResponse.dialog_state_out.microphone_mode.DIALOG_FOLLOW_ON
      // *   AssistResponse.audio_out
      // *   AssistResponse.audio_out
      // *   AssistResponse.audio_out
      //
      //
      // The user then says *bagels* and the Assistant responds
      // *OK, I've added bagels to your shopping list*. This is sent as another gRPC
      // connection call to the `Assist` method, again with streamed requests and
      // responses, such as:
      //
      // *   AssistRequest.config
      // *   AssistRequest.audio_in
      // *   AssistRequest.audio_in
      // *   AssistRequest.audio_in
      // *   AssistResponse.event_type.END_OF_UTTERANCE
      // *   AssistResponse.dialog_state_out.microphone_mode.CLOSE_MICROPHONE
      // *   AssistResponse.audio_out
      // *   AssistResponse.audio_out
      // *   AssistResponse.audio_out
      // *   AssistResponse.audio_out
      //
      // Although the precise order of responses is not guaranteed, sequential
      // `AssistResponse.audio_out` messages will always contain sequential portions
      // of audio.
      virtual void Assist(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::google::assistant::embedded::v1alpha2::AssistRequest,::google::assistant::embedded::v1alpha2::AssistResponse>* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* AssistRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* AsyncAssistRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* PrepareAsyncAssistRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> Assist(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(AssistRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> AsyncAssist(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(AsyncAssistRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>> PrepareAsyncAssist(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>>(PrepareAsyncAssistRaw(context, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void Assist(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::google::assistant::embedded::v1alpha2::AssistRequest,::google::assistant::embedded::v1alpha2::AssistResponse>* reactor) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* AssistRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* AsyncAssistRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* PrepareAsyncAssistRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Assist_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Initiates or continues a conversation with the embedded Assistant Service.
    // Each call performs one round-trip, sending an audio request to the service
    // and receiving the audio response. Uses bidirectional streaming to receive
    // results, such as the `END_OF_UTTERANCE` event, while sending audio.
    //
    // A conversation is one or more gRPC connections, each consisting of several
    // streamed requests and responses.
    // For example, the user says *Add to my shopping list* and the Assistant
    // responds *What do you want to add?*. The sequence of streamed requests and
    // responses in the first gRPC message could be:
    //
    // *   AssistRequest.config
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistResponse.event_type.END_OF_UTTERANCE
    // *   AssistResponse.speech_results.transcript "add to my shopping list"
    // *   AssistResponse.dialog_state_out.microphone_mode.DIALOG_FOLLOW_ON
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    //
    //
    // The user then says *bagels* and the Assistant responds
    // *OK, I've added bagels to your shopping list*. This is sent as another gRPC
    // connection call to the `Assist` method, again with streamed requests and
    // responses, such as:
    //
    // *   AssistRequest.config
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistRequest.audio_in
    // *   AssistResponse.event_type.END_OF_UTTERANCE
    // *   AssistResponse.dialog_state_out.microphone_mode.CLOSE_MICROPHONE
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    // *   AssistResponse.audio_out
    //
    // Although the precise order of responses is not guaranteed, sequential
    // `AssistResponse.audio_out` messages will always contain sequential portions
    // of audio.
    virtual ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_Assist : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Assist() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Assist() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssist(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Assist<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Assist : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_Assist() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackBidiHandler< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>(
          [this] { return this->Assist(); }));
    }
    ~ExperimentalWithCallbackMethod_Assist() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>* Assist() {
      return new ::grpc::internal::UnimplementedBidiReactor<
        ::google::assistant::embedded::v1alpha2::AssistRequest, ::google::assistant::embedded::v1alpha2::AssistResponse>;}
  };
  typedef ExperimentalWithCallbackMethod_Assist<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Assist : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Assist() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Assist() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Assist : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_Assist() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Assist() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssist(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Assist : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_Assist() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this] { return this->Assist(); }));
    }
    ~ExperimentalWithRawCallbackMethod_Assist() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Assist(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::google::assistant::embedded::v1alpha2::AssistResponse, ::google::assistant::embedded::v1alpha2::AssistRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Assist() {
      return new ::grpc::internal::UnimplementedBidiReactor<
        ::grpc::ByteBuffer, ::grpc::ByteBuffer>;}
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace v1alpha2
}  // namespace embedded
}  // namespace assistant
}  // namespace google


#endif  // GRPC_google_2fassistant_2fembedded_2fv1alpha2_2fembedded_5fassistant_2eproto__INCLUDED
