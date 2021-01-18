#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QMainWindow>
#include <QMap>
#include <QPointer>

class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QTextCodec;
class BattInfo;

class ReportWidget : public QMainWindow
{
    Q_OBJECT

public:
    ReportWidget(QWidget *parent = 0);

    void AddTable(QString path);
    void AddPlot(QString path);
    void TakeInfoAbout(BattInfo &battery, QStringList peopleList,QStringList equipList);

protected:
    virtual void closeEvent(QCloseEvent *e);

private:
    void SetupFileActions();
    void SetupEditActions();
    void SetupTextActions();
    bool Load(const QString &f);
    bool MaybeSave();
    void SetCurrentFileName(const QString &fileName);

private slots:
    void FileNew();
    void FileOpen();
    bool FileSave();
    bool FileSaveAs();
    void FilePrint();
    void FilePrintPreview();
    void FilePrintPdf();

    void TextBold();
    void TextUnderline();
    void TextItalic();
    void TextFamily(const QString &f);
    void TextSize(const QString &p);
    void TextAlign(QAction *a);

    void CurrentCharFormatChanged(const QTextCharFormat &format);
    void CursorPositionChanged();

    void ClipboardDataChanged();
    void PrintPreview(QPrinter *);

private:
    void MergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void FontChanged(const QFont &f);
    void ColorChanged(const QColor &c);
    void AlignmentChanged(Qt::Alignment a);



    QAction// *actionSave,
        *actionTextBold,
        *actionTextUnderline,
        *actionTextItalic,
       // *actionTextColor,
        *actionAlignLeft,
        *actionAlignCenter,
        *actionAlignRight,
        *actionAlignJustify,
        *actionUndo,
        *actionRedo;
      //  *actionCut,
     //   *actionCopy,
     //   *actionPaste;

   // QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QToolBar *tb;
    QString fileName;
    QTextEdit *textEdit;

    QTextCodec *codec;

    bool templatLoaded;

};

#endif
