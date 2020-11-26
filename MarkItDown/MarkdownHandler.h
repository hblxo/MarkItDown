#ifndef MARKDOWNHANDLER_H
#define MARKDOWNHANDLER_H

#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QRegularExpression>

class MarkdownHandler
{
public:
    MarkdownHandler();

    static void wrapText(QTextEdit *editor, QString leftWrap, QString rightWrap = NULL);
//    static void wrapLine(QString leftWrap, QString rightWrap = NULL);
    static bool isAlreadyPrefixed(QTextEdit *editor, QRegularExpression rx);

    //isAlreadyWrapped : check if selected blocks are already wrapped
    static bool isAlreadyWrapped(QTextEdit *editor, QString leftWrap, QString rightWrap = NULL);
    static void wrapParagraph(QTextEdit *editor, QString leftWrap, QString rightWrap = NULL);

//    static void prependLine(QTextEdit *editor, QString str);
//    static void appendLine(QTextEdit *editor, QString str);
    static void prependEachLine(QTextEdit *editor, QString str);
    static void unPrependEachLine(QTextEdit *editor, QRegularExpression rx);
};

#endif // MARKDOWNHANDLER_H
