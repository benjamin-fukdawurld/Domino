#include "DominoApplication.h"

DominoApplication::DominoApplication(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    const QIcon openIcon = QIcon::fromTheme("application-exit", QIcon(":/images/quit.png"));
    m_quitAction = new QAction(openIcon, "&Quit...", this);
    m_quitAction->setShortcuts(QKeySequence::Quit);
    m_quitAction->setStatusTip("Quit");
}

DominoApplication::~DominoApplication()
{

}

AbstractGameAgent *DominoApplication::getGameAgent()
{
    if(m_gsm == nullptr)
        return nullptr;

    return m_gsm->agent;
}

const AbstractGameAgent *DominoApplication::getGameAgent() const
{
    if(m_gsm == nullptr)
        return nullptr;

    return m_gsm->agent;
}

AbstractPartyAgent *DominoApplication::getPartyAgent()
{
    if(m_gsm == nullptr)
        return nullptr;

    return &(m_gsm->agent->partyAgent);
}

const AbstractPartyAgent *DominoApplication::getPartyAgent() const
{
    if(m_gsm == nullptr)
        return nullptr;

    return &(m_gsm->agent->partyAgent);
}

GameController *DominoApplication::getGameController()
{
    return m_gameController;
}

const GameController *DominoApplication::getGameController() const
{
    return m_gameController;
}

void DominoApplication::setGameController(GameController *controller)
{
    m_gameController = controller;
}

PartyController *DominoApplication::getPartyController()
{
    return m_partyController;
}

const PartyController *DominoApplication::getPartyController() const
{
    return m_partyController;
}

void DominoApplication::setPartyController(PartyController *controller)
{
    m_partyController = controller;
}

void DominoApplication::onQuit()
{
    m_gameController->stop();
    quit();
}

void DominoApplication::setUp()
{
    connect(this, &DominoApplication::lastWindowClosed, this, &DominoApplication::onQuit);
    connect(m_quitAction, &QAction::triggered, this, &DominoApplication::onQuit);
}

PartyStateMachine *DominoApplication::getPartyStateMachine()
{
    return &m_gsm->get_state<PartyStateMachine&>();
}

const PartyStateMachine *DominoApplication::getPartyStateMachine() const
{
    return &m_gsm->get_state<PartyStateMachine&>();;
}
