#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QRegularExpression>
#include <QClipboard>
#include <QMenu>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
    TextEdit(QWidget *parent);

public slots:
//    void    ShowContextMenu(const QPoint& pos);

};

#endif // TEXTEDIT_H
