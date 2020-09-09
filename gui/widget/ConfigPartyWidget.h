#ifndef CONFIGPARTYWIDGET_H
#define CONFIGPARTYWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class ConfigPartyWidget : public QWidget
{
    Q_OBJECT
    protected:
        QSpinBox *m_nbPlayerSpin;
        QPushButton *m_startPartyButton;

    public:
        explicit ConfigPartyWidget(QWidget *parent = nullptr);
        ~ConfigPartyWidget() override;

    protected:
        void lay();

    signals:
        void startParty(uint8_t);

    private slots:
        void onStartCLicked();
};

#endif // CONFIGPARTYWIDGET_H
