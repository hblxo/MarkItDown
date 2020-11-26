#include "MarkdownHandler.h"

MarkdownHandler::MarkdownHandler()
{

}

//void    MarkdownHandler::wrapLine(QString leftWrap, QString rightWrap)
//{
//    (void)(leftWrap); (void)rightWrap;
//}

//void    MarkdownHandler::prependLine(QTextEdit *editor, QString str)
//{
//    QTextCursor cursor = editor->textCursor();

//    cursor.setPosition(cursor.selectionStart());
//    cursor.movePosition(QTextCursor::StartOfBlock);
//    cursor.insertText(str);
//}

bool    MarkdownHandler::linesAreAlreadyPrefixed(QTextEdit *editor, QRegularExpression rx)
{
    QTextCursor     cursor = editor->textCursor();
    QTextDocument   *doc = editor->document();

    int start = doc->findBlock(cursor.selectionStart()).blockNumber();
    int end = doc->findBlock(cursor.selectionEnd()).blockNumber();
    cursor.setPosition(cursor.selectionStart());

    for (int i = start; i <= end; i++)
    {
        cursor.movePosition(QTextCursor::StartOfBlock);
        if (cursor.block().text().contains(rx))
            return true;
        cursor.movePosition(QTextCursor::NextBlock);
    }
    return false;
}

void    MarkdownHandler::prependEachLine(QTextEdit *editor, QString str)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    int start = doc->findBlock(cursor.selectionStart()).blockNumber();
    int end = doc->findBlock(cursor.selectionEnd()).blockNumber();
    cursor.setPosition(cursor.selectionStart());

    for (int i = start; i <= end; i++)
    {
        if (cursor.block().begin() == cursor.block().end())
            continue;
        cursor.movePosition(QTextCursor::StartOfBlock);
        cursor.insertText(str);
        cursor.movePosition(QTextCursor::NextBlock);
    }
}

void    MarkdownHandler::unPrependEachLine(QTextEdit *editor, QRegularExpression rx)
{
    QTextCursor     cursor = editor->textCursor();
    QTextDocument   *doc = editor->document();

    int start = doc->findBlock(cursor.selectionStart()).blockNumber();
    int end = doc->findBlock(cursor.selectionEnd()).blockNumber();
    cursor.setPosition(cursor.selectionStart());
    for (int i = start; i <= end; i++)
    {
        cursor.movePosition(QTextCursor::StartOfBlock);
        if (cursor.block().text().contains(rx))
        {
            cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            cursor.insertText(cursor.selectedText().remove(rx));
        }
        cursor.movePosition(QTextCursor::NextBlock);
    }
}

//void    MarkdownHandler::appendLine(QTextEdit *editor, QString str)
//{
//}

void    MarkdownHandler::wrapText(QTextEdit *editor, QString leftWrap, QString rightWrap)
{
    QTextCursor cursor = editor->textCursor();
    QString     text = cursor.selectedText();

    if (rightWrap == NULL)
        rightWrap = leftWrap;
    if (text.indexOf(leftWrap) == 0 && text.lastIndexOf(rightWrap) == text.length() - rightWrap.length())
    {
        text.remove(0, leftWrap.length());
        text.remove(text.length() - rightWrap.length(), rightWrap.length());
        cursor.insertText(text);
    }
    else
        cursor.insertText(leftWrap + text + rightWrap);
}

bool    MarkdownHandler::blocksAreAlreadyWrapped(QTextEdit *editor, QString leftWrap, QString rightWrap)
{
    QTextCursor cursor = editor->textCursor();
    int         start = cursor.selectionStart();
    int         end = cursor.selectionEnd();

    cursor.setPosition(start);
    if (cursor.block().previous().text().indexOf(leftWrap) != 0
            || cursor.block().previous().text().lastIndexOf(leftWrap) != 0)
        return false;
    cursor.setPosition(end);
    if (cursor.block().next().text().indexOf(rightWrap) != 0
            || cursor.block().next().text().lastIndexOf(rightWrap) != 0)
        return false;
    return true;
}

void    MarkdownHandler::wrapParagraph(QTextEdit *editor, QString leftWrap, QString rightWrap)
{
    QTextCursor cursor = editor->textCursor();
    int         end = cursor.selectionEnd();

    if (rightWrap == NULL)
        rightWrap = leftWrap;
    cursor.beginEditBlock();
    cursor.setPosition(cursor.selectionStart());
    cursor.movePosition(QTextCursor::StartOfBlock);
    if  (blocksAreAlreadyWrapped(editor, leftWrap, rightWrap))
    {
        cursor.movePosition(QTextCursor::PreviousBlock);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.setPosition(end);
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        editor->setTextCursor(cursor);
    }
    else
    {
        editor->setTextCursor(cursor);
        cursor.insertText(leftWrap + "\r");
        cursor.setPosition(end);
        cursor.movePosition(QTextCursor::EndOfBlock);
        editor->setTextCursor(cursor);
        cursor.insertText("\r" + rightWrap);
        cursor.movePosition(QTextCursor::PreviousBlock);
        editor->setTextCursor(cursor);
    }
    cursor.endEditBlock();
}
