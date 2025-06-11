TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        game.cpp \
        main.cpp \
        movingplatform.cpp \
        platform.cpp \
        platformtracker.cpp \
        player.cpp \
        sharkplatform.cpp \
        shell.cpp \
        staticplatform.cpp \
        texturemenager.cpp
INCLUDEPATH += "C:\aplikacje\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" \

LIBS += -L"C:\aplikacje\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    button.h \
    config.h \
    game.h \
    movingplatform.h \
    platform.h \
    platformtracker.h \
    player.h \
    sharkplatform.h \
    shell.h \
    staticplatform.h \
    texturemenager.h
