/**
 * \file Yard.cpp
 *
 * \author Jacob Sak
 */

#include "pch.h"
#include "Yard.h"
#include "DecorCastle.h"
#include "Pomeranian.h"
#include "Animal.h"
#include "XmlNode.h"
#include <algorithm>

using namespace Gdiplus;
using namespace xmlnode;
using namespace std;

/**
 * Yard constructor
 */
CYard::CYard()
{
	mBackground = unique_ptr<Gdiplus::Bitmap>(
		Bitmap::FromFile(L"images/backyard1.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/background1.png");
	}

}

/**
 * Destructor
 */
CYard::~CYard()
{
}

/** Draw the yard
 * \param graphics The GDI+ graphics context to draw on
 */
void CYard::OnDraw(Gdiplus::Graphics* graphics)
{

	//RectF rc;
	//graphics->GetClip(&rc);
	//graphics->DrawImage(mBackground.get(), &rc);
	graphics->DrawImage(mBackground.get(), 0, 0,
		mBackground->GetWidth()*3, mBackground->GetHeight()*3);

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));
	graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

	/// Populates yard
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
}

/**
 * Add an item to the yard
 * \param item New item to add
 */
void CYard::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** Test an x,y click location to see if it clicked
* on some item in the yard.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CYard::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

/**
 * If item exists and vector, moves it to the "top" (the end)
 * of the vector
 * \param item an object derived from CItem
 */
void CYard::ToFront(std::shared_ptr<CItem> item)
{
	// finds and erases item from vector
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}

/**
 * Save the yard as a .aqua XML file.
 *
 * Open an XML file and stream the yard data to it.
 *
 * \param filename The filename of the file to save the yard to
 */
void CYard::Save(const std::wstring& filename)
{
	//
	// Create an XML document
	//
	auto root = CXmlNode::CreateDocument(L"aqua");

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	try
	{
		root->Save(filename);
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/**
* Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CYard::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	// A pointer for the item we are loading
	shared_ptr<CItem> item;

	// We have an item. What type?
	wstring type = node->GetAttributeValue(L"type", L"");
	if (type == L"castle")
	{
		item = make_shared<CDecorCastle>(this);
	}
	if (type == L"pomeranian")
	{
		item = make_shared<CPomeranian>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		Add(item);
	}
}

/**
 * Load the yard from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * \param filename The filename of the file to load the yard from.
 */
void CYard::Load(const std::wstring& filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
			{
				XmlItem(node);
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}

/**
 * Clear the yard data.
 *
 * Deletes all known items in the yard.
 */
void CYard::Clear()
{
	mItems.clear();  // Clear and destroy the items in the yard
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CYard::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
}