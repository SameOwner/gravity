#include "Citizen.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/DebugDraw.h"


Citizen::Citizen(IWorld * world, const Vector3 & position, MODEL_ID id,int type, const IBodyPtr & body):
	Actor(world,"Citizen",position,body),animation_(),modelid_(id), chooser_(world,position, type),state_(State::Idle)
{
	//chooser_.setPoint(position_);
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
	change_State(State::Walk);
}

void Citizen::initialize()
{
}

void Citizen::update(float deltaTime)
{
	animation_.Update(MathHelper::Sign(deltaTime)*0.5f);
	switch (state_)
	{
	case Citizen::State::Idle:
		idle(deltaTime);
		break;
	case Citizen::State::Walk:
		walk(deltaTime);
		break;
	case Citizen::State::Down:
		down(deltaTime);
		break;
	default:
		break;
	}
}

void Citizen::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));

	body_->transform(getPose())->draw();

	DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "%f,%f,%f", position_.x, position_.y, position_.z);
}

void Citizen::end()
{
}

void Citizen::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Bullet, (void*)&hitdir);

}

void Citizen::change_Animation(Animation animID, float animFrame, float animSpeed, bool isLoop, float blendRate) {
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);
}

void Citizen::change_State(State state)
{
	state_ = state;
	change_Animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).isLoop);

	switch (state_)
	{
	case Citizen::State::Idle:
		timer_ = 10.0f;
		break;
	case Citizen::State::Walk:
		chooser_.chooseGoal();
		break;
	case Citizen::State::Down:
		break;
	default:
		break;
	}
}

void Citizen::idle(float deltaTime){
	//if (animation_.IsAnimEnd()) {
	timer_ -= deltaTime;
	if (timer_ <= 0.0f) {
		change_State(State::Walk);
	}
}

void Citizen::walk(float deltaTime){
	float power = 3.0f;
	bool isEnd;
	Vector3 toTargetPosition = (chooser_(position_, isEnd) - position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f*power*power);
	position_ += rotation_.Forward()*0.3f*power;
	if (isEnd) {
		change_State(State::Idle);
	}
}

void Citizen::down(float deltaTime)
{
	change_State(State::Walk);
}
