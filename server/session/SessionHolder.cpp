#include "SessionHolder.h"

std::shared_ptr<const std::string> SessionHolder::CreateSession(size_t width, size_t height)
{
    std::lock_guard<std::shared_mutex> lock(_mutex);

    auto session = std::make_shared<Session>(width, height);
    auto sessionID = session.get()->getSessionID();
    _sessions.insert({*sessionID.get(), session});
    
    return sessionID;
}

std::shared_ptr<Session> SessionHolder::FindSession(const std::string &id)
{
    // read mutex (shared mutex)
    std::shared_lock<std::shared_mutex> lock(_mutex);

    auto it = _sessions.find(id);
    if (it != _sessions.end())
    {
        return it->second;
    }
    return nullptr;
}

bool SessionHolder::RemoveSession(const std::string &id)
{
    std::lock_guard<std::shared_mutex> lock(_mutex);

    auto it = _sessions.find(id);
    if (it != _sessions.end())
    {
        _sessions.erase(it);
        return true;
    }
    return false;
}
