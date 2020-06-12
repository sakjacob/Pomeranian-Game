#include "pch.h"
#include "CppUnitTest.h"

#include "Item.h"
#include "Yard.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/// mockItem filename 
const std::wstring AnimalBetaImageName = L"images/beta.png";

namespace Testing
{

	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		/** Constructor
		 * \param yard The yard this is a member of */
		CItemMock(CYard* yard) : CItem(yard, AnimalBetaImageName) {}
	};

	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCItemConstruct)
		{
			CYard yard;
			CItemMock item(&yard);
		}

		TEST_METHOD(TestCItemGettersSetters)
		{
			// Construct an item to test
			CYard yard;
			CItemMock item(&yard);

			// Test initial values
			Assert::AreEqual(0, item.GetX(), 0);
			Assert::AreEqual(0, item.GetY(), 0);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(210, 300);
			Assert::AreEqual(210, item.GetX(), 0.0001);
			Assert::AreEqual(300, item.GetY(), 0.0001);

			// Test a second with with different values
			item.SetLocation(400, 150);
			Assert::AreEqual(400, item.GetX(), 0.0001);
			Assert::AreEqual(150, item.GetY(), 0.0001);
		}

		TEST_METHOD(TestCFItemHitTest)
		{
			// Create a animal to test
			CYard yard;
			CItemMock mockItem(&yard);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			mockItem.SetLocation(100, 200);

			// Center of the mockItem should be a true
			Assert::IsTrue(mockItem.CItem::HitTest(100, 200));

			// Left of the mockItem
			Assert::IsFalse(mockItem.CItem::HitTest(10, 200));

			// Right of the mockItem
			Assert::IsFalse(mockItem.CItem::HitTest(200, 200));

			// Above the mockItem
			Assert::IsFalse(mockItem.CItem::HitTest(100, 0));

			// Below the mockItem
			Assert::IsFalse(mockItem.CItem::HitTest(100, 300));

			// Of mockItem transparent pixel
			Assert::IsFalse(mockItem.CItem::HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
		}
	};
}