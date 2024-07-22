#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"


ResourceManager::ResourceManager()
{
	ResourceManager::pInstance = this;
}

ResourceManager::~ResourceManager()
{
	assert(m_BitmapMap.empty());
	assert(m_AnimationAssetMap.empty());
}

ResourceManager* ResourceManager::pInstance = nullptr;

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end())
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}
	D2D->CreateD2DBitmapFromFile(strFilePath.c_str(), bitmap);
	m_BitmapMap[strFilePath] = *bitmap;	// ������ ��Ʈ���� �ʿ� �����Ѵ�.
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� ��Ʈ���� �����Ѵ�.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset)
{
	if (m_AnimationAssetMap.find(strFilePath) != m_AnimationAssetMap.end())
	{
		*asset = m_AnimationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	}
	// ������ ���� ��������. AnimationAsset �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.

	AnimationAsset* pTemp = new AnimationAsset;
	// ������ �ִϸ��̼� ���¿� �ִϸ��̼� �����͸� �ε��Ѵ�.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;
		return false;
	}
	else
	{
		*asset = pTemp;
		(*asset)->AddRef();
	}
	// ������ �ִϸ��̼� ������ �ʿ� �����Ѵ�.
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	for (auto& e : m_AnimationAssetMap) {
		delete e.second;
	}
	m_AnimationAssetMap.clear();
}
