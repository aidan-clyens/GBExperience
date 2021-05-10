#pragma once

#include <string>
#include <QThread>

#include "../gameboy.h"


class GameThread : public QThread {
    Q_OBJECT

    public:
        explicit GameThread(QObject *);
        virtual ~GameThread();

        void init(QString &);
        void run();
    
    private:
        std::string m_rom_file;
};