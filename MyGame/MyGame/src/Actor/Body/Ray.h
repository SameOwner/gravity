#pragma once

#include "Base/Body.h"

// C
class Ray : public Body {
public:
	// RXgN^
	Ray(const Vector3& position, const Vector3& direction);
public:
	// ÕË»è
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// ÕË»è()
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override;
	// ÕË»è(JvZ)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override;
	// ÕË»è(üª)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override;
	// ÕË»è(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override;
	// ÕË»è(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override;
	// ÕË»è(C)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override;
	// ÕË»è(f)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override;

	// BodyÌ½sÚ®
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// BodyÌÏ·
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// BodyÌ½sÚ®
	Ray translate_e(const Vector3& pos) const;
	// BodyÌÏ·
	Ray transform_e(const Matrix& mat) const;

	// }``æ
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};