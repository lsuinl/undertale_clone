#pragma once
#include "../D2DBasic/D2DBasic.h"
#include "../D2DBasic/ScreenManager.h"
#include "../D2DBasic/Battle.h"
#include "../D2DBasic/Ending.h"
#include "../D2DBasic/GameOver.h"
#include "../D2DBasic/snowMap.h"
#include "../D2DBasic/Story.h"
#include "../D2DBasic/Title.h"

class XYSystem : public D2DBasic
{
private:

public:
	XYSystem();
	~XYSystem();
	virtual void Initialize(HINSTANCE hInstance) override;
	virtual void Update(float time) override;
	virtual void Render() override;
	virtual void Finalize() override;
};