#include "stdafx.h"

#include <Windows.h>
#include <d3dx9.h>

#include "D3DText.h"
#include "UtilityError.h"
#include "D3D9GraphicsLayer.h"

namespace GameUtilities
{
	/****************/
	/* Constructors */
	/****************/
	D3DText::D3DText( const D3DTextInfo &info ) : m_info( info )
	{
	}

	/***********/
	/* Methods */
	/***********/
	
	//////////
	// Draw //
	//////////
	void				  
	D3DText::Draw() const
	{
		D3DCOLOR color = D3DCOLOR_ARGB( m_info.argb[0], m_info.argb[1], m_info.argb[2], m_info.argb[3] );

		// Create the D3DX Font
		LPD3DXFONT pD3DXFont;
		D3DXFONT_DESC fontDesc;
		fontDesc.Height = 25 * m_info.fontSize;
		fontDesc.Width = 13 * m_info.fontSize;
		fontDesc.MipLevels = 0;
		fontDesc.Italic = FALSE;
		fontDesc.CharSet = DEFAULT_CHARSET;
		fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		fontDesc.Quality = DEFAULT_QUALITY;
		fontDesc.PitchAndFamily = DEFAULT_PITCH;
		std::string fontFaceName = "Arial";
		strncpy( fontDesc.FaceName, fontFaceName.c_str(), fontFaceName.size() + 1 );

		HRESULT hr = D3DXCreateFontIndirect( Graphics()->GetD3DDevice(), &fontDesc, &pD3DXFont );
		if( FAILED( hr ) )
			throw UtilityError( "[D3DText::Draw]: Failed to create D3DXFont." );

		// Rectangle where the text will be located
		RECT textRect = { (long)m_info.position.x, (long)m_info.position.y, 0, 0 };

		// Calculate the rectangle the text will occupy
		pD3DXFont->DrawText( NULL , m_info.contents.c_str(), -1, &textRect, DT_CALCRECT, color );

		if( m_info.justification == D3DTextInfo::Center )
		{
			// center rectangle on text position.
			LONG offset = -1 * (LONG)(( textRect.right - textRect.left ) / 2.0 );
			textRect.left += offset;
			textRect.right += offset;
		}
		else if( m_info.justification == D3DTextInfo::Right )
		{
			// right justify text on text position
			LONG offset = -1 * ( textRect.right - textRect.left );
			textRect.left += offset;
			textRect.right += offset;
		}

		pD3DXFont->DrawText( NULL, m_info.contents.c_str(), -1, &textRect, DT_LEFT, color );

		pD3DXFont->Release();
	}
		
}