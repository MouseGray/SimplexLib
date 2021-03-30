CONFIG += qt

TEMPLATE = lib
DEFINES += SIMPLEXLIB_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basis.cpp \
    engine.cpp \
    matrix.cpp \
    matrixii.cpp \
    matrixiii.cpp \
    matrixiv.cpp \
    matrixv.cpp \
    matrixx.cpp \
    num.cpp \
    rgb.cpp \
    storage.cpp

HEADERS += \
    SimplexLib_global.h \
    basis.h \
    engine.h \
    matrix.h \
    matrixii.h \
    matrixiii.h \
    matrixiv.h \
    matrixv.h \
    matrixx.h \
    num.h \
    rgb.h \
    storage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
