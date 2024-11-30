#include "ExecutorImpl.hpp"
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
  return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose) {}
void ExecutorImpl::Execute(const std::string& commands) noexcept {
    for (const auto cmd : commands) {
        if (cmd == 'M') {
            switch (pose.heading) {
                case 'E': ++pose.x; break;
                case 'W': --pose.x; break;
                case 'N': ++pose.y; break;
                case 'S': --pose.y; break;
            }
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
 return pose;
}
}
