#-------------------------------------------------
#
# Project created by QtCreator 2018-12-12T17:19:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = core_wars_ready
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Core.cpp \
    Instr_ADD.cpp \
    Instr_DAT.cpp \
    Instr_DIV.cpp \
    Instr_DJN.cpp \
    Instr_JMN.cpp \
    Instr_JMP.cpp \
    Instr_JMZ.cpp \
    Instr_MOD.cpp \
    Instr_MOV.cpp \
    Instr_MUL.cpp \
    Instr_NOP.cpp \
    Instr_SEQ.cpp \
    Instr_SLT.cpp \
    Instr_SNE.cpp \
    Instr_SPL.cpp \
    Instr_SUB.cpp \
    Instruction.cpp \
    Mars.cpp \
    Parser.cpp \
    Arena.cpp \
    Setting.cpp

HEADERS += \
        mainwindow.h \
    Core.h \
    Factory.h \
    Instruction.h \
    Mars.h \
    Parser.h \
    ReadyDataForCommand.h \
    Warrior.h \
    Arena.h \
    Setting.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
