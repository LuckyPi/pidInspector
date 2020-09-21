# pidInspector 
dll/exe Hijack easy verification tool.

## Summary
pidInspector makes dll/exe hijack verification easy. Aids in vulnerability research by identifying the immediate executing application commonly used in dll/exe hijacking. 

## Features
pidInspector.exe and pidInspector_dll.dll log the executing DateTime, userID, it's path, it's PID, parent application fullPath, parentPID and if the process has writeAccess to the system folder. The appendable log file is created in the public writable documents folder C:\Users\Public\Documents\pidInspector.txt

pidInspector makes for a nice rapid way of verifying hijack conditions without having to generate Metasploit, CobaltStrike, other payloads and virtual environments, etc.

## Usage
Find your suspect hijack using [Process Monitor](https://docs.microsoft.com/en-us/sysinternals/downloads/procmon) or your tool of preference. Here are two great blogs on dll hijacking.
<br> 
https://hacknpentest.com/windows-privilege-escalation-dll-hijacking/
<br>
https://pentestlab.blog/2017/03/27/dll-hijacking/

Rename pidInspector to the missing dll/exe name and place in the search path. You can download pidInspector precompiled binaries [here](https://github.com/LuckyPi/pidInspector/releases/latest). The dllLoad.exe application is for testing the pidInspector_dll.dll without preforming a hijack.   
  

*I strongly suggest limiting pidInspector to the applications folder/path and not using Windows, Windows\System, Windows\System32 folders. You may have a hard time removing pidInspector if its a shared dll.* 

**Log output:**  

| dll or exe | date/time                | user  | pidInspector path                        | pidInspector PID | PPID path                   | PPID  | Write to System32 |
|---------|--------------------------|-------|------------------------------------------|------------------|-----------------------------|-------|-------------------|
| dll     | Sun Sep 21 19:20:14 2020 | Inigo | C:\pidInspector\x64\Release\dllLoad.exe  | 14416            | C:\Windows\System32\cmd.exe | 10080 | YES               |
| exe     | Sun Sep 21 19:21:07 2020 | Inigo | C:\pidInspector\x64\Release\pidInspector.exe | 17728            | C:\Windows\explorer.exe     | 9064  | NO                |


## Disclaimer
pidInspector shouldn't cause any issues, there is nothing inherently destructive in this code but I suggest limiting it to testing environments. Please forgive the butchering of C/C++. However use at your own risk. This code is provided for educational purposes ONLY. Developer assume no liability and shall not be held responsible for any damage that may result from use or misuse of the provided code. It's the end users responsibility to obey all applicable local, state, federal and country specific laws.

### Changelog
v1.0 
 * Initial release.

