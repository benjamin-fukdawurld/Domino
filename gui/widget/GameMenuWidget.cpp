#include "gui/widget/GameMenuWidget.h"

#include <QVBoxLayout>

GameMenuWidget::GameMenuWidget(QWidget *parent) : QWidget(parent),
    m_playButton(new QPushButton("play", this)),
    m_quitButton(new QPushButton("quit", this))
{
    lay();
    connect(m_playButton, &QPushButton::clicked, this, &GameMenuWidget::playClicked);
    connect(m_quitButton, &QPushButton::clicked, this, &GameMenuWidget::quitClicked);
}

GameMenuWidget::~GameMenuWidget() {}

void GameMenuWidget::lay()
{
    QVBoxLayout *vlay(new QVBoxLayout(this));
    vlay->addStretch(2);
    vlay->addWidget(m_playButton);
    vlay->addStretch(1);
    vlay->addWidget(m_quitButton);
    vlay->addStretch(2);
    setLayout(vlay);
}
