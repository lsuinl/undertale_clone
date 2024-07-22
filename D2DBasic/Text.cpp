#include "Text.h"

void Text::ReadFile(std::wstring fileName)
{
	std::wifstream file(fileName);
	file.imbue(std::locale("en_US.UTF-8"));

	std::wostringstream wss;
	wss << file.rdbuf(); // ������ ��ü ������ ��Ʈ����Ʈ������ �б�
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
	if (text == textList[index]) { //�ð������� �ڵ� �̵�
		if (time > 3.0f) {
			NextText();
			time = 0;
		}
	}
	else if (time > 0.1f) { //����ϱ�
		time = 0;
		PlayText();
	}
}
