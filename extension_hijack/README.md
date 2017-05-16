# extension_hijacker
Demo of a possible malware persistence method. Hijacking extensions registered for the current user.
+ <b>proxy_app</b> - a proxy application, used to handle hijacked extensions
+ <b>hijacker_app</b> - installs the proxy application and redirects extension handling to the proxy

<b>WARNING:</b> This application affects execution flow of the programs. Please use it at your own risk and responsibility. In order to avoid unwanted changes, deploy it on a Virtual Machine.<br/>
Compiled exe (32 bit): https://drive.google.com/open?id=0Bzb5kQFOXkiSWW1SS01yeUhYeDg
