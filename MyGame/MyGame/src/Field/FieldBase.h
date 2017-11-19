#pragma once
#include"../Math/Collision/CollisionMesh.h"

// フィールドクラス
class FieldBase {
public:
	// コンストラクタ
	FieldBase(int field=-1, int skybox=-1);
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// フィールドのハンドル取得
	int modelHandle();
	CollisionMesh& getMesh();
	// コピー禁止
	FieldBase(const FieldBase& other) = delete;
	FieldBase& operator = (const FieldBase& other) = delete;
private:
	int field_;
	int skyBox_;
	CollisionMesh mesh_;
};
