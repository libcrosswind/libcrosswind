#pragma once

#include <functional>
#include <forward_list> 
#include <vector>

namespace cw{
namespace core{
namespace functional{

    template<class R, class... Args>
    class delegate;

}// namespace functional
}// namespace core
}// namespace cw


template<class R, class... Args>
class cw::core::functional::delegate
{
public:
    template<typename U>
    delegate& operator += (const U &function)
    {
        auto before_end = callbacks.before_begin();
        for (auto& _ : callbacks)
            ++ before_end;

        callbacks.insert_after(before_end, function);

        return *this;
    }

    template<typename U>
    delegate& operator -= (const U &function){

        callbacks.remove(function);
        return *this;

    }

    std::vector<R> operator () (Args... args)
    {
        std::vector<R> res;
        for (auto callback : callbacks)
        {
            res.push_back(callback(args...));
        }
        return res;
    }

    void clear(){
        callbacks.clear();
        return *this;
    }

private:
    std::forward_list<std::function<R(Args... args)> > callbacks;
};// class delegate


// specialization
namespace cw{
namespace core{
namespace functional{

template<class... Args>
class delegate<void, Args...>
{
public:
    template<typename U>
    delegate& operator += (const U &function)
    {
        auto before_end = callbacks.before_begin();
        for (auto& _ : callbacks)
            ++ before_end;

        callbacks.insert_after(before_end, function);

        return *this;
    }

    template<typename U>
    delegate& operator -= (const U &function){

        callbacks.remove(function);
        return *this;

    }

    void operator () (Args... args)
    {
        for (auto callback : callbacks)
        {
            callback(args...);
        }
    }

    void clear(){
        callbacks.clear();
        return *this;
    }

private:
    std::forward_list<std::function<void(Args... args)> > callbacks;
};// delegate class void specialization

}// namespace functional
}// namespace core
}// namespace cw

