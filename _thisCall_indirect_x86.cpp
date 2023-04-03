#include <windows.h>
#include <iostream>

using pseudoConst = void*( __thiscall* )(void*, int, int, const char*);
using oAdd = int( __thiscall* )(void*, int, int, int);
using oprint = void( __thiscall* )(void* pThis);

DWORD WINAPI myThreadProc( HMODULE hInstDLL )
{
	AllocConsole( ); // To allocate console for logging
	FILE* f;
	freopen_s( &f, "CONOUT$", "w", stdout );
	std::cout << "Yo Hitbokx here!!\n";

	uintptr_t moduleBase{ (uintptr_t)GetModuleHandle( NULL ) };
	void* pThis{ (void*)(0x12FEEC) };

	pseudoConst constructor{ (pseudoConst)(moduleBase + 0x1720) };
	oAdd add{ (oAdd)(moduleBase + 0x1A50) };
	oprint print{ (oprint)(moduleBase + 0x19D0) };

	while ( !GetAsyncKeyState( VK_END ) & 1 )
	{
		if ( GetAsyncKeyState( VK_NUMPAD3 ) & 1 )
		{ 
			constructor( pThis, 1337, 1234, "Hitbokxx HACKS" );
			int result{ add( 0, 0, 0 ) };
			std::cout << result << '\n';
		}
		Sleep( 5 );
	}
	//unload of Dll and reource deallocation code.

	if ( f )
		fclose( f );
	FreeConsole( );
	FreeLibraryAndExitThread( hInstDLL, 0 );//to call DLL_PROCESS_DETACH and resource deallocation
	return 0;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:

			::DisableThreadLibraryCalls( hinstDLL );
			CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( myThreadProc ), hinstDLL, 0, nullptr );
			break;

		case DLL_PROCESS_DETACH:
			//perform any necesary clean-up
			break;

	}
	return TRUE; //Succesful DLL_PROCESS_ATTACH
}