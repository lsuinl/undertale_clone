#include "snowMap.h"
#include "ResourceManager.h"
#include "SoundManager.h"
snowMap::snowMap()
{
	AnimationScene* Background = CreateGameObject<GameObject>()->CreateComponent<AnimationScene>();	//배경
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/background/back.png", &Background->m_pBitmap);
 	Background->LoadAnimationAsset(L"../Resource/background/back.png", L"../Resource/csv/mapback.csv"); 
	Background->m_RelativeLocation = { 0,600 };
	Background->m_size = { 10000,10000 }; Background->m_RelativeScale = { 3.25f,3.25f }; Background->SetAnimation(7, false);

	SoundManager::GetInstance()->PlayMusic(eSoundList::snowMap, eSoundChannel::BGM);
	CreateNPC(L"../Resource/text/save.txt", L"../Resource/csv/save.csv", L"../Resource/ui/box.png",{ 3.5,3.5 }, { 10,10 }, { 30,30 }, { 2505,3000 }, 23, "../Resource/music/effect/beep.mp3");//저장
	CreateNPC(L"../Resource/text/box.txt", L"../Resource/csv/box.csv", L"../Resource/ui/box.png",{ 3.5,3.5 }, { 10,10 }, { 50,50 }, { 2670,2990 }, 22, "../Resource/music/effect/beep.mp3");//상자
	CreateNPC(L"../Resource/text/rabit1.txt", L"../Resource/csv/rabit2.csv", L"../Resource/charcacter/extra.png",{ 3.5,3.5 }, { 10,40 }, { 80,30 }, { 3730,3110 }, 16, "../Resource/music/effect/toriel.mp3");//산책토끼
	CreateNPC(L"../Resource/text/bluebear.txt", L"../Resource/csv/bluebear.csv", L"../Resource/charcacter/extra.png",{ 3.5,3.5 }, { 0,30 }, { 80,50 }, { 3970,3034 }, 17);//파란곰
	CreateNPC(L"../Resource/text/rabit2.txt", L"../Resource/csv/rabit1.csv", L"../Resource/charcacter/extra.png",{ 3.5,3.5 }, { 00,40 }, { 80,30 }, { 3546,2868 }, 15, "../Resource/music/effect/flower.mp3");//토끼1
	CreateNPC(L"../Resource/text/brownbear.txt", L"../Resource/csv/brownbear.csv", L"../Resource/charcacter/extra.png",{ 3.5,3.5 }, { 00,40 }, { 100,70 }, { 4655,2925 }, 18, "../Resource/music/effect/argore.mp3");//갈색곰
	CreateNPC(L"../Resource/text/mouse.txt", L"../Resource/csv/mouse.csv", L"../Resource/charcacter/extra.png",{ 3.7,3.7 }, { 15,30 }, { 60,30 }, { 5524,2915 }, 19, "../Resource/music/effect/flower.mp3");//생쥐
	CreateNPC(L"../Resource/text/orange.txt", L"../Resource/csv/orange.csv", L"../Resource/charcacter/extra.png",{ 3.5,3.5 }, { 0,45 }, { 60,30 }, { 5695,2924 }, 20);//주황몬스터
	CreateNPC(L"../Resource/text/ghost.txt", L"../Resource/csv/ghost.csv", L"../Resource/charcacter/ghost.png",{ 4,4 }, { 10,0 }, { 120,60 }, { 6020,2800 }, 25, "../Resource/music/effect/beep.mp3");//ghost
	CreateNPC(L"../Resource/text/temmie.txt", L"../Resource/csv/temmie.csv", L"../Resource/charcacter/temmie.png",{ 3.5,3.5 }, { 10,10 }, { 70,70 }, { 5400,2914 }, 26, "../Resource/music/effect/temmie.mp3");//temmie
	CreateNPC(L"../Resource/text/sense.txt", L"../Resource/csv/sense.csv", L"../Resource/charcacter/sense.png",{ 3.5,3.5 }, { 0,20 }, { 60,30 }, { 8800,2970 }, 27, "../Resource/music/effect/sense.mp3");//sense
	CreateNPC(L"../Resource/text/dog.txt", L"../Resource/csv/dog.csv", L"../Resource/charcacter/dog.png",{ 3,3 }, { 10,10 }, { 70,70 }, { 600,2900 }, 24, "../Resource/music/effect/argore.mp3");//강아쥐
	
	Player = CreateGameObject<Hero>();	//캐릭터
	AnimationScene* ani = dynamic_cast<AnimationScene*>(Player->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/player.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorun.csv");
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorunside.csv");
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorunback.csv");
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidle.csv");
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidleside.csv");
	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidleback.csv");
	ani->m_RelativeScale = { 3,3 };
	ani->m_center = { ani->m_center.x,ani->m_center.y + 30 };
	ani->m_size = { 60,30 };
	//ani->m_RelativeLocation = { 500,3050 };
	ani->m_RelativeLocation = { 4600,3050 };
	ani->SetAnimation(10, false);

	Kid* kid = CreateGameObject<Kid>();	//KID
	kid->SetTextFile(L"../Resource/text/kid.txt");
	kid->SetTypeSound("../Resource/music/effect/flowerDevil.mp3");
	ani = dynamic_cast<AnimationScene*>(m_GameObjects.back()->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/inkid.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/charcacter/inkid.png", L"../Resource/csv/kid.csv");
	ani->m_RelativeScale = { 3.7,3.7 };
	ani->m_center = { ani->m_center.x+5,ani->m_center.y + 20 };
	ani->m_size = { 60,30 }; ani->m_RelativeLocation = { 4350,3050 }; ani->SetAnimation(21, false);


	//벽만들기
	CreateWalls(walls, ani, 0, 2770, 100, 700);//왼쪽
	CreateWalls(walls, ani, 9500, 2770, 100, 700);  //오른쪽
	CreateWalls(walls, ani, 0, 3170, 10000, 200); //아래
	CreateWalls(walls, ani, 0, 2650, 10000, 200); //위

	CreateWalls(walls, ani, 750, 2760, 550, 200); //위
	CreateWalls(walls, ani, 750, 3100, 550, 200); //아래
	CreateWalls(walls, ani, 1440, 2860, 580, 110); //위; //팻말
	CreateWalls(walls, ani, 2100, 2860, 1280, 110); //집 
	CreateWalls(walls, ani, 4100, 2950, 230, 140); //트리
	CreateWalls(walls, ani, 4580, 2820, 680, 110); //집 2
	CreateWalls(walls, ani, 6200, 2800, 4000, 110); //2번째 위..
	CreateWalls(walls, ani, 6900, 2870, 700, 110); //NPC
	CreateWalls(walls, ani, 7600, 2930, 110, 90); //우체통
	CreateWalls(walls, ani, 7800, 2900, 700, 110); //집 3
	CreateWalls(walls, ani, 8500, 2870, 1500, 110); //집 4
}

void snowMap::CreateNPC(std::wstring text, std::wstring csv, std::wstring png, D2D_VECTOR_2F scale, D2D_VECTOR_2F center, D2D1_POINT_2F size, D2D_VECTOR_2F xy,int index, const char* file)
{
	NPC* npc = CreateGameObject<NPC>();
	npc->SetTextFile(text);
	ani = dynamic_cast<AnimationScene*>(npc->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(png, &ani->m_pBitmap);
	ani->LoadAnimationAsset(png, csv);
	ani->m_RelativeScale = scale;
	ani->m_center = { ani->m_center.x+center.x,ani->m_center.y  +center.y};
	ani->m_size = size; ani->m_RelativeLocation = xy; ani->SetAnimation(index, false);
	if (file != nullptr) npc->SetTypeSound(file);
}


snowMap::~snowMap()
{
}

void snowMap::Update(float deltaTime)
{
	__super::Update(deltaTime);
	SetCullingBound(&Player->Camera->m_ViewBoundBox);
}

void snowMap::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

