#ifndef GAMEMENUWIDGET_H
#define GAMEMENUWIDGET_H

#include <QPushButton>
#include <QWidget>

class GameMenuWidget : public QWidget
{
    Q_OBJECT
    protected:
        QPushButton *m_playButton;
        QPushButton *m_quitButton;

    public:
        explicit GameMenuWidget(QWidget *parent = nullptr);
        ~GameMenuWidget() override;

    signals:
        void playClicked();
        void quitClicked();

    protected:
        void lay();
};

#endif // GAMEMENUWIDGET_H
