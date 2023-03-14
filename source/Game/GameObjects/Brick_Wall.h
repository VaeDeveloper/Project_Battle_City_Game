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
class Brick_Wall : public Game_Object
{
public:
	
	enum class EBrick_Wall_Type : uint8_t		/* Brick Wall Type */
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

	enum class EBrick_State : uint8_t		/* State Bricks */
	{
		All = 0,
		Top_Left,
		Top_Right,
		Top,
		Bottom_Left,
		Left,
		Top_Right_Bottom_Left,
		Top_Bottom_Left,
		Bottom_Right,
		Top_Left_Bottom_Right,
		Right,
		Top_Bottom_Right,
		Bottom,
		Top_Left_Bottom,
		Top_Right_Bottom,
		Destroyed
	};

	enum class EBrick_Location : uint8_t
	{
		Top_Left,
		Top_Right,
		Bottom_Left,
		Bottom_Right
	};

	Brick_Wall(const EBrick_Wall_Type brick_wall_type, const glm::vec2& position,  const glm::vec2& size, const float rotation, const float layer);

	/* Override */
	virtual void Render() const override;
	virtual void Update(const uint64_t delta) override;

private:
	void Render_Brick(const EBrick_Location brick_location) const;

	std::array<EBrick_State, 4> Curr_Brick_State;
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> Sprites;
	std::array<glm::vec2, 4> Block_Offsets;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
