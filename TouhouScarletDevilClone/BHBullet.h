#pragma once
#include "BHObject.h"

class BHBullet : public BHObject
{
protected:

	// angluar accel
	float AngleRate;
	// accel
	float SpeedRate;
	float movementSpeed;
public:
	void Init(int shape_id, FPOINT position,
		float angle, float angle_rate,
		float movementSpeed, float speedRate);
	// BHObject��(��) ���� ��ӵ�
	void Update() override;
	void Render();
};

