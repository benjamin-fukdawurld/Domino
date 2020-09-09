#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30 //or whatever you need
#define BOOST_MPL_LIMIT_MAP_SIZE 30 //or whatever you need

#define BOOST_DISABLE_PRAGMA_MESSAGE

#include "gui/controller/DominoApplication.h"
#include <QPushButton>

#include <string>
#include <iostream>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "engine/statemachine/GameStateMachine.h"
#include "engine/statemachine/PartyStateMachine.h"
#include "engine/ai/DoublePlayerAgent.h"
#include "engine/statemachine/PartyAgent.h"
#include "engine/statemachine/GameStateMachineEvents.h"
#include "gui/widget/MainWindow.h"
#include "gui/widget/GameCentralWidget.h"
#include "gui/controller/UiPartyAgent.h"

#include "engine/ai/QLearningPlayerAgent.h"

#include "rapidjson/filewritestream.h"
#include <rapidjson/prettywriter.h>
#include <cstdio>

using namespace rapidjson;

int main_no_gui(int, char *[])
{
    PartyAgent p_agent([](uint8_t playerIndex, Board &b) -> IPlayerAgent* {
        //if(playerIndex == 0)
            return new QLearningPlayerAgent(std::string("output")
                                            + std::to_string(static_cast<int>(playerIndex))
                                            + ".json",
                                            playerIndex, &b.getPlayer(playerIndex), &b.getDominos());

        //return new DoubleWeightPlayerAgent(playerIndex, &b.getPlayer(playerIndex), &b.getDominos());
    });
    GameAgent agent(p_agent);
    GameStateMachine gsm(&agent);
    gsm.start();
    gsm.process_event(to_menu_event());
    gsm.process_event(to_config_party_event());
    gsm.process_event(to_party_event(4));

    std::cout << "\n----------------------------------------------------------------------\n";

    PartyStateMachine &fsm = gsm.get_state<PartyStateMachine&>();
    /*for(size_t i = 0; i < 500; ++i)
    {
        fsm.board.reset();
        fsm.board.serve();
        gsm.replayAction(to_party_event(4));
    }

    for(size_t i = 0; i < 4; ++i)
        static_cast<QLearningPlayerAgent*>(p_agent.players[i].get())->setExplorationRate(0.8f);

    for(size_t i = 0; i < 10; ++i)
    {
        for(size_t i = 0; i < 1000; ++i)
        {
            fsm.board.reset();
            fsm.board.serve();
            gsm.replayAction(to_party_event(4));
        }

        static_cast<QLearningPlayerAgent*>(p_agent.players[0].get())->setVerbose(true);
        fsm.board.reset();
        fsm.board.serve();
        gsm.replayAction(to_party_event(4));
        static_cast<QLearningPlayerAgent*>(p_agent.players[0].get())->setVerbose(false);

        std::cout << "\n----------------------------------------------------------------------\n";
    }

    for(size_t i = 0; i < 4; ++i)
        static_cast<QLearningPlayerAgent*>(p_agent.players[i].get())->setExplorationRate(0.0f);*/

    for(size_t i = 0; i < 99; ++i)
    {
        fsm.board.reset();
        fsm.board.serve();
        gsm.replayAction(to_party_event(4));

        std::cout << "\n----------------------------------------------------------------------\n";
    }


    for(size_t i = 0; i < 4; ++i)
    {
        static_cast<QLearningPlayerAgent*>(p_agent.players[i].get())->exportQValues(
                std::string("output") + std::to_string(i) + ".json"
            );
    }

    gsm.stop();
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc > 1 && std::string(argv[1]) == "--no-gui")
        return main_no_gui(argc - 1, argv + 1);

    GameStateMachine gsm;
    DominoApplication app(argc, argv);
    GameController gameController(gsm, &app);
    app.setGameStateMachine(&gsm);
    PartyController partyController(*app.getPartyStateMachine(), &app);
    app.setGameController(&gameController);
    app.setPartyController(&partyController);
    app.setUp();
    MainWindow w;
    w.show();

    return app.exec();
}
