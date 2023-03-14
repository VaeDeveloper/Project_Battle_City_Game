#include "Beton_Wall.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Beton_Wall::Beton_Wall(const EBeton_Wall_Type beton_wall_type, const glm::vec2& position, const glm::vec2& size, const float rotation)
: Game_Object(position, size, rotation), Curr_Block_State{ EBlock_State::Destroyed,EBlock_State::Destroyed,EBlock_State::Destroyed,EBlock_State::Destroyed },
  Sprites(Resource_Manager::Get_Sprite("betonWall")),
  Block_Offsets{ glm::vec2(0, Size.y / 2.f),glm::vec2(Size.x / 2.f, Size.y / 2.f),glm::vec2(0, 0),glm::vec2(Size.x / 2.f, 0) }
{

	switch (beton_wall_type)
	{
	case EBeton_Wall_Type::All:
		Curr_Block_State.fill(EBlock_State::Enabled);
		break;
	case EBeton_Wall_Type::Top:
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Left)]		= EBlock_State::Enabled;
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Right)]		= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Bottom:												
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Left)]		= EBlock_State::Enabled;
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Right)]	= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Left:												
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Left)]		= EBlock_State::Enabled;
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Left)]		= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Right:												
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Right)]		= EBlock_State::Enabled;
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Right)]	= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Top_Left:											
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Left)]		= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Top_Right:											
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Top_Right)]		= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Bottom_Left:											
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Left)]		= EBlock_State::Enabled;
		break;																	
	case EBeton_Wall_Type::Bottom_Right:										
		Curr_Block_State[static_cast<size_t>(EBlock_Location::Bottom_Right)]	= EBlock_State::Enabled;
		break;
	}



}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Beton_Wall::Render() const
{
	Render_Block(EBlock_Location::Top_Left);
	Render_Block(EBlock_Location::Top_Right);
	Render_Block(EBlock_Location::Bottom_Left);
	Render_Block(EBlock_Location::Bottom_Right);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Beton_Wall::Update(const uint64_t delta)
{
}
void Beton_Wall::Render_Block(const EBlock_Location block_location) const
{
	const EBlock_State state = Curr_Block_State[static_cast<size_t>(block_location)];

	if (state != EBlock_State::Destroyed)
	{
		Sprites->Render(Position + Block_Offsets[static_cast<size_t>(block_location)], Size / 2.f, Rotation);
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
