#include "BaseRoom.h"

void BaseRoom::Draw(const glance::ShaderProgram& program, const glance::ShaderMVPUniformMap& uniformMap) const
{
	for (auto&& roomPart : m_roomParts)
	{
		program.SetUniform4fv(uniformMap.modelUniform.c_str(), roomPart->BuildModelMatrix());
		roomPart->Draw();
	}
}
