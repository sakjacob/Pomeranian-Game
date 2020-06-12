/**
 * \file Item.h
 *
 * \author Jacob Sak
 *
 * This file does something I am not sure of yet
 */

#pragma once

#include <memory>
#include <string>
#include "XmlNode.h"

using namespace Gdiplus;

/**
 * Forward reference
 */
class CYard;

/**
 * Represents an Item
 */
class CItem
{
protected:
	CItem(CYard* yard, const std::wstring &filename);


public:
	virtual ~CItem();

	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	/** The X location of the item
    * \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/** The width of the item
	* \returns width in pixels */
	double GetImageWidth() const { return mItemImage->GetWidth(); }

	/** The height of the item
	* \returns height in pixels */
	double GetImageHeight() const { return mItemImage->GetHeight(); }

	/// Get the yard this item is in
	/// \returns Yard pointer
	CYard* GetYard() { return mYard; }

	void virtual SetLocation(double x, double y, bool nudge = false);

	/// Draw this item
	/// \param graphics Graphics device to draw on
	void Draw(Gdiplus::Graphics* graphics);

	bool HitTest(int x, int y);

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }

private:

	// Item location in the yard
	double  mX = 0;     ///< X location for the center of the item
	double  mY = 0;     ///< Y location for the center of the item

	bool mMirror = false;   ///< True mirrors the item image

	/// The yard this item is contained in
	CYard* mYard;

	/// The image of this item
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;
};

