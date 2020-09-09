#ifndef UIPARTYAGENT_H
#define UIPARTYAGENT_H

#include <QObject>
#include "gui/widget/PartyWidget.h"
#include "engine/statemachine/PartyStateMachine.h"
#include "engine/statemachine/AbstractPartyAgent.h"
#include "engine/statemachine/AbstractPlayerAgent.h"

class UiPartyAgent : public QObject, public AbstractPartyAgent
{
    Q_OBJECT
    private:
        enum class NextAction
        {
            Invalid = -1,
            Replay = 0,
            Menu,
            Quit
        };
    protected:
        PlayerGenerator m_playerGenerator;
        std::vector<std::unique_ptr<IPlayerAgent>> m_players;

        PartyWidget *m_partyWidget;

        Hand *m_playerHand;
        uint8_t m_playerIndex;

    private:
        NextAction m_nextAction;

    public:
        explicit UiPartyAgent(PlayerGenerator playerGenerator,
                              PartyWidget *partyWidget = nullptr, QObject *parent = nullptr);

        PartyWidget *getPartyWidget() { return m_partyWidget; }
        const PartyWidget *getPartyWidget() const { return m_partyWidget; }
        void setPartyWidget(PartyWidget *widget) { m_partyWidget = widget; }

        void onPartyEntry() override {}
        void onPartyExit() override;

        void pickFirstPlayer(msm::back::state_machine<PartyDef> &fsm) override;
        void onPass(uint8_t index, msm::back::state_machine<PartyDef> &fsm) override;
        void onFirstPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm) override;
        void onPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm) override;
        void onPartyDone(uint8_t index, msm::back::state_machine<PartyDef> &fsm) override;

        void onReset(msm::back::state_machine<PartyDef> &) override {}

        void onInitEntry(uint8_t nb_players, msm::back::state_machine<PartyDef> &fsm) override;
        void onInitExit(msm::back::state_machine<PartyDef> &) override {}
        void onReadyToPlayEntry(msm::back::state_machine<PartyDef> &) override {}
        void onReadyToPlayExit(msm::back::state_machine<PartyDef> &) override {}
        void onPlayEntry(msm::back::state_machine<PartyDef> &) override {}
        void onPlayExit(msm::back::state_machine<PartyDef> &) override {}
        void onPartyDoneEntry(msm::back::state_machine<PartyDef> &) override;
        void onPartyDoneExit(msm::back::state_machine<PartyDef> &) override;
        void onNoTransition(std::string_view evt_name, int state) override;

    signals:
        void readyToPlay();
        void firstPlayerSelected(uint8_t index, Hand &h);
        void nextPlayerTurn(uint8_t index, Hand &h);
        void playerPassed(uint8_t index);
        void replayClicked(uint8_t nb_player);
        void menuClicked();
        void quitClicked();

        void playButtonStatusChange(bool value);

    public slots:
        void setPlayButtonStatus(bool enabled);
        void onPlayButtonClicked(bool);
        void onDominoPlayed(bool);
        void initBoard(Board &board, uint8_t nb_players);

    private:
        void play(uint8_t index, Board &board);
};

#endif // UIPARTYAGENT_H
