#include "game_thread.h"


GameThread::GameThread(QObject *parent):
QThread(parent),
m_rom_file("")
{
    
}

GameThread::~GameThread() {

}

void GameThread::init(QString &rom_file) {
    m_rom_file = rom_file.toStdString();
}

void GameThread::run() {
    GameBoy gb(false, false);
    gb.load_rom(m_rom_file);

    while (gb.is_display_open()) {
        gb.tick();
    }
}