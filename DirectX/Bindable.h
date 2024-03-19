#pragma once
#include "GraphicsResource.h"
#include <memory>
#include <string>
#include "ConditionalNoexcept.h"

class Drawable;
class TechniqueProbe;
class Graphics;

namespace Bind
{
	class Bindable : public GraphicsResource
	{
	public:
		virtual void Bind( Graphics& gfx ) noxnd = 0;
		virtual void InitializeParentReference( const Drawable& ) noexcept
		{}
		virtual void Accept( TechniqueProbe& )
		{}
		virtual std::string GetUID() const noexcept
		{
			assert( false );
			return "";
		}
		virtual ~Bindable() = default;
	};

	class CloningBindable : public Bindable
	{
	public:
		virtual std::unique_ptr<CloningBindable> Clone() const noexcept = 0;
	};
}

/*Use this macro to declare resolve function for a bindable child class. It's used since virtual functions can't be static but being
static is vital for this system*/
#define DECLARE_RESOLVE(ptrType, ...) static std::shared_ptr<ptrType> Resolve(__VA_ARGS__)
/*Use this one to declare UID generation*/
#define DECLARE_GENERATEUID(...) static std::string GenerateUID(__VA_ARGS__)
/*This macro overrides a virtual bindalbe function member*/
#define DECLARE_OVERRIDE_GETUID(...) std::string GetUID(__VA_ARGS__) const noexcept override
/*Defines resolve function in cpp file of implemented class*/
#define DEFINE_RESOLVE(ptrType, ClassName, ...) std::shared_ptr<ptrType> ClassName::Resolve(__VA_ARGS__)
/*Defins GenerateUID functions*/
#define DEFINE_GENERATEUID(ClassName, ...) std::string ClassName::GenerateUID(__VA_ARGS__)
/*Define overriden GetUID()*/
#define DEFINE_OVERIDDEN_GETUID(ClassName) std::string ClassName::GetUID() const noexcept