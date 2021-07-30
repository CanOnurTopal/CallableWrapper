#ifndef CALLABLEWRAPPER_CALLABLEWRAPPER_H
#define CALLABLEWRAPPER_CALLABLEWRAPPER_H


namespace CallableWrapper {

    template<typename ReturnType, typename... Args>
    class CallableWrapper
    {
        public:
            CallableWrapper() = default;
            virtual ~CallableWrapper(){};
            virtual ReturnType operator()(Args... args) = 0;
    };

    template<typename Callable, typename ReturnType, typename... Args>
    class CallableObjWrapper : public CallableWrapper<ReturnType, Args...>
    {
        public:
            CallableObjWrapper(Callable callable);
            virtual ~CallableObjWrapper() override = default;
            virtual ReturnType operator()(Args... args) override;
        private:
            Callable callable_;
    };

    template<typename Callable, typename ReturnType, typename... Args>
    class CallablePtrWrapper : public CallableWrapper<ReturnType, Args...>
    {
        public:
            CallablePtrWrapper(Callable callable);
            virtual ~CallablePtrWrapper() override = default;
            virtual ReturnType operator()(Args... args) override;
        private:
            Callable callable_;
    };

    template<typename ReturnType, typename... Args>
    class CallableWrapperFactory{
        public:
            template<typename Callable>
            static CallableWrapper<ReturnType, Args...>* create(Callable callable);
        private:
            CallableWrapperFactory();
    };
} // namespace CallableWrapper

#include "callablewrapper.cpp"
#endif // CALLABLEWRAPPER_CALLABLEWRAPPER_H
