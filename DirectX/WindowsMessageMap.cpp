#include "WindowsMessageMap.h"
#include <string>
#include <sstream>
#include <iomanip>


//secret messages
#define WM_UAHDESTROYWINDOW 0x0090
#define WM_UAHDRAWMENU 0x0091
#define WM_UAHDRAWMENUITEM 0x0092
#define WM_UAHINITMENU 0x0093
#define WM_UAHMEASUREMENUITEM 0x0094
#define WM_UAHNCPAINTMENUPOPUP 0x0095

#define REGISTER_MESSAGE(msg){msg, #msg}


WindowsMessageMap::WindowsMessageMap()
	: map({
			REGISTER_MESSAGE(WM_CREATE),
			REGISTER_MESSAGE(WM_DESTROY),
			REGISTER_MESSAGE(WM_MOVE),
			REGISTER_MESSAGE(WM_SIZE),
			REGISTER_MESSAGE(WM_ACTIVATE),
			REGISTER_MESSAGE(WM_SETFOCUS),
			REGISTER_MESSAGE(WM_KILLFOCUS),
			REGISTER_MESSAGE(WM_ENABLE),
			REGISTER_MESSAGE(WM_SETREDRAW),
			REGISTER_MESSAGE(WM_SETTEXT),
			REGISTER_MESSAGE(WM_GETTEXT),
			REGISTER_MESSAGE(WM_GETTEXTLENGTH),
			REGISTER_MESSAGE(WM_PAINT),
			REGISTER_MESSAGE(WM_CLOSE),
			REGISTER_MESSAGE(WM_QUERYENDSESSION),
			REGISTER_MESSAGE(WM_QUIT),
			REGISTER_MESSAGE(WM_QUERYOPEN),
			REGISTER_MESSAGE(WM_ERASEBKGND),
			REGISTER_MESSAGE(WM_SYSCOLORCHANGE),
			REGISTER_MESSAGE(WM_PRINT),
			REGISTER_MESSAGE(WM_ENDSESSION),
			REGISTER_MESSAGE(WM_SHOWWINDOW),
			REGISTER_MESSAGE(WM_CTLCOLORMSGBOX)
		}) {}

std::string WindowsMessageMap::operator()(DWORD msg, LPARAM lp, WPARAM wp) const
{
	constexpr int firstColWidth = 25;
	const auto i = map.find(msg);

	std::ostringstream oss;
	if (i != map.end())
		oss << std::left << std::setw(firstColWidth) << i->second << std::right;
	else
	{
		std::ostringstream padss;
		padss << "Uknown message: 0x" << std::hex << msg;
		oss << std::left << std::setw(firstColWidth) << padss.str() << std::right;
	}
	oss << "    LP: 0x" << std::hex << std::setfill('0') << std::setw(8) << lp;
	oss << "    WP: 0x" << std::hex << std::setfill('0') << std::setw(8) << wp;
	return oss.str();
}

