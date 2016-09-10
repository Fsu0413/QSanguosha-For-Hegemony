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

#ifndef _SOCKET_H
#define _SOCKET_H

#include "libqsgscoreglobal.h"

// @todo: These classes don't have any meaningful effect. Should it be removed later?
// Another question, why do these classes appear in the QSanguosha-v2? For legacy API compatibility with V1?

// @Fs: I happened on something we may support later using these pure virtual classes....
// If we introduce a new connection mechanism(e.g. Bluetooth connection), we can inherit these pure virtual classes
// to develop it, and does not need to couple with the existing network connection logic.

class ClientSocket;

class LIBQSGSCORE_EXPORT ServerSocket : public QObject
{
    Q_OBJECT

public:
    virtual bool listen() = 0;
    virtual void daemonize() = 0;

signals:
    void new_connection(ClientSocket *connection);
};

class LIBQSGSCORE_EXPORT ClientSocket : public QObject
{
    Q_OBJECT

public:
    virtual void connectToHost() = 0;
    virtual void connectToHost(const QHostAddress &address) = 0;
    virtual void connectToHost(const QHostAddress &address, ushort port) = 0;
    virtual void disconnectFromHost() = 0;
    virtual void send(const QByteArray &message) = 0;
    virtual bool isConnected() const = 0;
    virtual QString peerName() const = 0;
    virtual QString peerAddress() const = 0;
    virtual ushort peerPort() const = 0;

signals:
    void message_got(const QByteArray &msg);
    void error_message(const QString &msg);
    void disconnected();
    void connected();
};

typedef char buffer_t[65535];

#endif

