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

void    MarkdownHandler::prependEachLine(QTextEdit *editor, QString str)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    int start = doc->findBlock(cursor.selectionStart()).blockNumber();
    int end = doc->findBlock(cursor.selectionEnd()).blockNumber();
    cursor.setPosition(cursor.selectionStart());

    for (int i = start; i <= end; i++)
    {
        cursor.movePosition(QTextCursor::StartOfBlock);
        cursor.insertText(str);
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

void    MarkdownHandler::wrapParagraph(QTextEdit *editor, QString leftWrap, QString rightWrap)
{
    QTextCursor cursor = editor->textCursor();
    QString     tmp = cursor.selectedText();
    int         end = cursor.selectionEnd();

    if (rightWrap == NULL)
        rightWrap = leftWrap;
    cursor.beginEditBlock();
    cursor.setPosition(cursor.selectionStart());
    cursor.movePosition(QTextCursor::StartOfBlock);
    editor->setTextCursor(cursor);
    cursor.insertText(leftWrap);
    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::EndOfBlock);
    editor->setTextCursor(cursor);
    cursor.insertText(rightWrap);
    cursor.endEditBlock();
/*
    if (block.text().indexOf(leftWrap) == 0 && block.text().lastIndexOf(rightWrap) == block.text().length() - rightWrap.length())
    {
        //to-do : remove wrap if existing at the beginning and end of selected block
        //?? : right condition
*/
}
