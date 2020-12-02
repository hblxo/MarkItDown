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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow  *ui;
//    QFontComboBox   *fontBox;
    QComboBox       *fontSize;
//    QTabWidget      *editTabs;
    void            setActions();
    QTextEdit       *getCurrentTab();

public slots:
    void    enableActions(bool boolean);
    void    onTextChanged();
    void    openTab();
    void    openTab(const QString& title);
    void    closeTab();
    void    formatOList();
    void    formatUList();
    void    formatBold();
    void    formatItalic();
    void    formatLink();
    void    formatInlineCode();
    void    formatCodeSnippet();
    void    printRule();
    void    save();
    void    open();
    void    copy();
    void    cut();
    void    paste();
    void    undo();
    void    redo();
    void    formatTitle(int t);
    void    formatQuote();
    void    formatStrikethrough();

    // to-do : contextual menu
    // to-do : deactivate actions if no tab
    // to-do : override Os keyboard shortcut

    // to-do : undo and redo
    // to-do : image link
    // to-do : about page
    // to-do : options panel (auto-save, hard break with enter key, etc.)
};
#endif // MAINWINDOW_H
