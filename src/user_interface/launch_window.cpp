#include "launch_window.h"
#include "./ui_launch_window.h"


LaunchWindow::LaunchWindow(QWidget *parent):
QMainWindow(parent),
m_ui(new Ui::LaunchWindow),
m_rom_folder(QDir::homePath()),
m_rom_file(""),
m_game_started(false),
m_game_thread(new GameThread(this))
{
    m_ui->setupUi(this);
    m_ui->startButton->setEnabled(false);
}

LaunchWindow::~LaunchWindow() {
    delete m_ui;
    delete m_game_thread;
}

void LaunchWindow::on_openFileButton_clicked() {
    QString file_name = QFileDialog::getOpenFileName(this, "Load ROM", m_rom_folder.absolutePath());
    QFileInfo file_info(file_name);

    if (file_info.suffix() == "gb") {
        m_ui->fileNameLabel->setText("Loaded ROM file: " + file_name);
        m_ui->startButton->setEnabled(true);

        m_rom_file = file_name;
        m_rom_folder = file_info.absoluteDir();
    }
    else {
        m_ui->fileNameLabel->setText("Invalid ROM file: Must have 'gb' extension");
        m_ui->startButton->setEnabled(false);
    }
}

void LaunchWindow::on_startButton_clicked() {
    if (!m_game_thread->isRunning()) {
        m_game_thread->init(m_rom_file);
        m_game_thread->start();
        m_game_started = true;
    }
}

