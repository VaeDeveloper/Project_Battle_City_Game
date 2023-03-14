#pragma once 

#include "Game_Object.h"

#include <memory>
#include <glm/vec2.hpp>
#include <array>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Brick Wall Game Object
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Sprite;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Eagle : public Game_Object
{
public:

	enum class EEagle_State : uint8_t
	{
		Alive = 0,
		Dead
	};

	Eagle(const glm::vec2& position,  const glm::vec2& size, const float rotation);

	/* Override */
	virtual void Render() const override;
	virtual void Update(const uint64_t delta) override;

private:
	/* Sprite Object */
	std::array<std::shared_ptr<RenderEngine::Sprite>, 2> Sprites;

	/* Block Offset location */
	std::array<glm::vec2, 4> Block_Offsets;

	/* Eagle State */
	EEagle_State Eagle_State;

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
