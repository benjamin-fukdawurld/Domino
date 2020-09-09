#ifndef PARTYWIDGET_H
#define PARTYWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QTreeView>
#include <QStringListModel>
#include <QPushButton>

#include "gui/model/BoardModel.h"
#include "gui/model/DominoDelegate.h"

#include "engine/Dominos.h"
#include "engine/Hand.h"

class PartyWidget : public QWidget
{
    Q_OBJECT
    protected:
        BoardModel *m_boardModel;
        QTreeView *m_boardView;
        QTableView *m_handView;
        QTreeView *m_dominosView;
        DominoDelegate *m_delegate;
        QPushButton *m_play;

    public:
        PartyWidget(QWidget *parent = nullptr);
        ~PartyWidget() override;

        BoardModel *getBoardModel();
        const BoardModel *getBoardModel() const;

        QTreeView *getDominosWidget();
        const QTreeView *getDominosWidget() const;

        QTreeView *getBoardView();
        const QTreeView *getBoardView() const;

        QTableView *getHandWidget();
        const QTableView *getHandWidget() const;

        QPushButton *getPlayButton();


    public slots:
        void setBoard(Board *b);
        void selectionChanged(QItemSelection selection);

    protected:
        void lay();
        bool isPlayEnabled();
};

#endif // PARTYWIDGET_H
