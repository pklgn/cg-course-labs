#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "LandscapeElement.h"

LandscapeElement::Id LandscapeElement::GetId() const
{
	return m_id;
}

LandscapeElement::Type LandscapeElement::GetType() const
{
	return m_type;
}

void LandscapeElement::SetSize(Size size)
{
	m_size = size;
}

Size LandscapeElement::GetSize() const
{
	return m_size;
}

void LandscapeElement::SetPosition(Vector2d position)
{
	m_position = position;
}

Vector2d LandscapeElement::GetPosition() const
{
	return m_position;
}

LandscapeElement::LandscapeElement(Type type, Size size, Vector2d position)
	: m_type(type)
	, m_size(size)
	, m_position(position)
{
	auto id = boost::uuids::random_generator_mt19937()();
	m_id = boost::uuids::to_string(id);
}
