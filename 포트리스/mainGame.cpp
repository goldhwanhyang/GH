#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);

	//UFO 프레임 이미지 초기화
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);

	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//플레이어 클래스 생성 및 초기화
	_player = new player;
	_player->init();

	//에너미매니져 클래스 생성 및 초기확
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//플레이어와 적매니져 상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	//픽셀충돌 클래스 생성 및 초기화
	_pc = new pixelCollision;
	_pc->init();

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	//플레이어 해제
	_player->release();
	SAFE_DELETE(_player);

	//에너미매니져 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	//픽셀충돌 해제
	_pc->release();
	SAFE_DELETE(_pc);
	
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다

	//플레이어 클래스 업데이트
	//_player->update();

	//적매니져 클래스 업데이트
	//_enemyManager->update();
	//충돌함수
	//this->collision();

	//픽셀충돌 업데이트
	_pc->update();

	

}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//백그라운드 이미지 렌더
	//IMAGEMANAGER->render("백그라운드", getMemDC());

	//플레이어 클래스 렌더
	//_player->render();

	//에너미매니져 클래스 렌더
	//_enemyManager->render();

	//픽셀충돌 렌더
	_pc->render();


//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}

void mainGame::collision()
{
	/*
	//충돌처리
	//플레이어의 총알 & 적 => 충돌처리
	//플레이어에서 총알클래스 가져온다
	//총알클래스에서 벡터 가져온다
	//플레이어->미사일클래스->총알벡터[]
	for (int i = 0; i < _player->getMissile()->getVBullet().size(); i++)
	{
		//RECT rc;//임시용렉트
		//RECT rcEnemy;
		//RECT rcBullet = _player->getMissile()->getVBullet()[i].rc;
		//if (IntersectRect(&rc, &rcBullet, &rcEnemy))
		//{
		//
		//}
	}

	//에너미클래스에 총알클래스가 있을때
	에너미매니져->에너미클래스->총알클래스->총알벡터
	
	//에너미매니져에서 총알클래스 들고 있을때
	에너미매니져->총알클래스->총알벡터

	*/

	//플레이어 총알 vs 미니언 충돌처리
	for (int i = 0; i < _player->getMissile()->getVBullet().size(); i++)//플레이어가 쏜 총알
	{
		for (int j = 0; j < _enemyManager->getVMinion().size(); j++)//에너미클래스
		{
			//충돌했냐?
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissile()->getVBullet()[i].rc,
				&_enemyManager->getVMinion()[j]->getRect()))
			{
				//플레이어 총알 삭제
				_player->removeMissileM1(i);
				//미니언 삭제
				_enemyManager->removeMinion(j);
				break;
			}
		}
	}

}
