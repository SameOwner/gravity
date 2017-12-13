#include "Citizen.h"

Citizen::Citizen(IWorld * world, const Vector3 & position, MODEL_ID id, const IBodyPtr & body):
	Actor(world,"Citizen",position,body),animation_(Model::GetInstance().GetHandle(id)),modelid_(id)
{
	change_Animation(Animation::Idle);
}

void Citizen::initialize()
{
}

void Citizen::update(float deltaTime)
{
	animation_.update(MathHelper::Sign(deltaTime)*0.5f);

}

void Citizen::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
}

void Citizen::end()
{
}

void Citizen::onCollide(Actor & other)
{
}

void Citizen::change_Animation(Animation animID, float animFrame, float animSpeed, bool isLoop, float blendRate) {
	animation_.changeAnimation(AnimLoader::getInstance().getAnimKey(modelid_, (int)animID), isLoop, animSpeed, blendRate, animFrame);
}
