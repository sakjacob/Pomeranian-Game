/**
 * \file pomeranian.h
 *
 * \author Jacob Sak
 *
 * This class defines a Pomeranian
 */

#pragma once
#include "Animal.h"

 /**
  * Creates a singe pomeranian 
  */
class CPomeranian : public CAnimal
{
public:
	/// Default constructor (disabled)
	CPomeranian() = delete;

	/// Copy constructor (disabled)
	CPomeranian(const CPomeranian&) = delete;

	CPomeranian(CYard* yard);

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;


private:
	/// min  speed in x direction
	double minSpeedX = 5;

	/// min  speed in y direction
	double minSpeedY = 40;

	/// possible speed above min x direction
	double maxSpeedX = 20;

	/// possible speed above min y direction
	double maxSpeedY = 60;
};

