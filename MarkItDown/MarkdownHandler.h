#ifndef MARKDOWNHANDLER_H
#define MARKDOWNHANDLER_H

#include <QString>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>

class MarkdownHandler
{
public:
    MarkdownHandler();

    static void wrapLine(QString leftWrap, QString rightWrap = NULL);
    static void wrapText(QTextEdit *editor, QString leftWrap, QString rightWrap = NULL);
    static void wrapParagraph(QTextEdit *editor, QString leftWrap, QString rightWrap = NULL);
    static void prependLine(QTextEdit *editor, QString str);
    static void appendLine(QTextEdit *editor, QString str);
    static void prependEachLine(QTextEdit *editor, QString str);
};

#endif // MARKDOWNHANDLER_H
