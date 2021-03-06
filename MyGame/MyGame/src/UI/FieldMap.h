#pragma once
#include"UI.h"

class IWorld;
class FieldMap:public UI {
public:
	FieldMap(IWorld* world,const Vector2& position);
	
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw() const override;


private:
	IWorld* world_;
};