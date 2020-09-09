#-------------------------------------------------
#
# Project created by QtCreator 2020-08-01T02:36:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Domino
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

CONFIG += c++17

INCLUDEPATH += ../FanatikDevelopment/FDFramework/thirdparty/boost \
../FanatikDevelopment/FDFramework/thirdparty/rapidjson/include

SOURCES += \
    engine/ai/QLearningPlayerAgent.cpp \
    engine/statemachine/AbstractGameAgent.cpp \
    engine/statemachine/AbstractPartyAgent.cpp \
    engine/statemachine/AbstractPlayerAgent.cpp \
    engine/ai/DominoProbabilityMap.cpp \
    engine/ai/DominoProbabilityTensor.cpp \
    engine/ai/DoublePlayerAgent.cpp \
    engine/statemachine/GameAgent.cpp \
    engine/statemachine/PartyAgent.cpp \
    engine/statemachine/PartyStateMachineEvents.cpp \
    engine/ai/ProbabilityPlayerAgent.cpp \
    engine/ai/RandomPlayerAgent.cpp \
    engine/ai/WeightPlayerAgent.cpp \
    gui/controller/DominoApplication.cpp \
    gui/controller/UiPlayerAgent.cpp \
    gui/model/DominoDelegate.cpp \
    gui/widget/PartyDoneWidget.cpp \
        main.cpp \
\
        engine/Board.cpp \
        engine/Domino_functions.cpp \
        engine/Dominos.cpp \
        engine/Hand.cpp \
        engine/RemainingDominos.cpp \
        engine/statemachine/PartyStateMachine.cpp \
        engine/statemachine/GameStateMachine.cpp \
\
        gui/widget/ConfigPartyWidget.cpp \
        gui/widget/GameCentralWidget.cpp \
        gui/widget/GameMenuWidget.cpp \
        gui/widget/PartyWidget.cpp \
        gui/widget/MainWindow.cpp \
\
        gui/model/BoardModel.cpp \
\
        gui/controller/GameController.cpp \
        gui/controller/PartyController.cpp \
        gui/controller/UiGameAgent.cpp \
        gui/controller/UiPartyAgent.cpp \

HEADERS += \
        engine/Board.h \
        engine/DominoWrapper.h \
        engine/Domino_functions.h \
        engine/Domino_types.h \
        engine/Dominos.h \
        engine/Hand.h \
        engine/RemainingDominos.h \
    engine/ai/QLearningPlayerAgent.h \
    engine/statemachine/AbstractGameAgent.h \
    engine/statemachine/AbstractPartyAgent.h \
    engine/statemachine/AbstractPlayerAgent.h \
    engine/ai/DominoProbabilityMap.h \
    engine/ai/DominoProbabilityTensor.h \
    engine/ai/DoublePlayerAgent.h \
    engine/statemachine/GameAgent.h \
        engine/statemachine/GameStateMachine.h \
    engine/statemachine/GameStateMachineEvents.h \
    engine/statemachine/GameStateMachineStates.h \
    engine/statemachine/PartyAgent.h \
        engine/statemachine/PartyStateMachine.h \
\
    engine/statemachine/PartyStateMachineEvents.h \
    engine/statemachine/PartyStateMachineStates.h \
    engine/ai/ProbabilityPlayerAgent.h \
    engine/ai/RandomPlayerAgent.h \
    engine/ai/WeightPlayerAgent.h \
    gui/controller/DominoApplication.h \
    gui/controller/UiPlayerAgent.h \
    gui/model/DominoDelegate.h \
        gui/widget/ConfigPartyWidget.h \
        gui/widget/GameCentralWidget.h \
        gui/widget/GameMenuWidget.h \
    gui/widget/PartyDoneWidget.h \
        gui/widget/PartyWidget.h \
        gui/widget/MainWindow.h \
\
        gui/model/BoardModel.h \
\
        gui/controller/GameController.h \
        gui/controller/PartyController.h \
        gui/controller/UiGameAgent.h \
        gui/controller/UiPartyAgent.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
