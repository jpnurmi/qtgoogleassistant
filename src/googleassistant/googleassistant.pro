TARGET = QtGoogleAssistant
MODULE = googleassistant

QT = core-private networkauth multimedia
DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

QMAKE_USE_PRIVATE += googleapis
QMAKE_USE += grpc grpcpp protobuf

HEADERS += \
    $$PWD/qgoogleassistant.h \
    $$PWD/qgoogleassistant_p.h \
    $$PWD/qgoogleassistantaudio.h \
    $$PWD/qgoogleassistantaudio_p.h \
    $$PWD/qgoogleassistantaudioinput.h \
    $$PWD/qgoogleassistantaudioinput_p.h \
    $$PWD/qgoogleassistantaudiooutput.h \
    $$PWD/qgoogleassistantaudiooutput_p.h \
    $$PWD/qgoogleassistantchannel_p.h \
    $$PWD/qgoogleassistantrequest.h \
    $$PWD/qgoogleassistantresponse.h \
    $$PWD/qtgoogleassistantglobal.h

SOURCES += \
    $$PWD/qgoogleassistant.cpp \
    $$PWD/qgoogleassistantaudio.cpp \
    $$PWD/qgoogleassistantaudioinput.cpp \
    $$PWD/qgoogleassistantaudiooutput.cpp \
    $$PWD/qgoogleassistantchannel.cpp \
    $$PWD/qgoogleassistantrequest.cpp \
    $$PWD/qgoogleassistantresponse.cpp

load(qt_module)
