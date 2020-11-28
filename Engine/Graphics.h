/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include <cassert>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	Color GetPixel(int x, int y) const;

	template<typename E>
	void DrawSprite(int x, int y, const Surface& s, E effect, bool reversed = false)
	{
		DrawSprite(x, y, s.GetRect(), s, effect, reversed);
	}
	template<typename E>
	void DrawSprite(int x, int y, const RectI& srcRect, const Surface& s, E effect, bool reversed = false)
	{
		DrawSprite(x, y, srcRect, GetScreenRectI(), s, effect, reversed);
	}
	template<typename E>
	void DrawSprite(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, E effect, bool reversed = false)
	{
		assert(srcRect.Left >= 0);
		assert(srcRect.Right <= s.GetWidth());
		assert(srcRect.Top >= 0);
		assert(srcRect.Bottom <= s.GetHeight());

		if (x < clip.Left)
		{
			srcRect.Left += clip.Left - x;
			x = clip.Left;
		}
		if (y < clip.Top)
		{
			srcRect.Top += clip.Top - y;
			y = clip.Top;
		}
		if (x + srcRect.GetWidth() > clip.Right)
			srcRect.Right -= x + srcRect.GetWidth() - clip.Right;
		if (y + srcRect.GetHeight() > clip.Bottom)
			srcRect.Bottom -= y + srcRect.GetHeight() - clip.Bottom;

		if (!reversed)
		{
			for (int sy = srcRect.Top; sy < srcRect.Bottom; ++sy)
				for (int sx = srcRect.Left; sx < srcRect.Right; ++sx)
					effect(*this, s.GetPixel(sx, sy), x + sx - srcRect.Left, y + sy - srcRect.Top);
		}
		else
		{
			const int xOffset = srcRect.Left + srcRect.Right - 1;
			for (int sy = srcRect.Top; sy < srcRect.Bottom; ++sy)
				for (int sx = srcRect.Left; sx < srcRect.Right; ++sx)
					effect(*this, s.GetPixel(xOffset - sx, sy), x + sx - srcRect.Left, y + sy - srcRect.Top);
		}
	}

	void DrawRect(int x0, int y0, int x1, int y1, Color c);
	void DrawRectDim(int x, int y, int width, int height, Color c)
	{
		DrawRect(x, y, x + width, y + height, c);
	}
	void DrawCircle(int xCenter, int yCenter, int radius, Color c, int innerRadius = 0);
	void DrawIsoRightTriUL(int x, int y, int size, Color c);
	void DrawIsoRightTriUR(int x, int y, int size, Color c);
	void DrawIsoRightTriBL(int x, int y, int size, Color c);
	void DrawIsoRightTriBR(int x, int y, int size, Color c);
	~Graphics();
	static RectF GetScreenRectF();
	static RectI GetScreenRectI();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture = {};
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};