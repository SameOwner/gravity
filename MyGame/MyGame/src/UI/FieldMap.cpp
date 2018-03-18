#include "FieldMap.h"
#include"../World/IWorld.h"
#include"../Actor/Actor.h"
#include"../ID/EnumIDs.h"
#include"../Graphic/Sprite.h"


FieldMap::FieldMap(IWorld* world,const Vector2 & position):
	UI("FieldMap",position),world_(world)
{
}

void FieldMap::initialize()
{
}

void FieldMap::update(float deltaTime)
{

}

void FieldMap::draw() const
{
	float size = 0.5f;//表示サイズ
	float posrate = 0.2f;//座標補正倍率
	Vector2 center = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_FIELDMAP) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_FIELDMAP, position_, center, Vector2::One*size);

	std::list<std::weak_ptr<Actor>> actors;
	world_->findActors(ActorGroup::POINT_ACTOR, "Enemy", actors);
	for (auto a : actors) {
		Vector2 pos = Vector2{ a.lock()->getPosition().x,-a.lock()->getPosition().z }*posrate*size;
		pos += position_;
		DrawCircle(pos.x, pos.y, 5, GetColor(255, 0, 0));
	}

	Vector2 posit = Vector2{ world_->findActor("Player")->getPosition().x, -world_->findActor("Player")->getPosition().z }*posrate*size;
	posit += position_;
	DrawCircle(posit.x, posit.y, 5, GetColor(0, 255, 0));
}
