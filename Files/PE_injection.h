#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "pch.h"

HANDLE get_process_handle(DWORD pid);
bool PE_injection(unsigned char shellcode[], const int shellcode_size, HANDLE process_handle);