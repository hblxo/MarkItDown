#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QRegularExpression>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
    TextEdit(QWidget *parent);

public slots:
    void    setBold();
    void    setItalic();
    void    setLink();
    void    save();
    void    setTitle(int t);
};

#endif // TEXTEDIT_H
