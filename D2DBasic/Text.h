#pragma once
#include "pch.h"
class Text
{
public:
	int index = 0;//�ε���
	std::wstring text; //���� ������ �ؽ�Ʈ.
	float time;
	std::wstring name;
	int length; //�ؽ�Ʈ���� ����
	std::vector<int> textTime; //�ش� �ؽ�Ʈ������ ����� �ð�
	std::vector<std::wstring> textList; //�ؽ�Ʈ���� ����

	void ReadFile(std::wstring fileName);
	void PlayText();

	void NextText();
	std::wstring GetText();

	void Update(float deltaTime);
};



