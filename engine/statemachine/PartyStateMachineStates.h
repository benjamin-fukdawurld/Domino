#ifndef PARTYSTATEMACHINESTATES_H
#define PARTYSTATEMACHINESTATES_H

#include <boost/msm/front/state_machine_def.hpp>

#include <iostream>

namespace msm = boost::msm;

struct InitParty : public msm::front::state<>
{
        template <class Event,class FSM>
        void on_entry(Event const &evt, FSM &fsm)
        {
            //std::cout <<"Entering InitParty" << std::endl;
            fsm.agent->onInitEntry(evt.numberOfPlayers, fsm);
        }
        template <class Event,class FSM>
        void on_exit(Event const&, FSM &fsm)
        {
            //std::cout <<"Quitting InitParty" << std::endl;
            fsm.agent->onInitExit(fsm);
        }
};

struct ReadyToPlay : public msm::front::state<>
{
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& fsm)
        {
            //std::cout <<"Entering ReadyToPlay" << std::endl;
            fsm.agent->onReadyToPlayEntry(fsm);
        }
        template <class Event,class FSM>
        void on_exit(Event const&, FSM &fsm)
        {
            //std::cout <<"Quitting ReadyToPlay" << std::endl;
            fsm.agent->onReadyToPlayExit(fsm);
        }
};

struct Play : public msm::front::state<>
{
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& fsm)
        {
            //std::cout <<"Entering Play" << std::endl;
            fsm.agent->onPlayEntry(fsm);
        }
        template <class Event,class FSM>
        void on_exit(Event const&, FSM &fsm)
        {
            //std::cout <<"Quitting Play" << std::endl;
            fsm.agent->onPlayExit(fsm);
        }
};

struct PartyDone : public msm::front::state<>
{
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& fsm)
        {
            //std::cout <<"Entering PartyDone" << std::endl;
            fsm.agent->onPartyDoneEntry(fsm);
        }
        template <class Event,class FSM>
        void on_exit(Event const&, FSM &fsm)
        {
            //std::cout <<"Quitting PartyDone" << std::endl;
            fsm.agent->onPartyDoneExit(fsm);
        }
};

#endif // PARTYSTATEMACHINESTATES_H
