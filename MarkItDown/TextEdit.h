#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QRegularExpression>
#include <QClipboard>
#include <QMenu>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
    explicit TextEdit(QWidget *parent);

    void       setCurrentFile(const QString& fileName);
    QString     getCurrentFile();

public slots:
//    void    ShowContextMenu(const QPoint& pos);

private:
    QString     _currentFile;
    bool        _saved;
public:
    bool isSaved() const;

    void setSaved(bool saved);
};

#endif // TEXTEDIT_H
