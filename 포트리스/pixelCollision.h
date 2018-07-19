#pragma once
#include "gameNode.h"

#define PI 3.14
#define BULLET_MAX 50

//��ũ ����ü
struct tagTank
{
	image* img;			//��ũ �̹���
	RECT rc;			//��ũ ��Ʈ

	POINT center;		//��ũ�� ����
	POINT cannonEnd;	//������ ����
	int radius;			//��ũ ������ ������
	int cannon;			//���� ����
	float angle;		//���� ����
	float x, y;			//��ũ ��ǥ
};

//�Ѿ� ����ü
struct tagTankBullet
{
	RECT rc;							//�Ѿ��Ƿ�Ʈ
	float x, y;							//�Ѿ� ���� ��ǥ
	float radius;						//�Ѿ� ������
	float speed, angle, gravity;		//�������� �׸��� ���Ѱ�
	bool isfire;						//�Ѿ� ���� �Ƚ���
};

class pixelCollision : public gameNode
{
private:
	image* _mountain;		//��׶��� �̹���
	image* _ball;			//�� �̹���
	RECT _rc;				//�� ��Ʈ


	image* _fortress;		//��׶��� �̹���
	RECT _tankRect;			//��ũ ��Ʈ
	int _probeY;			//�ȼ��浹 Ž���� y��

	//���콺 ��Ʈ
	RECT _mR;
	RECT _mR2;
	HBRUSH brush;
	
	//��ũ , ��ũ�Ѿ�
	tagTank _tank;
	tagTankBullet _Tbullet[BULLET_MAX];
		 
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻� �Լ�
	void fire();
	//�Ѿ˹��� �Լ�
	void move();

	pixelCollision() {}
	~pixelCollision() {}
};

