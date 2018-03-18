#pragma once
#include"UI.h"

class IWorld;
class FieldMap:public UI {
public:
	FieldMap(IWorld* world,const Vector2& position);
	
	//‰Šú‰»
	virtual void initialize()override;
	//XV
	virtual void update(float deltaTime)override;
	//•`‰æ
	virtual void draw() const override;


private:
	IWorld* world_;
};