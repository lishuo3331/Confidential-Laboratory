#include <Windows.h>
#include "Utils.h"

BOOL VMDriverServices();
BOOL get_services(_In_ SC_HANDLE hServiceManager, _In_ DWORD serviceType, _Out_ ENUM_SERVICE_STATUS_PROCESS** serviceBuffer, _Out_ DWORD* serviceCount);
