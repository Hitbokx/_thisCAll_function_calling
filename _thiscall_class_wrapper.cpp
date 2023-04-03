#include <windows.h>
#include <iostream>

uintptr_t moduleBase{ (uintptr_t)GetModuleHandle( NULL ) };

class funcDummy
{
private:
	int m_x{ 1337 };
	int m_y{ 1234 };
	const char* m_c{ "Hitbokxx HACKS" };

public:
	funcDummy( int x, int y, const char* c ) :m_x{ 1337 }, m_y{ 1234 }, m_c{ "Hitbokxx HACKS" }{}

	int funcMathDummy( int a, int b, int c )
	{
		a = 0;
		b = 0;
		c = 0;

		using FncPtr = int( __thiscall* )(void*, int, int, int);
		FncPtr fncPtr{ (FncPtr)(moduleBase + 0x1A50) };

		return fncPtr( this, a, b, c );
	}

	void func( )
	{
		using FncPtr = void( __thiscall* )(void* pThis);
		FncPtr fncPtr{ (FncPtr)(moduleBase + 0x19D0) };

		fncPtr( this );
	}
};

DWORD WINAPI myThreadProc( HMODULE hInstDLL )
{
	AllocConsole( ); // To allocate console for logging
	FILE* f;
	freopen_s( &f, "CONOUT$", "w", stdout );
	std::cout << "Yo Hitbokx here!!\n";

	funcDummy* pFuncDummy{ (funcDummy*)(0x12FEEC) };

	while ( !GetAsyncKeyState( VK_END ) & 1 )
	{
		if ( GetAsyncKeyState( VK_NUMPAD3 ) & 1 )
		{
			std::cout << pFuncDummy->funcMathDummy( 1, 2, 3 ) << '\n';

			pFuncDummy->func( );
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