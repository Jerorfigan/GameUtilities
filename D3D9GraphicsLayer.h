#pragma once

/***************************************/
/***************************************/
/* Manages the D3D9 interface objects. */
/***************************************/
/***************************************/

#include <d3d9.h>
#include <d3dx9.h>

#include "Globals.h"

namespace GameUtilities
{

	class D3D9GraphicsLayer
	{
		/****************/
		/* Constructors */
		/****************/
	protected:
		D3D9GraphicsLayer( HWND hWnd );

		/***********/
		/* Methods */
		/***********/
	public:
		void Flip();
		void Reset();
		LPDIRECT3D9 GetD3D();
		LPDIRECT3DDEVICE9 GetD3DDevice();
		LPDIRECT3DSURFACE9 GetBackBuffer();
		LPD3DXSPRITE GetSpriteInterface();

		uint GetBackBufferWidth();
		uint GetBackBufferHeight();
		void ReleaseUnmanagedResources();
		bool DeviceLost();

	private:
		void InitD3D( GUID* pGuid, uint backBuffWidth, uint backBuffHeight, uint bpp, bool fullscreen );

		/**************/
		/* Destructor */
		/**************/
	public:
		~D3D9GraphicsLayer();

		/********/
		/* Data */
		/********/
	private:
		HWND				     m_hWnd;
		LPDIRECT3D9			     m_pD3D;
		D3DPRESENT_PARAMETERS    m_D3DPresParams;
		LPDIRECT3DDEVICE9	     m_pD3DDevice;
		LPDIRECT3DSURFACE9       m_pBackBuffer;
		LPD3DXSPRITE             m_pSpriteInterface;
		uint				     m_backBufferWidth;
		uint				     m_backBufferHeight;
		D3DFORMAT			     m_bestSurfaceFormat;
		bool					 m_deviceLost;

		/******************/
		/* Static methods */
		/******************/
	public:
		static void Create( HWND hWnd, uint backBuffWidth, uint backBuffHeight, GUID* pGuid, bool fullscreen = true );
		static void Destroy();
		static D3D9GraphicsLayer* GetGraphics();

		/***************/
		/* Static data */
		/***************/
	private:
		static D3D9GraphicsLayer*    m_pD3D9GraphicsLayer;
	};

	/***********/
	/* Inlines */
	/***********/
	inline LPDIRECT3D9 D3D9GraphicsLayer::GetD3D()
	{
		return m_pD3D;
	}

	inline LPDIRECT3DDEVICE9 D3D9GraphicsLayer::GetD3DDevice()
	{
		return m_pD3DDevice;
	}

	inline LPDIRECT3DSURFACE9 D3D9GraphicsLayer::GetBackBuffer()
	{
		return m_pBackBuffer;
	}

	inline LPD3DXSPRITE D3D9GraphicsLayer::GetSpriteInterface()
	{
		return m_pSpriteInterface;
	}

	inline uint D3D9GraphicsLayer::GetBackBufferWidth()
	{
		return m_backBufferWidth;
	}

	inline uint D3D9GraphicsLayer::GetBackBufferHeight()
	{
		return m_backBufferHeight;
	}

	inline bool D3D9GraphicsLayer::DeviceLost()
	{
		return m_deviceLost;
	}

	inline D3D9GraphicsLayer* D3D9GraphicsLayer::GetGraphics()
	{
		return m_pD3D9GraphicsLayer;
	}

	/* Global abbreviated wrapper for D3D9GraphicsLayer::GetGraphics */
	inline D3D9GraphicsLayer* Graphics()
	{
		return D3D9GraphicsLayer::GetGraphics();
	}

}