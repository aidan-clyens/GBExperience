#include "launch_window.h"
#include "./ui_launch_window.h"

#include <QFileDialog>
#include <QFileInfo>


LaunchWindow::LaunchWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::LaunchWindow),
    m_rom_folder(QDir::homePath())
{
    m_ui->setupUi(this);
    m_ui->startButton->setEnabled(false);
}

LaunchWindow::~LaunchWindow() {
    delete m_ui;
}

void LaunchWindow::on_openFileButton_clicked() {
    QString file_name = QFileDialog::getOpenFileName(this, "Load ROM", m_rom_folder.absolutePath());
    QFileInfo file_info(file_name);

    if (file_info.suffix() == "gb") {
        m_ui->fileNameLabel->setText("Loaded ROM file: " + file_name);
        m_ui->startButton->setEnabled(true);

        m_rom_folder = file_info.absoluteDir();
    }
    else {
        m_ui->fileNameLabel->setText("Invalid ROM file: Must have 'gb' extension");
        m_ui->startButton->setEnabled(false);
    }
}

void LaunchWindow::on_startButton_clicked() {

}

