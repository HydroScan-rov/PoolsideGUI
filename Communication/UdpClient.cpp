#include "UdpClient.h"

UdpClient::UdpClient() {
    uv_interface = new IServerData();

    senderSocket = new QUdpSocket(this);

    receiverSocket = new QUdpSocket(this);
    receiverSocket->bind(QHostAddress("127.0.0.1"), 5001); //  pult address
    connect(receiverSocket, &QUdpSocket::readyRead, this, &UdpClient::readPendingDatagrams);

    this->start();
}

UdpClient::~UdpClient() {
    senderSocket->close();
    delete senderSocket;
    delete receiverSocket;
    delete uv_interface;
    delete timeoutTimer;
}

void UdpClient::run() {
    exec();
}

int UdpClient::exec() {
    while (1) {
        QByteArray msg;
        msg = uv_interface->generateMessage();
        QNetworkDatagram datagram;
        datagram.setData(msg);

        senderSocket->writeDatagram(msg, uv_interface->getCurrentPackageLenght(), QHostAddress("127.0.0.1"), 5000); //  ROV address
        qDebug() << "writeDatagram";
        for (size_t i = 0; i < 34; i++)
        {
            qDebug() << static_cast<uint8_t>(msg[i]);
        }


        msleep(1000); //  50 Hz
    }
}


void UdpClient::readPendingDatagrams() { // parse a message that came from ROV
    while (receiverSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = receiverSocket->receiveDatagram();
        QByteArray msg = datagram.data();
        bool exception_caught = false;

        // qDebug() << "hasPendingDatagrams"; // for debug
        // for (int i = 0; i < 10; i++) {
        //     qDebug() << msg[i];
        // }

        try {
            uv_interface->parseMessage(msg);
        }
        catch (const std::invalid_argument& error) {
            // qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
            exception_caught = true;
        }

        if (!exception_caught) {
            // qDebug() << "[UDP_CLIENT] Message parced " << messageType << "||" << msg.size();
            emit dataUpdated();
        }
    }
}
