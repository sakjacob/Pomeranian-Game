/**
 * \file DecorCastle.h
 *
 * \author Jacob Sak
 *
 * This class defines a beta animal
 */

#pragma once
#include "Item.h"

 /**
  * Creates a singe beta animal
  */
class CDecorCastle : public CItem
{
public:
	/// Default constructor (disabled)
	CDecorCastle() = delete;

	/// Copy constructor (disabled)
	CDecorCastle(const CDecorCastle&) = delete;

	CDecorCastle(CYard* yard);

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

