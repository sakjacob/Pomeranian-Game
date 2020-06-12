#include "pch.h"
#include "CppUnitTest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "Yard.h"
#include "AnimalBeta.h"
#include "AnimalSparty.h"
#include "AnimalMagikarp.h"
#include "DecorCastle.h"
#include "XmlNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/**
	* Create a path to a place to put temporary files
	*/
	wstring TempPath()
	{
		// Create a path to temporary files
		wchar_t path_nts[MAX_PATH];
		GetTempPath(MAX_PATH, path_nts);

		// Convert null terminated string to wstring
		return wstring(path_nts);
	}

	/**
	* Read a file into a wstring and return it.
	* \param filename Name of the file to read
	* \return File contents
	*/
	wstring ReadFile(const wstring& filename)
	{
		ifstream t(filename);
		wstring str((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		return str;
	}

	/**
	* Test to ensure an yard .aqua file is empty
	*/
	void TestEmpty(wstring filename)
	{
		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
	}

	/**
	*  Populate an yard with three Beta animal
	*/
	void PopulateThreeBetas(CYard* yard)
	{
		// seed random values so they are testable
		const unsigned int RandomSeed = 1238197374;
		srand(RandomSeed);

		shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(yard);
		animal1->SetLocation(100, 200);
		yard->Add(animal1);

		shared_ptr<CAnimalBeta> animal2 = make_shared<CAnimalBeta>(yard);
		animal2->SetLocation(400, 400);
		yard->Add(animal2);

		shared_ptr<CAnimalBeta> animal3 = make_shared<CAnimalBeta>(yard);
		animal3->SetLocation(600, 100);
		yard->Add(animal3);
	}

	void TestThreeBetas(wstring filename)
	{
		// recalculate "random" values from PopulateThreeBetas
		const unsigned int RandomSeed = 1238197374;
		srand(RandomSeed);
		((double)rand());  // unneeded numbers
		((double)rand());  
		double mSpeedX1 = ((double)rand());
		double mSpeedY1 = ((double)rand());

		string speedXString = to_string(mSpeedX1);
		string speedYString = to_string(mSpeedY1);


		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		// Ensure three items
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

		// Ensure the positions are correct
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

		// Ensure the types are correct
		Assert::IsTrue(regex_search(xml,
			wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));

	}

	void PopulateAllTypes(CYard *yard) 
	{
		// seed random values so they are testable
		const unsigned int RandomSeed = 1238197374;
		srand(RandomSeed);

		shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(yard);
		animal1->SetLocation(100, 200);
		yard->Add(animal1);

		shared_ptr<CAnimalSparty> animal2 = make_shared<CAnimalSparty>(yard);
		animal2->SetLocation(400, 400);
		yard->Add(animal2);

		shared_ptr<CAnimalMagikarp> animal3 = make_shared<CAnimalMagikarp>(yard);
		animal3->SetLocation(600, 100);
		yard->Add(animal3);

		shared_ptr<CDecorCastle> castle = make_shared<CDecorCastle>(yard);
		castle->SetLocation(200, 300);
		yard->Add(castle);
	}

	void TestAllTypes(wstring filename)
	{
		// recalculate "random" values from PopulateAllTypes
		const unsigned int RandomSeed = 1238197374;
		srand(RandomSeed);
		((double)rand());  // unneeded numbers
		((double)rand());
		double mSpeedX1 = ((double)rand());
		double mSpeedY1 = ((double)rand());

		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		// Ensure four items
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

		// Ensure the positions are correct
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"200\" y=\"300\"")));

		// Ensure the types are correct
		Assert::IsTrue(regex_search(xml,
			wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"Sparty\"/><item.* type=\"Magikarp\"/><item.* type=\"castle\"/></aqua>")));
	}

	TEST_CLASS(CYardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCYardConstruct)
		{
			CYard yard;
		}

		TEST_METHOD(TestCYardHitTest)
		{
			CYard yard;

			Assert::IsTrue(yard.HitTest(100, 200) == nullptr,
				L"Testing empty yard");

			shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(&yard);
			animal1->SetLocation(100, 200);
			yard.Add(animal1);

			Assert::IsTrue(yard.HitTest(100, 200) == animal1,
				L"Testing animal at 100, 200");
		}

		TEST_METHOD(TestCYardStackAnimalTest)
		{
			// Create two animal
			CYard yard;
			shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(&yard);
			shared_ptr<CAnimalBeta> animal2 = make_shared<CAnimalBeta>(&yard);

			// Stack them on top of each other
			animal1->SetLocation(100, 200);
			animal2->SetLocation(100, 200);

			// Add them both to the same yard
			yard.Add(animal1);
			yard.Add(animal2);

			Assert::IsTrue(yard.HitTest(100, 200) == animal2);
		}

		TEST_METHOD(TestCYardNullptrReturnTest)
		{
			// Create two animal
			CYard yard;
			shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(&yard);
			shared_ptr<CAnimalBeta> animal2 = make_shared<CAnimalBeta>(&yard);

			// Stack them on top of each other
			animal1->SetLocation(100, 200);
			animal2->SetLocation(100, 200);

			// Add them both to the same yard
			yard.Add(animal1);
			yard.Add(animal2);

			Assert::IsTrue(yard.HitTest(10, 200) == nullptr);
		}


		TEST_METHOD(TestCYardSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an yard
			CYard yard;

			//
			// First test, saving an empty yard
			//
			wstring file1 = path + L"test1.aqua";
			yard.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the yard
			//

			PopulateThreeBetas(&yard);

			wstring file2 = path + L"test2.aqua";
			yard.Save(file2);

			TestThreeBetas(file2);

			//
			// Test all types
			//
			CYard yard3;
			PopulateAllTypes(&yard3);

			wstring file3 = path + L"test3.aqua";
			yard3.Save(file3);

			TestAllTypes(file3);
		}

		TEST_METHOD(TestCYardClear)
		{
			// initialize and populate yard
			CYard yard;
			shared_ptr<CAnimalBeta> animal1 = make_shared<CAnimalBeta>(&yard);
			shared_ptr<CAnimalBeta> animal2 = make_shared<CAnimalBeta>(&yard);
			animal1->SetLocation(100, 200);
			animal2->SetLocation(200, 100);
			yard.Add(animal1);
			yard.Add(animal2);

			// Test to make sure they're there
			Assert::IsTrue(yard.HitTest(100, 200) == animal1);
			Assert::IsTrue(yard.HitTest(200, 100) == animal2);

			// Clear yard
			yard.Clear();

			// Now test the animal are NOT there
			Assert::IsTrue(yard.HitTest(100, 200) == nullptr);
			Assert::IsTrue(yard.HitTest(200, 100) == nullptr);
		}

		TEST_METHOD(TestCYardLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two yards
			CYard yard, yard2;

			//
			// First test, saving an empty yard
			//
			wstring file1 = path + L"test1.aqua";

			yard.Save(file1);
			TestEmpty(file1);

			yard2.Load(file1);
			yard2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the yard
			//

			PopulateThreeBetas(&yard);

			wstring file2 = path + L"test2.aqua";
			yard.Save(file2);
			TestThreeBetas(file2);

			yard2.Load(file2);
			yard2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CYard yard3;
			PopulateAllTypes(&yard3);

			wstring file3 = path + L"test3.aqua";
			yard3.Save(file3);
			TestAllTypes(file3);

			yard2.Load(file3);
			yard2.Save(file3);
			TestAllTypes(file3);
		}
	};
}