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
    void    setList();
    void    setBold();
    void    setItalic();
    void    setLink();
    void    setCode();
    void    printRule();
    void    save();
    void    open();
    void    copy();
    void    cut();
    void    paste();
    void    setTitle(int t);

    //to-do : setQuote();
    //to-do : setStroke()
    //to-do : undo and redo
};
#endif // MAINWINDOW_H
