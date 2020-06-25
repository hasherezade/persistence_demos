# com_hijack

Persistence by COM hijacking. Read more [here](https://speakerdeck.com/hshrzd/wicked-malware-persistence-methods?slide=43).

Hijacks <i>CLSID_MMDeviceEnumerator</i> (CLSID: {BCDE0395-E52F-467C-8E3D-C4579291692E}), used i.e. by Firefox. As a result, the demo DLL is loaded along with the application using the COM.
<br/><br/>
<b>WARNING:</b> This application affects execution flow of the programs. Please use it at your own risk and responsibility. In order to avoid unwanted changes, deploy it on a Virtual Machine.<br/>
Compiled exe (32 bit): https://www.hybrid-analysis.com/sample/e624863387832c7bbe47d17a346aab6a76638a2c9b5368fd7308a28775f1478a?environmentId=100
