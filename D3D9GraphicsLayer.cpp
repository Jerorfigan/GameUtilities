#include "stdafx.h"

#include "D3D9GraphicsLayer.h"
#include "UtilityError.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/

	D3D9GraphicsLayer::D3D9GraphicsLayer( HWND hWnd ) : 
		m_hWnd( hWnd ),
		m_deviceLost( false )
	{
		if( m_pD3D9GraphicsLayer )
		{
			throw UtilityError( "[D3D9GraphicsLayer::D3D9GraphicsLayer]: Attempt to create multiple instances of singleton class D3D9GraphicsLayer.");
		}

		m_pD3D9GraphicsLayer = this;

		m_pD3D = NULL;
		m_pD3DDevice = NULL;
		m_pBackBuffer = NULL;
	}

	/***********/
	/* Methods */
	/***********/

	void D3D9GraphicsLayer::Flip()
	{
		// Make sure the device has been created.
		if( !m_pD3DDevice )
		{
			throw UtilityError( "[D3D9GraphicsLayer::Flip]: Flip called when D3D Device is uninitialized." );
		}
	
		// Transfer the contents of the back buffer to the primary surface.
		HRESULT hResult = m_pD3DDevice->Present( NULL, NULL, NULL, NULL );

		if( hResult == D3DERR_DEVICELOST )
		{
			m_deviceLost = true;
		}
		else if( hResult != D3D_OK )
		{
			throw UtilityError( "[D3D9GraphicsLayer::Flip]: Call to IDirect3DDevice9::Present failed unexpectedly." );
		}
	}

	void D3D9GraphicsLayer::Reset()
	{
		HRESULT hResult = m_pD3DDevice->Reset( &m_D3DPresParams );

		if( FAILED( hResult ) )
		{
			throw UtilityError( "[D3D9GraphicsLayer::Reset]: Call to IDirect3DDevice9::Reset failed unexpectedly." );
		}

		// Re-acquire pointer to backbuffer.
		m_pD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer );

		// Re-create the D3DXSprite interface.
		D3DXCreateSprite( m_pD3DDevice, &m_pSpriteInterface );
	}

	void D3D9GraphicsLayer::ReleaseUnmanagedResources()
	{
		SafeRelease( m_pSpriteInterface );
		SafeRelease( m_pBackBuffer ); 
	}

	void D3D9GraphicsLayer::InitD3D( GUID* pGuid, uint backBuffWidth, uint backBuffHeight, uint bpp, bool fullscreen )
	{
		// Create the Direct3D object
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if( !m_pD3D )
		{
			throw UtilityError( "[D3D9GraphicsLayer::InitD3DFullScreen]: Could not create IDirect3D9 interface." );
		}

		// Structure to hold the creation parameters for the device
		ZeroMemory( &m_D3DPresParams, sizeof(m_D3DPresParams) );

		m_D3DPresParams.BackBufferWidth			   =    backBuffWidth;
		m_D3DPresParams.BackBufferHeight		   =    backBuffHeight;
	
		// Set the flags for the bit depth - only supports 16, 24, and 32 bit formats
		if( bpp == 16 )
		{
			m_D3DPresParams.BackBufferFormat	   =    D3DFMT_R5G6B5;
		}
		else if( bpp == 24 )
		{
			m_D3DPresParams.BackBufferFormat	   =    D3DFMT_X8R8G8B8;
		}
		else if( bpp == 32 )
		{
			m_D3DPresParams.BackBufferFormat	   =    D3DFMT_A8R8G8B8;
		}
		else
		{
			m_D3DPresParams.BackBufferFormat	   =    D3DFMT_A8R8G8B8;
		}

		// Only have one back buffer associated with the primary surface
		m_D3DPresParams.BackBufferCount			   =    1;
		// No multisampling
		m_D3DPresParams.MultiSampleType			   =    D3DMULTISAMPLE_NONE;
		// The quality of the multisampling
		m_D3DPresParams.MultiSampleQuality		   =    0;
		// Copy the back buffer to the primary surface normally
		m_D3DPresParams.SwapEffect				   =    D3DSWAPEFFECT_DISCARD;
		// The handle to the window to render in to
		m_D3DPresParams.hDeviceWindow			   =    m_hWnd;
		// Fullscreen operation
		m_D3DPresParams.Windowed				   =    fullscreen ? FALSE : TRUE;
		// Let Direct3D look after the depth buffer
		m_D3DPresParams.EnableAutoDepthStencil	   =    TRUE;
		// Set the depth buffer depth to 16 bits
		m_D3DPresParams.AutoDepthStencilFormat	   =    D3DFMT_D16;
		// Use the default refresh rate
		m_D3DPresParams.FullScreen_RefreshRateInHz =    D3DPRESENT_RATE_DEFAULT;
		// Update the screen as soon as possible (dont wait for vsync)
		m_D3DPresParams.PresentationInterval	   =    D3DPRESENT_INTERVAL_DEFAULT;
		// Allow the back buffer to be locked
		m_D3DPresParams.Flags					   =    D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
		// Create the device using hardware acceleration if available
		HRESULT hResult = m_pD3D->CreateDevice( 
			D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL, 
			m_hWnd,					
			D3DCREATE_HARDWARE_VERTEXPROCESSING, 
			&m_D3DPresParams, 
			&m_pD3DDevice );

		if( FAILED( hResult ) )
		{
			throw UtilityError( "[D3D9GraphicsLayer::InitD3DFullScreen]: Could not create IDirect3D9Device interface." );
		}

		// Store backbuffer dimensions.
		m_backBufferWidth = backBuffWidth;
		m_backBufferHeight = backBuffHeight;

		// Store pointer to backbuffer.
		m_pD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer );

		// Create D3DXSprite interface.
		D3DXCreateSprite( m_pD3DDevice, &m_pSpriteInterface );
	}

	/**************/
	/* Destructor */
	/**************/

	D3D9GraphicsLayer::~D3D9GraphicsLayer()
	{
		SafeRelease( m_pSpriteInterface );
		SafeRelease( m_pBackBuffer );
		SafeRelease( m_pD3DDevice );
		SafeRelease( m_pD3D );
	}

	/******************/
	/* Static methods */
	/******************/

	void D3D9GraphicsLayer::Create( HWND hWnd, uint backBuffWidth, uint backBuffHeight, GUID* pGuid, bool fullscreen )
	{
		new D3D9GraphicsLayer( hWnd );

		// Init Direct3D and the device for fullscreen operation.
		Graphics()->InitD3D( pGuid, backBuffWidth, backBuffHeight, 32u, fullscreen );
	}

	void D3D9GraphicsLayer::Destroy()
	{
		delete m_pD3D9GraphicsLayer;
		m_pD3D9GraphicsLayer = NULL;
	}

	/***************/
	/* Static data */
	/***************/
	D3D9GraphicsLayer* D3D9GraphicsLayer::m_pD3D9GraphicsLayer = NULL;

}