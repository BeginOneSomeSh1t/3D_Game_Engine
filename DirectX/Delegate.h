#pragma once
#include <utility>
#include <unordered_map>
#include <random>
#include <functional>
#include <vector>

namespace Delegate
{

	// Delegate definitions

	/*Single delegate is a class that can store a one pointer to function instance*/
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
		bool IsSubAssigned() const noexcept
		{
			if (pFunc != nullptr)
				return true;
			else
				return false;
		}
		void Detach() noexcept
		{
			pFunc = nullptr;
		}

		/*Call the func pointer if it is valid*/
		RetVal operator()(Args&&... args) noexcept
		{
			if (IsSubAssigned())
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
		using PairType = std::pair<int, FuncPtr>;
		using Subs = std::unordered_map<int, FuncPtr>;
		using Pairs = std::vector<PairType>;

		MultiCastDelegate() = default;

		/*Gets a subscriber under uniqued index. Returns empty std::function if there wasn't such entry*/
		FuncPtr GetSubscriber(int uniqueIndx) noexcept
		{
			if (auto sub = subs.find(uniqueIndx) != subs.end())
				return sub->second;
			else
				return FuncPtr();
		}
		bool IsSubExists(int uniqueIndx)
		{
			if (subs.find(uniqueIndx) != subs.end())
				return true;
			else
				return false;
		}
		/*Detaches all currently bound function pointer from the map container*/
		void DetachAll()
		{
			subs.clear();
		}
		/*Assigns a function pointer to this delegate and returns
		a unique id of this function to be able to access it later
		This function returns -1 in case the assignment wasn't successful*/
		int Assign(FuncPtr sub)
		{
			auto randKey = rand();
			if (sub != nullptr)
			{
				subs[randKey] = sub;
				return randKey;
			}
			else
				return -1;

		}
		/*Assigns a func pointer to this delegate and returns the duplicate of the
		pointed index in case there wasn't an element under the index. In case
		there was an element under the pointed index, then it'll generate new rand index and return it.
		You always want to store this function's return value*/
		int Assign(FuncPtr sub, int&& willingIndx)
		{
			if (subs.find(willingIndx) != subs.end())
			{
				auto randKey = rand();
				subs[randKey] = sub;
				return randKey;
			}
			else
			{
				subs[willingIndx] = sub;
				return std::move(willingIndx);
			}
		}
		bool Assign(Pairs pairs)
		{
			if (!pairs.empty())
			{
				for (auto& p : pairs)
				{
					if (!IsSubExists(p.first))
						subs[p.first] = p.second;
					else
						return false;
				}
				return true;
			}
			else
				return false;
		}
		/*Detaches (clears) an entry of the map container via the provided index.
		returns true, if the element under the index was successfully deleted,
		otherwise false*/
		bool Detach(int uniqueId) noexcept
		{
			if (auto it = subs.find(uniqueId) != subs.end())
			{
				subs.erase(it);
				return true;
			}
			else
				return false;
		}
		void operator()(Args&&... args) noexcept
		{
			for (const auto& s : subs)
				s.second(std::forward<Args>(args)...);
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
