#pragma once

// 위치 정보
struct POSITION
{
	float x = 0;
	float y = 0;
};

// 발사대 모델 구조체
struct LCS_MODEL {

	// 발사대 모델 위치 정보
	POSITION launcherPosition;

	// 탄 갯수
	int MAX_HOT_INVENTORY = 4;
};