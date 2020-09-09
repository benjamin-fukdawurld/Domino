#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "engine/statemachine/GameStateMachine.h"
#include "gui/controller/UiGameAgent.h"

class GameController : public QObject
{
    Q_OBJECT
    protected:
        GameStateMachine &m_gsm;

    public:
        explicit GameController(GameStateMachine &gsm, QObject *parent = nullptr);
        virtual ~GameController();

    signals:

    public slots:
        void start();
        void stop();
        void quit();
        void goToMenu();
        void goToConfigParty();
        void goToParty(uint8_t nbPlayers);
};

#endif // GAMECONTROLLER_H
