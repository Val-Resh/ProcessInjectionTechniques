#include "pch.h"
#include "process_enumeration.h"


using namespace std;

bool validate_list(list<DWORD> pids_list) {
	return pids_list.size() > 0;
}

list<DWORD> enumerate_processes() {
	list<DWORD> pids_list;
	HANDLE process_snapshot = get_process_snapshot();
	if (process_snapshot != NULL) {
		pids_list = get_pids_list(process_snapshot);
	}
	return pids_list;
}

HANDLE get_process_snapshot() {
	HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (process_snapshot == INVALID_HANDLE_VALUE) {
		DWORD error_code = GetLastError();
		if (error_code == ERROR_ACCESS_DENIED) {
			cout << "Access Denied. Error code: " << error_code << endl;
			return NULL;
		}
		else {
			cout << "Error code:" << error_code << endl;
			return NULL;
		}
	}
	return process_snapshot;
}

list<DWORD> get_pids_list(HANDLE process_snapshot) {
	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(PROCESSENTRY32);
	list<DWORD> pids_list;
	
	if (!Process32First(process_snapshot, &process_entry)) {
		cout << "Process32First() function failed." << endl;
		CloseHandle(process_snapshot);
		return pids_list;
	}

	do {
		pids_list.push_back(process_entry.th32ProcessID);
	} while (Process32Next(process_snapshot, &process_entry));

	CloseHandle(process_snapshot);
	return pids_list;
}