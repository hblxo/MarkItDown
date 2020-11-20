#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QFontComboBox>
#include <QTextEdit>
#include <QTextDocumentFragment>
#include <QTextStream>
#include <QTextBlock>
#include <QShortcut>
#include "TextEdit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    QFontComboBox   *fontBox;
    QComboBox       *fontSize;
    QTabWidget      *editTabs;
    void            setActions();
    QTextEdit       *getCurrentTab();

public slots:
    void    onTextChanged();
    void    openTab();
    void    openTab(QString title);
    void    close();
    void    formatOList();
    void    formatUList();
    void    formatBold();
    void    formatItalic();
    void    formatLink();
    void    formatCodeSnippet();
    void    printRule();
    void    save();
    void    open();
    void    copy();
    void    cut();
    void    paste();
    void    formatTitle(int t);

    //to-do : formatQuote();
    //to-do : format Strokeline()
    //to-do : undo and redo
    //to-do : image link
    //to-do : options panel (auto-save, hardbreak with enter key, etc.)
};
#endif // MAINWINDOW_H
