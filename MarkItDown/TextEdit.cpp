#include "TextEdit.h"

TextEdit::TextEdit()
{

}

TextEdit::TextEdit(QWidget *parent)
{
    this->setParent(parent);
}

void    TextEdit::setBold()
{
    QTextCursor cursor = this->textCursor();
    this->insertPlainText("**" + cursor.selectedText() + "**");
    //to-do : unset bold if already set
}

void    TextEdit::setItalic()
{
    QTextCursor cursor = this->textCursor();
    this->insertPlainText("*" + cursor.selectedText() + "*");
    //to-do : unset italic if already set
}

void    TextEdit::setLink()
{
    QTextCursor cursor = this->textCursor();
    this->insertPlainText("["+ cursor.selectedText() + "]()");
    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
    this->setTextCursor(cursor);
    //to-do : set automatic link if an url is pasted
}

void    TextEdit::setTitle(int t)
{
    QString prefix;
    for (int i = 1; i <= t; i++)
    {
        prefix += "#";
    }
    if (t != 0)
        prefix += " ";
    QTextCursor cursor = this->textCursor();
//    moveCursor(QTextCursor::StartOfLine);
//    this->insertPlainText(prefix);
    cursor.select(QTextCursor::LineUnderCursor);
//    QRegExp exp("^(?:#+ )");
    cursor.insertText(cursor.selectedText().replace(QRegularExpression("(^(?:#+ )|^ *)"), prefix));
    // ^(
    //to-do : reverse or change Title to other size
}

void    TextEdit::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer le document"), "/home/", "");
    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << this->toPlainText();
     }
}
