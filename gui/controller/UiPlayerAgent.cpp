#include "UiPlayerAgent.h"

#include <cassert>

void UiPlayerAgent::initProbabilities(uint8_t nb_player)
{
    m_probaMgr.setNumberOfPlayers(nb_player);
    m_probaMgr.setHand(m_playerIndex, *m_hand);
}

void UiPlayerAgent::setHandSelectionModel(QItemSelectionModel *selectionModel)
{
    m_handSelectionModel = selectionModel;
}

void UiPlayerAgent::setDominosSelectionModel(QItemSelectionModel *selectionModel)
{
    m_dominosSelectionModel = selectionModel;
}

std::optional<domino_move> UiPlayerAgent::play()
{
    assert(hasHand() && hasDominos() && hasHandSelectionModel() && hasDominosSelectionModel());
    auto indexes = m_handSelectionModel->selectedIndexes();
    if(indexes.empty())
        return std::nullopt;

    std::cout << m_probaMgr.to_string() << std::endl;
    size_t index = static_cast<size_t>(indexes.front().column());
    domino_t &d = m_hand->at(index);
    if(domino_isDouble(d))
    {
        if(m_dominos->isPlaceableFront(d))
            return std::make_pair(index, DominoInsertPosition::Head);

        return std::make_pair(index, DominoInsertPosition::Tail);
    }

    if(m_dominos->isPlaceableFront(d) && !m_dominos->isPlaceableBack(d))
        return std::make_pair(index, DominoInsertPosition::Head);

    if(!m_dominos->isPlaceableFront(d) && m_dominos->isPlaceableBack(d))
        return std::make_pair(index, DominoInsertPosition::Tail);

    indexes = m_dominosSelectionModel->selectedIndexes();
    m_dominosSelectionModel->clear();
    m_handSelectionModel->clear();


    return std::make_pair(index,
        (indexes.front().row() == 0 ? DominoInsertPosition::Head : DominoInsertPosition::Tail)
    );
}

void UiPlayerAgent::onPlayerPass(uint8_t player_index)
{
    m_probaMgr.playerPassed(player_index, *m_dominos);
    std::cout << m_probaMgr.to_string() << std::endl;
}

void UiPlayerAgent::onPlayerPlayed(uint8_t player_index, domino_t domino)
{
    m_probaMgr.playerPlayed(player_index, domino);
    std::cout << m_probaMgr.to_string() << std::endl;
}
