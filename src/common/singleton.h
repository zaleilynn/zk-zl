#ifndef LYNN_SRC_COMMON_SINGLETON_HPP_
#define LYNN_SRC_COMMON_SINGLETON_HPP_

#include "common/mutex.h"

using zlynn::MutexLocker;
///全局维护一个类，控制它的创建实例函数，如果有就不创建，直接返回
///定义使用的模板类
///怎么去删除这个创建的对象呢?应该不会造成内存泄漏，毕竟一个程序只有一个这个东西随着程序的消亡而消亡
template <typename T>
class Singleton {
public:
    static T* Instance() {
        MutexLocker locker(m_lock);
        if (m_instance == NULL)
            m_instance = new T;
        return m_instance;
    }

private:
    static zlynn::Mutex m_lock;
    static T* m_instance;
};

template <typename T>
T* Singleton<T>::m_instance = NULL;
template <typename T>
zlynn::Mutex Singleton<T>::m_lock;

#endif
