#pragma once
#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
#include <vector>
#include <string>
#include "MyException.h"

class ScriptCommander
{
public:
	class Completion : public MyException
	{
	public:
		Completion( const std::string& content ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
	private:
		std::string content;
	};
	class Exception : public MyException
	{
	public:
		Exception( int line,const char* file,const std::string& script = "",const std::string& message = "" ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
	private:
		std::string script;
		std::string message;
	};
public:
	ScriptCommander( const std::vector<std::string>& args );
private:
	void Publish(std::string path) const;
};