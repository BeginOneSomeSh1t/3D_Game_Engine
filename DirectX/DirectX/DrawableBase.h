#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"
#include "ConditionalNoexcept.h"

template<typename T>
class DrawableBase : public Drawable
{
protected:
	/*Returns whether a static container was initialized with at least one object or not*/
	static bool IsStaticInitialized() noexcept
	{
		return !staticBinds.empty();
	}
	/*Ass bindable to static binds container*/
	static void AddStaticBind(std::unique_ptr<Bind::Bindable> bind) noxnd
	{
		assert("Use AddStaticIndexBuffer if you want to add an index buffer" && typeid(*bind) != typeid(Bind::IndexBuffer));
		staticBinds.push_back(std::move(bind));
	}
	/*Add index buffer to static binds container*/
	void AddStaticIndexBuffer(std::unique_ptr<Bind::IndexBuffer> ibuf) noxnd
	{
		assert("Attempting to add a second one buffer" && pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}
	/*Set index buffer from static binds container*/
	void SetIndexBufferFromStatic() noxnd
	{
		assert("Attemtping to add a second buffer" && pIndexBuffer == nullptr);
		for (const auto& b : staticBinds)
		{
			if (const auto pBuff = dynamic_cast<Bind::IndexBuffer*>(b.get()))
			{
				pIndexBuffer = pBuff;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && pIndexBuffer == nullptr);
	}
	
	const std::vector<std::unique_ptr<Bind::Bindable>>& GetStaticBinds() const noexcept override
	{
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<Bind::Bindable>> staticBinds;
};
/*Allocate memory for the statc member*/
template<typename T>
std::vector<std::unique_ptr<Bind::Bindable>> DrawableBase<T>::staticBinds;