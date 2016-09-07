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

#ifndef _NATIVESOCKET_H
#define _NATIVESOCKET_H

#include "libqsgscoreglobal.h"
#include "socket.h"

class QUdpSocket;

class LIBQSGSCORE_EXPORT NativeServerSocket : public ServerSocket
{
    Q_OBJECT

public:
    NativeServerSocket();

    bool listen() final override;
    void daemonize() final override;

private slots:
    void processNewConnection();
    void processNewDatagram();

private:
    // @todo: use D-pointer to handle this
    QTcpServer *server;
    QUdpSocket *daemon;
};


class LIBQSGSCORE_EXPORT NativeClientSocket : public ClientSocket
{
    Q_OBJECT

public:
    NativeClientSocket();
    NativeClientSocket(QTcpSocket *socket);

    void connectToHost() final override;
    void connectToHost(const QHostAddress &address) final override;
    void connectToHost(const QHostAddress &address, ushort port) final override;
    void disconnectFromHost() final override;
    void send(const QByteArray &message) final override;
    bool isConnected() const final override;
    QString peerName() const final override;
    QString peerAddress() const final override;
    ushort peerPort() const final override;

private slots:
    void getMessage();
    void raiseError(QAbstractSocket::SocketError socket_error);

private:
    // @todo: use D-pointer to handle this
    QTcpSocket *const socket;

    void init();
};

#endif

