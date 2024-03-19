#pragma once

// error exception helper macro
#define MYWND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__, hr)
#define MYWND_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define MYWND_NOGFX_EXCEPT() Window::NoGfxException(__LINE__,__FILE__)