#include "sox_platform.h"

#if defined(_WIN32)

// todo: ...

#else

sox_p_result sox_p_init() { return (sox_p_result){ true, NULL }; }
sox_p_result sox_p_shutdown() { return (sox_p_result){ true, NULL }; }

static char const *sox_p_get_error_str()
{
	return strerror(errno);
}

#endif

sox_p_socket_result sox_p_socket()
{
	sox_p_socket_t result = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // todo: use actual params!

	if (result == SOX_P_INVALID_SOCKET)
		return (sox_p_socket_result) { SOX_P_INVALID_SOCKET, sox_p_get_error_str() };

	return (sox_p_socket_result) { result, NULL };
}

sox_p_close_socket_result sox_p_close_socket(sox_p_socket_t s)
{
#if defined(_WIN32)
	int result = closesocket(s);
#else
	int result = close(s);
#endif

	if (result != 0)
		return (sox_p_close_socket_result) { false, sox_p_get_error_str() };

	return (sox_p_close_socket_result) { true, NULL };
}
