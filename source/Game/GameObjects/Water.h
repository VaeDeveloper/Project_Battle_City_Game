#pragma once 

#include "Game_Object.h"
#include "../../Renderer/Sprite_Animator.h"

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
class Water : public Game_Object
{
public:
	
	/* block location */
	enum class EBlock_Location : uint8_t
	{
		Top_Left,
		Top_Right,
		Bottom_Left,
		Bottom_Right
	};

	Water(const glm::vec2& position,  const glm::vec2& size, const float rotation);

	/* Override */
	virtual void Render() const override;

	/* Update */
	void Update(const uint64_t delta) override;


private:
	/* Render Block Sprite Location */
	void Render_Block(const EBlock_Location block_location) const;

	/* Sprite Object */
	std::shared_ptr<RenderEngine::Sprite> Sprites;

	RenderEngine::Sprite_Animator W_Sprite_Animator;

	/* Block Offset location */
	std::array<glm::vec2, 4> Block_Offsets;

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
