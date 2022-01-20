/**
 * Part of WinLamb - Win32 API Lambda Library
 * https://github.com/rodrigocfd/winlamb
 * Copyright 2017-present Rodrigo Cesar de Freitas Dias
 * This library is released under the MIT License
 */

#pragma once
#include <crtdbg.h>
#include <Windows.h>
#include <CommCtrl.h>
#include "lippincott.h"

#pragma comment(lib, "Comctl32.lib")

#include <ratio>
#include <chrono>

std::chrono::time_point<std::chrono::system_clock> t0 ;

namespace wl {
namespace _wli {

template<typename wnd_mainT>
int run_main(HINSTANCE hInst, int cmdShow) noexcept {
	int ret = 0;
	try { // any exception which was not caught, except those from within message lambdas
		wnd_mainT wndMain;
		ret = wndMain.winmain_run(hInst, cmdShow);
	} catch (...) {
		lippincott();
		ret = -1;
	}
	_ASSERT(!_CrtDumpMemoryLeaks());
	return ret;
}

}//namespace _wli
}//namespace wl

double elapsed ( ) {
	std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now ( );
	return std::chrono::duration<double> ( t1 - t0 ).count ( );
}

// Instantiates your main class into a generic WinMain function.
#define RUN(wnd_mainT) \
int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int cmdShow) { \
	t0 = std::chrono::system_clock::now(); \
	return wl::_wli::run_main<wnd_mainT>(hInst, cmdShow); \
}