#include "Text.h"
#include "SoundManager.h"

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
	SoundManager::GetInstance()->PlayMusic(eSoundList::typeing, eSoundChannel::typing);
	isEnd = false;
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
	if (index < textList.size()&&GetIsSentenceEnd() && length != index) {
		text = L"";
		index++;
		if (index == textList.size()) {
			isEnd = true;
			return;
		}
		SoundManager::GetInstance()->PlayMusic(eSoundList::typeing, eSoundChannel::typing);
	}
}

void Text::Update(float deltaTime)
{
	if (!isEnd) {
		time += deltaTime;
		if (GetIsSentenceEnd()) {
			SoundManager::GetInstance()->StopMusic(eSoundChannel::typing);
			if (time > 3.0f&&timeout) { //�ð������� �ڵ� �̵�
				NextText();
				time = 0;
			}
		}
		else if (time > 0.1f) { //����ϱ�
			time = 0;
			PlayText();
		}
	}
}
