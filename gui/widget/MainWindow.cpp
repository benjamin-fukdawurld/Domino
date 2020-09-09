#include "MainWindow.h"

#include "gui/controller/DominoApplication.h"

#include "engine/ai/DoublePlayerAgent.h"

#include <gui/controller/UiPlayerAgent.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_menuWidget(new GameMenuWidget(this)),
      m_configWidget(new ConfigPartyWidget(this)),
      m_partyWidget(new PartyWidget(this)),
      m_centralWidget(new GameCentralWidget(m_menuWidget, m_configWidget, m_partyWidget, this)),
      m_partyAgent([](uint8_t index, Board &b) -> IPlayerAgent*
                    {
                        if(index == 0)
                            return new UiPlayerAgent(index, &b.getPlayer(index), &b.getDominos());

                        return new DoubleWeightPlayerAgent(index, &b.getPlayer(index), &b.getDominos());
                    },
                    m_partyWidget, this),
      m_gameAgent(m_centralWidget, m_partyAgent, this)
{
    setMinimumSize(600, 480);
    qApp->getGameStateMachine()->agent = &m_gameAgent;
    qApp->getGameController()->start();

    setCentralWidget(m_centralWidget);
    connect(m_menuWidget, &GameMenuWidget::playClicked, qApp->getGameController(), &GameController::goToConfigParty);
    connect(m_menuWidget, &GameMenuWidget::quitClicked, qApp->getGameController(), &GameController::quit);
    connect(m_configWidget, &ConfigPartyWidget::startParty, qApp->getGameController(), &GameController::goToParty);
    connect(&m_partyAgent, &UiPartyAgent::readyToPlay, qApp->getPartyController(), &PartyController::onReadyToPlay);
    connect(&m_partyAgent, &UiPartyAgent::firstPlayerSelected, qApp->getPartyController(), &PartyController::onFirstPlay);
    connect(&m_partyAgent, &UiPartyAgent::nextPlayerTurn, qApp->getPartyController(), &PartyController::onNextPlayerTurn);
    connect(&m_partyAgent, &UiPartyAgent::playerPassed, qApp->getPartyController(), &PartyController::onPlayerPass);

    connect(&m_partyAgent, &UiPartyAgent::replayClicked, this, &MainWindow::onReplay);
    connect(&m_partyAgent, &UiPartyAgent::menuClicked, qApp->getGameController(), &GameController::goToMenu);
    connect(&m_partyAgent, &UiPartyAgent::quitClicked, qApp->getGameController(), &GameController::quit);

    qApp->getGameController()->goToMenu();
}

MainWindow::~MainWindow()
{
    qApp->getGameController()->stop();
}

void MainWindow::onReplay(uint8_t nb_players)
{
    m_partyAgent.initBoard(qApp->getPartyStateMachine()->board, nb_players);
    qApp->getPartyController()->onReadyToPlay();
}
