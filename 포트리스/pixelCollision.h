#pragma once
#include "gameNode.h"

#define PI 3.14
#define BULLET_MAX 50

//탱크 구조체
struct tagTank
{
	image* img;			//탱크 이미지
	RECT rc;			//탱크 렉트

	POINT center;		//탱크의 중점
	POINT cannonEnd;	//포신의 끝점
	int radius;			//탱크 몸통의 반지름
	int cannon;			//포신 길이
	float angle;		//포신 각도
	float x, y;			//탱크 좌표
};

//총알 구조체
struct tagTankBullet
{
	RECT rc;							//총알의렉트
	float x, y;							//총알 중점 좌표
	float radius;						//총알 반지름
	float speed, angle, gravity;		//포물선을 그리기 위한것
	bool isfire;						//총알 쐈나 안쐈나
};

class pixelCollision : public gameNode
{
private:
	image* _mountain;		//백그라운드 이미지
	image* _ball;			//공 이미지
	RECT _rc;				//공 렉트


	image* _fortress;		//백그라운드 이미지
	RECT _tankRect;			//탱크 렉트
	int _probeY;			//픽셀충돌 탐지할 y값

	//마우스 렉트
	RECT _mR;
	RECT _mR2;
	HBRUSH brush;
	
	//탱크 , 탱크총알
	tagTank _tank;
	tagTankBullet _Tbullet[BULLET_MAX];
		 
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//총알발사 함수
	void fire();
	//총알무브 함수
	void move();

	pixelCollision() {}
	~pixelCollision() {}
};

