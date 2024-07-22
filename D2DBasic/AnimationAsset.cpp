#include "pch.h"
#include "AnimationAsset.h"

bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//�ؽ�Ʈ ������ ��� csv���� ����� �о�´�.
	// �Ʒ� �Լ��� csv������ ó���Ѵ�.
	if (FilePath == std::wstring(L"../Resource/background.csv"))
		LoadAnimationFromCSV(0, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/run.csv"))
		LoadAnimationFromCSV(1, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/idle.csv"))//��Ʈ������
		LoadAnimationFromCSV(2, FilePath.c_str());
	else if(FilePath == std::wstring(L"../Resource/csv/attack.csv"))//��Ʈ ���ݹޱ�
		LoadAnimationFromCSV(3, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/death.csv"))//��Ʈ ����.
		LoadAnimationFromCSV(4, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/kenmove.csv")) //��1 ����
		LoadAnimationFromCSV(5, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/introduction.csv")) //���丮 ���
		LoadAnimationFromCSV(6, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/mapback.csv")) //���� �� �Ű�
		LoadAnimationFromCSV(7, FilePath.c_str());
	//ĳ�����̵�
	else if (FilePath == std::wstring(L"../Resource/csv/herorun.csv")) //ĳ���� �̵� (��)
		LoadAnimationFromCSV(8, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/herorunside.csv")) //ĳ���� �̵� (��)
		LoadAnimationFromCSV(9, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/herorunback.csv")) //ĳ���� �̵� (��)
		LoadAnimationFromCSV(10, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidle.csv")) //ĳ���� ������ (��)
		LoadAnimationFromCSV(11, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidleside.csv")) //ĳ���� ������(��)
		LoadAnimationFromCSV(12, FilePath.c_str());
	else if (FilePath == std::wstring(L"../Resource/csv/heroidleback.csv")) //ĳ���� ������ (��)
		LoadAnimationFromCSV(13, FilePath.c_str());
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	int FrameCount = 0;			// �������� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_Animations[index].Frames.resize(FrameCount); //�߰�.
	m_Animations[index].Frames.reserve(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
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
