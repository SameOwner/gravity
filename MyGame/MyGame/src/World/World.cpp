#include "World.h"
#include"../ID/EnumIDs.h"
#include"../Actor/Actor.h"
#include"../Field/FieldBase.h"
#include"../Actor/Other/CameraActor.h"
#include"../Input/InputChecker.h"

World::World():field_(nullptr)
{
}

void World::initialize()
{
	actors_.initialize();
	uiManager_.initialize();
	field_ = nullptr;
	camera_.reset();
	map_.initialize();
	map_.getWorld(this);//テスト用
	walkMap_.initialize();
	fade_.init();

}

void World::update(float deltaTime)
{
	if (field_ != nullptr)field_->update(deltaTime);
	actors_.update(deltaTime);
	uiManager_.update(deltaTime);
	fade_.update(deltaTime);
}

void World::draw() const
{
	//fieldがいたら描画
	if(field_!=nullptr)
		field_->draw();

	actors_.draw();
	uiManager_.draw();

	map_.draw();

	fade_.draw();
}

void World::handleMessage(EventMessage message, void * param)
{
}

void World::addActor(ActorGroup group, const ActorPtr & actor)
{
	actors_.addActor(group, actor);
}

void World::addUI(const UIPtr & ui)
{
	uiManager_.add(ui);
}

void World::loadMap(const std::string & pointfilename,const std::string& mapfilename)
{
	map_.load(pointfilename,mapfilename);
}

void World::addWalkPoint(const std::string & pointfilename, const std::string & mapfilename)
{
	walkMap_.load(pointfilename, mapfilename);
}

void World::addCamera(const std::shared_ptr<CameraActor> & cameraActor)
{
	camera_ = cameraActor;
	actors_.addActor(ActorGroup::ETCETERA_ACTOR, cameraActor);

}

ActorPtr World::findActor(const std::string & name)
{
	return actors_.findActor(name);
}

void World::findActors(ActorGroup group,const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	actors_.findActor(group,name, actorList);
}

int World::getActorCount(ActorGroup group) const
{
	return actors_.getSize(group);
}

void World::sendMessage(EventMessage message, void * param)
{
	actors_.handleMessage(message, param);
}

FieldPtr World::getField()
{
	return field_;
}

void World::setField(FieldPtr field)
{
	field_ = field;
}

CityMap & World::getCityMap()
{
	return map_;
}

WalkGraph & World::getWalkMap()
{
	return walkMap_;
}

FadeSprite & World::getFade()
{
	return fade_;
}

std::weak_ptr<CameraActor> World::getCamera() const
{
	return camera_;
}
