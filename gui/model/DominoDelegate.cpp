#include "DominoDelegate.h"

#include <engine/Domino_types.h>
#include <engine/Domino_functions.h>

#include <QPainter>

void DominoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    painter->save();
    if (index.data().canConvert<domino_t>())
    {
        domino_t d = qvariant_cast<domino_t>(index.data());

        if(!domino_isDouble(d))
        {
            painter->setRenderHint(QPainter::Antialiasing, true);
            const int xOffset = 16;
            painter->translate(xOffset, 0);
        }
    }

    QStyledItemDelegate::paint(painter, option, index);
    painter->restore();
}

QSize DominoDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *DominoDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void DominoDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QStyledItemDelegate::setEditorData(editor, index);
}

void DominoDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QStyledItemDelegate::setModelData(editor, model, index);
}

void DominoDelegate::commitAndCloseEditor()
{

}
