#ifndef CALLABLEWRAPPER_CALLABLEWRAPPER_CPP
#define CALLABLEWRAPPER_CALLABLEWRAPPER_CPP

#include "callablewrapper.h"
#include <utility>
namespace CallableWrapper {

    template<typename C, typename RT, typename... Args>
    CallableObjWrapper<C,RT,Args...>::CallableObjWrapper(C callable):
        callable_(callable)
    {
    }

    template<typename C, typename RT, typename... Args>
    RT CallableObjWrapper<C,RT,Args...>::operator()(Args... args){
        return callable_(std::forward<Args>(args)...);
    }

    template<typename C, typename RT, typename... Args>
    CallablePtrWrapper<C,RT,Args...>::CallablePtrWrapper(C callable)
    {
        callable_ = callable;
    }

    template<typename C, typename RT, typename... Args>
    RT CallablePtrWrapper<C,RT,Args...>::operator()(Args... args){
        return (*callable_)(std::forward<Args>(args)...);
    }

    template<typename RT, typename... Args>
    template<typename Callable>
    CallableWrapper<RT, Args...>* CallableWrapperFactory<RT,Args...>::create(Callable callable){
        if constexpr (std::is_pointer_v<Callable>){
            return new CallablePtrWrapper<Callable, RT,Args...>(callable);
        }
        else if (std::is_copy_constructible_v<Callable>) {
            return new CallableObjWrapper<Callable, RT,Args...>(callable);
        }
        else if (std::is_move_constructible_v<Callable>) {
            return new CallableObjWrapper<Callable, RT,Args...>(std::move(callable));
        }
        return new CallableObjWrapper<Callable, RT,Args...>(callable);
    }

} // namespace CallableWrapper

#endif
