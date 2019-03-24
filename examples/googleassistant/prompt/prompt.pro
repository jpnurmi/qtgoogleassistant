TEMPLATE = app
TARGET = prompt
QT += googleassistant
CONFIG += console

SOURCES += \
    main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/googleassistant/prompt
INSTALLS += target
