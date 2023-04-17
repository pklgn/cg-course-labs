#pragma once
#include <memory>
#include <string>
#include "../../Common/Types/DimensionTypes.h"

class LandscapeElement : public std::enable_shared_from_this<LandscapeElement>
{
public:
	using Id = std::string;
	std::shared_ptr<LandscapeElement> GetPtr()
	{
		return shared_from_this();
	}

	// No public constructor, only a factory function,
	// so there's no way to have getptr return nullptr.
	[[nodiscard]] static std::shared_ptr<LandscapeElement> Create(Size size, Vector2d position)
	{
		// Not using std::make_shared<Best> because the c'tor is private.
		return std::shared_ptr<LandscapeElement>(new LandscapeElement(size, position));
	}

	Id GetId() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetPosition(Vector2d position);
	Vector2d GetPosition() const;

private:
	LandscapeElement() = default;
	LandscapeElement(Size size, Vector2d position);

	Id m_id;
	Size m_size;
	Vector2d m_position;
};
