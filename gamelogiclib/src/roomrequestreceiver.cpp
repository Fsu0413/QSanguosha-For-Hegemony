
#include "roomobject.h"

RoomRequestReceiver::RoomRequestReceiver()
{
}

RoomRequestReceiver::~RoomRequestReceiver()
{
}

const QJsonDocument &RoomRequestReceiver::waitForResult(int timeout)
{
    QMutexLocker l(&m_mutex);
    bool ok = true;

    // todo_Fs: the timeout here is wrong, should use an other value to calculate it
    while ((m_result.isEmpty() || m_result.isNull()) && ok)
        ok = m_cond.wait(l.mutex(), timeout);

    return m_result;
}

void RoomRequestReceiver::resultReceived(const QJsonDocument &result)
{
    if (result.isEmpty() || result.isNull())
        return;

    QMutexLocker l(&m_mutex);
    m_result = result;
    m_cond.wakeAll();
}
