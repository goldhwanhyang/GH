#pragma once
#include "gameNode.h"
#include "player.h"	//플레이어 클래스 사용하기 위해
#include "enemyManager.h"
#include "pixelCollision.h"

class mainGame : public gameNode
{
private:
	player * _player;	//플레이어 클래스 선언
	enemyManager* _enemyManager;

	pixelCollision* _pc;
<<<<<<< HEAD
	// 정말 돌이킬 수 없나?
	// dsfkjaklsdjflakjsdfl;akjsdf

=======
	// 정말 돌이킬 수 없나?d
	//asdfasefasef/sadfasdf/asef/eas/f/wewf/
	/*a/sdf
		sd//as
		df/
		*/
>>>>>>> 17f8dbc2b61ff011d8fff1e39bd1f7738ce458b5
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//충돌함수
	void collision();

	mainGame() {}
	~mainGame() {}
};

