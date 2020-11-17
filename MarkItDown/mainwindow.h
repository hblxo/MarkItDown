#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontComboBox>
#include <QTextEdit>

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
    QTabWidget      *editTabs;
    QTextEdit       *newText;

public slots:
    void            onTextChanged();

};
#endif // MAINWINDOW_H
