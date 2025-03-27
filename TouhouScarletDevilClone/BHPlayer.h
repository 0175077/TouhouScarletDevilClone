#pragma once
#include "BHObject.h"
class BHPlayer : public BHObject
{
public:
	// ������
	BHPlayer() = default;
	
	virtual void Move(FPOINT moveDirection, bool isPressingShift);

	void MoveBackToBorder();

	void OnCollide(BHObject* objectCollided);

	// BHObject��(��) ���� ��ӵ�
	void Update() override;
};

