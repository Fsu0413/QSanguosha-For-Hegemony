/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#include "nativesocket.h"
#include "settings.h"

class NativeServerSocketPrivate
{
public:
    QTcpServer *server;
    QUdpSocket *daemon;
};

NativeServerSocket::NativeServerSocket()
    :d_ptr(new NativeServerSocketPrivate)
{
    Q_D(NativeServerSocket);
    d->server = new QTcpServer(this);
    d->daemon = nullptr;
    connect(d->server, &QTcpServer::newConnection, this, &NativeServerSocket::processNewConnection);
}

bool NativeServerSocket::listen()
{
    Q_D(NativeServerSocket);
    return d->server->listen(QHostAddress::Any, QSgsCoreSettings::serverPort());
}

void NativeServerSocket::daemonize()
{
    Q_D(NativeServerSocket);
    d->daemon = new QUdpSocket(this);
    d->daemon->bind(QSgsCoreSettings::serverPort(), QUdpSocket::ShareAddress);
    connect(d->daemon, &QUdpSocket::readyRead, this, &NativeServerSocket::processNewDatagram);
}

void NativeServerSocket::processNewDatagram()
{
    Q_D(NativeServerSocket);
    while (d->daemon->hasPendingDatagrams()) {
        QHostAddress from;
        char ask_str[256];

        d->daemon->readDatagram(ask_str, sizeof(ask_str), &from);

        QByteArray data = QSgsCoreSettings::serverName().toUtf8();
        d->daemon->writeDatagram(data, from, QSgsCoreSettings::detectorPort());
        d->daemon->flush();
    }
}

void NativeServerSocket::processNewConnection()
{
    Q_D(NativeServerSocket);
    QTcpSocket *socket = d->server->nextPendingConnection();
    NativeClientSocket *connection = new NativeClientSocket(socket);
    emit new_connection(connection);
}

// ---------------------------------

class NativeClientSocketPrivate
{
public:
    QTcpSocket *socket;
};

NativeClientSocket::NativeClientSocket()
    : d_ptr(new NativeClientSocketPrivate)
{
    Q_D(NativeClientSocket);
    d->socket = new QTcpSocket(this);
    init();
}

NativeClientSocket::NativeClientSocket(QTcpSocket *socket)
    : d_ptr(new NativeClientSocketPrivate)
{
    Q_D(NativeClientSocket);
    d->socket = socket;
    socket->setParent(this);
    init();
}

void NativeClientSocket::init()
{
    Q_D(NativeClientSocket);
    connect(d->socket, &QTcpSocket::disconnected, this, &NativeClientSocket::disconnected);
    connect(d->socket, &QTcpSocket::readyRead, this, &NativeClientSocket::getMessage);
    connect(d->socket, (void (QTcpSocket::*)(QAbstractSocket::SocketError))(&QTcpSocket::error), this, &NativeClientSocket::raiseError);
    connect(d->socket, &QTcpSocket::connected, this, &NativeClientSocket::connected);
}

void NativeClientSocket::connectToHost()
{
    Q_D(NativeClientSocket);
    QString address = QStringLiteral("127.0.0.1");
    ushort port = 9527u;

    if (QSgsCoreSettings::hostAddress().contains(QChar::fromLatin1(':'))) {
        QStringList texts = QSgsCoreSettings::hostAddress().split(QChar::fromLatin1(':'));
        address = texts.value(0);
        port = texts.value(1).toUShort();
    } else {
        address = QSgsCoreSettings::hostAddress();
        if (address == QStringLiteral("127.0.0.1"))
            port = QSgsCoreSettings::serverPort();
    }

    d->socket->connectToHost(address, port);
}

void NativeClientSocket::connectToHost(const QHostAddress &address)
{
    Q_D(NativeClientSocket);
    ushort port = QSgsCoreSettings::serverPort();
    d->socket->connectToHost(address, port);
}

void NativeClientSocket::connectToHost(const QHostAddress &address, ushort port)
{
    Q_D(NativeClientSocket);
    d->socket->connectToHost(address, port);
}

void NativeClientSocket::getMessage()
{
    Q_D(NativeClientSocket);
    while (d->socket->canReadLine()) {
        QByteArray msg = d->socket->readLine();
#ifndef QT_NO_DEBUG
        printf("recv: %s", msg.constData());
#endif
        emit message_got(msg);
    }
}

void NativeClientSocket::disconnectFromHost()
{
    Q_D(NativeClientSocket);
    d->socket->disconnectFromHost();
}

void NativeClientSocket::send(const QByteArray &message)
{
    Q_D(NativeClientSocket);
    if (message.isEmpty())
        return;
    d->socket->write(message);
    if (!message.endsWith('\n')) {
        d->socket->write("\n");
    }

#ifndef QT_NO_DEBUG
    printf(": %s\n", message.constData());
#endif
    d->socket->flush();
}

bool NativeClientSocket::isConnected() const
{
    Q_D(const NativeClientSocket);
    return d->socket->state() == QTcpSocket::ConnectedState;
}

QString NativeClientSocket::peerName() const
{
    Q_D(const NativeClientSocket);
    QString peer_name = d->socket->peerName();
    if (peer_name.isEmpty())
        peer_name = QStringLiteral("%1:%2").arg(d->socket->peerAddress().toString()).arg(d->socket->peerPort());

    return peer_name;
}

QString NativeClientSocket::peerAddress() const
{
    Q_D(const NativeClientSocket);
    return d->socket->peerAddress().toString();
}

ushort NativeClientSocket::peerPort() const
{
    Q_D(const NativeClientSocket);
    return d->socket->peerPort();
}

void NativeClientSocket::raiseError(QAbstractSocket::SocketError socket_error)
{
    // translate error message
    QString reason;
    switch (socket_error) {
    case QAbstractSocket::ConnectionRefusedError:
        reason = tr("Connection was refused or timeout"); break;
    case QAbstractSocket::RemoteHostClosedError:
        reason = tr("Remote host close this connection"); break;
    case QAbstractSocket::HostNotFoundError:
        reason = tr("Host not found"); break;
    case QAbstractSocket::SocketAccessError:
        reason = tr("Socket access error"); break;
    case QAbstractSocket::NetworkError:
        return; // this error is ignored ...
    default: reason = tr("Unknown error"); break;
    }

    emit error_message(tr("Connection failed, error code = %1\n reason:\n %2").arg(socket_error).arg(reason));
}

