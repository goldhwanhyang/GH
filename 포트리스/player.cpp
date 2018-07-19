#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	//로켓(플레이어) 이미지 초기화 및 위치 세팅
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));

	//미사일 클래스 생성 및 초기화
	_missile = new missile;
	_missile->init(5, 500);

	//미사일M1 클래스 생성 및 초기화
	_missileM1 = new missileM1;
	_missileM1->init(3, 600);

	return S_OK;
}

void player::release(void)
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
	//미사일M1 클래스 해제
	_missileM1->release();
	SAFE_DELETE(_missileM1);
}

void player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() + _rocket->getWidth() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);

	}

	//총알발사
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//총알클래스야 니꺼 발사시켜
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//폭탄발사
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//미사일M1 클래스야 니꺼 발사시켜
		_missileM1->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//미사일 클래스 업데이트
	_missile->update();
	//미사일M1 클래스 업데이트
	_missileM1->update();

	//충돌함수
	this->collision();
}

void player::render(void)
{
	//로켓이미지 렌더
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());

	//미사일 클래스 렌더
	_missile->render();
	//미사일M1 클래스 렌더
	_missileM1->render();
}

void player::removeMissileM1(int index)
{
	//미사일M1 니가 총알 삭제해!!!
	_missileM1->removeMissileM1(index);
}

//충돌함수(플레이어의 총알들 적매니져의 미니언)
void player::collision()
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_missileM1->removeMissileM1(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}
