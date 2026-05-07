// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用，源码未直接 #include。
//   为编译完整性提供模板实现，由 CommonModule 内部其他文件（如 ThreadRunner）使用。
//
// API：Push / Pop（阻塞）/ TryPop（非阻塞）/ Size / Clear。
// 基于 std::mutex + std::condition_variable，C++11 起即可。
#pragma once
#ifndef _INC_BLOCKINGQUEUE_
#define _INC_BLOCKINGQUEUE_

#include <mutex>
#include <condition_variable>
#include <queue>

template<typename T>
class BlockingQueue
{
public:
    void Push(const T& _item)
    {
        {
            std::lock_guard<std::mutex> lk(m_mu);
            m_q.push(_item);
        }
        m_cv.notify_one();
    }

    void Push(T&& _item)
    {
        {
            std::lock_guard<std::mutex> lk(m_mu);
            m_q.push(std::move(_item));
        }
        m_cv.notify_one();
    }

    // 阻塞直到队列非空。返回出队的元素。
    T Pop()
    {
        std::unique_lock<std::mutex> lk(m_mu);
        m_cv.wait(lk, [this]() { return !m_q.empty(); });
        T v = std::move(m_q.front());
        m_q.pop();
        return v;
    }

    // 非阻塞版本：成功则把元素写入 *_pOut 并返回 true；空队列返回 false。
    bool TryPop(T* _pOut)
    {
        std::lock_guard<std::mutex> lk(m_mu);
        if (m_q.empty()) return false;
        *_pOut = std::move(m_q.front());
        m_q.pop();
        return true;
    }

    size_t Size() const
    {
        std::lock_guard<std::mutex> lk(m_mu);
        return m_q.size();
    }

    bool Empty() const
    {
        std::lock_guard<std::mutex> lk(m_mu);
        return m_q.empty();
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lk(m_mu);
        std::queue<T> empty;
        std::swap(m_q, empty);
    }

private:
    mutable std::mutex      m_mu;
    std::condition_variable m_cv;
    std::queue<T>           m_q;
};

#endif // _INC_BLOCKINGQUEUE_
