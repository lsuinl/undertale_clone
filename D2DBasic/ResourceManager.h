#pragma once
#include "TimeSystem.h"
#include "D2DBasic.h"
//�̹��� ���ҽ��� �����մϴ�.

class AnimationAsset;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	D2DEngine* D2D;
	static ResourceManager* pInstance; //���ҽ� ������ ���� �Ŵ���

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap; //���� �̹������� ��� ����.
	std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;  //�ִϸ��̼� ������ ��� ����

	bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap); //�̹����� ������
	void ReleaseD2DBitmap(std::wstring strFilePath);//�̹��� �޸� ����

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset); //�ִϸ��̼� �������� ��ȯ
	void ReleaseAnimationAsset(std::wstring strFilePath); //�ִϸ��̼� ������ �޸� ����
};

