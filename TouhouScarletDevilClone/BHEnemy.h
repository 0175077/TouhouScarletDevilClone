#pragma once
#include "BHObject.h"
class BHObjectController;

// class IPatternInfo;
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    Image* moveImage;
    FPOINT moveDir;

    BHObjectController* controller;
    
    // IPatternInfo* patterns;
    // IPatternInfo* currentPattern;
public:
    // ������
    BHEnemy() = default;
    virtual ~BHEnemy () = default;

    inline void SetMoveImage(Image* moveImage) { this->moveImage = moveImage; }
    
    void Init(Image* image, float hit, FPOINT position, float radianAngle) override;

    virtual void Move(float angle, float speed);
    
    void Render(HDC hdc) override;

    void Update() override;

    void Shoot();

    void OnHit(ICircleCollideable* hitObject) override;

    void Release() override;

    void GetDamaged();
    
    inline float GetHit() override { return hit; }
    // inline FPOINT GetPos() override { return position; }
};

