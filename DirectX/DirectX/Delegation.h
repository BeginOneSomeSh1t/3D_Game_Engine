#pragma once
#include <functional>

template<typename FuncSignature>
using Delegate = std::function<FuncSignature>;

#define DELEGATE_CALL(delegateRef) if(delegateRef) delegateRef()
#define DELEGATE_BIND_TO(delegateRef, ToRef) delegateRef = ToRef
#define DELEGATE_UNBIND(delegateRef) delegateRef = nullptr

