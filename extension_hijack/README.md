# extension_hijacker
Demo of a possible malware persistence method. Hijacking extensions registered for the current user. Read more [here](https://speakerdeck.com/hshrzd/wicked-malware-persistence-methods?slide=50)

+ <b>proxy_app</b> - a proxy application, used to handle hijacked extensions
+ <b>hijacker_app</b> - installs the proxy application and redirects extension handling to the proxy

<b>WARNING:</b> This application affects execution flow of the programs. Please use it at your own risk and responsibility. In order to avoid unwanted changes, deploy it on a Virtual Machine.<br/>
Compiled exe (32 bit): https://www.hybrid-analysis.com/sample/12b229c97f4c4675227b35fae4079faf6fc5903590309944bc5d222bbbdd017f?environmentId=100
