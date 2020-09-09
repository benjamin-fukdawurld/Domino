#include "gui/widget/PartyWidget.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include "gui/model/DominoDelegate.h"

PartyWidget::PartyWidget(QWidget *parent) : QWidget(parent),
    m_boardModel(new BoardModel(this)),
    m_boardView(new QTreeView(this)),
    m_handView(new QTableView(this)),
    m_dominosView(new QTreeView(this)),
    m_delegate(new DominoDelegate(this)),
    m_play(new QPushButton("play"))
{
    QHBoxLayout *hlay(new QHBoxLayout(this));
    hlay->addWidget(m_boardView, 2);
    QVBoxLayout *vlay(new QVBoxLayout());
    vlay->addWidget(m_dominosView, 4);
    vlay->addWidget(m_handView, 2);
    vlay->addWidget(m_play);
    hlay->addLayout(vlay, 5);
    setLayout(hlay);
    m_boardView->setModel(m_boardModel);
    m_dominosView->setModel(m_boardModel);
    m_dominosView->setItemDelegate(m_delegate);
    m_dominosView->setSelectionMode(QTableView::SingleSelection);
    m_handView->setModel(m_boardModel);
    m_handView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_handView->setSelectionMode(QTableView::SingleSelection);
    connect(m_handView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &PartyWidget::selectionChanged);
    connect(m_dominosView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &PartyWidget::selectionChanged);
    m_play->setEnabled(false);
}

PartyWidget::~PartyWidget() {}

BoardModel *PartyWidget::getBoardModel()
{
    return m_boardModel;
}

const BoardModel *PartyWidget::getBoardModel() const
{
    return m_boardModel;
}

QTreeView *PartyWidget::getDominosWidget()
{
    return m_dominosView;
}

const QTreeView *PartyWidget::getDominosWidget() const
{
    return m_dominosView;
}


QTreeView *PartyWidget::getBoardView()
{
    return m_boardView;
}

const QTreeView *PartyWidget::getBoardView() const
{
    return m_boardView;
}

QTableView *PartyWidget::getHandWidget()
{
    return m_handView;
}

const QTableView *PartyWidget::getHandWidget() const
{
    return m_handView;
}

QPushButton *PartyWidget::getPlayButton()
{
    return m_play;
}

void PartyWidget::setBoard(Board *b)
{
    m_boardModel->setBoard(b);
    m_dominosView->setRootIndex(m_boardModel->getDominosRootIndex());
    m_handView->setRootIndex(m_boardModel->getPlayerHandIndex(0));
    m_handView->setRowHeight(0, 96);
}

void PartyWidget::selectionChanged(QItemSelection)
{
    m_play->setEnabled(isPlayEnabled());
}

bool PartyWidget::isPlayEnabled()
{
    if(m_handView->selectionModel()->selection().empty())
        return false;

    size_t dominoIndex =
            static_cast<size_t>(m_handView->selectionModel()->selectedIndexes().front().column());
    Board *board = getBoardModel()->getBoard();
    Hand &h = board->getPlayer(0);
    domino_t d = h.at(dominoIndex);
    auto *dominoSelectionModel = m_dominosView->selectionModel();

    auto indexes = dominoSelectionModel->selectedIndexes();

    if(indexes.empty())
    {
        if(domino_isDouble(d)
           && board->getDominos().isPlaceableFront(d)
           && board->getDominos().isPlaceableBack(d))
            return true;

        if(board->getDominos().isPlaceableFront(d) && !board->getDominos().isPlaceableBack(d))
            return true;

        if(!board->getDominos().isPlaceableFront(d) && board->getDominos().isPlaceableBack(d))
            return true;

        return false;
    }

    if(indexes.front().row() == 0)
        return board->getDominos().isPlaceableFront(d);

    return board->getDominos().isPlaceableBack(d);
}

