TEMPLATE = subdirs
SUBDIRS += \
    googleapis \
    googleassistant

googleassistant.depends += \
    googleapis
