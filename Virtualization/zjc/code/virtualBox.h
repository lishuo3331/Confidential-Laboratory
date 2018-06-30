#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Mpr.lib")

#include "Common.h"
#include "Utils.h"

VOID vbox_reg_key_value();
VOID vbox_reg_keys();
VOID vbox_files();
BOOL vbox_dir();

BOOL vbox_check_mac();
VOID vbox_devices();
BOOL vbox_window_class();
BOOL vbox_network_share();
VOID vbox_processes();
BOOL vbox_eventlogfile_wmi();
BOOL vbox_firmware_SMBIOS();
BOOL vbox_firmware_ACPI();