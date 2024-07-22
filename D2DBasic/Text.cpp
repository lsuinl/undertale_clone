#include "Text.h"
#include "SoundManager.h"

void Text::ReadFile(std::wstring fileName)
{
	SoundManager::GetInstance()->LoadMusic(eSoundList::typeing, true, "../Resource/music/effect/typeing.mp3");
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
	SoundManager::GetInstance()->PlayMusic(eSoundList::typeing, eSoundChannel::Effect);
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
		SoundManager::GetInstance()->StopMusic(eSoundChannel::Effect);
		if (time > 3.0f) {
			SoundManager::GetInstance()->PlayMusic(eSoundList::typeing, eSoundChannel::Effect);
			NextText();
			time = 0;
		}
	}
	else if (time > 0.1f) { //����ϱ�
		time = 0;
		PlayText();
	}
}
