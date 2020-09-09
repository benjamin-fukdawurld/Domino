#include "engine/statemachine/PartyAgent.h"

#include "engine/statemachine/PartyStateMachine.h"

#include <iostream>

PartyAgent::PartyAgent(PlayerGenerator playerGenerator) :
    playerGenerator(playerGenerator)
{

}

void PartyAgent::onPartyEntry()
{
    //std::cout << "Party Agent Entering Party" << std::endl;
}

void PartyAgent::onPartyExit()
{
    //std::cout << "Party Agent Leaving Party" << std::endl;
    players.clear();
}

void PartyAgent::pickFirstPlayer(msm::back::state_machine<PartyDef> &fsm)
{
    for(uint8_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j < fsm.board.getNumberOfPlayers(); ++j)
        {
            for(const auto &d: fsm.board.getPlayer(j))
            {
                if(d.first == i && d.second == i)
                {
                    fsm.process_event(first_play_event(static_cast<uint8_t>(j), fsm.board.getPlayer(j)));
                    return;
                }
            }
        }
    }

    fsm.process_event(first_play_event(0, fsm.board.getPlayer(0)));
}

void PartyAgent::onPass(uint8_t player_index, msm::back::state_machine<PartyDef> &fsm)
{
    /*std::cout << "Player " << static_cast<int>(player_index + 1) << " passed on: "
              << static_cast<int>(fsm.board.getDominos().head()) << "|"
              << static_cast<int>(fsm.board.getDominos().tail()) << std::endl;*/

    for(auto &p : players)
        p->onPlayerPass(player_index);

    fsm.process_event(play_event(fsm.nextPlayerIndex(player_index), fsm.nextPlayerHand(player_index)));
}

void PartyAgent::onFirstPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    Hand &h = fsm.board.getPlayer(index);
    auto it = std::find_if(h.begin(), h.end(), [](domino_t){ return true; });
    assert(it != h.end());

    domino_t d = h.remove(static_cast<size_t>(std::distance(h.begin(), it)));
    fsm.board.getDominos().push_front(d);

    for(auto &player : players)
        player->onPlayerPlayed(index, d);
    fsm.process_event(play_event(fsm.nextPlayerIndex(index), fsm.nextPlayerHand(index)));
}

void PartyAgent::onPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    Hand &h = fsm.board.getPlayer(index);
    //std::cout << "Player " << static_cast<int>(index + 1) << ": " << h.to_string() << std::endl;
    IPlayerAgent *player = players[index].get();
    std::optional<domino_move> dominoMove = player->play();
    if(!dominoMove.has_value())
    {
        //std::cout << "Must pass!" << std::endl;
        fsm.process_event(pass_event(index, fsm.board.getPlayer(index)));
        return;
    }

    //std::cout << "Select a domino: ";
    size_t i = dominoMove->first;
    //std::cout << h.at(i) << std::endl;

    domino_t d = h.remove(i);
    if(fsm.board.getDominos().isPlaceableFront(d))
        fsm.board.getDominos().push_front(d);
    else
        fsm.board.getDominos().push_back(d);

    for(auto &player : players)
        player->onPlayerPlayed(index, d);

    fsm.process_event(play_event(fsm.nextPlayerIndex(index), fsm.nextPlayerHand(index)));
}

void PartyAgent::onPartyDone(uint8_t index, msm::back::state_machine<PartyDef> &fsm)
{
    std::cout << "Player " << static_cast<int>(index + 1) << " won" << std::endl
              << fsm.board.to_string() << std::endl;
    for(auto &player : players)
        player->onPlayerWon(index);
}

void PartyAgent::onReset(msm::back::state_machine<PartyDef> &fsm)
{
    fsm.board.reset();
    fsm.board.serve();
}

void PartyAgent::onInitEntry(uint8_t nb_players, msm::back::state_machine<PartyDef> &fsm)
{
    fsm.board = Board();
    fsm.board.setNumberOfPlayers(nb_players);
    fsm.board.shuffleDominos();
    fsm.board.serve();
    for(uint8_t i = 0; i < nb_players; ++i)
        players.emplace_back(playerGenerator(i, fsm.board));
    //std::cout << fsm.board.to_string() << std::endl;
    fsm.process_event(ready_to_play_event());
}

void PartyAgent::onInitExit(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onReadyToPlayEntry(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onReadyToPlayExit(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onPlayEntry(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onPlayExit(msm::back::state_machine<PartyDef> &fsm)
{
    ////std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onPartyDoneEntry(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onPartyDoneExit(msm::back::state_machine<PartyDef> &fsm)
{
    //std::cout << fsm.board.to_string() << std::endl;
}

void PartyAgent::onNoTransition(std::string_view evt_name, int state)
{
    std::cout << "Party no transition from state " << state
              << " on event " << evt_name << std::endl;
}
