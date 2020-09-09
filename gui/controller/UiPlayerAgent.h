#ifndef UIPLAYERAGENT_H
#define UIPLAYERAGENT_H

#include "engine/statemachine/AbstractPlayerAgent.h"
#include "engine/ai/DominoProbabilityMap.h"
#include "engine/ai/DominoProbabilityTensor.h"

#include <QItemSelectionModel>

class UiPlayerAgent : public AbstractPlayerAgent
{
    protected:
        QItemSelectionModel *m_handSelectionModel;
        QItemSelectionModel *m_dominosSelectionModel;
        DominoProbabilityTensor m_probaMgr;

    public:
        using AbstractPlayerAgent::AbstractPlayerAgent;

        ~UiPlayerAgent() override = default;

        void initProbabilities(uint8_t nb_player);

        bool hasHandSelectionModel() const { return m_handSelectionModel != nullptr; }
        QItemSelectionModel *getHandSelectionModel() { return m_handSelectionModel; }
        const QItemSelectionModel *getHandSelectionModel() const { return m_handSelectionModel; }
        virtual void setHandSelectionModel(QItemSelectionModel *selectionModel);

        bool hasDominosSelectionModel() const { return m_dominosSelectionModel != nullptr; }
        QItemSelectionModel *getDominosSelectionModel() { return m_dominosSelectionModel; }
        const QItemSelectionModel *getDominosSelectionModel() const { return m_dominosSelectionModel; }
        virtual void setDominosSelectionModel(QItemSelectionModel *selectionModel);

        std::optional<domino_move> play() override;

        void onPlayerPass(uint8_t playerIndex) override;

        void onPlayerPlayed(uint8_t player_index, domino_t domino) override;

        void onPlayerWon(uint8_t) override {}
};

#endif // UIPLAYERAGENT_H
