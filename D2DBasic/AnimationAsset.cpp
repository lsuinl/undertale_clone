#include "pch.h"
#include "AnimationAsset.h"

bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//텍스트 파일을 열어서 csv파일 목록을 읽어온다.
	// 아래 함수로 csv파일을 처리한다.
	if (FilePath == std::wstring(L"../Resource/background.csv"))
		LoadAnimationFromCSV(0, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/run.csv"))
		LoadAnimationFromCSV(1, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/idle.csv"))//하트가만히
		LoadAnimationFromCSV(2, FilePath.c_str());
	else if(FilePath == std::wstring(L"../Resource/csv/attack.csv"))//하트 공격받기
		LoadAnimationFromCSV(3, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/death.csv"))//하트 죽음.
		LoadAnimationFromCSV(4, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/kenmove.csv")) //적1 공격
		LoadAnimationFromCSV(5, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/introduction.csv")) //스토리 배경
		LoadAnimationFromCSV(6, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/mapback.csv")) //메인 맵 매경
		LoadAnimationFromCSV(7, FilePath.c_str());
	//캐릭터이동
	else if (FilePath == std::wstring(L"../Resource/csv/herorun.csv")) //캐릭터 이동 (앞)
		LoadAnimationFromCSV(8, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/herorunside.csv")) //캐릭터 이동 (옆)
		LoadAnimationFromCSV(9, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/herorunback.csv")) //캐릭터 이동 (뒤)
		LoadAnimationFromCSV(10, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidle.csv")) //캐릭터 가만히 (앞)
		LoadAnimationFromCSV(11, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidleside.csv")) //캐릭터 가만히(옆)
		LoadAnimationFromCSV(12, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidleback.csv")) //캐릭터 가만히 (뒤)
		LoadAnimationFromCSV(13, FilePath.c_str());
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	int FrameCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_Animations[index].Frames.resize(FrameCount); //추가.
	m_Animations[index].Frames.reserve(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			m_Animations[index].Frames[j].Source.left = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.top = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.right = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.bottom = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Duration = (float)_wtof(token.c_str());
		}
	}		
	return true;
}
