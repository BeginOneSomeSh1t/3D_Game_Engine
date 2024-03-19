#pragma once

//target Windows 7 or later;
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>
//The following #defines disable a bunch of unused windows stuff. If you
//get weird errors when trying to do some windows stuff, try removeing some
//(or all) of these defines (It will increase the build time though)


//DEFINES
#ifndef FULL_WINTARD
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#endif //FULL_WINTARD

#define NOMINMAX

#define STRICT

#include <Windows.h>