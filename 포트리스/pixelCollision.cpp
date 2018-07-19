#include "stdafx.h"
#include "pixelCollision.h"


HRESULT pixelCollision::init(void)
{
	//포트리스 백그라운드 이미지
	_fortress = IMAGEMANAGER->addImage("for", "fortressMap_1500x600.bmp", 1500, 600, true, RGB(255, 0, 255));

	//탱크 이미지
	_tank.img = IMAGEMANAGER->addImage("Tank", "Tank_60x65.bmp", 60, 65, true, RGB(255, 0, 255));

	//탱크 위치 초기화
	_tank.angle = PI / 5;																				//
	_tank.x = WINSIZEX / 2 - 450;																		//탱크 x좌표 초기화
	_tank.y = WINSIZEY / 2 - 50;																		//탱크 y좌표 초기화
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, _tank.img->getWidth(), _tank.img->getHeight());			//탱크 렉트
	_tank.radius = 50;																					//탱크 몸통 반지름
	_tank.cannon = 50;																					//포신 길이
	_tank.center.x = WINSIZEX / 2 - 450;																		//탱크 x좌표
	_tank.center.y = WINSIZEY / 2 - 50;																			//탱크 y좌표

	//y축으로 탐지(공의 하단에 사각형 만들기)
	_probeY = _tank.y + _tank.img->getHeight() / 2;


	//총알 초기화
	for (int i = 0; i < BULLET_MAX; i++)
	{
		_Tbullet[i].angle = PI / 180 * 90.f;		
		_Tbullet[i].speed = 15.0f;					
		_Tbullet[i].gravity = 0.0f;					
		_Tbullet[i].radius = 10.0f;
		//_Tbullet[i].rc = RectMakeCenter(_tankRect.right + 5, _tankRect.top / 2, _Tbullet[i].radius, _Tbullet[i].radius);
		_Tbullet[i].isfire = false;
	}

	return S_OK;
}

void pixelCollision::release(void)
{

}

void pixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_tank.x -= 3.0f;
		_tank.center.x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_tank.x += 3.0f;
		_tank.center.x += 3.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_tank.angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_tank.angle -= 0.04f;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//총알 발사
		this->fire();
	}
	//총알 무브
	this->move();

	//포신 끝점 x, y좌표를 각도에 따라 계속 업데이트 되게 한다.
	_tank.cannonEnd.x = cosf(_tank.angle) * _tank.cannon + _tank.x;
	_tank.cannonEnd.y = -sinf(_tank.angle) * _tank.cannon + _tank.y;

	//탱크 렉트 움직이기
	_tankRect = RectMakeCenter(_tank.x, _tank.y, _tank.img->getWidth(), _tank.img->getHeight());
	_probeY = _tank.y + _tank.img->getHeight() / 2;

	/*이부분이 픽셀충돌의 핵심*/
	//탐지할 y값의 범위를 위아래로 원하는 만큼 검사를 한다
	for (int i = _probeY - 50; i < _probeY + 300; i++)
	{
		COLORREF color = GetPixel(_fortress->getMemDC(), _tank.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_tank.y = i - _tank.img->getHeight() / 2;
			break;
		}
	}
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, _tank.img->getWidth(), _tank.img->getHeight());			//탱크 렉트
}

void pixelCollision::render(void)
{
	//백그라운드 렌더
	//_mountain->render(getMemDC());
	_fortress->render(getMemDC());

	//탱크 그리기
	EllipseMakeCenter(getMemDC(), _tank.center.x, _tank.center.y, _tank.radius * 2, _tank.radius * 2);
	//Rectangle(getMemDC(), _tank.rc);

	//탱크 포신 그리기
	LineMake(getMemDC(), _tank.rc.left + (_tank.rc.right - _tank.rc.left) / 2 , _tank.rc.top + (_tank.rc.bottom - _tank.rc.top) / 2 , _tank.cannonEnd.x, _tank.cannonEnd.y);
	//탱크 이미지 렌더
	_tank.img->render(getMemDC(), _tankRect.left, _tankRect.top);
	if (KEYMANAGER->isToggleKey('A'))
	{
		//작은 사각형 렌더
		RECT rc = RectMakeCenter(_tank.x, _probeY, 10, 10);
		Rectangle(getMemDC(), rc);
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_Tbullet[i].isfire) continue;
		EllipseMakeCenter(getMemDC(), _Tbullet[i].x, _Tbullet[i].y, _Tbullet[i].radius * 2, _Tbullet[i].radius * 2);
	}
}


void pixelCollision::fire()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_Tbullet[i].isfire) continue;

		_Tbullet[i].isfire = true;
		_Tbullet[i].angle = _tank.angle;
		_Tbullet[i].x = cosf(_tank.angle) * (_tank.cannon + 50) + (_tank.rc.left + (_tank.rc.right - _tank.rc.left) / 2);
		_Tbullet[i].y = -sinf(_tank.angle) * (_tank.cannon + 50) + (_tank.rc.top + (_tank.rc.bottom - _tank.rc.top) / 2);
		
		//_Tbullet[i].rc = RectMakeCenter(_tankRect.right + 5, _tankRect.top / 2, _Tbullet[i].radius, _Tbullet[i].radius);		
		break;
	}
}

void pixelCollision::move()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_Tbullet[i].isfire) continue;
		_Tbullet[i].gravity += 0.5f;
		_Tbullet[i].x += cosf(_Tbullet[i].angle) * _Tbullet[i].speed;
		_Tbullet[i].y += -sinf(_Tbullet[i].angle) * _Tbullet[i].speed + _Tbullet[i].gravity;
	}

}


//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
//{
//	brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
//	FillRect(_fortress->getMemDC(), &_mR,brush);
//	
//	SelectObject(_fortress->getMemDC(), GetStockObject(DC_BRUSH));
//	SetDCBrushColor(_fortress->getMemDC(), RGB(255, 0, 255));
//	SelectObject(_fortress->getMemDC(), GetStockObject(DC_PEN));
//	SetDCPenColor(_fortress->getMemDC(), RGB(255, 0, 255));
//	DeleteObject(brush);
//}
//if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
//{
//	HBRUSH MyBrush, OldBrush;
//	HPEN MyPen, OldPen;
//
//	MyBrush = CreateSolidBrush(RGB(255, 0, 255));
//	OldBrush = (HBRUSH)SelectObject(_fortress->getMemDC(), MyBrush);
//
//	//PS_SOILD 펜인데 선도있꼬 닷지로 그려주는것도 있다, 숫자 : 굵기 , 색
//	MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
//	OldPen = (HPEN)SelectObject(_fortress->getMemDC(), MyPen);
//
//	EllipseMakeCenter(_fortress->getMemDC(), _ptMouse.x, _ptMouse.y, 50, 50);
//
//	SelectObject(_fortress->getMemDC(), OldBrush);
//	SelectObject(_fortress->getMemDC(), OldPen);
//
//	DeleteObject(MyBrush);
//	DeleteObject(OldBrush);
//
//	DeleteObject(MyPen);
//	DeleteObject(OldPen);
//}
//EllipseMakeCenter(getMemDC(), _ptMouse.x, _ptMouse.y, 50, 50); 마우스
//_mR = RectMakeCenter(_ptMouse.x, _ptMouse.y, 35, 35);