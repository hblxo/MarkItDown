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

    static void wrapText(QTextEdit *editor, const QString& leftWrap, QString rightWrap = nullptr);
//    static void wrapLine(QString leftWrap, QString rightWrap = NULL);

    //isAlreadyWrapped : check if selected blocks are already wrapped
    static bool blocksAreAlreadyWrapped(QTextEdit *editor, const QString& leftWrap, const QString& rightWrap = nullptr);
    static void wrapParagraph(QTextEdit *editor, const QString& leftWrap, QString rightWrap = nullptr);

//    static void prependLine(QTextEdit *editor, QString str);
//    static void appendLine(QTextEdit *editor, QString str);
    static bool linesAreAlreadyPrefixed(QTextEdit *editor, const QRegularExpression& rx);
    static void prependEachLine(QTextEdit *editor, const QString& str);
    static void unPrependEachLine(QTextEdit *editor, const QRegularExpression& rx);
};

#endif // MARKDOWNHANDLER_H
