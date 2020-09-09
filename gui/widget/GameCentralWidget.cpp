#include "gui/widget/GameCentralWidget.h"

#include <QApplication>

GameCentralWidget::GameCentralWidget(GameMenuWidget *menu, ConfigPartyWidget *config, PartyWidget *party, QWidget *parent) :
    QStackedWidget(parent)
{
    addWidget(menu);
    addWidget(config);
    addWidget(party);
    setCurrentIndex(0);

    connect(menu, &GameMenuWidget::playClicked, this, &GameCentralWidget::setConfigPartyWidget);
    connect(config, &ConfigPartyWidget::startParty, this, &GameCentralWidget::setPartyWidget);
}

GameCentralWidget::~GameCentralWidget()
{

}

QWidget *GameCentralWidget::getWidget(GameCentralWidget::Widget widget)
{
    return QStackedWidget::widget(static_cast<int>(widget));
}

GameMenuWidget *GameCentralWidget::getMenuWidget()
{
    return static_cast<GameMenuWidget*>(getWidget(Widget::Menu));
}

ConfigPartyWidget *GameCentralWidget::getConfigPartyWidget()
{
    return static_cast<ConfigPartyWidget*>(getWidget(Widget::ConfigParty));
}

PartyWidget *GameCentralWidget::getPartyWidget()
{
    return static_cast<PartyWidget*>(getWidget(Widget::Party));
}

void GameCentralWidget::setVisibleWidget(GameCentralWidget::Widget widget)
{
    setCurrentIndex(static_cast<int>(widget));
}

void GameCentralWidget::setMenuWidget()
{
    setVisibleWidget(Widget::Menu);
}

void GameCentralWidget::setConfigPartyWidget()
{
    setVisibleWidget(Widget::ConfigParty);
}

void GameCentralWidget::setPartyWidget()
{
    setVisibleWidget(Widget::Party);
}
