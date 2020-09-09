#include "gui/widget/ConfigPartyWidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

ConfigPartyWidget::ConfigPartyWidget(QWidget *parent) : QWidget(parent),
    m_nbPlayerSpin(new QSpinBox(this)),
    m_startPartyButton(new QPushButton("start", this))
{
    m_nbPlayerSpin->setValue(2);
    m_nbPlayerSpin->setMinimum(2);
    m_nbPlayerSpin->setMaximum(4);
    m_nbPlayerSpin->setSingleStep(1);

    connect(m_startPartyButton, &QPushButton::clicked, this, &ConfigPartyWidget::onStartCLicked);
    lay();
}

ConfigPartyWidget::~ConfigPartyWidget() {}

void ConfigPartyWidget::lay()
{
    QVBoxLayout *vlay = new QVBoxLayout();
    QHBoxLayout *hlay = new QHBoxLayout();
    hlay->addWidget(new QLabel("Number of players:"));
    hlay->addWidget(m_nbPlayerSpin);
    vlay->addLayout(hlay);
    vlay->addWidget(m_startPartyButton);
    setLayout(vlay);
}

void ConfigPartyWidget::onStartCLicked()
{
    emit startParty(static_cast<uint8_t>(m_nbPlayerSpin->value()));
}
