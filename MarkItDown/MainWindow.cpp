#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MarkdownHandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    fontSize = new QComboBox();
    fontSize->addItem(tr("Normal"), 0);
    fontSize->addItem(tr("Title 1"), 1);
    fontSize->addItem(tr("Title 2"), 2);
    fontSize->addItem(tr("Title 3"), 3);
    fontSize->addItem(tr("Title 4"), 4);
    fontSize->addItem(tr("Title 5"), 5);
    fontSize->addItem(tr("Title 6"), 6);
    ui->toolBar->addWidget(fontSize);
    setActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::setActions()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(ui->actionBold, SIGNAL(triggered()), this, SLOT(formatBold()));
    connect(ui->actionItalic, SIGNAL(triggered()), this, SLOT(formatItalic()));
    connect(ui->actionLink, SIGNAL(triggered()), this, SLOT(formatLink()));
    connect(ui->actionCodeSnippet, SIGNAL(triggered()), this, SLOT(formatCodeSnippet()));
    connect(ui->actionInlineCode, SIGNAL(triggered()), this, SLOT(formatInlineCode()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(fontSize, SIGNAL(activated(int)), this, SLOT(formatTitle(int)));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->actionRule, SIGNAL(triggered()), this, SLOT(printRule()));
    connect(ui->actionList, SIGNAL(triggered()), this, SLOT(formatOList()));
    connect(ui->actionUList, SIGNAL(triggered()), this, SLOT(formatUList()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeTab()));
    connect(ui->actionQuote, SIGNAL(triggered()), this, SLOT(formatQuote()));
    connect(ui->actionStrike, SIGNAL(triggered()), this, SLOT(formatStrikethrough()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    enableActions(false);
}

void    MainWindow::enableActions(bool boolean)
{
    ui->actionBold->setEnabled(boolean);
    ui->actionItalic->setEnabled(boolean);
    ui->actionLink->setEnabled(boolean);
    ui->actionCodeSnippet->setEnabled(boolean);
    ui->actionInlineCode->setEnabled(boolean);
    ui->actionSave->setEnabled(boolean);
    fontSize->setEnabled(boolean);
    ui->actionCopy->setEnabled(boolean);
    ui->actionCut->setEnabled(boolean);
    ui->actionPaste->setEnabled(boolean);
    ui->actionRule->setEnabled(boolean);
    ui->actionList->setEnabled(boolean);
    ui->actionUList->setEnabled(boolean);
    ui->actionClose->setEnabled(boolean);
    ui->actionQuote->setEnabled(boolean);
    ui->actionStrike->setEnabled(boolean);
    ui->actionUndo->setEnabled(boolean);
    ui->actionRedo->setEnabled(boolean);
}

void MainWindow::onTextChanged()
{
    QTextEdit *currentTab = getCurrentTab();
    QString md = currentTab->toPlainText();
    ui->textBrowser->setMarkdown(md);
}

void    MainWindow::openTab()
{
   openTab("Nouveau Document");
}

void    MainWindow::openTab(const QString& title)
{
    QTextEdit       *newTextEdit;
    newTextEdit = new TextEdit(this);
    ui->tabWidget->addTab(newTextEdit, title);
    connect(newTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    ui->tabWidget->setCurrentWidget(newTextEdit);
    if (ui->tabWidget->count() == 1)
        enableActions(true);
}

QTextEdit   *MainWindow::getCurrentTab()
{
    return qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
}


void    MainWindow::formatBold()
{
    QTextEdit   *activeTab = getCurrentTab();

    MarkdownHandler::wrapText(activeTab, "**");
}

void    MainWindow::formatItalic()
{
    QTextEdit   *activeTab = getCurrentTab();

    MarkdownHandler::wrapText(activeTab, "*");
}

void    MainWindow::formatLink()
{
    QTextEdit   *activeTab = getCurrentTab();
    QTextCursor cursor = activeTab->textCursor();
    activeTab->insertPlainText("["+ cursor.selectedText() + "]()");
    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
    activeTab->setTextCursor(cursor);
}

void    MainWindow::formatTitle(int t)
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

void    MainWindow::formatInlineCode()
{
    QTextEdit   *activeTab = getCurrentTab();

    MarkdownHandler::wrapText(activeTab, "`");
}

void    MainWindow::formatCodeSnippet()
{
    QTextEdit   *activeTab = getCurrentTab();

    MarkdownHandler::wrapParagraph(activeTab, "```");
}

void    MainWindow::save()
{
    QTextEdit   *activeTab = getCurrentTab();

    if (activeTab == nullptr)
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
        out << activeTab->toPlainText();
        ui->tabWidget->setTabText(ui->tabWidget->indexOf(activeTab), fileName);
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
        openTab(fileName);
        QTextEdit   *activeTab = getCurrentTab();
        activeTab->append(in.readAll());
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
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();
    const QString& tmp = originalText;
    QTextCursor cursor = activeTab->textCursor();

    if (QRegularExpression("^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]").match(originalText).hasMatch())
    {
        if (cursor.hasSelection())
            clipboard->setText("[" + cursor.selection().toPlainText() + "](" + originalText + ")");
        else
            clipboard->setText("[" + originalText + "](" + originalText + ")");
    }
    activeTab->paste();
    clipboard->setText(tmp);
}

void    MainWindow::undo()
{
    QTextEdit  *activeTab = getCurrentTab();

    activeTab->undo();
}

void    MainWindow::redo()
{
    QTextEdit  *activeTab = getCurrentTab();

    activeTab->redo();
}

void MainWindow::printRule()
{
    QTextEdit   *activeTab = getCurrentTab();
    QTextCursor cursor = activeTab->textCursor();
    cursor.insertText("\n----\n");
}

void    MainWindow::closeTab()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    if (ui->tabWidget->count() == 0)
        enableActions(false);
}

void    MainWindow::formatUList()
{
    QTextEdit   *activeTab = getCurrentTab();
    QRegularExpression oRegex = QRegularExpression("^( *[0-9]+(\\.|\\))( |\t)+)");
    QRegularExpression uRegex = QRegularExpression("^( *(-|\\*|\\+)( |\t)+)");


    if (MarkdownHandler::linesAreAlreadyPrefixed(activeTab, uRegex))
        MarkdownHandler::unPrependEachLine(activeTab, uRegex);
    else if (MarkdownHandler::linesAreAlreadyPrefixed(activeTab, oRegex))
    {
        MarkdownHandler::unPrependEachLine(activeTab, oRegex);
        MarkdownHandler::prependEachLine(activeTab, "* ");
    }
    else
        MarkdownHandler::prependEachLine(activeTab, "* ");
}

void    MainWindow::formatOList()
{
    QTextEdit   *activeTab = getCurrentTab();
    QRegularExpression oRegex = QRegularExpression("^( *[0-9]+(\\.|\\))( |\t)+)");
    QRegularExpression uRegex = QRegularExpression("^( *(-|\\*|\\+)( |\t)+)");

    if (MarkdownHandler::linesAreAlreadyPrefixed(activeTab, oRegex))
        MarkdownHandler::unPrependEachLine(activeTab, oRegex);
    else if (MarkdownHandler::linesAreAlreadyPrefixed(activeTab, uRegex))
    {
        MarkdownHandler::unPrependEachLine(activeTab, uRegex);
        MarkdownHandler::prependEachLine(activeTab, "1. ");
    }
    else
        MarkdownHandler::prependEachLine(activeTab, "1. ");

    // to-do : empty lists
    // to-do : nested lists
    // "^(?:\d+\.|[*+-]) .*(?:\r?\n(?!(?:\d+\.|[*+-]) ).*)*/gm"
}

void    MainWindow::formatQuote()
{
    QTextEdit   *activeTab = getCurrentTab();

    if (MarkdownHandler::linesAreAlreadyPrefixed(activeTab, QRegularExpression("^ ?>+ ?")))
        MarkdownHandler::unPrependEachLine(activeTab, QRegularExpression("^ ?>+ ?"));
    else
        MarkdownHandler::prependEachLine(activeTab, "> ");
}

void    MainWindow::formatStrikethrough()
{
    QTextEdit   *activeTab = getCurrentTab();

    MarkdownHandler::wrapText(activeTab, "~~");
}
