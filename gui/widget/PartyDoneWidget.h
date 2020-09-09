#ifndef PARTYDONEWIDGET_H
#define PARTYDONEWIDGET_H

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>

class PartyDoneWidget : public QMessageBox
{
    Q_OBJECT
    private:
        QPushButton *m_replayButton;
        QPushButton *m_menuButton;
        QPushButton *m_quitButton;

    public:
        PartyDoneWidget(QWidget *parent = nullptr);
        ~PartyDoneWidget() override;
        bool isReplayClicked();
        bool isMenuClicked();
        bool isQuitClicked();
};

#endif // PARTYDONEWIDGET_H
