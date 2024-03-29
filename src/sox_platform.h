#pragma once

#include <stdbool.h>

#define RESULT(T, NAME)    \
	typedef struct NAME    \
	{                      \
		T value;           \
		char const *error; \
	}                      \
	NAME;

#if defined(_WIN32)

	#define WIN32_LEAN_AND_MEAN

	#define NOGDICAPMASKS	 // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
	#define NOVIRTUALKEYCODES // VK_*
	#define NOWINMESSAGES	 // WM_*, EM_*, LB_*, CB_*
	#define NOWINSTYLES		  // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
	#define NOSYSMETRICS	  // SM_*
	#define NOMENUS			  // MF_*
	#define NOICONS			  // IDI_*
	#define NOKEYSTATES		  // MK_*
	#define NOSYSCOMMANDS	 // SC_*
	#define NORASTEROPS		  // Binary and Tertiary raster ops
	#define NOSHOWWINDOW	  // SW_*
	#define OEMRESOURCE		  // OEM Resource values
	#define NOATOM			  // Atom Manager routines
	#define NOCLIPBOARD		  // Clipboard routines
	#define NOCOLOR			  // Screen colors
	#define NOCTLMGR		  // Control and Dialog routines
	#define NODRAWTEXT		  // DrawText() and DT_*
	#define NOGDI			  // All GDI defines and routines
	#define NOKERNEL		  // All KERNEL defines and routines
	#define NOUSER			  // All USER defines and routines
	#define NONLS			  // All NLS defines and routines
	#define NOMB			  // MB_* and MessageBox()
	#define NOMEMMGR		  // GMEM_*, LMEM_*, GHND, LHND, associated routines
	#define NOMETAFILE		  // typedef METAFILEPICT
	#define NOMINMAX		  // Macros min(a, b) and max(a, b)
	#define NOMSG			  // typedef MSG and associated routines
	#define NOOPENFILE		  // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
	#define NOSCROLL		  // SB_* and scrolling routines
	#define NOSERVICE		  // All Service Controller routines, SERVICE_ equates, etc.
	#define NOSOUND			  // Sound driver routines
	#define NOTEXTMETRIC	  // typedef TEXTMETRIC and associated routines
	#define NOWH			  // SetWindowsHook and WH_*
	#define NOWINOFFSETS	  // GWL_*, GCL_*, associated routines
	#define NOCOMM			  // COMM driver routines
	#define NOKANJI			  // Kanji support stuff.
	#define NOHELP			  // Help engine interface.
	#define NOPROFILER		  // Profiler interface.
	#define NODEFERWINDOWPOS  // DeferWindowPos routines
	#define NOMCX			  // Modem Configuration Extensions

	#include <winsock2.h>
	#include <ws2tcpip.h>

	#undef WIN32_LEAN_AND_MEAN

	#undef NOGDICAPMASKS	 // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
	#undef NOVIRTUALKEYCODES // VK_*
	#undef NOWINMESSAGES	 // WM_*, EM_*, LB_*, CB_*
	#undef NOWINSTYLES		 // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
	#undef NOSYSMETRICS		 // SM_*
	#undef NOMENUS			 // MF_*
	#undef NOICONS			 // IDI_*
	#undef NOKEYSTATES		 // MK_*
	#undef NOSYSCOMMANDS	 // SC_*
	#undef NORASTEROPS		 // Binary and Tertiary raster ops
	#undef NOSHOWWINDOW		 // SW_*
	#undef OEMRESOURCE		 // OEM Resource values
	#undef NOATOM			 // Atom Manager routines
	#undef NOCLIPBOARD		 // Clipboard routines
	#undef NOCOLOR			 // Screen colors
	#undef NOCTLMGR			 // Control and Dialog routines
	#undef NODRAWTEXT		 // DrawText() and DT_*
	#undef NOGDI			 // All GDI defines and routines
	#undef NOKERNEL			 // All KERNEL defines and routines
	#undef NOUSER			 // All USER defines and routines
	#undef NONLS			 // All NLS defines and routines
	#undef NOMB				 // MB_* and MessageBox()
	#undef NOMEMMGR			 // GMEM_*, LMEM_*, GHND, LHND, associated routines
	#undef NOMETAFILE		 // typedef METAFILEPICT
	#undef NOMINMAX			 // Macros min(a, b) and max(a, b)
	#undef NOMSG			 // typedef MSG and associated routines
	#undef NOOPENFILE		 // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
	#undef NOSCROLL			 // SB_* and scrolling routines
	#undef NOSERVICE		 // All Service Controller routines, SERVICE_ equates, etc.
	#undef NOSOUND			 // Sound driver routines
	#undef NOTEXTMETRIC		 // typedef TEXTMETRIC and associated routines
	#undef NOWH				 // SetWindowsHook and WH_*
	#undef NOWINOFFSETS		 // GWL_*, GCL_*, associated routines
	#undef NOCOMM			 // COMM driver routines
	#undef NOKANJI			 // Kanji support stuff.
	#undef NOHELP			 // Help engine interface.
	#undef NOPROFILER		 // Profiler interface.
	#undef NODEFERWINDOWPOS  // DeferWindowPos routines
	#undef NOMCX			 // Modem Configuration Extensions

	typedef SOCKET sox_p_socket_t;
	
	#define SOX_P_INVALID_SOCKET INVALID_SOCKET
	#define SOX_P_SOCKET_ERROR SOCKET_ERROR

#else

	#include <arpa/inet.h>
	#include <errno.h>
	#include <netdb.h>
	#include <string.h>
	#include <sys/ioctl.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h>

	typedef int sox_p_socket_t;
	
	#define SOX_P_INVALID_SOCKET -1
	#define SOX_P_SOCKET_ERROR -1

#endif

RESULT(bool, sox_p_result)
sox_p_result sox_p_init();
sox_p_result sox_p_shutdown();

RESULT(sox_p_socket_t, sox_p_socket_result)
sox_p_socket_result sox_p_socket();

RESULT(bool, sox_p_close_socket_result)
sox_p_close_socket_result sox_p_close_socket();
