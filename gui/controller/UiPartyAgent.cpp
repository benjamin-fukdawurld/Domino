#include "gui/controller/UiPartyAgent.h"

#include "UiPlayerAgent.h"
#include "gui/widget/PartyDoneWidget.h"

UiPartyAgent::UiPartyAgent(PlayerGenerator playerGenerator,
                           PartyWidget *partyWidget, QObject *parent) :
    QObject(parent),
    m_playerGenerator(playerGenerator),
    m_partyWidget(partyWidget),
    m_nextAction(NextAction::Invalid)
{
    connect(m_partyWidget->getPlayButton(), &QPushButton::clicked, this, &UiPartyAgent::onPlayButtonClicked);
    connect(this, &UiPartyAgent::playButtonStatusChange, this, &UiPartyAgent::setPlayButtonStatus);
    m_partyWidget->getPlayButton()->setEnabled(false);
}

void UiPartyAgent::onPartyExit()
{
    m_players.clear();
}

void UiPartyAgent::pickFirstPlayer(msm::back::state_machine<PartyDef> &fsm)
{
    for(uint8_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j < fsm.board.getNumberOfPlayers(); ++j)
        {
            for(const auto &d: fsm.board.getPlayer(j))
            {
                if(d.first == i && d.second == i)
                {
                    emit firstPlayerSelected(static_cast<uint8_t>(j), fsm.board.getPlayer(j));
                    return;
                }
            }
        }
    }

    emit firstPlayerSelected(static_cast<uint8_t>(0), fsm.board.getPlayer(0));
}

void UiPartyAgent::onPass(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    std::cout << "Player " << static_cast<int>(index + 1) << " passed on: "
              << static_cast<int>(fsm.board.getDominos().head()) << "|"
              << static_cast<int>(fsm.board.getDominos().tail()) << std::endl;

    m_playerHand = &fsm.nextPlayerHand(index);
    m_playerIndex = fsm.nextPlayerIndex(index);

    for(auto &player : m_players)
        player->onPlayerPass(index);

    emit playButtonStatusChange(true);
}

void UiPartyAgent::onFirstPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    Hand &h = fsm.board.getPlayer(index);
    std::cout << fsm.board.to_string() << std::endl;
    for(uint8_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j < h.size(); ++j)
        {
            const domino_t &d = h.at(j);
            if(d.first == i && d.second == i)
            {
                m_partyWidget->getBoardModel()->push_domino_front(d);
                m_partyWidget->getBoardModel()->remove_domino_from_hand(index, j);
                m_playerHand = &fsm.nextPlayerHand(index);
                m_playerIndex = fsm.nextPlayerIndex(index);
                for(auto &player : m_players)
                    player->onPlayerPlayed(index, d);
                onDominoPlayed(true);

                return;
            }
        }
    }
}

void UiPartyAgent::onPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    if(index == 0)
    {
        emit playButtonStatusChange(true);
        return;
    }

    emit playButtonStatusChange(false);
    play(index, fsm.board);

    onDominoPlayed(true);
}

void UiPartyAgent::onPartyDone(uint8_t index, msm::back::state_machine<PartyDef> &)
{
    m_partyWidget->getHandWidget()->setEnabled(false);
    PartyDoneWidget msgBox(m_partyWidget);
    msgBox.setText(QString("Player %0 won !").arg(index + 1));
    msgBox.setDetailedText(QString::fromStdString(m_partyWidget->getBoardModel()->getBoard()->to_string()));
    msgBox.exec();


    if(msgBox.isReplayClicked())
        m_nextAction = NextAction::Replay;
    else if(msgBox.isMenuClicked())
        m_nextAction = NextAction::Menu;
    else if(msgBox.isQuitClicked())
        m_nextAction = NextAction::Quit;

    m_partyWidget->getHandWidget()->setEnabled(true);
}

void UiPartyAgent::onInitEntry(uint8_t nb_players, msm::back::state_machine<PartyDef> &fsm)
{
    initBoard(fsm.board, nb_players);
    emit readyToPlay();
}

void UiPartyAgent::onPartyDoneEntry(msm::back::state_machine<PartyDef> &)
{
    emit playButtonStatusChange(false);
    switch(m_nextAction)
    {
        case NextAction::Replay:
        emit replayClicked(static_cast<uint8_t>(m_players.size()));
        break;

        case NextAction::Menu:
        emit menuClicked();
        break;

        case NextAction::Quit:
            emit quitClicked();
        break;

        default:
        break;
    }

    m_nextAction = NextAction::Invalid;
}

void UiPartyAgent::onPartyDoneExit(msm::back::state_machine<PartyDef> &)
{
}

void UiPartyAgent::onNoTransition(std::string_view evt_name, int state)
{
    std::cout << "Party no transition from state " << state
              << " on event " << evt_name << std::endl;
}

void UiPartyAgent::setPlayButtonStatus(bool)
{
    if(m_players.empty())
        return;
    if(m_players[0]->getHand()->canPlay(*m_players[0]->getDominos()))
        m_partyWidget->getPlayButton()->setText("play");
    else
    {
        m_partyWidget->getPlayButton()->setEnabled(true);
        m_partyWidget->getPlayButton()->setText("pass");
    }
}

void UiPartyAgent::onPlayButtonClicked(bool)
{
    play(0, *m_partyWidget->getBoardModel()->getBoard());
    onDominoPlayed(true);
}

void UiPartyAgent::onDominoPlayed(bool)
{
    emit nextPlayerTurn(m_playerIndex, *m_playerHand);
}

void UiPartyAgent::initBoard(Board &board, uint8_t nb_players)
{
    m_partyWidget->getPlayButton()->setEnabled(false);
    board.clear();
    board.setNumberOfPlayers(nb_players);
    board.shuffleDominos();
    board.serve();
    m_partyWidget->setBoard(&board);
    m_players.clear();
    for(uint8_t i = 0; i < nb_players; ++i)
        m_players.emplace_back(m_playerGenerator(i, board));

    UiPlayerAgent *player = static_cast<UiPlayerAgent*>(m_players[0].get());
    player->setHandSelectionModel(m_partyWidget->getHandWidget()->selectionModel());
    player->setDominosSelectionModel(m_partyWidget->getDominosWidget()->selectionModel());
    player->initProbabilities(nb_players);
}

void UiPartyAgent::play(uint8_t index, Board &board)
{
    Hand &h = board.getPlayer(index);
    std::cout << "Player " << static_cast<int>(index + 1) << ": " << h.to_string() << std::endl;
    IPlayerAgent *player = m_players[index].get();
    std::optional dominoIndex = player->play();
    if(!dominoIndex.has_value())
    {
        std::cout << "Must pass!" << std::endl;
        emit playerPassed(index);
        return;
    }

    std::cout << "Select a domino: ";
    auto dominoMove = dominoIndex.value();
    std::cout << h.at(dominoMove.first) << std::endl;

    domino_t d = m_partyWidget->getBoardModel()->remove_domino_from_hand(index, dominoMove.first);
    if(dominoMove.second == Head)
        m_partyWidget->getBoardModel()->push_domino_front(d);
    else
        m_partyWidget->getBoardModel()->push_domino_back(d);

    for(auto &player : m_players)
        player->onPlayerPlayed(index, d);

    m_playerIndex = (index + 1) % board.getNumberOfPlayers();
    m_playerHand = &board.getPlayer(m_playerIndex);
}
