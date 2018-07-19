#pragma once
#include "gameNode.h"
#include "bullet.h"  //미사일클래스 사용하기 위해

//#include "enemyManager.h"
//적매니져 상호참조하기 위해 클래스 전방선언
class enemyManager;

class player : public gameNode
{
private:
	image * _rocket;		//로켓(플레이어) 이미지
	missile* _missile;		//미사일 클래스
	missileM1* _missileM1;  //미사일M1 클래스
	
	enemyManager* _em;		//동적할당 하면 안된다!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//미사일M1 총알삭제
	void removeMissileM1(int index);

	//충돌함수
	void collision();

	//미사일M1 클래스 가져오기
	missileM1* getMissile() { return _missileM1; }

	//로켓이미지 가져오기
	image* getPlayerImage() { return _rocket; }

	//상호참조시 적매니져포인터를 넘길 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

