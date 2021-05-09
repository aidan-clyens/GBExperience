#pragma once

#include <QMainWindow>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class LaunchWindow; }
QT_END_NAMESPACE

class LaunchWindow : public QMainWindow {
    Q_OBJECT

public:
    LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();

private slots:
    void on_openFileButton_clicked();

    void on_startButton_clicked();

private:
    Ui::LaunchWindow *m_ui;
    QDir m_rom_folder;
};
