#pragma once

#include "Sprite.h"

#include <map>
#include <vector>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Sprite
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Renderer
{
	class Animated_Sprite : public Sprite
	{
	public:
		//============================================================================================================================================================
		// Constructors and Destructors
		/*	Use the actual constructor for this class */
		Animated_Sprite(const std::shared_ptr<Texture2D> texture,
			const std::string initial_subtexture,
			const std::shared_ptr<Shader_Program> shader_program,
			const glm::vec2& position = glm::vec2(0.0f),
			const glm::vec2& size = glm::vec2(1.0f),
			const float rotation = 0.0f);
		//============================================================================================================================================================

		//============================================================================================================================================================
		//Override function
		/* override Render method is sprite class */
		virtual void Render() const override;
		//============================================================================================================================================================



		//============================================================================================================================================================
		// Public method 
		/* Set Animation State */
		void Set_State(const std::string& new_state);

		/* Update Animation */
		void Update(const uint64_t delta);

		/*  Initial Animation Statement for sprite */
		void Insert_State(std::string state, std::vector<std::pair<std::string, uint64_t>> subtextures_duration);
		//============================================================================================================================================================

	private:
		//============================================================================================================================================================
		// Private Variables

		mutable bool Dirty;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> States_Map;

		size_t Current_Frame;
		uint64_t Current_Animation_Time;

		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator Current_Animation_Duration;

		//============================================================================================================================================================

	};
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
