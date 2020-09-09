#include "gui/model/BoardModel.h"

#include <QPixmap>

#include "engine/Domino_types.h"

BoardModel::BoardModel(QObject *parent): QAbstractItemModel (parent),
    m_board(nullptr),
    m_rootItem(new BoardModelItem(nullptr))
{

}

BoardModel::~BoardModel()
{
    delete m_rootItem;
}

QModelIndex BoardModel::getDominosRootIndex()
{
    if(m_board == nullptr || m_rootItem == nullptr)
        return QModelIndex();

    AbstractBoardModelItem *childItem = m_rootItem->child(0);
    if(childItem == nullptr)
        return QModelIndex();

    return createIndex(0, 0, childItem);
}

QModelIndex BoardModel::getHandsRootIndex() const
{
    return index(1, 0);
}

QModelIndex BoardModel::getUnusedRootIndex() const
{
    return index(2, 0);
}

QModelIndex BoardModel::getPlayerHandIndex(int player) const
{
    return index(player, 0, getHandsRootIndex());
}

QModelIndex BoardModel::getPlayerDominosIndex(int player) const
{
    return index(0, 0, getPlayerHandIndex(player));
}



int BoardModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return static_cast<AbstractBoardModelItem*>(parent.internalPointer())->columnCount();

    return m_rootItem->columnCount();
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    AbstractBoardModelItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<AbstractBoardModelItem*>(parent.internalPointer());

    if(parentItem == nullptr)
        return 0;

    return parentItem->childCount();
}

Qt::ItemFlags BoardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    AbstractBoardModelItem *item = static_cast<AbstractBoardModelItem*>(index.internalPointer());
    return item->flags(index.column());
}

QVariant BoardModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return m_rootItem->data(section, role);

    return QVariant();
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    AbstractBoardModelItem *item = static_cast<AbstractBoardModelItem*>(index.internalPointer());
    if(item == nullptr)
        return QVariant();

    return item->data(index.column(), role);
}

QModelIndex BoardModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    AbstractBoardModelItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<AbstractBoardModelItem*>(parent.internalPointer());

    AbstractBoardModelItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex BoardModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

    AbstractBoardModelItem *childItem = static_cast<AbstractBoardModelItem*>(index.internalPointer());
    AbstractBoardModelItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

void BoardModel::setBoard(Board *b)
{
    beginResetModel();
    m_board = b;
    m_rootItem->setBoard(b);
    setUpTree();
    endResetModel();
}

void BoardModel::updateModel()
{
    beginResetModel();
    endResetModel();
}

bool BoardModel::push_domino_front(domino_t d)
{
    beginInsertRows(getDominosRootIndex(), 0, 0);
    bool result = m_board->getDominos().push_front(d);
    if(result)
    {
        DominoItem *item(new DominoItem(m_board->getDominos(), 0, m_rootItem->child(0)));
        m_rootItem->child(0)->prependChild(item);
    }
    endInsertRows();
    dataChanged(getHandsRootIndex(), getUnusedRootIndex());

    return result;
}

bool BoardModel::push_domino_back(domino_t d)
{
    int row = static_cast<int>(m_board->getDominos().size());
    beginInsertRows(getDominosRootIndex(), row, row);
    bool result = m_board->getDominos().push_back(d);
    if(result)
    {
        DominoItem *item(new DominoItem(m_board->getDominos(), static_cast<size_t>(row), m_rootItem->child(0)));
        m_rootItem->child(0)->appendChild(item);
    }
    endInsertRows();
    dataChanged(getHandsRootIndex(), getUnusedRootIndex());

    return result;
}

void BoardModel::add_domino(domino_t d)
{
    int row = static_cast<int>(m_board->getDominos().size());
    beginInsertRows(getDominosRootIndex(), row, row);
    m_board->getDominos().add(d);
    DominoItem *item(new DominoItem(m_board->getDominos(), static_cast<size_t>(row), m_rootItem->child(0)));
    m_rootItem->child(0)->appendChild(item);
    endInsertRows();
}

domino_t BoardModel::pop_domino_front()
{
    beginRemoveRows(getDominosRootIndex(), 0, 0);
    getDominosItem()->removeChild(0);
    domino_t d = m_board->getDominos().pop_front();
    endRemoveRows();

    return d;
}

domino_t BoardModel::pop_domino_back()
{
    int row = static_cast<int>(m_board->getDominos().size());
    beginRemoveRows(getDominosRootIndex(), row, row);
    getDominosItem()->removeChild(row);
    domino_t d = m_board->getDominos().pop_back();
    endRemoveRows();

    return d;
}

domino_t BoardModel::pop_domino(size_t index)
{
    int row = static_cast<int>(index);
    beginRemoveRows(getDominosRootIndex(), row, row);
    getDominosItem()->removeChild(row);
    domino_t d = m_board->getDominos().pop(index);
    endRemoveRows();

    return d;
}

void BoardModel::add_domino_to_hand(size_t player, domino_t d)
{
    int col = static_cast<int>(m_board->getPlayer(player).size());
    beginInsertColumns(getPlayerHandIndex(static_cast<int>(player)), col, col);
    m_board->getPlayer(player).add(d);
    endInsertColumns();
}

domino_t BoardModel::remove_domino_from_hand(size_t player, size_t index)
{
    int col = static_cast<int>(index);
    beginRemoveColumns(getPlayerHandIndex(static_cast<int>(player)), col, col);
    Hand &h = m_board->getPlayer(player);
    domino_t result = h.remove(index);
    endRemoveColumns();
    return result;
}

void BoardModel::setUpTree()
{
    DominosItem *dominos(new DominosItem(m_board->getDominos(), m_rootItem));
    HandsItem *hands(new HandsItem(*m_board, m_rootItem));
    m_rootItem->appendChild(dominos);
    m_rootItem->appendChild(hands);
    for(size_t i = 0; i < m_board->getDominos().size(); ++i)
    {
        DominoItem *item(new DominoItem(m_board->getDominos(), i, dominos));
        dominos->appendChild(item);
    }

    for(size_t i = 0; i < m_board->getNumberOfPlayers(); ++i)
    {
        HandItem *item(new HandItem(*m_board, i, hands));
        hands->appendChild(item);
        HandDominosItem *dom_item(new HandDominosItem(*m_board, i, item));
        item->appendChild(dom_item);
    }

}

DominosItem *BoardModel::getDominosItem() { return static_cast<DominosItem*>(m_rootItem->child(0)); }
DominosItem *BoardModel::getHandsItem() { return static_cast<DominosItem*>(m_rootItem->child(1)); }

AbstractBoardModelItem::~AbstractBoardModelItem()
{
    qDeleteAll(m_childItems);
}

void AbstractBoardModelItem::clear()
{
    qDeleteAll(m_childItems);
    m_childItems.clear();
}

void AbstractBoardModelItem::prependChild(AbstractBoardModelItem *child)
{
    m_childItems.prepend(child);
}

void AbstractBoardModelItem::appendChild(AbstractBoardModelItem *child) { m_childItems.push_back(child); }

void AbstractBoardModelItem::insertChild(size_t pos, AbstractBoardModelItem *child)
{
    m_childItems.insert(static_cast<int>(pos), child);
}

AbstractBoardModelItem *AbstractBoardModelItem::child(int row)
{
    return m_childItems[row];
}

void AbstractBoardModelItem::removeChild(int row)
{
    delete  m_childItems[row];
    m_childItems.remove(row);
}

int AbstractBoardModelItem::childCount() const
{
    return m_childItems.size();
}

int AbstractBoardModelItem::columnCount() const
{
    return 1;
}

Qt::ItemFlags AbstractBoardModelItem::flags(int) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}



int AbstractBoardModelItem::row() const
{
    if (m_parent)
        return m_parent->m_childItems.indexOf(const_cast<AbstractBoardModelItem*>(this));

    return 0;
}

AbstractBoardModelItem *AbstractBoardModelItem::parentItem()
{
    return m_parent;
}

DominoItem::DominoItem(Dominos &dominos, size_t pos, AbstractBoardModelItem *parentItem):
    AbstractBoardModelItem (parentItem),
    m_dominos(dominos),
    m_domino(m_dominos.at(pos))
{

}

void DominoItem::appendChild(AbstractBoardModelItem *) { assert(false && "This method must not be called"); }

AbstractBoardModelItem *DominoItem::child(int) { return nullptr; }

int DominoItem::childCount() const { return 0; }

Qt::ItemFlags DominoItem::flags(int) const
{
    int r = row();
    if(r == 0 || static_cast<size_t>(r) == m_dominos.size() - 1)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled;
}

QVariant DominoItem::data(int column, int role) const
{
    if(column != 0)
        return QVariant();

    if(role == Qt::ToolTipRole)
    return domino_to_string(m_domino).c_str();

    if(role == Qt::DisplayRole)
            return QVariant::fromValue(m_domino);

    if(role == Qt::DecorationRole)
    {
        QString path(":/Dominos/%0.png");
        QPixmap pixmap = QPixmap(path.arg(domino_id(m_domino))).scaled(32, 64, Qt::KeepAspectRatio);
        if(domino_isDouble(m_domino))
        {
            QMatrix rm;
            rm.rotate(90);
            pixmap = pixmap.transformed(rm);
        }
        else if(m_domino.first > m_domino.second)
        {
            QMatrix rm;
            rm.rotate(180);
            pixmap = pixmap.transformed(rm);
        }

        return pixmap;
    }

    return QVariant();
}

DominosItem::DominosItem(Dominos &dominos, AbstractBoardModelItem *parentItem) :
    AbstractBoardModelItem (parentItem),
    m_dominos(dominos)
{

}

int DominosItem::columnCount() const
{
    return 1;
}

QVariant DominosItem::data(int column, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(column == 0)
        return "dominos";

    if(role == Qt::SizeHintRole)
    {
        return QSize(100, 200);
    }

    return QVariant();
}

QVariant BoardModelItem::data(int column, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(column == 0)
        return "board";

    return QVariant();
}

HandsItem::HandsItem(Board &board, AbstractBoardModelItem *parentItem) :
    AbstractBoardModelItem (parentItem),
    m_board(board)
{

}

int HandsItem::columnCount() const
{
    return 1;
}

QVariant HandsItem::data(int column, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(column == 0)
        return "hands";

    return QVariant();
}

HandItem::HandItem(Board &board, size_t pos, AbstractBoardModelItem *parentItem) :
    AbstractBoardModelItem (parentItem),
    m_board(board),
    m_hand(board.getPlayer(pos)),
    m_pos(pos)
{
}

int HandItem::columnCount() const
{
    return static_cast<int>(m_hand.size());
}

QVariant HandItem::data(int column, int role) const
{
    if(role != Qt::DisplayRole || column != 0)
        return QVariant();

    return QString("Player %0").arg(m_pos);
}

HandDominosItem::HandDominosItem(Board &board, size_t player_number, AbstractBoardModelItem *parentItem):
    AbstractBoardModelItem (parentItem),
    m_board(board),
    m_hand(m_board.getPlayer(player_number))
{

}

int HandDominosItem::columnCount() const
{
    return 1;
}

QVariant HandDominosItem::data(int column, int role) const
{
    if(column >= static_cast<int>(m_hand.size()))
    return QVariant();

    domino_t &d = m_hand.at(static_cast<size_t>(column));

    if(role == Qt::ToolTipRole)
        return domino_to_string(d).c_str();

    if(role == Qt::DisplayRole)
        return QVariant::fromValue(d);

    if(role == Qt::DecorationRole)
    {
        QString path(":/Dominos/%0.png");
        QPixmap pixmap = QPixmap(path.arg(domino_id(d))).scaled(48, 96, Qt::KeepAspectRatio);
        if(d.first > d.second)
        {
            QMatrix rm;
            rm.rotate(180);
            pixmap = pixmap.transformed(rm);
        }

        return pixmap;
    }

    return QVariant();
}

Qt::ItemFlags HandDominosItem::flags(int column) const
{
    domino_t &d = m_hand.at(static_cast<size_t>(column));
    if(m_board.getDominos().isPlaceable(d))
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}
