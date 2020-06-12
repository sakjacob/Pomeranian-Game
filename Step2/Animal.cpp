#include "pch.h"
#include "Animal.h"
#include "Yard.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 35;

/**
 * Constructor
 * \param yard The yard we are in
 * \param filename Filename for the image we use
 */
CAnimal::CAnimal(CYard* yard, const std::wstring& filename) :
	CItem(yard, filename)
{
	mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
	mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
}

/**
 * Determines speed and direction of animal
 * \param minSpeedX minimum speed in x direction in pixels per second
 * \param minSpeedY minimum speed in y direction in pixels per second
 * \param maxSpeedX maximum speed in y direction in pixels per second
 * \param maxSpeedY maximum speed in y direction in pixels per second
 */
void CAnimal::SetSpeed(double minSpeedX, double minSpeedY, double maxSpeedX, double maxSpeedY)
{
	mSpeedX = minSpeedX + ((double)rand() / RAND_MAX) * (maxSpeedX - minSpeedX);
	mSpeedY = minSpeedY + ((double)rand() / RAND_MAX) * (maxSpeedY - minSpeedY);
}

/**
 * Handle updates in time of our animal
 *
 * This is called before we draw and allows us to
 * move our animal. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CAnimal::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);

	double rightTurn = GetYard()->GetWidth() - 10 - GetImageWidth() / 2;
	double leftTurn = GetYard()->GetWidth() - rightTurn;
	double bottomTurn = GetYard()->GetHeight() - 10 - GetImageHeight() / 2;
	double topTurn = GetYard()->GetHeight() - bottomTurn;
	/// Changes direction when animal hits right border of screen
	if (mSpeedX > 0 && GetX() >= rightTurn)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	/// Changes diretion when animal hits left border of screen
	if (mSpeedX < 0 && GetX() <= leftTurn)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	/// Changes direction when animal hits the bottom border of screen
	if (mSpeedY > 0 && GetY() >= bottomTurn)
	{
		mSpeedY = -mSpeedY;
	}

	/// Changes direction when animal hits the top border of screen
	if (mSpeedY < 0 && GetY() <= topTurn)
	{
		mSpeedY = -mSpeedY;
	}
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return ptr to a XmlNode object
 */
std::shared_ptr<xmlnode::CXmlNode>
CAnimal::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	auto itemNode = CItem::XmlSave(node);  //save values stored in CItem class

	// Save Speed values
	itemNode->SetAttribute(L"speedx", mSpeedX);
	itemNode->SetAttribute(L"speedy", mSpeedY);

	return itemNode;
}


/**
 * Load the attributes for an animal node.
 *
 * This is the  base class version that loads the attributes
 * common to all animal.
 *
 * \param node The Xml node we are loading the item from
 */
void CAnimal::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
	mSpeedX = node->GetAttributeDoubleValue(L"speedx", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"speedy", 0);
	SetMirror(mSpeedX < 0);
}
