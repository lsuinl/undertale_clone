#pragma once
#include "TimeSystem.h"
#include "D2DBasic.h"
//이미지 리소스를 관리합니다.

class AnimationAsset;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	D2DEngine* D2D;
	static ResourceManager* pInstance; //리소스 관리를 위한 매니저

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap; //단일 이미지들을 담는 공간.
	std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;  //애니메이션 에셋을 담는 공간

	bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap); //이미지를 가져옴
	void ReleaseD2DBitmap(std::wstring strFilePath);//이미지 메모리 해제

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset); //애니메이션 에셋으로 전환
	void ReleaseAnimationAsset(std::wstring strFilePath); //애니메이션 에셋의 메모리 해제
};

