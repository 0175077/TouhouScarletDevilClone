#pragma once
#include "BHObject.h"
#include "config.h"
// #include "IPoolable.h"
#include "ObjectPool.h"

class D2DImage;
class BHBullet : public BHObject
{
protected:
	float imageAngle = 0;
	// angluar accel
	float angleRate;
	// accel
	float speedRate;
	float movementSpeed;
	ObjectPool<BHBullet>* pool;
public:
	void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;

	void Launch(float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet);
	
	void Release() override;
	
	// BHObject을(를) 통해 상속됨
	void Update(float dt) override;
	void Render(HDC hdc) override;

	void OnHit(ICollideable* hitObject) override;

	inline void SetPool(ObjectPool<BHBullet>* pool) {this->pool = pool;}

	void Move(float angle, float speed, float dt) override;

	void Reset();
	// void Shoot(float angle, int shootAmount = 1) override {};
	void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override {};

	bool IsOutofScreen();
};

