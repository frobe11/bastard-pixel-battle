#pragma once
#include "Session.h"
#include <shared_mutex>
#include <unordered_map>
class SessionHolder
{
private:
    static inline std::unordered_map<std::string, std::shared_ptr<Session>> _sessions;
    static inline std::shared_mutex _mutex;

    SessionHolder() = delete;
    SessionHolder(SessionHolder &other) = delete;

public:
    static std::shared_ptr<const std::string> CreateSession(size_t width, size_t height);

    static std::shared_ptr<Session> FindSession(const std::string &id);

    static bool RemoveSession(const std::string &id);
};
