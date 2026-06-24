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

	// 탄 정보 (true : 발사가능 / false : 발사완료)
	std::array<bool, 4> inventory = { true, true, true, true };

	// 모의 중지에 사용되는 모델 초기화 함수
	void modelReset() {

		// 위치는 유지, 탄 상태만 초기화
		this->inventory = { true, true, true, true };
	}

	// 발사 (해당 missleID의 상태값 변경)
	void fire(int missleID) {
		this->inventory[missleID] = false;
	}
};