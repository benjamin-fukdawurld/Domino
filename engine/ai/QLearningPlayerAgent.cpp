#include "QLearningPlayerAgent.h"

#include <random>

#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/prettywriter.h>
#include <cstdio>
#include <cassert>

float QLearningPlayerAgent::getLearningRate() const
{
    return m_learningRate;
}

void QLearningPlayerAgent::setLearningRate(float learningRate)
{
    m_learningRate = learningRate;
}

float QLearningPlayerAgent::getDiscount() const
{
    return m_discountRate;
}

void QLearningPlayerAgent::setDiscount(float discount)
{
    m_discountRate = discount;
}

float QLearningPlayerAgent::getExplorationRate() const
{
    return m_explorationRate;
}

void QLearningPlayerAgent::setExplorationRate(float explorationRate)
{
    m_explorationRate = explorationRate;
}

QLearningPlayerAgent::QLearningPlayerAgent(uint8_t playerIndex, Hand *hand, Dominos *dominos) :
    AbstractPlayerAgent(playerIndex, hand, dominos),
    m_qValuesMap(),
    m_learningRate(0.1f),
    m_discountRate(0.95f),
    m_explorationRate(0.0f),
    m_victories(0),
    m_verbose(false)
{}

QLearningPlayerAgent::QLearningPlayerAgent(std::string_view inputFile, uint8_t playerIndex, Hand *hand, Dominos *dominos) :
    QLearningPlayerAgent(playerIndex, hand, dominos)
{
    assert(importQValues(inputFile));
}

QLearningPlayerAgent::~QLearningPlayerAgent()
{
    std::cout << "Victory Count: " << m_victories << std::endl;
}

bool QLearningPlayerAgent::importQValues(std::string_view file)
{
    FILE* fp = fopen(file.data(), "r"); // non-Windows use "r"

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document d;
    d.ParseStream(is);

    fclose(fp);
    return from_json(d["value"]);
}

void QLearningPlayerAgent::exportQValues(std::string_view file)
{
    rapidjson::Document d(rapidjson::kObjectType);
    d.AddMember(rapidjson::Value("value" , 5),
                to_json(d), d.GetAllocator());

    FILE* fp = fopen(file.data(), "w");

    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    d.Accept(writer);

    fclose(fp);
}

std::optional<domino_move> QLearningPlayerAgent::play()
{
    static std::random_device random_device;
    static std::default_random_engine random_engine/*(random_device())*/;
    std::uniform_real_distribution dist(0.0f, 1.0f);
    action_vector &actMap = getCurrentActions();
    prepareMap(actMap);
    ActionCell *currentAction = nullptr;
    if(dist(random_engine) > m_explorationRate)
        currentAction = getHighestQValue(actMap);
    else
    {
        size_t pos = std::uniform_int_distribution(0, static_cast<int>(actMap.size() - 1))(random_engine);
        currentAction = actMap[pos].get();
    }

    if(!m_lastActions.empty())
    {
        ActionCell *act = m_lastActions.back();
        act->value = getNewQValue(act->value, currentAction->value, getReward(false));
    }

    /*for(auto &act: actMap)
        std::cout << domino_to_string(getHand()->at(act->dominoMove.first))
                  << ": " << act->value << " ";
    std::cout << std::endl;*/

    m_lastActions.push_back(currentAction);
    return (currentAction->isPassAction ? std::optional<domino_move>() : currentAction->dominoMove);
}

void QLearningPlayerAgent::onPlayerPass(uint8_t index)
{
    if(m_verbose)
    std::cout << "Player " << static_cast<int>(index + 1) << " pass"
              << std::endl;
}

void QLearningPlayerAgent::onPlayerPlayed(uint8_t index, domino_t d)
{
    if(m_verbose)
    std::cout << "Player " << static_cast<int>(index + 1) << " : "
              << domino_to_string(d)
              << std::endl;
}

void QLearningPlayerAgent::onPlayerWon(uint8_t index)
{
    if(!m_lastActions.empty())
    {
        bool isWinner = index == getPlayerIndex();
        if(isWinner)
            ++m_victories;
        m_lastActions.back()->value = getNewQValue(m_lastActions.back()->value,
                                                    -1000, getReward(isWinner));
    }
    m_lastActions.clear();
}

const QLearningPlayerAgent::domino_hand_action_map &QLearningPlayerAgent::getQValuesMap() const
{
    return m_qValuesMap;
}

void QLearningPlayerAgent::setQValuesMap(const domino_hand_action_map &qValuesMap)
{
    m_qValuesMap = qValuesMap;
}

rapidjson::Value QLearningPlayerAgent::to_json(rapidjson::Document &doc) const
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("learning", 8), rapidjson::Value(m_learningRate),
                     doc.GetAllocator());
    result.AddMember(rapidjson::Value("discount", 8), rapidjson::Value(m_discountRate),
                     doc.GetAllocator());
    result.AddMember(rapidjson::Value("explore", 7), rapidjson::Value(m_explorationRate),
                     doc.GetAllocator());
    rapidjson::Value qvalues(rapidjson::kArrayType);
    for(auto &dominoState : m_qValuesMap)
    {
        rapidjson::Value dominosJson(rapidjson::kObjectType);
        dominosJson.AddMember(rapidjson::Value("key", 3),
                              rapidjson::Value(dominoState.first),
                              doc.GetAllocator());
        rapidjson::Value dominosValueJson(rapidjson::kArrayType);
        for(auto &handState : dominoState.second)
        {
            rapidjson::Value handJson(rapidjson::kObjectType);
            handJson.AddMember(rapidjson::Value("key", 3),
                               rapidjson::Value(handState.first),
                               doc.GetAllocator());
            rapidjson::Value handValueJson(rapidjson::kArrayType);
            for(auto &action : handState.second)
                handValueJson.PushBack(action->to_json(doc), doc.GetAllocator());

            handJson.AddMember(rapidjson::Value("value", 5),
                               handValueJson,
                               doc.GetAllocator());

            dominosValueJson.PushBack(handJson, doc.GetAllocator());
        }
        dominosJson.AddMember(rapidjson::Value("value", 5),
                              dominosValueJson,
                              doc.GetAllocator());
        qvalues.PushBack(dominosJson, doc.GetAllocator());
    }
    result.AddMember(rapidjson::Value("qvalues", 7),
                          qvalues,
                          doc.GetAllocator());

    return result;
}

bool QLearningPlayerAgent::from_json(const rapidjson::Value &val)
{
    if(!val.IsObject() || !val.HasMember("learning")
       || !val.HasMember("discount") || !val.HasMember("qvalues")
       || !val.HasMember("explore"))
        return false;

    m_learningRate = val["learning"].GetFloat();
    m_discountRate = val["discount"].GetFloat();
    m_explorationRate = val["explore"].GetFloat();

    for(auto &dominoState : val["qvalues"].GetArray())
    {
        auto &key = dominoState["key"];
        auto &dominoMap = m_qValuesMap[key.GetUint64()];
        for(auto &handState : dominoState["value"].GetArray())
        {
            auto &handKey = handState["key"];
            auto &handMap = dominoMap[handKey.GetUint64()];
            for(auto &action : handState["value"].GetArray())
            {
                ActionCellPtr act(new ActionCell(0.0f));
                if(!act->from_json(action))
                    return false;

                handMap.push_back(act);
            }
        }
    }

    return true;
}

QLearningPlayerAgent::action_vector &QLearningPlayerAgent::getActions(const state_t &state)
{
    return m_qValuesMap[state.first->hash()][state.second->hash()];
}

void QLearningPlayerAgent::prepareMap(action_vector &actMap)
{
    static std::random_device random_device;
    static std::default_random_engine random_engine/*(random_device())*/;
    auto playables = getHand()->getPlayable(*getDominos());
    std::uniform_real_distribution dist(-1.0f, 0.0f);
    if(playables.empty())
    {
        if(std::find_if(actMap.begin(), actMap.end(), [](const ActionCellPtr &act)
            {
                return act->isPassAction;
            }) == actMap.end())
        {
            actMap.emplace_back(new ActionCell(dist(random_engine)));
        }

        return;
    }

    for(auto &p : playables)
    {
        ActionCellPtr act(new ActionCell(p, dist(random_engine)));
        if(std::find_if(actMap.begin(), actMap.end(), [&act](const ActionCellPtr &other)
            {
                return act->operator==(*other);
            }) == actMap.end())
        {
            actMap.emplace_back(act);
        }
    }
}

float QLearningPlayerAgent::getNewQValue(float currentQValue, float maxFutureQValue, float reward)
{
    return (1 - m_learningRate) * currentQValue
            + (m_learningRate * (reward + m_discountRate * maxFutureQValue));
}

float QLearningPlayerAgent::getReward(bool hasWon) const
{
    float result = -(getHand()->size() / 7.0f);
    if(hasWon)
    {
        result += 1.0f;
        result *= 1 - (getDominos()->size() / 28.0f);
    }
    else
    {
        if(getDominos()->size() > 0)
        result *= 1 + (getDominos()->size() / 28.0f);
    }


    return result;
}

rapidjson::Value QLearningPlayerAgent::ActionCell::to_json(rapidjson::Document &doc) const
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("move", 4),
                     isPassAction ? rapidjson::Value(rapidjson::kNullType)
                                  : domino_move_to_json(dominoMove, doc),
                     doc.GetAllocator());

    result.AddMember(rapidjson::Value("value", 5),
                     rapidjson::Value(value),
                     doc.GetAllocator());

    return result;
}

bool QLearningPlayerAgent::ActionCell::from_json(const rapidjson::Value &val)
{
    if(!val.IsObject() || !val.HasMember("move") || !val.HasMember("value"))
        return false;

    if(val["move"].IsNull())
        isPassAction = true;
    else
    {
        domino_move_from_json(dominoMove, val["move"]);
        isPassAction = false;
    }

    value = val["value"].GetFloat();
    return true;
}
