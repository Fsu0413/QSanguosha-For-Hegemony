
#include "roomobject.h"

RoomRequestReceiver::RoomRequestReceiver()
{
}

RoomRequestReceiver::~RoomRequestReceiver()
{
}

QVariant RoomRequestReceiver::waitForResult(int timeout)
{
    QMutexLocker l(&m_mutex);
    bool ok = true;

    while (!m_result.isValid() && ok)
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
