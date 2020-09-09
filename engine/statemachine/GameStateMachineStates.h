#ifndef GAMESTATEMACHINESTATES_H
#define GAMESTATEMACHINESTATES_H

#include <boost/msm/front/state_machine_def.hpp>

#include <iostream>

namespace msm = boost::msm;

struct InitialState : public msm::front::state<> {};

struct Menu : public msm::front::state<>
{
        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& ) { /*std::cout << "entering: Menu" << std::endl;*/ }
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) { /*std::cout << "leaving: Menu" << std::endl;*/ }
};

struct ConfigParty : public msm::front::state<>
{
        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& ) { /*std::cout << "entering: ConfigParty" << std::endl;*/ }
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) { /*std::cout << "leaving: ConfigParty" << std::endl;*/ }
};

struct Quit : public msm::front::state<>
{
        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& ) {/*std::cout << "entering: Quit" << std::endl;*/}
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) {/*std::cout << "leaving: Quit" << std::endl;*/}
};

#endif // GAMESTATEMACHINESTATES_H
