#ifndef DOMINOAPPLICATION_H
#define DOMINOAPPLICATION_H

#include <QApplication>
#include <QAction>

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<DominoApplication *>(QCoreApplication::instance()))

#include <engine/statemachine/GameStateMachine.h>
#include <engine/statemachine/AbstractGameAgent.h>

#include "gui/controller/GameController.h"
#include "gui/controller/PartyController.h"

class DominoApplication : public QApplication
{
    Q_OBJECT
    protected:
        GameStateMachine *m_gsm;
        GameController *m_gameController;
        PartyController *m_partyController;

        QAction *m_quitAction;

    public:
        DominoApplication(int argc, char *argv[]);
        ~DominoApplication() override;

        GameStateMachine *getGameStateMachine() { return m_gsm; }
        const GameStateMachine *getGameStateMachine() const { return m_gsm; }
        void setGameStateMachine(GameStateMachine *gsm) { m_gsm = gsm; }

        PartyStateMachine *getPartyStateMachine();
        const PartyStateMachine *getPartyStateMachine() const;

        AbstractGameAgent *getGameAgent();
        const AbstractGameAgent *getGameAgent() const;

        AbstractPartyAgent *getPartyAgent();
        const AbstractPartyAgent *getPartyAgent() const;

        GameController *getGameController();
        const GameController *getGameController() const;
        void setGameController(GameController *controller);

        PartyController *getPartyController();
        const PartyController *getPartyController()const;
        void setPartyController(PartyController *controller);

        QAction *getQuitAction() { return m_quitAction; }

    public slots:
        void onQuit();

        void setUp();
};

#endif // DOMINOAPPLICATION_H
