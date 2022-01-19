/**
 * Part of WinLamb - Win32 API Lambda Library
 * https://github.com/rodrigocfd/winlamb
 * Copyright 2017-present Rodrigo Cesar de Freitas Dias
 * This library is released under the MIT License
 */

#pragma once
#include <system_error>
#include <vector>
#include <Windows.h>

#define WM_IDLE				WM_APP

namespace wl {
namespace _wli {

// Wraps the main program loop.
class base_loop final {
private:
	std::vector<HWND> _modelessChildren;

public:
	int run_loop(HWND hWnd, HACCEL hAccel = nullptr) const {
		MSG msg { } ;
		BOOL ret = TRUE;
		while ( ret ) {
			while ( PeekMessage ( &msg , hWnd , 0 , 0 , PM_REMOVE ) ) {
				if ( ret == -1 ) {
					throw std::system_error ( GetLastError ( ) , std::system_category ( ) ,
								  "GetMessage failed" );
				}
				if ( msg.message == WM_QUIT )
					ret = FALSE;
				if ( this->_is_modeless_msg ( &msg ) ||
				     ( hAccel && TranslateAcceleratorW ( hWnd , hAccel , &msg ) ) ||
				     IsDialogMessageW ( hWnd , &msg ) )
					continue;
				TranslateMessage ( &msg );
				DispatchMessageW ( &msg );
			}
			SendMessageW ( hWnd , WM_IDLE , NULL , NULL ) ;
		}
		return static_cast<int>(msg.wParam); // this can be used as program return value
	}

	void add_modeless(HWND hWnd) {
		this->_modelessChildren.emplace_back(hWnd);
	}

	void remove_modeless(HWND hWnd) {
		for (std::vector<HWND>::iterator it = this->_modelessChildren.begin();
			it != this->_modelessChildren.end(); ++it)
		{
			if (*it == hWnd) {
				this->_modelessChildren.erase(it);
				break;
			}
		}
	}

private:
	bool _is_modeless_msg(MSG* pMsg) const noexcept {
		for (const HWND hModl : this->_modelessChildren) {
			if (!hModl || !IsWindow(hModl)) continue; // skip invalid HWND
			if (IsDialogMessageW(hModl, pMsg)) return true;
		}
		return false;
	}
};

}//namespace _wli
}//namespace wl
