#include "pch.h"
#include "CppUnitTest.h"


#include "AnimalBeta.h"
#include "Yard.h"
#include "Item.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{

	TEST_CLASS(CAnimalBetaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(CAnimalBetaConstructorTest)
		{
			CYard yard;
			CAnimalBeta beta(&yard);
		}
	};
}