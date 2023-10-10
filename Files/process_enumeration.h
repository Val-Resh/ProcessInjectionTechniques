#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "pch.h"

std::list<DWORD> enumerate_processes();
HANDLE get_process_snapshot();
std::list<DWORD> get_pids_list(HANDLE process_snapshot);
bool validate_list(std::list<DWORD> pids_list);