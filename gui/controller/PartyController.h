#ifndef PARTYCONTROLLER_H
#define PARTYCONTROLLER_H

#include <QObject>
#include "engine/statemachine/PartyStateMachine.h"
#include "gui/controller/UiPartyAgent.h"

class PartyController : public QObject
{
    Q_OBJECT
    protected:
        PartyStateMachine &m_psm;
    public:
        PartyController(PartyStateMachine &psm, QObject *parent = nullptr);

    public slots:
        void onReadyToPlay();
        void onFirstPlay(uint8_t index, Hand &h);
        void onNextPlayerTurn(uint8_t index, Hand &h);
        void onPlayerPass(uint8_t index);
};

#endif // PARTYCONTROLLER_H
