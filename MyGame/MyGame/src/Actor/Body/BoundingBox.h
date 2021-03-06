#pragma once

#include "Base/Body.h"

// AABB
class BoundingBox : public Body {
public:
	//AABBÌ»èðì¬
	BoundingBox(const Vector3& min, const Vector3& max);
public:
	// ÕË»è
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// ÕË»è()
	virtual bool intersects(const BoundingSphere& sphere, HitInfo& hitinfo) const override;
	// ÕË»è(JvZ)
	virtual bool intersects(const BoundingCapsule& capsule, HitInfo& hitinfo) const override;
	// ÕË»è(üª)
	virtual bool intersects(const BoundingSegment& segment, HitInfo& hitinfo) const override;
	// ÕË»è(AABB)
	virtual bool intersects(const BoundingBox& aabb, HitInfo& hitinfo) const override;
	// ÕË»è(OBB)
	virtual bool intersects(const OrientedBoundingBox& obb, HitInfo& hitinfo) const override;
	// ÕË»è(C)
	virtual bool intersects(const Ray& ray, HitInfo& hitinfo) const override;
	// ÕË»è(f)
	virtual bool intersects(const CollisionModel& model, HitInfo& hitinfo) const override;
	
	// ïÜ»è(_)
	virtual bool contains(const Vector3& point) const override;
	// ïÜ»è()
	virtual bool contains(const BoundingSphere& sphere) const override;
	// ïÜ»è(üª)
	virtual bool contains(const BoundingSegment& segment) const override;
	// ïÜ»è(AABB)
	virtual bool contains(const BoundingBox& aabb) const override;
	// ïÜ»è(OBB)
	virtual bool contains(const OrientedBoundingBox& obb) const override;

	// BodyÌ½sÚ®
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// BodyÌÏ·
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// BodyÌ½sÚ®
	BoundingBox translate_e(const Vector3& pos) const;
	// BodyÌÏ·
	BoundingBox transform_e(const Matrix& mat) const;

	// üÌÕË»è
	bool intersects(const Vector3& position, const Vector3& direction, float& start, float& end) const;
	// ßÚ_
	Vector3 ClosestPoint(const Vector3& target)const;
	// ¸_
	Vector3 CornerPoint(int cornerIndex)const;
	// é`ÌTCY
	Vector3 Size()const;
	// SÀW
	Vector3 Center()const;

	// }``æ
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};
