/**
 * Part of WinLamb - Win32 API Lambda Library
 * https://github.com/rodrigocfd/winlamb
 * Copyright 2017-present Rodrigo Cesar de Freitas Dias
 * This library is released under the MIT License
 */

#pragma once
#include <Windows.h>

namespace wl {

// Common ground to everything which has a HWND.
// Actually, to follow the convention, it should be named base_wnd_pubm.
class wnd {
private:
	const HWND& _hWnd;

public:
	wnd(const HWND& hWnd) noexcept : _hWnd(hWnd) { }

	// Swap Window Buffers
	void swapbuffers ( ) const noexcept {
		SwapBuffers ( GetDC ( _hWnd ) ) ;
	}

	// Show Window
	void show ( ) const noexcept {
		ShowWindow ( _hWnd , SW_SHOW ) ;
	}

	// Hide Window
	void hide ( ) const noexcept {
		ShowWindow ( _hWnd , SW_HIDE );
	}

	// Minimize Window
	void minimize ( ) const noexcept {
		ShowWindow ( _hWnd , SW_MINIMIZE );
	}

	// Maximize Window
	void maxmize ( ) const noexcept {
		ShowWindow ( _hWnd , SW_MAXIMIZE );
	}
	
	// get client size
	SIZE clientsize ( ) const noexcept {
		RECT rect;
		GetClientRect ( _hWnd , &rect ) ;
		return { rect.right - rect.left , rect.bottom - rect.top } ;
	}

	// get window size
	SIZE windowsize ( ) const noexcept {
		RECT rect;
		GetWindowRect ( _hWnd , &rect );
		return { rect.right - rect.left , rect.bottom - rect.top };
	}

	// Is Window Shown
	bool shown ( ) const noexcept {
		return IsWindowVisible ( _hWnd ) ;
	}

	// Returns the window handle.
	HWND hwnd() const noexcept {
		return this->_hWnd;
	}
};

}//namespace wl
