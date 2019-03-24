TEMPLATE = app
TARGET = maiassistant
QT += quickcontrols2 googleassistant

SOURCES += \
    main.cpp

RESOURCES += \
    main.qml

target.path = $$[QT_INSTALL_EXAMPLES]/googleassistant/maiassistant
INSTALLS += target
