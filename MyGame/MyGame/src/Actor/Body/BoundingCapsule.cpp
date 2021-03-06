#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "../../Math/Collision/Collision.h"

// RXgN^
BoundingCapsule::BoundingCapsule(const Vector3& pos, const Matrix& mat, const float& len, const float& rad) :
	Body(ShapeType::Capsule, pos, mat, rad, len) {
	mPoints[0] = pos + Vector3::Up * (len*0.5f);// - rad);
	mPoints[1] = pos - Vector3::Up * (len*0.5f);// - rad);
}

// ÕË»è
bool BoundingCapsule::isCollide(const IBody & other, HitInfo & hitinfo) const {
	if (!other.enabled() || !enabled())return false;
	
	return other.intersects(*this, hitinfo);
}

// ÕË»è()
bool BoundingCapsule::intersects(const BoundingSphere & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Capsule(other.position(), other.radius(), mPosition, mMatrix, mLength, mRadius);
}

// ÕË»è(JvZ)
bool BoundingCapsule::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const {
	return Collision::Capsule_Capsule(mPosition, mMatrix, mLength, mRadius, other.mPosition, other.mMatrix, other.mLength, other.mRadius);
}

// ÕË»è(üª)
bool BoundingCapsule::intersects(const BoundingSegment & other, HitInfo & hitinfo) const {
	return Collision::Capsule_Segment(other.position(), other.matrix(), other.length(), mPosition, mMatrix, mLength, mRadius);
}

// ÕË»è(AABB)
bool BoundingCapsule::intersects(const BoundingBox & other, HitInfo & hitinfo) const {
	return false;
}

// ÕË»è(OBB)
bool BoundingCapsule::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(C)
bool BoundingCapsule::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(f)
bool BoundingCapsule::intersects(const CollisionModel & other, HitInfo & hitinfo) const {
	return false;
}

// BodyÌ½sÚ®
IBodyPtr BoundingCapsule::translate(const Vector3 & pos) const {
	return std::make_shared<BoundingCapsule>(translate_e(pos));
}

// BodyÌÏ·
IBodyPtr BoundingCapsule::transform(const Matrix & mat) const {
	return std::make_shared<BoundingCapsule>(transform_e(mat));
}

// BodyÌ½sÚ®
BoundingCapsule BoundingCapsule::translate_e(const Vector3 & pos) const{
	return BoundingCapsule(mPosition + pos, mMatrix, mLength, mRadius);
}

// BodyÌÏ·
BoundingCapsule BoundingCapsule::transform_e(const Matrix & mat) const{
	return BoundingCapsule(mPosition + mat.Translation(), mMatrix * mat.RotationMatrix(), mLength * mat.Scale().y, mRadius * mat.Scale().x);
}

// }``æ
void BoundingCapsule::draw() const{
#ifdef _DEBUG

	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix;

	DrawCapsule3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), mRadius, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
#endif
}

void BoundingCapsule::draw(const Vector3 & position) const
{
#ifdef _DEBUG

	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix +position;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix +position;

	DrawCapsule3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), mRadius, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

#endif
}
