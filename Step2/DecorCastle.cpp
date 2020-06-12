#include "pch.h"
#include "DecorCastle.h"
#include <string>

using namespace std;

/// Animal filename 
const wstring DecorCastleImageName = L"images/castle.png";

/**
* Constructor
* \param yard Yard this animal is a member of
*/
CDecorCastle::CDecorCastle(CYard* yard) : CItem(yard, DecorCastleImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return ptr to a XmlNode object
 */
std::shared_ptr<xmlnode::CXmlNode>
CDecorCastle::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"castle");

	return itemNode;
}
