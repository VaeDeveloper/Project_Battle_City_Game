#pragma once

#include "Game_Object.h"

#include <array>
#include <memory>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Bullet Class
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
class Sprite;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Bullet : public Game_Object
{
#pragma region Init_
  public:
    enum class EOrientation : uint8_t
    {
        Top,
        Bottom,
        Right,
        Left
    };

    Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer);
#pragma endregion Init_

#pragma region Active_
    virtual void Render() const override;

    void Fire(const glm::vec2& position, const glm::vec2& direction);

    bool Is_Active() const { return bIs_Active; }

  private:
    std::shared_ptr<RenderEngine::Sprite> Sprite_Top;
    std::shared_ptr<RenderEngine::Sprite> Sprite_Bottom;
    std::shared_ptr<RenderEngine::Sprite> Sprite_Right;
    std::shared_ptr<RenderEngine::Sprite> Sprite_Left;

    bool bIs_Active;
    EOrientation Orientation;
#pragma endregion Active_
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
