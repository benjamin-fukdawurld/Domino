#ifndef PARTYSTATEMACHINE_H
#define PARTYSTATEMACHINE_H

#include "engine/Board.h"
#include "engine/statemachine/AbstractPartyAgent.h"
#include "engine/statemachine/PartyStateMachineEvents.h"
#include "engine/statemachine/PartyStateMachineStates.h"
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

#include <iostream>

namespace msm = boost::msm;
namespace mpl = boost::mpl;



struct PartyDef : public msm::front::state_machine_def<PartyDef>
{
        Board board;
        AbstractPartyAgent *agent;

        uint8_t nextPlayerIndex(uint8_t current_index) { return (current_index + 1) % board.getNumberOfPlayers(); }
        Hand &nextPlayerHand(uint8_t current_index) { return board.getPlayer(nextPlayerIndex(current_index)); }
        size_t previousPlayerIndex(uint8_t current_index)
        {
            return current_index == 0 ? board.getNumberOfPlayers() - 1 : --current_index;
        }

        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const &, FSM &)
        {
            //std::cout << "Entering Party" << std::endl;
            agent->onPartyEntry();
        }
        template <class Event,class FSM>
        void on_exit(Event const&, FSM &)
        {
            //std::cout << "Quitting Party" << std::endl;
            agent->onPartyExit();
        }

        typedef InitParty initial_state;

        void readyToPlayAction(const ready_to_play_event &);
        void readyToPlayAction(const reset_event &);

        void playAction(const first_play_event &evt);

        bool playGuard(const play_event &);

        void playAction(const play_event &evt);

        void playAction(const pass_event &evt);

        bool partyDoneGuard(const play_event &);

        bool partyNotDoneGuard(const play_event &evt);

        void partyDoneAction(const play_event &evt);




        typedef PartyDef pt; // makes transition table cleaner
        // Transition table for Playing
        struct transition_table : mpl::vector<
                //      Start     Event             Next         Action               Guard
                //    +-----------+--------------------+---------------+-----------------------+----------------------+
                a_row <InitParty  , ready_to_play_event     , ReadyToPlay, &pt::readyToPlayAction                             >,
                a_row <ReadyToPlay, first_play_event        , Play       , &pt::playAction                           >,
                row   <Play       , play_event              , PartyDone  , &pt::partyDoneAction  , &pt::partyDoneGuard      >,
                row   <Play       , play_event              , Play       , &pt::playAction       , &pt::partyNotDoneGuard   >,
                a_row <Play       , pass_event              , Play       , &pt::playAction                                  >,
                a_row <PartyDone  , ready_to_play_event     , ReadyToPlay, &pt::readyToPlayAction                           >,
                a_row <PartyDone  , reset_event             , ReadyToPlay, &pt::readyToPlayAction                           >
                //    +---------+-------------+---------+---------------------+----------------------+
                > {};
        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM &,int state)
        {
            agent->onNoTransition(typeid (e).name(), state);
        }
};

// back-end
typedef msm::back::state_machine<PartyDef> PartyStateMachine;

#endif // PARTYSTATEMACHINE_H
