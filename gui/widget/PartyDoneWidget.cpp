#include "PartyDoneWidget.h"

PartyDoneWidget::PartyDoneWidget(QWidget *parent) :
    QMessageBox(parent),
    m_replayButton(addButton("replay", QMessageBox::ActionRole)),
    m_menuButton(addButton("menu", QMessageBox::ActionRole)),
    m_quitButton(addButton("quit", QMessageBox::ActionRole))
{
}

PartyDoneWidget::~PartyDoneWidget()
{

}

bool PartyDoneWidget::isReplayClicked()
{
    return clickedButton() == m_replayButton;
}

bool PartyDoneWidget::isMenuClicked()
{
    return clickedButton() == m_menuButton;
}

bool PartyDoneWidget::isQuitClicked()
{
    return clickedButton() == m_quitButton;
}
