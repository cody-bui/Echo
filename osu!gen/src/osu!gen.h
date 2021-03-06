#pragma once

#include <EchoGen.h>

namespace OsuGen
{
	class Program : public EchoGen::Application
	{
	private:
		// patterns
		EchoGen::PatternList* patterns;
	public:
		Program();

		virtual void Run();

		~Program();
	};
}

EchoGen::Application* CreateApp()
{
	return new OsuGen::Program();
}