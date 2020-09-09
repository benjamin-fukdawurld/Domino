#ifndef GAMEENGINESTATEMACHINE_H
#define GAMEENGINESTATEMACHINE_H

#include "engine/Board.h"
#include "engine/statemachine/AbstractGameAgent.h"
#include "engine/statemachine/GameStateMachineEvents.h"
#include "engine/statemachine/GameStateMachineStates.h"
#include "engine/statemachine/PartyStateMachine.h"
#include "engine/statemachine/PartyAgent.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;

// front-end: define the FSM structure
struct GameStateMachineDef : public msm::front::state_machine_def<GameStateMachineDef>
{
        AbstractGameAgent *agent;

        GameStateMachineDef(AbstractGameAgent *agent = nullptr) : agent(agent) {}

        typedef ::PartyStateMachine Party;

        template <class Event,class FSM>
        void on_entry(Event const& ,FSM &fsm);

        template <class Event,class FSM>
        void on_exit(Event const&,FSM& );

        void menuAction(const to_menu_event &evt);

        void configPartyAction(const to_config_party_event &evt);

        void quitAction(const quit_event &evt);

        void partyAction(const to_party_event &evt);

        void replayAction(const to_party_event &evt);


        typedef InitialState initial_state;

        struct transition_table : mpl::vector<
                //     Start            Event                  Next         Action               Guard
                //   +-----------------+----------------------+------------+---------------------+----------------------+
                a_row < InitialState   , to_menu_event        , Menu       , &GameStateMachineDef::menuAction           >,
                a_row < Menu           , to_config_party_event, ConfigParty, &GameStateMachineDef::configPartyAction    >,
                a_row < Menu           , quit_event           , Quit       , &GameStateMachineDef::quitAction           >,
                a_row < ConfigParty    , to_party_event       , Party      , &GameStateMachineDef::partyAction          >,
                a_row < ConfigParty    , to_menu_event        , Menu       , &GameStateMachineDef::menuAction           >,
                a_row < Party          , to_menu_event        , Menu       , &GameStateMachineDef::menuAction           >,
                a_row < Party          , to_party_event       , Party      , &GameStateMachineDef::replayAction         >,
                a_row < Party          , quit_event           , Quit       , &GameStateMachineDef::quitAction           >
                > {};

        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM&,int state)
        {
            std::cout << "no transition from state " << state
                      << " on event " << typeid(e).name() << std::endl;
        }
};

// Pick a back-end
typedef msm::back::state_machine<GameStateMachineDef> GameStateMachine;

template <class Event,class FSM>
void GameStateMachineDef::on_entry(Event const& ,FSM &fsm)
{
    //std::cout << __func__ << std::endl;
    agent->onGameEntry(fsm.template get_state<Party&>());
}

template <class Event,class FSM>
void GameStateMachineDef::on_exit(Event const&,FSM& )
{
    //std::cout << __func__ << std::endl;
    agent->onGameExit();
}

#endif // GAMEENGINESTATEMACHINE_H
