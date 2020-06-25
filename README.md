# persistence_demos

[![Build status](https://ci.appveyor.com/api/projects/status/wr9barnysm7ovfgi?svg=true)](https://ci.appveyor.com/project/hasherezade/persistence-demos)

Demos for the presentation ["Wicked malware persistence methods"](https://speakerdeck.com/hshrzd/wicked-malware-persistence-methods).

+ <b>com_hijack</b> - loads a demo DLL via COM hijacking
+ <b>extension_hijack</b> - hijacks extensions handlers in order to run a demo app while the file with the given extension is opened
+ <b>shim_persist</b> - installs a shim that injects a demo DLL into explorer.exe
+ <b>restricted_directory</b> - drops a PE into a restricted directory (that cannot be accessed or deleted), and launches it
