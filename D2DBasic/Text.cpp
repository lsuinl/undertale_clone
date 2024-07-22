#include "Text.h"

void Text::ReadFile(std::wstring fileName)
{
	std::wifstream file(fileName);
	file.imbue(std::locale("en_US.UTF-8"));

	std::wostringstream wss;
	wss << file.rdbuf(); // 파일의 전체 내용을 스트링스트림으로 읽기
	std::wstring content = wss.str();

	std::wistringstream wiss(content);
	std::wstring token;
	while (std::getline(wiss, token, L'&')) {
		textList.push_back(token);
	}
	name = fileName;
	length = textList.size();
}

void Text::PlayText()
{
	if (textList[index].size() > text.length()) {
		text += textList[index][text.length()];
	}
}

std::wstring Text::GetText() {
	return text;
}

void Text::NextText()
{
	if (text == textList[index] && length != index) {
		index++;
		text = L"";
	}
}

void Text::Update(float deltaTime)
{
	time += deltaTime;
	if (text == textList[index]) { //시간지나면 자동 이동
		if (time > 3.0f) {
			NextText();
			time = 0;
		}
	}
	else if (time > 0.1f) { //출력하기
		time = 0;
		PlayText();
	}
}
