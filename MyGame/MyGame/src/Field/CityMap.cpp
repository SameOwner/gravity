#include "CityMap.h"
#include"../Resource/CsvReader.h"
#include"../World/IWorld.h"//テスト用
#include"../Actor/Actor.h"

CityMap::CityMap()
{
}

CityMap::~CityMap()
{
	carPoints_.clear();
	carPointMap_.clear();

}

void CityMap::initialize()
{
	carPoints_.clear();
	carPointMap_.clear();

}

void CityMap::load(const std::string & pointfilename, const std::string& mapfilename)
{
	CsvReader cr{ pointfilename };

	for (int i = 0; i < cr.rows(); i++) {
		carPoints_.emplace_back(
			cr.getf(i, 0),
			cr.getf(i, 1),
			cr.getf(i, 2)
		);
	}
	cr.load(mapfilename);

	carPointMap_.initialize(cr.columns(), cr.rows());

	for (int r = 0; r < cr.rows(); r++) {
		for (int c = 0; c < cr.columns(); c++) {
			int x = cr.geti(r, c);
			carPointMap_.setElement(c, r, x);
		}
	}
}

int CityMap::getNextCarPoint(int current, int goal)
{
	return carPointMap_.getElement(current, goal);
}

Vector3 CityMap::getPosition(int point)
{
	return carPoints_[point];
}

void CityMap::getWorld(IWorld * wrd)
{
	world = wrd;
}

int CityMap::getSize() const
{
	return carPoints_.size();
}

int CityMap::getNearestPoint(const Vector3 & position)
{
	int result = 0;
	float nearlength = Vector3::Distance(position, carPoints_.front());

	float length;
	for (int i = 0; i < carPoints_.size(); i++) {
		length = Vector3::Distance(position, carPoints_.at(i));
		if (length < nearlength) {
			nearlength = length;
			result = i;
		}
	}
	return result;
}

void CityMap::draw() const
{
	Vector3 pos = world->findActor("Player")->getPosition();
	int nearest = 0;
	float length = 999999;
	int count = 0;
	for (auto& cp : carPoints_) {
		float dist = Vector3::Distance(cp, pos);
		if (dist < length) {
			length = dist;
			nearest = count;
		}
		DrawSphere3D(cp, 10.0f, 32, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
		count++;
	}
	DrawFormatString(720, 300, GetColor(255, 255, 255), "%d", nearest);
}
