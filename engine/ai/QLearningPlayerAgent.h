#ifndef QLEARNINGAGENT_H
#define QLEARNINGAGENT_H

#include <engine/statemachine/AbstractPlayerAgent.h>

#include <unordered_map>
#include <memory>
#include <sstream>

class QLearningPlayerAgent : public AbstractPlayerAgent
{
    private:
        struct ActionCell
        {
            domino_move dominoMove;
            float value;
            bool isPassAction;

            ActionCell(float value): value(value), isPassAction(true) {}
            ActionCell(domino_move dominoMove, float value) : dominoMove(dominoMove), value(value), isPassAction(false) {}

            bool operator==(const ActionCell &cell)
            {
                return (isPassAction && cell.isPassAction)
                        || (dominoMove.first == cell.dominoMove.first
                            && dominoMove.second == cell.dominoMove.second);
            }

            bool operator<(const ActionCell &cell)
            {
                return value < cell.value;
            }

            rapidjson::Value to_json(rapidjson::Document &doc) const;

            bool from_json(const rapidjson::Value &val);
        };

    public:
        typedef std::shared_ptr<ActionCell> ActionCellPtr;
        typedef std::vector<ActionCellPtr> action_vector;
        typedef std::unordered_map<size_t, action_vector> hand_action_map;
        typedef std::unordered_map<size_t, hand_action_map> domino_hand_action_map;
        typedef std::pair<const Dominos*, const Hand *> state_t;

    protected:
        domino_hand_action_map m_qValuesMap;
        std::vector<ActionCell*> m_lastActions;
        float m_learningRate;
        float m_discountRate;
        float m_explorationRate;
        int m_victories;
        bool m_verbose;

    public:
        QLearningPlayerAgent(uint8_t playerIndex, Hand *hand, Dominos *dominos);
        QLearningPlayerAgent(std::string_view inputFile, uint8_t playerIndex, Hand *hand, Dominos *dominos);

        ~QLearningPlayerAgent() override;

        bool importQValues(std::string_view file);
        void exportQValues(std::string_view file);

        std::optional<domino_move> play() override;
        void onPlayerPass(uint8_t playerIndex) override;
        void onPlayerPlayed(uint8_t playerIndex, domino_t domino) override;
        void onPlayerWon(uint8_t index) override;

        const domino_hand_action_map &getQValuesMap() const;
        void setQValuesMap(const domino_hand_action_map &qValuesMap);

        bool isVerbose() const { return m_verbose; }
        void setVerbose(bool value) { m_verbose = value; }

        rapidjson::Value to_json(rapidjson::Document &doc) const;

        bool from_json(const rapidjson::Value &val);

        float getLearningRate() const;
        void setLearningRate(float learningRate);

        float getDiscount() const;
        void setDiscount(float discount);

        float getExplorationRate() const;
        void setExplorationRate(float explorationRate);

    private:
        state_t getCurrentState() const { return std::make_pair(getDominos(), getHand()); }
        action_vector &getActions(const state_t &state);
        action_vector &getCurrentActions() { return getActions(getCurrentState()); }

        void prepareMap(action_vector &actMap);

        float getNewQValue(float currentQValue, float maxFutureQValue, float reward);

        ActionCell *getHighestQValue(action_vector &actions)
        {
            return std::max_element(actions.begin(), actions.end(),
                [](const ActionCellPtr &a, const ActionCellPtr &b)
                {
                    return a->value < b->value;
                })->get();
        }

        float getReward(bool hasWon) const;
};

#endif // QLEARNINGAGENT_H
