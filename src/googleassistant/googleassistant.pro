TARGET = QtGoogleAssistant
MODULE = googleassistant

QMAKE_USE_PRIVATE = googleapis
QT = core-private networkauth multimedia
DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

INCLUDEPATH += $$QMAKE_INCDIR_GRPC $$QMAKE_INCDIR_GRPCPP $$QMAKE_INCDIR_PROTOBUF
LIBS += $$QMAKE_LIBS_GRPC $$QMAKE_LIBS_GRPCPP $$QMAKE_LIBS_PROTOBUF

HEADERS += \
    $$PWD/qgoogleassistant.h \
    $$PWD/qgoogleassistant_p.h \
    $$PWD/qgoogleassistantaudio.h \
    $$PWD/qgoogleassistantaudio_p.h \
    $$PWD/qgoogleassistantaudioinput.h \
    $$PWD/qgoogleassistantaudioinput_p.h \
    $$PWD/qgoogleassistantaudiooutput.h \
    $$PWD/qgoogleassistantaudiooutput_p.h \
    $$PWD/qgoogleassistantauth.h \
    $$PWD/qgoogleassistantchannel_p.h \
    $$PWD/qgoogleassistantrequest.h \
    $$PWD/qgoogleassistantresponse.h \
    $$PWD/qtgoogleassistantglobal.h

SOURCES += \
    $$PWD/qgoogleassistant.cpp \
    $$PWD/qgoogleassistantaudio.cpp \
    $$PWD/qgoogleassistantaudioinput.cpp \
    $$PWD/qgoogleassistantaudiooutput.cpp \
    $$PWD/qgoogleassistantauth.cpp \
    $$PWD/qgoogleassistantchannel.cpp \
    $$PWD/qgoogleassistantrequest.cpp \
    $$PWD/qgoogleassistantresponse.cpp

load(qt_module)
