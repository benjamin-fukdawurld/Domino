#include "gui/controller/PartyController.h"

PartyController::PartyController(PartyStateMachine &psm, QObject *parent): QObject(parent),
    m_psm(psm)
{}

void PartyController::onReadyToPlay()
{
    m_psm.process_event(ready_to_play_event());
}

void PartyController::onFirstPlay(uint8_t index, Hand &h)
{
    m_psm.process_event(first_play_event(index, h));
}

void PartyController::onNextPlayerTurn(uint8_t index, Hand &h)
{
    m_psm.process_event(play_event(index, h));
}

void PartyController::onPlayerPass(uint8_t index)
{
    m_psm.process_event(pass_event(index, m_psm.board.getPlayer(index)));
}
