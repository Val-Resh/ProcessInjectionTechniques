# MITRE ATT&CK Process Injection

This project aims to cover the majority of Window's based process injection techniques. The purpose of this project is to learn how these techniques work programmatically to develop a deeper understanding. The project does not attempt to bypass EDRs, instead it provides the foundations to understand the differences between the different types of process injection. 

The MITRE ATT&CK Process Injection Referece:
https://attack.mitre.org/techniques/T1055/

## Project Status:

- Portable Executable Injection (COMPLETED)
- Thread Execution Hijacking (TODO)
- Asynchronous Procedure Call (TODO)
- Thread Local Storage (TODO)
- Extra Window Memory Injection (TODO)
- Process Hollowing (TODO)
- Process Doppelgänging (TODO)
- ListPlanting (TODO)

## Usage:

The payload to inject into a process must be placed within the main function's variable `shellcode` before compilation. <br>
Ensure the files are compiled to the correct bit architecture. <br>
The current state of the project does not include any commandline arguments, so running the executable does not require any arguments. In the future when additional injection techniques are added, I will include an arguement to specify which technique to use.
