#pragma once
#include <utility>
#include <memory>
#include <functional>
#include <random>
#include <unordered_map>

namespace Delegate
{

	// Delegate definitions

	/*Single delegate is a class that can store a one pointer to function instance
	You can bind static functions as well as either captured or non-captured lambdas
	If you desire to bind a class member function, you can make it as a static
	or use a captured lambda expression as an adapter for that function*/
	template<typename RetVal, typename... Args>
	class SingleDelegate
	{
	public:
		/*function signature as a std::function<RetVal(Args...)>*/
		using FuncPtr = std::function<RetVal(Args...)>;

		explicit SingleDelegate() noexcept
			:
			pFunc(nullptr)
		{}
		explicit SingleDelegate(FuncPtr pSub) noexcept
		{
			pFunc = pSub;
		}
		FuncPtr GetSubscriber() const noexcept
		{
			return pFunc;
		}
		bool IsSubBound() const noexcept
		{
			if (pFunc != nullptr)
				return true;
			else
				return false;
		}
		void Unbind() noexcept
		{
			pFunc = nullptr;
		}

		/*Call the func pointer if it is valid*/
		RetVal operator()(Args&&... args) noexcept
		{
			if (IsSubBound())
				return pFunc(std::forward<Args>(args)...);
			else
				return RetVal();
		}
		/*Bind a function to this delegate*/
		SingleDelegate& operator=(FuncPtr pSub) noexcept
		{
			pFunc = pSub;
			return *this;
		}

	private:
		FuncPtr pFunc;
	};

	/*Multi cast delegate is a class that provide a storage for several function pointers.
	When you call an instance of this class it will spread its call throughout all bound func pointers.
	This class can't conitan function signatures with return type anything but void*/
	template<typename...Args>
	class MultiCastDelegate
	{
	public:
		/*FuncPtr as std::function<void(Args...)>*/
		using FuncPtr = std::function<void(Args...)>;
		/*Subs as std::vector*/
		using Subs = std::unordered_map<int, FuncPtr>;

		explicit MultiCastDelegate() noexcept = default;
		Subs GetSubs() const noexcept
		{
			return subs;
		}
		void UnbindAll()
		{
			subs.clear();
		}
		/*Assigns a function and return the unique id to access it later
		return -1 is error value*/
		int Assign(FuncPtr pSub) noexcept
		{
			auto randKey = rand();
			if (pSub != nullptr)
			{
				subs[randKey] = pSub;
				return randKey;
			}
			else
				return -1;
		}
		bool Unbind(int uniqueIndx) noexcept
		{
			auto func = subs.find(uniqueIndx);
			if (func != nullptr)
			{
				subs[uniqueIndx] = nullptr;
				return true;
			}
			else
				return false;
		}
		void operator()(Args&&... args) noexcept
		{
			for (const auto& s : subs)
				s(std::forward<Args>(args)...);
		}
	private:
		Subs subs;
	};

}

#pragma region Macros

// Macro definitions
/*Declares a single delegate signature. Signature can be used to declare several delegates with the same signature*/
#define DECLARE_SINGLE_DELEGATE_SIGNATURE(SignatureName, RetVal, ...) using SignatureName = Delegate::SingleDelegate<RetVal, __VA_ARGS__>;

/*Declares a multicast delegate signature. Signature can be used to declare several delegates with the same signature*/
#define DECLARE_MULTICAST_DELEGATE_SIGNATURE(SignatureName, ...) using SignatureName = Delegate::MultiCastDelegate<__VA_ARGS__>;

/*Declares a single delegate with the passed name and parameters right in the place of macro usage*/
#define DECLARE_SINGLE_DELEGATE(Name, RetVal, ...) Delegate::SingleDelegate<RetVal, __VA_ARGS__> Name

/*Declares a multicast delegate with the passed name and parameters right in the place of macro usage*/
#define DECLARE_MULTICAST_DELEGATE(Name, ...) Delegate::MultiCastDelegate<__VA_ARGS__> Name

/*Expands a function signature of single delegate*/
#define SINGLE_DELEGATE_FUNC_TYPE(RetVal, ...) Delegate::SingleDelegate<RetVal, __VA_ARGS__>::FuncPtr

/*Expands a function signature of multicast delegate*/
#define MULTICAST_DELEGATE_FUNC_TYPE(...) Delegate::MultiCastDelegate<__VA_ARGS__>::FuncPtr

#pragma endregion
