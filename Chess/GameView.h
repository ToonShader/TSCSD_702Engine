#ifndef GAMEVIEW
#define GAMEVIEW

#include "702/702_Create.h"
#include "Objects.h"
#include "GameLogic.h"
#include "xnacollision.h"
#include "GeometryGenerator.h"
//#include "Common.h"

class GameLogic;

struct Vertex
{
	Vertex();
	Vertex(XMFLOAT3 pos, XMFLOAT4 color);
	Vertex(const GeometryGenerator::Vertex& other);
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct Mesh
{
	std::vector<Vertex> Vertices;
	std::vector<UINT> Indices;
};

/*struct ObjectInfo
{
	Object** BlackObjects;
	Object** RedObjects;
	Object** BoardObjects;
	UINT numBlack;
	UINT numRed;
	UINT numBoards;
};*/

//class MenuView;

class RenderTarget : private D3DAppControl
{
public:
	RenderTarget(HINSTANCE hInstance, GameLogic& gameLogic);
	~RenderTarget();

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Init();
	void OnResize();
	//void Reset();
	//game logic maintains current player
	//void AttachGameLogic(GameLogic& gameLogic);
	//bool AttachViews(int numViews, bool player, const GameView** gameViews);
	MenuDef::MenuType GetMenuItem();
	void MenuOpen(QuickDef::Player player, MenuDef::MenuLevel);
	void MenuClose();

	void SetViewProjection(CXMMATRIX viewProj);

	Object* ObjectPick(int sx, int sy, CXMMATRIX view, ObjectInfo& objects);
	void UpdateScene(float deltaTime, CXMMATRIX viewProj);
	void DrawScene(ObjectInfo& objects);

	//controls all mouse input
	//virtual void MouseInput(WPARAM btnState, int x, int y) = 0;
	//void OnMouseDown(WPARAM btnState, int x, int y);
	//void OnMouseUp	(WPARAM btnState, int x, int y);
	//void OnMouseMove(WPARAM btnState, int x, int y);

private:

	//friend PlayerView;
	void BuildBlankBuffer();
	void BuildGeometryBuffers();
	void BuildMenuBuffers();
	void BuildFX();
	void BuildVertexLayout();
	void BuildBoxExtents(GeometryGenerator::MeshData& meshData, XNA::AxisAlignedBox& boxData);

//protected:

	//void MenuPick();
	//used to send events to the game logic
	void SendEvent(Event& data);//why

	//virtual void Process();
	void GetDrawInfo(UINT& vertexOffset, UINT& indexOffset, UINT& indexCount, Object* object, Menu* menuItem);
	Mesh& GetMeshInfo(QuickDef::MoveType type, XNA::AxisAlignedBox** box);

	//void SaveGame(bool replay);

	//Menu functions
	void MenuProcess(Menu* menuItem);
	void SetMenuLevel(MenuDef::MenuLevel level);



private:
	Menu** mMenuList;
	MenuDef::MenuType mSelectedMenu;
	UINT mMenuListCount;
	MenuDef::MenuLevel mMenuLevel;
	//static int mReferences;

	//static bool mInitialized;
//	static int	mViews;

	ID3D11Buffer* mTestVertexBuffer;
	ID3D11Buffer* mTestIndexBuffer;

	UINT mTestIndexCount;

	ID3D11Buffer* mObjectsVertexBuffer;
	ID3D11Buffer* mObjectsIndexBuffer;
	ID3D11Buffer* mMenuVertexBuffer;
	ID3D11Buffer* mMenuIndexBuffer;

	Mesh mBoardMesh;
	Mesh mKingMesh;
	Mesh mQueenMesh;
	Mesh mKnightMesh;
	Mesh mBishopMesh;
	Mesh mRookMesh;
	Mesh mPawnMesh;
	Mesh mMenuMesh;

	XNA::AxisAlignedBox mKingBox;
	XNA::AxisAlignedBox mQueenBox;
	XNA::AxisAlignedBox mKnightBox;
	XNA::AxisAlignedBox mBishopBox;
	XNA::AxisAlignedBox mRookBox;
	XNA::AxisAlignedBox mPawnBox;
	XNA::AxisAlignedBox mBoardBox;
	XNA::AxisAlignedBox mMenuBox;

	ID3D11Buffer* mDebugVertexBuffer;
	ID3D11Buffer* mDebugIndexBuffer;

	UINT mDebugIndexCount;

	//UINT mMenuIndexCount;

	UINT mMenuBoxIndexOffset;
	UINT mMenuBoxIndexCount;
	UINT mMenuBoxVertexOffset;

	UINT mMenuNewVertexOffset;
	UINT mMenuNewIndexCount;
	UINT mMenuNewIndexOffset;

	UINT mMenuLoadVertexOffset;
	UINT mMenuLoadIndexCount;
	UINT mMenuLoadIndexOffset;

	UINT mMenuSaveVertexOffset;
	UINT mMenuSaveIndexCount;
	UINT mMenuSaveIndexOffset;

	UINT mMenuExitVertexOffset;
	UINT mMenuExitIndexCount;
	UINT mMenuExitIndexOffset;

	UINT mMenuPlayerVertexOffset;
	UINT mMenuPlayerIndexCount;
	UINT mMenuPlayerIndexOffset;

	UINT mMenuReplayVertexOffset;
	UINT mMenuReplayIndexCount;
	UINT mMenuReplayIndexOffset;

	UINT mMenuQueenVertexOffset;
	UINT mMenuQueenIndexCount;
	UINT mMenuQueenIndexOffset;

	UINT mMenuKnightVertexOffset;
	UINT mMenuKnightIndexCount;
	UINT mMenuKnightIndexOffset;

	UINT mMenuBishopVertexOffset;
	UINT mMenuBishopIndexCount;
	UINT mMenuBishopIndexOffset;

	UINT mMenuRookVertexOffset;
	UINT mMenuRookIndexCount;
	UINT mMenuRookIndexOffset;

	UINT mMenuRedVertexOffset;
	UINT mMenuRedIndexCount;
	UINT mMenuRedIndexOffset;

	UINT mMenuBlackVertexOffset;
	UINT mMenuBlackIndexCount;
	UINT mMenuBlackIndexOffset;

	UINT mMenuWinVertexOffset;
	UINT mMenuWinIndexCount;
	UINT mMenuWinIndexOffset;

	UINT mBoardVertexOffset;
	UINT mBoardIndexOffset;
	UINT mBoardIndexCount;

	UINT mKingVertexOffset;
	UINT mKingIndexOffset;
	UINT mKingIndexCount;

	UINT mQueenVertexOffset;
	UINT mQueenIndexOffset;
	UINT mQueenIndexCount;

	UINT mKnightVertexOffset;
	UINT mKnightIndexOffset;
	UINT mKnightIndexCount;

	UINT mBishopVertexOffset;
	UINT mBishopIndexOffset;
	UINT mBishopIndexCount;

	UINT mRookVertexOffset;
	UINT mRookIndexOffset;
	UINT mRookIndexCount;

	UINT mPawnVertexOffset;
	UINT mPawnIndexOffset;
	UINT mPawnIndexCount;

	ID3D11InputLayout* mInputLayout;

	ID3D11RasterizerState* mWireFrameRS;

	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mFXWorldViewProj;
	ID3DX11EffectVectorVariable* mFXColorBase;
	ID3DX11EffectVectorVariable* mFXColorSpecial;
	ID3DX11EffectVectorVariable* mFXColorRandom;



//protected:
	GameLogic* mGameLogic;
	//static MenuView* mMenu;
	bool mMenued;
	bool mMenuCloseable;
	bool mWireFrame;
	QuickDef::Player mRankingPlayer;

	//float mTheta;
	//float mPhi;
	//float mRadius;

	//each view will maintain its camera position
	XMFLOAT4X4 mView;//why?---------------------------------------------------------------------
	//XMVECTOR mViewWorld;
	XMFLOAT4X4 mProj;

	XMFLOAT4 mColorBlack;//why??---------------------------------------------------------------
	XMFLOAT4 mColorRed;
	XMFLOAT4 mColorHighlight;

	//Object* mSelectedObject;
};

class GameView
{
public:
	GameView(QuickDef::Player faction);
	virtual ~GameView();

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void SetRenderTarget(RenderTarget* target);
	void AttachGameLogic(GameLogic* gameLogic);
	void MouseInput(UINT msg, WPARAM btnState, int x, int y);
	void Frame(ObjectInfo& objects);

	virtual void SaveGame();
	virtual void Reset();
	void Win();

protected:
	ObjectInfo GetObjects();
	Object* ObjectPick(int x, int y, ObjectInfo& objects);
	void ProcessPicked(Object* picked);
	void UpdateViewProjection();
	bool SendEvent(Event& data);
	virtual void LogMove(UINT x, UINT z, UINT nx, UINT nz, Event& data, bool promotion) = 0;
	void MenuClose();


	virtual void OnMouseDown(WPARAM btnState, int x, int y) = 0;
	virtual void OnMouseUp  (WPARAM btnState, int x, int y) = 0;
	virtual void OnMouseMove(WPARAM btnState, int x, int y) = 0;


private:
	void MoveAssist();
	void ClearAssists();

private:
	static RenderTarget* mRenderTarget;
	static GameLogic* mGameLogic;
	//static MenuView* mMenuView;


protected:
	Object* mSelected;
	QuickDef::Player mFaction;
	POINT mLastMousePos;

	float mPhi;
	float mTheta;
	float mRadius;

	XMFLOAT4X4 mViewProj;
	XMFLOAT4 mViewDisplace;
};

class PlayerView : public GameView
{
public:
	PlayerView(QuickDef::Player faction);
	~PlayerView();

	void LogMove(UINT x, UINT z, UINT nx, UINT nz, Event& data, bool promotion);
	void Reset();
	void SaveGame();
	void LogPromotion(QuickDef::MoveType piece);
	//void MouseInput(UINT msg, WPARAM btnState, int x, int y);

private:
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp	(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	void CreateBuffer(int sx, int sy);

private://buffer creation purposed only
	static UINT mReferences;
	static std::fstream* mMoveFile;
	std::vector<Vertex> testVertices;
	UINT testSize;
	UINT test;
	POINT mLastDrawPos;


};

class ReplayView : public GameView
{
public:
	ReplayView(bool temp);
	~ReplayView();

	void LogMove(UINT x, UINT z, UINT nx, UINT nz, Event& data, bool promotion);
	void Reset();


	//void MouseInput(WPARAM btnState, int x, int y);
	void QuickRun();

private:
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp	(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	Object* FindObject(UINT x, UINT z, ObjectInfo& objects);

private:
	static std::fstream* mReplayFile;
	//bool mMenued;
};

/*class MenuManager// : public GameView
{
	MenuManager(QuickDef::MenuLevel currLevel);
	~MenuManager();

	//void MouseInput(WPARAM btnState, int x, int y);
	void Open();
	void Close();
	void Draw(ID3D11DeviceContext* immediateContext);
	void UpdateLevel(QuickDef::MenuLevel level);

	UINT GetMenuListNumber();
	Menu** GetMenus();

private:
	void CreateMenus(QuickDef::MenuLevel level);

private:
	UINT mMenuListNumber;
	Menu* mCurrMenuList[4];
	Menu* mFullMenuList[6];

	//void OnMouseDown(WPARAM btnState, int x, int y);
	//void OnMouseUp	(WPARAM btnState, int x, int y);
	//void OnMouseMove(WPARAM btnState, int x, int y);
};*/




#endif