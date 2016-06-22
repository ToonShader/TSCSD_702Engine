#include "Chess.h"

//***********************************
//		Chess definitions
//***********************************


Chess::Chess(HINSTANCE hInstance)
	:mhInstance(hInstance), mCurrentlyPlayer(true)
{
	mGameLogic = 0;
	mPlayerViews[0] = 0;
	mPlayerViews[1] = 0;
	mReplayView = 0;
	mRenderTarget = 0;
};

Chess::~Chess()
{
	if(mGameLogic)
		delete mGameLogic;
	if(mPlayerViews[0])
		delete mPlayerViews[0];
	if(mPlayerViews[1])
		delete mPlayerViews[1];
	if(mReplayView)
		delete mReplayView;
	if(mRenderTarget)
		delete mRenderTarget;
};

int Chess::Run()
{
	MSG Msg = {0}; // same as ZeroMemory() macro??-------

	//mTimer.Reset();

	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))//second param allows checks for messages of a specific window --- thread dependent?
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			MenuDef::MenuType menuItem = mRenderTarget->GetMenuItem();
			if (menuItem != MenuDef::None)
			{
				ProcessMenu(menuItem);
			}
			//CalculateFrameStats();
			mGameLogic->Frame();
		}
	}

	return (int)Msg.wParam;
};

bool Chess::Init()
{
	mGameLogic = new GameLogic();
	//mGameLogic->InitObjects();

	mPlayerViews[0] = new PlayerView(QuickDef::Black);
	mPlayerViews[1] = new PlayerView(QuickDef::Red);
	mReplayView = new ReplayView(false);

	mGameLogic->AttachViews(2, true, mPlayerViews);//-----------------------------------------------------------------------------------------------------------
	mPlayerViews[0]->AttachGameLogic(mGameLogic);

	mRenderTarget = new RenderTarget(mhInstance, *mGameLogic);//fix &
	mRenderTarget->Init();
	mPlayerViews[0]->SetRenderTarget(mRenderTarget);

	return true;
};

void Chess::ProcessMenu(MenuDef::MenuType action)
{
	switch (action)
	{
	case MenuDef::NewPlayer:
		if (! mCurrentlyPlayer)
		{
			mCurrentlyPlayer = true;
			mGameLogic->AttachViews(2, true, mPlayerViews);
			mGameLogic->Reset();
		}
		else
		{
			mGameLogic->Reset();
		}
		return;

	case MenuDef::NewReplay:
		if (mCurrentlyPlayer)
		{
			mCurrentlyPlayer = false;
			mGameLogic->AttachViews(1, false, &mReplayView);
			mGameLogic->Reset();
		}
		else
		{
			mGameLogic->Reset();
		}
		return;

	case MenuDef::LoadPlayer:
		if (mCurrentlyPlayer)
		{
			mGameLogic->Reset();
			mGameLogic->AttachViews(1, false, &mReplayView);
			mGameLogic->QuickRun();
			mGameLogic->AttachViews(2, true, mPlayerViews);
		}
		else
		{
			mCurrentlyPlayer = true;
			mGameLogic->Reset();
			mPlayerViews[0]->Reset();
			mPlayerViews[1]->Reset();
			mGameLogic->QuickRun();
			mGameLogic->AttachViews(2, true, mPlayerViews);
		}
		return;

	case MenuDef::LoadReplay:
		if (mCurrentlyPlayer)
		{
			mCurrentlyPlayer = false;
			mGameLogic->AttachViews(1, false, &mReplayView);
			mGameLogic->Reset();
		}
		else
		{
			mGameLogic->Reset();
		}
	}
};