CONFIG += protobuf static warn_off

INCLUDEPATH += $$QMAKE_INCDIR_GRPC $$QMAKE_INCDIR_GRPCPP $$QMAKE_INCDIR_PROTOBUF
LIBS += $$QMAKE_LIBS_GRPC $$QMAKE_LIBS_GRPCPP $$QMAKE_LIBS_PROTOBUF

load(qt_build_paths)
PROTOC_DIR = $$MODULE_BASE_OUTDIR/include/googleapis
MODULE_INCLUDEPATH += $$PROTOC_DIR

PROTO_PATH = ../3rdparty/googleapis

PROTO_FILES += \
    google/api/annotations.proto \
    google/api/http.proto \
    google/assistant/embedded/v1alpha2/embedded_assistant.proto \
    google/type/latlng.proto

load(qt_helper_lib)
