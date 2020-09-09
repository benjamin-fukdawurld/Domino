#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractListModel>

#include <boost/msm/front/state_machine_def.hpp>

#include "engine/Board.h"

Q_DECLARE_METATYPE(domino_t);

class AbstractBoardModelItem
{
    protected:
        QVector<AbstractBoardModelItem*> m_childItems;
        AbstractBoardModelItem *m_parent;

    public:
        AbstractBoardModelItem(AbstractBoardModelItem *parent = nullptr) : m_parent(parent) {}
        virtual ~AbstractBoardModelItem();

        void clear();

        virtual void prependChild(AbstractBoardModelItem *child);
        virtual void appendChild(AbstractBoardModelItem *child);
        virtual void insertChild(size_t pos, AbstractBoardModelItem *child);
        virtual AbstractBoardModelItem *child(int row);
        virtual void removeChild(int row);
        virtual int childCount() const;
        virtual int columnCount() const;
        virtual QVariant data(int column, int role) const = 0;
        virtual Qt::ItemFlags flags(int column) const;
        virtual int row() const;
        virtual AbstractBoardModelItem *parentItem();
};

class BoardModelItem : public AbstractBoardModelItem
{
    protected:
        Board *m_board;

    public:
        BoardModelItem(Board *board, AbstractBoardModelItem *parent = nullptr) :
            AbstractBoardModelItem(parent),
            m_board(board)
        {}
        ~BoardModelItem() override = default;

        Board *getBoard() { return m_board; }
        const Board *getBoard() const { return m_board; }
        void setBoard(Board *board) { clear(); m_board = board; }


        QVariant data(int column, int role) const override;
};

class DominoItem : public AbstractBoardModelItem
{
    protected:
        Dominos &m_dominos;
        domino_t &m_domino;

    public:
        explicit DominoItem(Dominos &dominos, size_t pos, AbstractBoardModelItem *parentItem = nullptr);
        ~DominoItem() override = default;

        void appendChild(AbstractBoardModelItem*) override;
        AbstractBoardModelItem *child(int) override;
        int childCount() const override;
        Qt::ItemFlags flags(int column) const override;
        QVariant data(int column, int role) const override;

};

class DominosItem : public AbstractBoardModelItem
{
    protected:
        Dominos &m_dominos;

    public:
        explicit DominosItem(Dominos &dominos, AbstractBoardModelItem *parentItem = nullptr);
        ~DominosItem() override = default;

        int columnCount() const override;
        QVariant data(int column, int role) const override;
};

class HandDominosItem : public AbstractBoardModelItem
{
    protected:
        Board &m_board;
        Hand &m_hand;

    public:
        explicit HandDominosItem(Board &board, size_t player_number, AbstractBoardModelItem *parentItem = nullptr);
        ~HandDominosItem() override = default;

        int columnCount() const override;
        QVariant data(int column, int role) const override;
        Qt::ItemFlags flags(int column) const override;

};

class HandItem : public AbstractBoardModelItem
{
    protected:
        Board &m_board;
        Hand &m_hand;
        size_t m_pos;

    public:
        HandItem(Board &board, size_t pos, AbstractBoardModelItem *parentItem);

        int columnCount() const override;
        QVariant data(int column, int role) const override;

};

class HandsItem : public AbstractBoardModelItem
{
    protected:
        Board &m_board;

    public:
        explicit HandsItem(Board &board, AbstractBoardModelItem *parentItem = nullptr);
        ~HandsItem() override = default;

        int columnCount() const override;
        QVariant data(int column, int role) const override;
};

class BoardModel : public QAbstractItemModel
{
    protected:
        Board *m_board;
        BoardModelItem *m_rootItem;

        enum IndexIds
        {
            DominosRootId = 1,
            HandsRootId = 2,
            UnusedRootId = 3,
            HandsId = 4,
            Hand1Id = 8,
            Hand2Id = 15,
            Hand3Id = 22,
            Hand4Id = 29,
            UnusedId = 36,
            DominosId = 50,
        };

        enum Fields
        {
            DominosField,
            HandsField,
            UnusedField,
            NbFields
        };

    public:
        BoardModel(QObject *parent = nullptr);
        ~BoardModel() override;

        QModelIndex getDominosRootIndex();
        QModelIndex getHandsRootIndex() const;
        QModelIndex getUnusedRootIndex() const;
        QModelIndex getPlayerHandIndex(int player) const;
        QModelIndex getPlayerDominosIndex(int player) const;

        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                                       int role) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

        QModelIndex	parent(const QModelIndex &index) const override;

        Board *getBoard() { return m_board; }
        const Board *getBoard() const { return m_board; }
        void setBoard(Board *b);

        void updateModel();

        bool push_domino_front(domino_t d);

        bool push_domino_back(domino_t d);

        void add_domino(domino_t d);

        domino_t pop_domino_front();

        domino_t pop_domino_back();

        domino_t pop_domino(size_t index);

        void add_domino_to_hand(size_t player, domino_t d);

        domino_t remove_domino_from_hand(size_t player, size_t index);

    private:
        void setUpTree();

        DominosItem *getDominosItem();
        DominosItem *getHandsItem();
};

#endif // BOARDMODEL_H
