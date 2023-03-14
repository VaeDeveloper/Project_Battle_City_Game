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
class Beton_Wall : public Game_Object
{
public:
	
	enum class EBeton_Wall_Type			/* Beton Wall Type */
	{
		All,
		Top,
		Bottom,
		Left,
		Right,
		Top_Left,
		Top_Right,
		Bottom_Left,
		Bottom_Right,

	};

	enum class EBlock_State				/* State Bricks */
	{
		Enabled = 0,
		Destroyed
	};

	enum class EBlock_Location
	{
		Top_Left,
		Top_Right,
		Bottom_Left,
		Bottom_Right
	};

	Beton_Wall(const EBeton_Wall_Type beton_wall_type, const glm::vec2& position,  const glm::vec2& size, const float rotation);

	/* Override */
	virtual void Render() const override;
	virtual void Update(const uint64_t delta) override;

private:
	void Render_Block(const EBlock_Location block_location) const;

	std::array<EBlock_State, 4> Curr_Block_State;
	std::shared_ptr<RenderEngine::Sprite> Sprites;
	std::array<glm::vec2, 4> Block_Offsets;

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
