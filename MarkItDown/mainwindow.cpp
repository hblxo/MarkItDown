#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fontBox = new QFontComboBox();
    ui->toolBar->addWidget(fontBox);

   newText = new QTextEdit();
    ui->tabWidget->addTab(newText, "New Page");
//    ui->textBrowser->setDocument(newText->document());
    //    ui->textBrowser->setMarkdown(newText->toMarkdown());
//    ui->textBrowser->setMarkdown(newText->document()->toMarkdown());
    connect(newText, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextChanged()
{
    QString md = newText->toPlainText();
    ui->textBrowser->setMarkdown(md);
}
