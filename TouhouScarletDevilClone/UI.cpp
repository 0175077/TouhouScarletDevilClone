#include "UI.h"

#include "D2DImage.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "Timer.h"

UI::UI()
{
	pos = { 0.0f,0.0f };
	BackGround_Image = ImageManager::GetInstance()->AddImage("BackGround", TEXT("Image/InGameBackGround.bmp"));
	Stage = ImageManager::GetInstance()->AddImage("Stage", TEXT("Image/Stage.bmp"));
	MaxScoreImage = ImageManager::GetInstance()->AddImage("MaxScoreImage", TEXT("Image/MaxScore.bmp"));
	ScoreImage = ImageManager::GetInstance()->AddImage("Score", TEXT("Image/Score.bmp"));
	PlayerHpBarImage = ImageManager::GetInstance()->AddImage("PlayerHpBar", TEXT("Image/PlayerHpBar.bmp"));
	BombImage = ImageManager::GetInstance()->AddImage("BombBar", TEXT("Image/BombBar.bmp"));
	PowerImage = ImageManager::GetInstance()->AddImage("Power", TEXT("Image/Power.bmp"));
	PowerBarImage = ImageManager::GetInstance()->AddImage("PowerBar", TEXT("Image/PowerBar.bmp"));
	PowerMaxImage = ImageManager::GetInstance()->AddImage("PowerMax", TEXT("Image/PowerMax.bmp"));
	GrazeImage = ImageManager::GetInstance()->AddImage("Graze", TEXT("Image/Graze.bmp"));
	EnemyPhaseImage = ImageManager::GetInstance()->AddImage("EnemyPhase", TEXT("Image/EnemyPhase.bmp"));
	BossHpBarImage = ImageManager::GetInstance()->AddImage("BossHpBar", TEXT("Image/BossHpBar.bmp"));
	circle = ImageManager::GetInstance()->AddImage("circle", TEXT("Image/circle.bmp"));
	FPSImage = ImageManager::GetInstance()->AddImage("FPS", TEXT("Image/FPS.bmp"));

	// Ÿ�̸�
	timer = new Timer();
	timer->Init();



	ReLoadScore();

	// ���� �ʱ�ȭ
	MaxScore = 32343;
	Score = 0;

	// ü�� �ʱ�ȭ
	PlayerHp = 3;
	// ��ź �ʱ�ȭ
	BombCount = 3;

	// hp �� ������ �ʱ�ȭ
	currPowerbarFrame = 0;
	elapPowerbarFrame = 0;
	currBossHpBarFrame = 350;

	// ���߿� �����
	isEnemyPhase = true;
}

UI::~UI()
{
	// BackGround_Image = nullptr;
	// Stage = nullptr;
	// MaxScoreImage = nullptr;
	// ScoreImage = nullptr;
	// PlayerHpBarImage = nullptr;
	// PlayerHpImage = nullptr;
	// BombImage = nullptr;
	// PowerImage = nullptr;
	// PowerBarImage = nullptr;
	// PowerMaxImage = nullptr;
	// GrazeImage = nullptr;
	// EnemyPhaseImage = nullptr;
	// BossHpBarImage = nullptr;
	// circle = nullptr;
	// FPSImage = nullptr;

	// if (BackGround) {
	// 	BackGround->Release();
	// 	delete BackGround;
	// 	BackGround = nullptr;
	// }
	//
	// if (PowerBarBuffer)
	// {
	// 	PowerBarBuffer->Release();
	// 	delete PowerBarBuffer;
	// 	PowerBarBuffer = nullptr;
	// }
	//
	// if (BossHpBarBuffer)
	// {
	// 	BossHpBarBuffer->Release();
	// 	delete BossHpBarBuffer;
	// 	BossHpBarBuffer = nullptr;
	// }

	numberImageKeys.clear();

}

void UI::Update(float dt)
{
	timer->Tick();
	ReLoadStar();
	// �Ŀ��� ������ ������Ʈ
	if (InputManager::isMoveDown()) {
		currPowerbarFrame++;
		if (currPowerbarFrame >= 160)
			currPowerbarFrame = 159;
	}
	else if (InputManager::isMoveUp()) {
		currPowerbarFrame--;
		if (currPowerbarFrame < 0)
			currPowerbarFrame = 0;
	}

	if (InputManager::isMoveRight()) {
		currBossHpBarFrame++;
		if (currBossHpBarFrame >= 350)
			currBossHpBarFrame = 349;
	}
	else if (InputManager::isMoveLeft()) {
		currBossHpBarFrame--;
		if (currBossHpBarFrame < 0)
			isEnemyPhase = false;
	}

	if (isEnemyPhase) {
		elapsedTime += dt;
		if (elapsedTime >= 1.0f)
		{
			remainTime--;
			elapsedTime = 0.0f;

			if (remainTime <= 0) {
				remainTime = 0;
				isEnemyPhase = false;
			}
		}
	}

	// ���� ���� ����
	//if (true)
	//	isEnemyPhase = true;
}

void UI::Render(HDC hdc)
{
	
	//Stage->Render(hdc, StagePos.x, StagePos.y);
	
	//if (BackGround && isBgReder) {
	//	BackGround->Render(hdc);
	//}

	BackGround_Image->Render(-WINSIZE_X/2, -WINSIZE_Y/2);


	MaxScoreImage->Render(MaxScorePos.x, MaxScorePos.y);
	ScoreImage->Render(ScorePos.x, ScorePos.y);
	PlayerHpBarImage->Render( PlayerHpPos.x, PlayerHpPos.y);
	BombImage->Render(BombPos.x, BombPos.y);
	PowerImage->Render( PowerPos.x, PowerPos.y);
	GrazeImage->Render( GrazePos.x, GrazePos.y);


	// ����
	RenderScoreAsImage(hdc, MaxScore, { MaxScorePos.x + 120, MaxScorePos.y });
	RenderScoreAsImage(hdc, Score, { ScorePos.x + 70, ScorePos.y });

	// ü�� �� ��ź
	RenderHpAsImage(hdc, PlayerHp, { PlayerHpPos.x + 120, PlayerHpPos.y });
	RenderBombAsImage(hdc, BombCount, { BombPos.x + 120, BombPos.y });

	// �Ŀ���
	RenderPowerBarAsImage(hdc, currPowerbarFrame, PowerPos);
	UpdatePowerBarMax(hdc, PowerPos);

	// ���� ����� �׸���
	if (isEnemyPhase) {
		RenderEnemyPhase(hdc);
		RenderTimerAsImage(hdc, remainTime, EnemyPhasePos);
	}


	// �� �׸���
	circle->Render(circlePos.x, circlePos.y);

	RenderFPSAsImage(hdc, timer->GetFPS(), FPSPos);
}

// ���� �̹��� �ε�
void UI::ReLoadScore()
{
	// Map�� ���� ���� key��
	const char* numberNames[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	MaxScore = 1234;
	Score = 12;

	// ���� �̹��� �ε�
	for (int i = 0; i < 10; ++i)
	{
		string key = numberNames[i];
		numberImageKeys.push_back(key);

		wchar_t fileName[64];
		wsprintf(fileName, L"Image/Num%S.bmp", key.c_str());

		if (!ImageManager::GetInstance()->FindImageAdd(key))
			ImageManager::GetInstance()->AddImage(
				key,
				fileName
			);
		int a = 0;
	}
}

void UI::ReLoadStar()
{
	string key;
	const wchar_t* path = TEXT("Image/PlayerHpImage.bmp");

	PlayerHp = 3;
	BombCount = 3;

	// HP �׸���
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < PlayerHp) {
			key = "Star";
			path = TEXT("Image/PlayerHpImage.bmp");
		}
		else {
			key = "EmptyStar";
			path = TEXT("");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path
		);
	}

	// ��ź �׸���
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < BombCount) {
			key = "Bomb";
			path = TEXT("Image/BombCount.bmp");
		}
		else {
			key = "EmptyBomb";
			path = TEXT("");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path
		);
	}
}

// ���ڸ� �̹����� ���
void UI::RenderScoreAsImage(HDC hdc, int number, FPOINT startPos)
{
	// ���� ��, 8�ڸ� ����
	const int digitWidth = 20;
	const int totalDigits = 8;

	// total ���̸�ŭ 0���� ä��
	string scoreStr = to_string(number);
	while (scoreStr.length() < totalDigits)
		scoreStr = "0" + scoreStr;

	// �� �ڸ����� �̹����� ���
	for (int i = 0; i < totalDigits; ++i)
	{
		char digitChar = scoreStr[i];	// �� �ڸ����� ���ڷ� ��ȯ
		string key(1, digitChar);		// ���ڸ� Ű�� ��ȯ

		// �̹����� ������ ���
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render( static_cast<int>(startPos.x + i * digitWidth), static_cast<int>(startPos.y));
		}
	}
}

// ü���� �̹����� ���
void UI::RenderHpAsImage(HDC hdc, int number, FPOINT Pos)
{
	// ���� ��, 8�ڸ� ����
	const int StarWidth = 20;
	const int MaxStar = 8;

	for (int i = 0; i < MaxStar; i++) {

		string key = (i < number) ? "Star" : "EmptyStar";

		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}
}


// ��ź�� �̹����� ���
void UI::RenderBombAsImage(HDC hdc, int number, FPOINT Pos)
{
	// ���� ��, 8�ڸ� ����
	const int StarWidth = 20;

	for (int i = 0; i < MaxHpAndBomb; i++) {

		string key = (i < number) ? "Bomb" : "EmptyBomb";

		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}

}


// �Ŀ� ���� �� MAX ǥ��
void UI::UpdatePowerBarMax(HDC hdc, FPOINT pos)
{
	int number = currPowerbarFrame;

	const int digitWidth = 20;

	string numberStr = to_string(number);
	int len = numberStr.length();

	for (int i = 0; i < len; i++)
	{
		string key(1, numberStr[i]);

		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key)) {
			if (number < 159)
				img->Render(pos.x + 130 + i * digitWidth, pos.y);
		}
	}
	if (currPowerbarFrame == 159)
		PowerMaxImage->Render(pos.x + 130, pos.y);
}

// �Ŀ��� �̹����� ���
void UI::RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos)
{
	D2DImage* img = ImageManager::GetInstance()->FindImage("PowerBar");
	if (!img) return;

	int frameWidth = img->GetWidth();
	int frameHeight = img->GetHeight();

	// ������ ���� �ٲ���� ���� �ٽ� �׸�
	if (currPowerbarFrame != prevPowerbarFrame)
	{
		if (PowerBarBuffer)
		{
			PowerBarBuffer->Release();
			delete PowerBarBuffer;
		}
		if (currPowerbarFrame > 0)
		{
			// PowerBarBuffer = new Image();
			// PowerBarBuffer->Init(frameWidth * currPowerbarFrame, frameHeight);

			for (int i = 0; i < currPowerbarFrame; ++i)
			{
				int frameX = i % img->GetMaxFrameX();
				int frameY = i / img->GetMaxFrameX();

				img->Render(frameX, frameY);
				// img->FrameRenderRaw(PowerBarBuffer->GetMemDC(),
				// 	i * frameWidth, 0, frameX, frameY);
			}
		}
		else
		{
			PowerBarBuffer = nullptr;
		}
		prevPowerbarFrame = currPowerbarFrame;
	}
	// ���� ���
	if (PowerBarBuffer && currPowerbarFrame > 0)
	{
		PowerBarBuffer->Render(Pos.x + 120, Pos.y);
	}
}

// ���� ���� �ϸ� ���� ��ܿ� EnemyPhase �̹��� ���
void UI::RenderEnemyPhase(HDC hdc)
{
	if (D2DImage* img = ImageManager::GetInstance()->FindImage("EnemyPhase")) {
		img->Render(EnemyPhasePos.x, EnemyPhasePos.y);
	}
	RenderBossHpBar(hdc, currBossHpBarFrame, { EnemyPhasePos.x + 60, EnemyPhasePos.y + 5 });
}

// ���� ü�¹� �̹����� ���
void UI::RenderBossHpBar(HDC hdc, int number, FPOINT Pos)
{
	D2DImage* img = ImageManager::GetInstance()->FindImage("BossHpBar");
	if (!img) return;

	int frameWidth = img->GetWidth();
	int frameHeight = img->GetHeight();

	if (currBossHpBarFrame != prevBossHpBarFrame)
	{
		if (BossHpBarBuffer)
		{
			BossHpBarBuffer->Release();
			delete BossHpBarBuffer;
		}

		if (currBossHpBarFrame > 0)
		{
			// BossHpBarBuffer = new D2DImage();
			// BossHpBarBuffer->Init(frameWidth * currBossHpBarFrame, frameHeight);

			for (int i = 0; i < currBossHpBarFrame; ++i)
			{
				int frameX = i % img->GetMaxFrameX();
				int frameY = i / img->GetMaxFrameX();

				img->Render(frameX, frameY);
				// img->FrameRenderRaw(BossHpBarBuffer->GetMemDC(),
				// 	i * frameWidth, 0, frameX, frameY);
			}
		}
		else
		{
			BossHpBarBuffer = nullptr;
		}

		prevBossHpBarFrame = currBossHpBarFrame;
	}

	// ���� ���
	if (BossHpBarBuffer && currBossHpBarFrame > 0)
	{
		BossHpBarBuffer->Render(Pos.x, Pos.y);
	}
}

void UI::RenderTimerAsImage(HDC hdc, int number, FPOINT Pos)
{
	const int digitWidth = 20;
	string timeStr = to_string(number);

	while (timeStr.length() < 2)
		timeStr = "0" + timeStr;

	for (int i = 0; i < timeStr.length(); i++)
	{
		string key(1, timeStr[i]);
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * digitWidth) + 425, static_cast<int>(Pos.y) - 5);
		}
	}
}

void UI::RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos)
{
	const int digitWidth = 20;
	string fpsStr = to_string(fps);

	FPSImage->Render(static_cast<int>(Pos.x + 80), static_cast<int>(Pos.y));
	for (int i = 0; i < fpsStr.length(); ++i)
	{
		string key(1, fpsStr[i]);
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * digitWidth), static_cast<int>(Pos.y));
		}
	}
}



