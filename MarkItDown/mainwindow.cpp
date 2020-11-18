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
    setActions();
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(openTab()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::setActions()
{
    connect(ui->actionBold, SIGNAL(triggered()), this, SLOT(setBold()));
    connect(ui->actionItalic, SIGNAL(triggered()), this, SLOT(setItalic()));
    connect(ui->actionLink, SIGNAL(triggered()), this, SLOT(setLink()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(fontSize, SIGNAL(activated(int)), this, SLOT(setTitle(int)));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
}

void MainWindow::onTextChanged()
{
    QTextEdit *currentTab = getCurrentTab();
    QString md = currentTab->toPlainText();
    ui->textBrowser->setMarkdown(md);
}

void    MainWindow::openTab()
{
    QTextEdit       *newTextEdit;
    newTextEdit = new TextEdit(this);
    ui->tabWidget->addTab(newTextEdit, tr("Nouveau Document"));
    connect(newTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    ui->tabWidget->setCurrentWidget(newTextEdit);
//    setActions();
}

QTextEdit   *MainWindow::getCurrentTab()
{
    return qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
}


void    MainWindow::setBold()
{
    QTextEdit   *activeTab = getCurrentTab();
    QTextCursor cursor = activeTab->textCursor();
    activeTab->insertPlainText("**" + cursor.selectedText() + "**");
    //to-do : unset bold if already set
}

void    MainWindow::setItalic()
{
    QTextEdit   *activeTab = getCurrentTab();
    QTextCursor cursor = activeTab->textCursor();
    activeTab->insertPlainText("*" + cursor.selectedText() + "*");
    //to-do : unset italic if already set
}

void    MainWindow::setLink()
{
    QTextEdit   *activeTab = getCurrentTab();
    QTextCursor cursor = activeTab->textCursor();
    activeTab->insertPlainText("["+ cursor.selectedText() + "]()");
    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
    activeTab->setTextCursor(cursor);
    //to-do : set automatic link if an url is pasted
}

void    MainWindow::setTitle(int t)
{
    QTextEdit   *activeTab = getCurrentTab();
    QString prefix;

    for (int i = 1; i <= t; i++)
    {
        prefix += "#";
    }
    if (t != 0)
        prefix += " ";
    QTextCursor cursor = activeTab->textCursor();
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.insertText(cursor.selectedText().replace(QRegularExpression("(^(?:#+ )|^ *)"), prefix));
}

void    MainWindow::save()
{
    QTextEdit   *activeTab = getCurrentTab();

    if (activeTab == NULL)
        return;
    QString defaultPath;
    defaultPath += "/tmp/";
    defaultPath += ui->tabWidget->currentWidget()->windowTitle();
    defaultPath += ".md";
    QString fileName = QFileDialog::getSaveFileName(activeTab, tr("Enregistrer le document"), defaultPath, "");
    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(activeTab, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }
        QTextStream out(&file);
//        out.setVersion(QDataStream::Qt_4_5);
        out << activeTab->toPlainText();
     }
}

void    MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Ouvrir un fichier"), "",
            tr("All Files (*.md)"));
    if (fileName.isEmpty())
            return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream in(&file);
        openTab();
        QTextEdit   *activeTab = getCurrentTab();
        activeTab->append(in.readAll());

        /*
        QTextStream in(&file);
        openTab();
        QTextEdit   *activeTab = getCurrentTab();
        activeTab->setText(in.readLine());
//        onTextChanged();
        file.close();*/
    }
}

void    MainWindow::copy()
{
    QTextEdit  *activeTab = getCurrentTab();
    activeTab->copy();
}

void    MainWindow::cut()
{
    QTextEdit  *activeTab = getCurrentTab();
    activeTab->cut();
}

void    MainWindow::paste()
{
    QTextEdit  *activeTab = getCurrentTab();
    activeTab->paste();
}
