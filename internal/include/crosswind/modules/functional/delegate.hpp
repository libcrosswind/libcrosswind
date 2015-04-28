#pragma once

#include <functional>
#include <vector>
#include <algorithm>

namespace cw{
namespace functional{

    template<class R, class... Args>
    class delegate;

}// namespace functional
}// namespace cw

template<class R, class... Args>
class cw::functional::delegate
{
public:
    template<typename U>
    delegate& operator += (const U &function){

        callbacks.push_back(function);

        return *this;
    }

/*    template<typename U>
    delegate& operator -= (U &function){

        auto iter = callbacks.begin();
        while (iter != callbacks.end())
        {
            if (*iter == function)
            {
                iter = callbacks.erase(iter);
            }
            else
            {
                ++iter;
            }
        }

        return *this;

    }*/

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
    std::vector<std::function<R(Args... args)> > callbacks;
};// class delegate


// specialization
namespace cw{
namespace functional{

template<class... Args>
class delegate<void, Args...>
{
public:
    template<typename U>
    delegate& operator += (const U &function)
    {
        callbacks.push_back(function);

        return *this;
    }

/*    template<typename U>
    delegate& operator -= (const U& function){

        auto end = std::remove_if (callbacks.begin(), callbacks.end(), [&](auto callback){
            return callback == const_cast<U&>(function);
        });

        callbacks.erase(end, callbacks.end());

        return *this;

    }
*/
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
    std::vector<std::function<void(Args... args)> > callbacks;

};// delegate class void specialization

}// namespace functional
}// namespace cw

