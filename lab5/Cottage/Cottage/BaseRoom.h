#pragma once
#include <vector>
#include <memory>
#include "../Model/IDrawable.h"
#include "../Model/IPolytopeDrawable.h"

class BaseRoom : public IDrawable
{
public:
	void Draw(const glance::ShaderProgram& program, const glance::ShaderMVPUniformMap& uniformMap) const override;

protected:
	std::vector<std::unique_ptr<IPolytopeDrawable>> m_roomParts;
};