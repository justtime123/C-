#include "ExecutorImpl.hpp"
#include <unordered_map>

namespace adas
{
// 方便查找下一个方向的映射表
const std::unordered_map<char, char>& NextHeadingE = [](){
    std::unordered_map<char, char> m;
    m['N'] = 'E';
    m['E'] = 'S';
    m['S'] = 'W';
    m['W'] = 'N';
    return m;
}();

const std::unordered_map<char, char>& NextHeadingW = [](){
    std::unordered_map<char, char> m;
    m['N'] = 'W';
    m['W'] = 'S';
    m['S'] = 'E';
    m['E'] = 'N';
    return m;
}();

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    for (const auto cmd : commands) {
        switch (cmd) {
            case 'M':
                switch (pose.heading) {
                    case 'E': ++pose.x; break;
                    case 'W': --pose.x; break;
                    case 'N': ++pose.y; break;
                    case 'S': --pose.y; break;
                }
                break;
            case 'L': // 左转
                pose.heading = NextHeadingW.at(pose.heading);
                break;
            case 'R': // 右转
                pose.heading = NextHeadingE.at(pose.heading);
                break;
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}