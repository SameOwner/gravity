#include "PointGenerator.h"
#include"../ID/EnumIDs.h"
#include"../Actor/Other/CheckPoint.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"

PointGenerator::PointGenerator():world_(nullptr),reader_()
{
}

PointGenerator::PointGenerator(IWorld * world,const std::string& filename)
	:world_(world), reader_(filename){
	generate();
}

void PointGenerator::setParameter(IWorld * world, const std::string & filename)
{
	//初期化
	pointCount_ = 0;
	isEnd_ = false;

	//値の設定
	world_ = world;
	reader_.load(filename);

	//生成
	generate();
}

PointGenerator::~PointGenerator()
{
	world_ = nullptr;
}

void PointGenerator::update(float deltaTime)
{
	if (world_ == nullptr)return;//ワールドを持ってなかったら生成しない

	if (isEnd_)return;//全部出し終わってたらもう生成しない
	
	//ポイントがいなくなってたら、次のポイントを生成する
	if (world_->getActorCount(ActorGroup::POINT_ACTOR) == 0) {
		generate();
	}
}

void PointGenerator::draw() const
{
	int t = reader_.rows() - pointCount_ + 1;
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, 0, GetColor(255, 255, 255), "%d",t);
}

bool PointGenerator::isEnd() const
{
	return isEnd_;
}

void PointGenerator::generate()
{
	//全部出したら終わり
	if (reader_.rows() <= pointCount_) {
		isEnd_ = true;
		pointCount_++;
		return;
	}
	Vector3 position;
	position.x = reader_.getf(pointCount_, 0);
	position.y = reader_.getf(pointCount_, 1);
	position.z = reader_.getf(pointCount_, 2);

	world_->addActor(ActorGroup::POINT_ACTOR, std::make_shared<CheckPoint>(world_, position));

	pointCount_++;
}
