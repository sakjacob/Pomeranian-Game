/**
 * \file Animal.h
 *
 * \author Jacob Sak
 *
 * Base Class for animales in the yard
 *
 * Derives from CItem class. Note that 
 * decorative objects are not CAnimal objects
 */

#pragma once

#include "Item.h"

/**
 * Base class for a animal
 * This applies to all of the animal, but not the decor
 * items in the yard.
 */
class CAnimal : public CItem
{
public:
	/// Default constructor (disabled)
	CAnimal() = delete;

	/// Copy constructor (disabled)
	CAnimal(const CAnimal&) = delete;

	void Update(double elapsed);

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

private:
	/// Animal speed in the X direction
	double mSpeedX;

	/// Animal speed in the Y direction
	double mSpeedY;

protected:
	CAnimal(CYard* yard, const std::wstring& filename);

	void SetSpeed(double minX, double minY, double rangeX, double rangeY);
};

