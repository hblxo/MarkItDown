#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontComboBox>
#include <QTextEdit>
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
//    QTextEdit       *activeTextEdit;
    void            setActions();
    QTextEdit       *getCurrentTab();

public slots:
    void            onTextChanged();
    void            openTab();
//    void            openTab(QString url);
    void    setBold();
    void    setItalic();
    void    setLink();
    void    save();
    void    copy();
    void    cut();
    void    paste();
    void    setTitle(int t);
};
#endif // MAINWINDOW_H
