#pragma once
#include "gameNode.h"
#include "player.h"	//�÷��̾� Ŭ���� ����ϱ� ����
#include "enemyManager.h"
#include "pixelCollision.h"

class mainGame : public gameNode
{
private:
	player * _player;	//�÷��̾� Ŭ���� ����
	enemyManager* _enemyManager;

	pixelCollision* _pc;
<<<<<<< HEAD
	// ���� ����ų �� ����?
	// dsfkjaklsdjflakjsdfl;akjsdf

=======
	// ���� ����ų �� ����?d
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

	//�浹�Լ�
	void collision();

	mainGame() {}
	~mainGame() {}
};

