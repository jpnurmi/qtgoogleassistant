#!/bin/bash

PROTOC=protoc
GRPC_CPP_PLUGIN=/usr/bin/grpc_cpp_plugin

PROTO_DIR=../3rdparty/googleapis
PROTO_FILES="\
    google/api/annotations.proto \
    google/api/http.proto \
    google/assistant/embedded/v1alpha2/embedded_assistant.proto \
    google/type/latlng.proto"

rm -f googleapis.pri
for file in $PROTO_FILES; do
    (set -x; $PROTOC $PROTO_DIR/$file --proto_path=$PROTO_DIR --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN)
    echo "HEADERS += ${file/.proto/.pb.h}" >> googleapis.pri
    echo "HEADERS += ${file/.proto/.grpc.pb.h}" >> googleapis.pri
    echo "SOURCES += ${file/.proto/.pb.cc}" >> googleapis.pri
    echo "SOURCES += ${file/.proto/.grpc.pb.cc}" >> googleapis.pri
done
