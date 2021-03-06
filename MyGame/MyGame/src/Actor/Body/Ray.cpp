#include "Ray.h"

// RXgN^
Ray::Ray(const Vector3 & position, const Vector3 & direction) :
	Body(ShapeType::Ray, position, Matrix::Identity, direction){}

// ÕË»è
bool Ray::isCollide(const IBody & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è()
bool Ray::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(JvZ)
bool Ray::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(üª)
bool Ray::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(AABB)
bool Ray::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(OBB)
bool Ray::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(C)
bool Ray::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// ÕË»è(f)
bool Ray::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// BodyÌ½sÚ®
IBodyPtr Ray::translate(const Vector3 & pos) const {
	return std::make_shared<Ray>(translate_e(pos));
}

// BodyÌÏ·
IBodyPtr Ray::transform(const Matrix & mat) const {
	return std::make_shared<Ray>(transform_e(mat));
}

// BodyÌ½sÚ®
Ray Ray::translate_e(const Vector3 & pos) const {
	return Ray(mPosition + pos, mDirection);
}

// BodyÌÏ·
Ray Ray::transform_e(const Matrix & mat) const {
	return Ray(mPosition * mat, mDirection);
}

// }``æ
void Ray::draw() const{}

void Ray::draw(const Vector3 & position) const
{
}
