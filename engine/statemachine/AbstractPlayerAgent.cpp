#include "AbstractPlayerAgent.h"

AbstractPlayerAgent::AbstractPlayerAgent(uint8_t playerIndex, Hand *hand, const Dominos *dominos):
    m_hand(hand),
    m_dominos(dominos),
    m_playerIndex(playerIndex)
{}

uint8_t AbstractPlayerAgent::getPlayerIndex() const { return m_playerIndex; }

void AbstractPlayerAgent::setPlayerIndex(uint8_t index) { m_playerIndex = index; }

Hand *AbstractPlayerAgent::getHand() { return m_hand; }

const Hand *AbstractPlayerAgent::getHand() const { return m_hand; }

void AbstractPlayerAgent::setHand(Hand *hand) { m_hand = hand; }

const Dominos *AbstractPlayerAgent::getDominos() const { return m_dominos; }

void AbstractPlayerAgent::setDominos(const Dominos *dominos) { m_dominos = dominos; }
