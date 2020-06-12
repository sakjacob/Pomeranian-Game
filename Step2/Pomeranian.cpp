#include "pch.h"
#include "Pomeranian.h"
#include <string>

using namespace std;

/// Animal filename 
const wstring AnimalBetaImageName = L"images/pomeranian.png";

/**
* Constructor
* \param yard Yard this animal is a member of
*/
CPomeranian::CPomeranian(CYard* yard) : CAnimal(yard, AnimalBetaImageName)
{
	CAnimal::SetSpeed(minSpeedX, minSpeedY, maxSpeedX, maxSpeedY);
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return ptr to a XmlNode object
 */
std::shared_ptr<xmlnode::CXmlNode>
CPomeranian::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	auto itemNode = CAnimal::XmlSave(node);

	itemNode->SetAttribute(L"type", L"pomeranian");

	return itemNode;
}


