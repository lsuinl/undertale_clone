#pragma once
#include "pch.h"
class Text
{
public:
	int index = 0;//인덱스
	std::wstring text; //실제 보여줄 텍스트.
	bool isEnd = false, timeout = true;
	float time;
	std::wstring name;
	int length; //텍스트들의 개수
	std::vector<int> textTime; //해당 텍스트단위가 재생될 시간
	std::vector<std::wstring> textList; //텍스트들의 집합

	void ReadFile(std::wstring fileName);
	void PlayText();

	bool GetIsSentenceEnd() { return  text == textList[index]; }
	bool GetIsEnd() { return isEnd; }
	void SetTimeout(bool a) { timeout =a; }
	void NextText();
	std::wstring GetText();

	void Update(float deltaTime);
};



