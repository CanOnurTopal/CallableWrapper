# CallableWrapper
## Why?
I created this library due to the problems std::function tool's problems handling lambdas and non copy constructable objects.
## How to use
Create a CallableWrapper object using the factory method
```
using namespace CallableWrapper;

CallableWrapper<ReturnType, Param1, Param2>* CW = CallableWrapperFactory<ReturnType, Param1, Param2>::create(callable);
```
The first template parameter is the return type of the callable. The rest of the template arguments are the parameter types.

Call the CallableWrapper object to call the underlying object.
