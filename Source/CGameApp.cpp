//-----------------------------------------------------------------------------
// File: CGameApp.cpp
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Original design by Adam Hoult & Gary Simmons. Modified by Pomacu Mircea Andrei.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "CGameApp.h"
#include <iostream>
#include <fstream>
extern HINSTANCE g_hInst;

//-----------------------------------------------------------------------------
// CGameApp Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CGameApp () (Constructor)
// Desc : CGameApp Class Constructor
//-----------------------------------------------------------------------------
CGameApp::CGameApp()
{
	// Reset / Clear all required values
	m_hWnd			= NULL;
	m_hIcon			= NULL;
	m_hMenu			= NULL;
	m_pBBuffer		= NULL;
	m_pPlayer		= NULL;
	n_pPlayer       = NULL;
	m_pBullet = NULL;
	enemy = NULL;
	crate = NULL;
	crate1 = NULL;
	m_LastFrameRate = 0;
}

//-----------------------------------------------------------------------------
// Name : ~CGameApp () (Destructor)
// Desc : CGameApp Class Destructor
//-----------------------------------------------------------------------------
CGameApp::~CGameApp()
{
	// Shut the engine down
	ShutDown();
}

//-----------------------------------------------------------------------------
// Name : InitInstance ()
// Desc : Initialises the entire Engine here.
//-----------------------------------------------------------------------------
bool CGameApp::InitInstance( LPCTSTR lpCmdLine, int iCmdShow )
{
	// Create the primary display device
	if (!CreateDisplay()) { ShutDown(); return false; }

	// Build Objects
	if (!BuildObjects()) 
	{ 
		MessageBox( 0, _T("Failed to initialize properly. Reinstalling the application may solve this problem.\nIf the problem persists, please contact technical support."), _T("Fatal Error"), MB_OK | MB_ICONSTOP);
		ShutDown(); 
		return false; 
	}

	// Set up all required game states
	SetupGameState();

	// Success!
	return true;
}

//-----------------------------------------------------------------------------
// Name : CreateDisplay ()
// Desc : Create the display windows, devices etc, ready for rendering.
//-----------------------------------------------------------------------------
bool CGameApp::CreateDisplay()
{
	LPTSTR			WindowTitle		= _T("GameFramework");
	LPCSTR			WindowClass		= _T("GameFramework_Class");
	USHORT			Width			= 800;
	USHORT			Height			= 600;
	RECT			rc;
	WNDCLASSEX		wcex;


	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= CGameApp::StaticWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInst;
	wcex.hIcon			= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= WindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if(RegisterClassEx(&wcex)==0)
		return false;

	// Retrieve the final client size of the window
	::GetClientRect( m_hWnd, &rc );
	m_nViewX		= rc.left;
	m_nViewY		= rc.top;
	m_nViewWidth	= rc.right - rc.left;
	m_nViewHeight	= rc.bottom - rc.top;

	m_hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, NULL, NULL, g_hInst, this);

	if (!m_hWnd)
		return false;

	// Show the window
	ShowWindow(m_hWnd, SW_SHOW);

	// Success!!
	return true;
}

//-----------------------------------------------------------------------------
// Name : BeginGame ()
// Desc : Signals the beginning of the physical post-initialisation stage.
//		From here on, the game engine has control over processing.
//-----------------------------------------------------------------------------
int CGameApp::BeginGame()
{
	MSG		msg;

	// Start main loop
	while(true) 
	{
		// Did we recieve a message, or are we idling ?
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) 
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage( &msg );
			DispatchMessage ( &msg );
		} 
		else 
		{
			// Advance Game Frame.
			FrameAdvance();

		} // End If messages waiting
	
	} // Until quit message is receieved

	return 0;
}

//-----------------------------------------------------------------------------
// Name : ShutDown ()
// Desc : Shuts down the game engine, and frees up all resources.
//-----------------------------------------------------------------------------
bool CGameApp::ShutDown()
{
	// Release any previously built objects
	ReleaseObjects ( );
	
	// Destroy menu, it may not be attached
	if ( m_hMenu ) DestroyMenu( m_hMenu );
	m_hMenu		 = NULL;

	// Destroy the render window
	SetMenu( m_hWnd, NULL );
	if ( m_hWnd ) DestroyWindow( m_hWnd );
	m_hWnd		  = NULL;
	
	// Shutdown Success
	return true;
}

//-----------------------------------------------------------------------------
// Name : StaticWndProc () (Static Callback)
// Desc : This is the main messge pump for ALL display devices, it captures
//		the appropriate messages, and routes them through to the application
//		class for which it was intended, therefore giving full class access.
// Note : It is VITALLY important that you should pass your 'this' pointer to
//		the lpParam parameter of the CreateWindow function if you wish to be
//		able to pass messages back to that app object.
//-----------------------------------------------------------------------------
LRESULT CALLBACK CGameApp::StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	// If this is a create message, trap the 'this' pointer passed in and store it within the window.
	if ( Message == WM_CREATE ) SetWindowLong( hWnd, GWL_USERDATA, (LONG)((CREATESTRUCT FAR *)lParam)->lpCreateParams);

	// Obtain the correct destination for this message
	CGameApp *Destination = (CGameApp*)GetWindowLong( hWnd, GWL_USERDATA );
	
	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc( hWnd, Message, wParam, lParam );
	
	// No destination found, defer to system...
	return DefWindowProc( hWnd, Message, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name : DisplayWndProc ()
// Desc : The display devices internal WndProc function. All messages being
//		passed to this function are relative to the window it owns.
//-----------------------------------------------------------------------------
LRESULT CGameApp::DisplayWndProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
	static UINT			fTimer;	

	// Determine message type
	switch (Message)
	{
		case WM_CREATE:
			break;
		
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_SIZE:
			if ( wParam == SIZE_MINIMIZED )
			{
				// App is inactive
				m_bActive = false;
			
			} // App has been minimized
			else
			{
				// App is active
				m_bActive = true;

				// Store new viewport sizes
				m_nViewWidth  = LOWORD( lParam );
				m_nViewHeight = HIWORD( lParam );
		
			
			} // End if !Minimized

			break;

		case WM_LBUTTONDOWN:
			// Capture the mouse
			SetCapture( m_hWnd );
			GetCursorPos( &m_OldCursorPos );
			break;

		case WM_LBUTTONUP:
			// Release the mouse
			ReleaseCapture( );
			break;

		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_RETURN:
				fTimer = SetTimer(m_hWnd, 1, 250, NULL);
				m_pPlayer->Explode();
			    break;
			case 0x51:
				fTimer = SetTimer(m_hWnd, 3, 250, NULL);
				n_pPlayer->Explode();
				break;
			case 0x43:
				fTimer = SetTimer(m_hWnd, 1, 250, NULL);
				double X_Axis, Y_Axis;

				m_pPlayer->GeterPoistionX(X_Axis);
				m_pPlayer->GeterPositionY(Y_Axis);

				m_pBullet->Position() = Vec2(X_Axis,Y_Axis - 85);
				m_pBullet->Shoot();
				break;

			}
			break;

		case WM_TIMER:
			switch(wParam)
			{
			case 1:
				if(!m_pPlayer->AdvanceExplosion())
					KillTimer(m_hWnd, 2);

			case 3:

				if (!n_pPlayer->AdvanceExplosion())
					KillTimer(m_hWnd, 2);

				if (!enemy->AdvanceExplosion())
					KillTimer(m_hWnd, 2);
			case 2:
				if (!crate->AdvanceExplosion())
					KillTimer(m_hWnd, 2);
				if (!crate1->AdvanceExplosion())
					KillTimer(m_hWnd, 2);
			case 4:
				if (!magicCrate->AdvanceExplosion())
					KillTimer(m_hWnd, 4);
			}
			break;

		case WM_COMMAND:
			break;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);

	} // End Message Switch
	
	return 0;
}

//-----------------------------------------------------------------------------
// Name : BuildObjects ()
// Desc : Build our demonstration meshes, and the objects that instance them
//-----------------------------------------------------------------------------
bool CGameApp::BuildObjects()
{
	m_pBBuffer = new BackBuffer(m_hWnd, m_nViewWidth, m_nViewHeight);
	
	m_pPlayer = new CPlayer(m_pBBuffer);

	//second player creation
	n_pPlayer = new CPlayer1(m_pBBuffer);

	enemy = new CPlayer1(m_pBBuffer);

	m_pBullet = new Bullet(m_pBBuffer);

	crate = new Crate(m_pBBuffer);

	crate1 = new Crate(m_pBBuffer);

	magicCrate = new MagicCrate(m_pBBuffer);

	enemyBullet = new EnemyBullet(m_pBBuffer);

	enemyBullet1 = new EnemyBullet(m_pBBuffer);

	if(!m_imgBackground.LoadBitmapFromFile("data/background.bmp", GetDC(m_hWnd)))
		return false;

	// Success!
	return true;
}

//-----------------------------------------------------------------------------
// Name : SetupGameState ()
// Desc : Sets up all the initial states required by the game.
//-----------------------------------------------------------------------------
void CGameApp::SetupGameState()
{
	m_pPlayer->Position() = Vec2(300, 400);

	n_pPlayer->Position() = Vec2(200, 50);

	enemy->Position() = Vec2(400, 100);

	crate->Position() = Vec2(100, 50);

	crate1->Position() = Vec2(700, 50);

	magicCrate->Position() = Vec2(500, 50);

	enemyBullet->Position() = Vec2(400, 100);

	enemyBullet1->Position() = Vec2(200, 50);
}

//-----------------------------------------------------------------------------
// Name : ReleaseObjects ()
// Desc : Releases our objects and their associated memory so that we can
//		rebuild them, if required, during our applications life-time.
//-----------------------------------------------------------------------------
void CGameApp::ReleaseObjects( )
{
	if(m_pPlayer != NULL)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (n_pPlayer != NULL)
	{
		delete n_pPlayer;
		n_pPlayer = NULL;
	}

	if (enemy != NULL)
	{
		delete enemy;
		enemy = NULL;
	}

	if (m_pBullet != NULL)
	{
		delete m_pBullet;
		m_pBullet = NULL;
	}

	if (enemyBullet != NULL)
	{
		delete enemyBullet;
		enemyBullet = NULL;
	}

	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
		enemyBullet1 = NULL;
	}

	if (crate != NULL)
	{
		delete crate;
		crate = NULL;
	}

	if (magicCrate != NULL)
	{
		delete magicCrate;
		magicCrate = NULL;
	}

	if (crate1 != NULL)
	{
		delete crate1;
		crate1 = NULL;
	}

	if(m_pBBuffer != NULL)
	{
		delete m_pBBuffer;
		m_pBBuffer = NULL;
	}


}

//-----------------------------------------------------------------------------
// Name : FrameAdvance () (Private)
// Desc : Called to signal that we are now rendering the next frame.
//-----------------------------------------------------------------------------
void CGameApp::FrameAdvance()
{
	static TCHAR FrameRate[ 50 ];
	static TCHAR TitleBuffer[ 255 ];

	// Advance the timer
	m_Timer.Tick( );

	// Skip if app is inactive
	if ( !m_bActive ) return;
	
	// Get / Display the framerate
	if ( m_LastFrameRate != m_Timer.GetFrameRate() )
	{
		m_LastFrameRate = m_Timer.GetFrameRate( FrameRate, 50 );
		sprintf_s( TitleBuffer, _T("Game : %s      Lives: %d      Score: %d"), FrameRate, m_pPlayer->GetLive(), m_pPlayer->GetScore());
		SetWindowText( m_hWnd, TitleBuffer );

	} // End if Frame Rate Altered

	// Poll & Process input devices
	ProcessInput();

	// Animate the game objects
	AnimateObjects();

	// Drawing the game objects
	DrawObjects();
}

//-----------------------------------------------------------------------------
// Name : ProcessInput () (Private)
// Desc : Simply polls the input devices and performs basic input operations
//-----------------------------------------------------------------------------
void CGameApp::ProcessInput( )
{
	static UCHAR pKeyBuffer[ 256 ];
	ULONG		Direction = 0;
	ULONG       Direction2 = 0;
	POINT		CursorPos;
	float		X = 0.0f, Y = 0.0f;

	// Retrieve keyboard state
	if ( !GetKeyboardState( pKeyBuffer ) ) return;

	// Check the relevant keys
	if ( pKeyBuffer[ VK_UP	] & 0xF0 ) Direction |= CPlayer::DIR_FORWARD;
	if ( pKeyBuffer[ VK_DOWN  ] & 0xF0 ) Direction |= CPlayer::DIR_BACKWARD;
	if ( pKeyBuffer[ VK_LEFT  ] & 0xF0 ) Direction |= CPlayer::DIR_LEFT;
	if ( pKeyBuffer[ VK_RIGHT ] & 0xF0 ) Direction |= CPlayer::DIR_RIGHT;

	/*if (pKeyBuffer[0x57] & 0xF0) Direction2 |= CPlayer::DIR_FORWARD;
	if (pKeyBuffer[0x53] & 0xF0) Direction2 |= CPlayer::DIR_BACKWARD;
	if (pKeyBuffer[0x41] & 0xF0) Direction2 |= CPlayer::DIR_LEFT;
	if (pKeyBuffer[0x44] & 0xF0) Direction2 |= CPlayer::DIR_RIGHT;*/

	// Move the player
	m_pPlayer->Move(Direction);
	n_pPlayer->Move();
	enemy->Move();

	
	bool flag = enemyBullet->Shoot();

	bool flag1 = enemyBullet1->Shoot();

	if (flag1 == true)
	{
		double a, b;
		n_pPlayer->GeterPoistionX(a);
		n_pPlayer->GeterPositionY(b);
		enemyBullet1->Position() = Vec2(a, b);
	}

	if (flag == true)
	{
		double a, b;
		enemy->GeterPoistionX(a);
		enemy->GeterPositionY(b);
		enemyBullet->Position() = Vec2(a, b);
	}

	if (pKeyBuffer[VK_NUMPAD4] & 0xF0)
		m_pPlayer->MoveLeft(m_pBBuffer);
	
	if (pKeyBuffer[VK_NUMPAD2] & 0xF0)
	    m_pPlayer->MoveDown(m_pBBuffer);
	
	if (pKeyBuffer[VK_NUMPAD6] & 0xF0)
		m_pPlayer->MoveRight(m_pBBuffer);

	if (pKeyBuffer[VK_NUMPAD8] & 0xF0)
		m_pPlayer->MoveUp(m_pBBuffer);

	if (pKeyBuffer[0x4D] & 0xF0)
	{
		std::ofstream output;
		output.open("data/save.txt");
		double x_axis, y_axis;
		m_pPlayer->GeterPoistionX(x_axis);
		m_pPlayer->GeterPositionY(y_axis);
		output << x_axis << " " << y_axis;
		output.close();
	}

	if (pKeyBuffer[0x4C] & 0xF0)
	{
		std::ifstream input;
		input.open("data/save.txt");
		double x_axis, y_axis;
		input >> x_axis >> y_axis;
		m_pPlayer->Position() = Vec2(x_axis, y_axis);
		m_pPlayer->MakeVelocity0();
		input.close();
	}

	if (m_pPlayer->GetLive() == 0)
	{
		static TCHAR TitleBuffer[255];
		sprintf_s(TitleBuffer, "Game Over");
		SetWindowText(m_hWnd, TitleBuffer);
	}

	crate->Move();	
	crate1->Move();
	magicCrate->Move();
	

	if (!m_pPlayer->GetLive()) 
	{
			MessageBox(m_hWnd,"Game over", "Game over", MB_OK);
			PostQuitMessage(0);
		
	}

	// Now process the mouse (if the button is pressed)
	if ( GetCapture() == m_hWnd )
	{
		// Hide the mouse pointer
		SetCursor( NULL );

		// Retrieve the cursor position
		GetCursorPos( &CursorPos );

		// Reset our cursor position so we can keep going forever :)
		SetCursorPos( m_OldCursorPos.x, m_OldCursorPos.y );

	} // End if Captured
}

//-----------------------------------------------------------------------------
// Name : AnimateObjects () (Private)
// Desc : Animates the objects we currently have loaded.
//-----------------------------------------------------------------------------
void CGameApp::AnimateObjects()
{
	m_pPlayer->Update(m_Timer.GetTimeElapsed());
	n_pPlayer->Update(m_Timer.GetTimeElapsed());
	m_pBullet->Update(m_Timer.GetTimeElapsed());
	crate->Update(m_Timer.GetTimeElapsed());
	crate1->Update(m_Timer.GetTimeElapsed());
	enemy->Update(m_Timer.GetTimeElapsed());
	magicCrate->Update(m_Timer.GetTimeElapsed());
	enemyBullet->Update(m_Timer.GetTimeElapsed());
	enemyBullet1->Update(m_Timer.GetTimeElapsed());


	//crate1->Update(m_Timer.GetTimeElapsed());
}

//-----------------------------------------------------------------------------
// Name : DrawObjects () (Private)
// Desc : Draws the game objects
//-----------------------------------------------------------------------------
void CGameApp::DrawObjects()
{
	m_pBBuffer->reset();

	//m_imgBackground.Paint(m_pBBuffer->getDC(), 0, 0);
	DrawBackground();

	m_pPlayer->Draw();
	
	crate->Draw();
	
	enemyBullet->Draw();

	enemyBullet1->Draw();

	magicCrate->Draw();

	crate1->Draw();

	enemy->Draw();

	n_pPlayer->Draw();

	m_pBullet->Draw();
	
	static UINT fTimer;

	srand(time(NULL));

	if (Collision(n_pPlayer, m_pPlayer))
	{
		m_pPlayer->DecreaseLives();

		fTimer = SetTimer(m_hWnd, 2, 100, NULL);
		
		m_pPlayer->Explode();
		m_pPlayer->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 1, 100, NULL);


		n_pPlayer->Explode();
		n_pPlayer->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 1, 0, NULL);

		m_pPlayer->Position() = Vec2(100, 400);
		n_pPlayer->Position() = Vec2(200, 100);
	}

	if (Collision1(m_pBullet, crate))
	{
		m_pPlayer->IncreaseScore();

		crate->Explode();
		crate->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 2, 50, NULL);

		double a, b;
		a = rand() % 500 +100;
		b = rand() % 300 + 100;
		crate->Position() = Vec2(a, b);
	}

	if (Collision1(m_pBullet, crate1))
	{
		m_pPlayer->IncreaseScore();

		crate1->Explode();
		crate1->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 2, 50, NULL);

		double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;
		crate1->Position() = Vec2(a, b);
	}

	if (Collision2(m_pPlayer, crate))
	{
		m_pPlayer->DecreaseLives();

		fTimer = SetTimer(m_hWnd, 2, 50, NULL);

		m_pPlayer->Explode();
		m_pPlayer->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 1, 50, NULL);
		crate->Explode();
		crate->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 1, 0, NULL);
		m_pPlayer->Position() = Vec2(100, 400);
		double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;
		crate->Position() = Vec2(a, b);
		
	}

	if (Collision3(m_pPlayer, magicCrate))
	{
		m_pPlayer->IncreaseLives();
		magicCrate->Explode();
		magicCrate->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 4, 0, NULL);
		double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;
		magicCrate->Position() = Vec2(a, b);

	}

	if (Collision4(m_pBullet, enemy))
	{
		m_pPlayer->IncreaseScore();

		enemy->Explode();
		enemy->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 3, 50, NULL);

		double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;
		enemy->Position() = Vec2(a, b);
	}

	if (Collision4(m_pBullet, n_pPlayer))
	{
		m_pPlayer->IncreaseScore();

		n_pPlayer->Explode();
		n_pPlayer->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 3, 50, NULL);

		double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;
		n_pPlayer->Position() = Vec2(a, b);
	}

	if (Collision5(enemyBullet, m_pPlayer))
	{
		m_pPlayer->DecreaseLives();

		m_pPlayer->Explode();
		m_pPlayer->AdvanceExplosion();
		fTimer = SetTimer(m_hWnd, 1, 50, NULL);
		/*double a, b;
		a = rand() % 500 + 100;
		b = rand() % 300 + 100;*/
		m_pPlayer->Position() = Vec2(300, 400);
	}

	m_pBBuffer->present();
}

bool CGameApp::Collision(CPlayer1* p1, CPlayer* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

bool CGameApp::Collision1(Bullet* p1, Crate* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

bool CGameApp::Collision2(CPlayer* p1, Crate* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

bool CGameApp::Collision3(CPlayer* p1, MagicCrate* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

bool CGameApp::Collision4(Bullet* p1, CPlayer1* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

bool CGameApp::Collision5(EnemyBullet* p1, CPlayer* p2)
{
	RECT r;
	r.left = p1->m_pSprite->mPosition.x - p1->m_pSprite->width() / 2;
	r.right = p1->m_pSprite->mPosition.x + p1->m_pSprite->width() / 2;
	r.top = p1->m_pSprite->mPosition.y - p1->m_pSprite->height() / 2;
	r.bottom = p1->m_pSprite->mPosition.y + p1->m_pSprite->height() / 2;

	RECT r2;
	r2.left = p2->m_pSprite->mPosition.x - p2->m_pSprite->width() / 2;
	r2.right = p2->m_pSprite->mPosition.x + p2->m_pSprite->width() / 2;
	r2.top = p2->m_pSprite->mPosition.y - p2->m_pSprite->height() / 2;
	r2.bottom = p2->m_pSprite->mPosition.y + p2->m_pSprite->height() / 2;


	if (r.right > r2.left && r.left < r2.right && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}
	if (r.left > r2.right && r.right < r2.left && r.bottom>r2.top && r.top < r2.bottom)
	{
		return true;
	}

	return false;

}

void CGameApp::DrawBackground()
{
	static int currentY = m_imgBackground.Height();

	static size_t lastTime = ::GetTickCount();
	size_t currentTime = ::GetTickCount();

	if (currentTime - lastTime > 100) // Scrolling background
	{
		lastTime = currentTime;
		currentY -= 10;
		if (currentY < 0)
			currentY = m_imgBackground.Height();
	}

	m_imgBackground.Paint(m_pBBuffer->getDC(), 0, currentY);
	//m_imgBackground.Paint(m_pBBuffer->getDC(), currentY, 0);

}

