#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    fontBox = new QFontComboBox();
//    ui->toolBar->addWidget(fontBox);

    fontSize = new QComboBox();
    fontSize->addItem(tr("Normal"), 0);
    fontSize->addItem(tr("Title 1"), 1);
    fontSize->addItem(tr("Title 2"), 2);
    fontSize->addItem(tr("Title 3"), 3);
    ui->toolBar->addWidget(fontSize);

    newText = new TextEdit(this);
    ui->tabWidget->addTab(newText, tr("Nouveau Document"));
    connect(newText, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    connect(ui->actionBold, SIGNAL(triggered()), newText, SLOT(setBold()));
    connect(ui->actionItalic, SIGNAL(triggered()), newText, SLOT(setItalic()));
    connect(ui->actionLink, SIGNAL(triggered()), newText, SLOT(setLink()));
    connect(ui->actionSave, SIGNAL(triggered()), newText, SLOT(save()));
    connect(fontSize, SIGNAL(activated(int)), newText, SLOT(setTitle(int)));
    connect(ui->actionCopy, SIGNAL(triggered()), newText, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), newText, SLOT(cut()));
    connect(ui->actionPaste, SIGNAL(triggered()), newText, SLOT(paste()));
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
