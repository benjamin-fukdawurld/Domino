#include "gui/controller/GameController.h"

#include <QApplication>

GameController::GameController(GameStateMachine &gsm, QObject *parent) : QObject(parent),
    m_gsm(gsm)
{
}

GameController::~GameController()
{
}

void GameController::start()
{
    m_gsm.start();
}

void GameController::stop()
{
    m_gsm.stop();
}

void GameController::quit()
{
    m_gsm.process_event(quit_event());
    m_gsm.stop();
    qApp->quit();
}

void GameController::goToMenu()
{
    m_gsm.process_event(to_menu_event());
}

void GameController::goToConfigParty()
{
    m_gsm.process_event(to_config_party_event());
}

void GameController::goToParty(uint8_t nbPlayers)
{
    m_gsm.process_event(to_party_event(nbPlayers));
}
