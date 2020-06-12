/**
 * \file Yard.h
 *
 * \author Jacob Sak
 *
 * This is the main class responsible for representing
 * an yard
 */

#pragma once

#include <memory>
#include <vector>
#include "Item.h"


/**
 * Initializes an Yard
 */
class CYard
{
public:

	CYard();
	virtual ~CYard();
	void Add(std::shared_ptr<CItem> item);

	/** Draw the yard
	* \param graphics The GDI+ graphics context to draw on
	*/
	void OnDraw(Gdiplus::Graphics* graphics);

	std::shared_ptr<CItem> HitTest(int x, int y);

	void ToFront(std::shared_ptr<CItem> item);

	void Save(const std::wstring& filename);

	void Load(const std::wstring& filename);

	void Clear();

	void virtual XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void Update(double elapsed);

	/// Get the width of the yard
	/// \returns Yard width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// Get the height of the yard
	/// \returns Yard height
	int GetHeight() const { return mBackground->GetHeight(); }

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image

	/// All of the items to populate our yard
	std::vector<std::shared_ptr<CItem> > mItems;
};

