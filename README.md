DFS-Backupper
=============
DFS-Backupper is a backupper project.

Development Environment
-----------------------
* Operating System: Microsoft Windows 10
* Programming Language: C++

Usage
-----
`[executable-filename] [command] <arguments>`  
Please look chapter "Commands".

Commands
--------
* clear  
	* Description: Clear setting file
	* Usage: `[executable-filename] clear [setting-name]`

* add  
	* Description: Addition a setting to setting file

	* Options
		* -d  
		Addition directory setting

		* -f  
		Addition file setting

	* Usage: `[executable-filename] add [setting-name] [-d|-f] [from] [to]`

* list
	* Description: Print list of settings
	* Usage: `[executable-filename] list [setting-name]`

* run
	* Description: Run backup
	* Usage: `[executable-filename] run [setting-name]`

Files
-----
* Source file
	* CommandProcess.cpp
	* DirSetting.cpp
	* FileSetting.cpp
	* commands.cpp
	* copy\_directory.cpp
	* exception.cpp
	* main.cpp
	* setting.cpp

* Header file
	* class.h
	* constant.h
	* function.h

* Other
	* .gitignore
	* LICENSE

History
-------
* 1.0 (February 11th, 2018)
	* First version

* 2.0 (February 11th, 2018)
	* Addition multi setting
