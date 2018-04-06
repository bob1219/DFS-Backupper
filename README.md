DFS-Backupper
=============
DFS-Backupper is a backupper project.

Development Environment
-----------------------
* Operating System: Microsoft Windows 10
* Programming Language: C++
* Builder: Microsoft Visual Studio 2017
* Makefile: Microsoft nmake

Usage
-----
`backup [command] <arguments>`  
Please look at chapter "Commands".

Commands
--------
* clear  
	* Description: Clear setting file
	* Usage: `backup clear [setting-name]`

* add  
	* Description: Addition a setting to setting file

	* Options
		* -d  
		Addition a directory setting

		* -f  
		Addition a file setting

	* Usage: `backup add [setting-name] [-d|-f] [from] [to]`

* list
	* Description: Print list of settings
	* Usage: `backup list [setting-name]`

* run
	* Description: Run backup
	* Usage: `backup run [setting-name]`

* remove
	* Description: Remove a setting

	* Options
		* -d  
		Remove a directory setting

		* -f  
		Remove a file setting

	* Usage: `backup remove [setting-name] [-d|-f] [from] [to]`

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
	* LogFile.cpp
	* copy\_file.cpp

* Header file
	* DirSetting.h
	* FileSetting.h
	* setting.h
	* exception.h
	* constant.h
	* function.h
	* LogFile.h

* Other
	* .gitignore
	* LICENSE
	* boost/
	* makefile
	* logs/
	* settings/
	* backup.exe
	* README.md

History
-------
* 1.0 (February 11th, 2018)
	* First version

* 2.0 (February 11th, 2018)
	* Addition multi setting

* 2.1 (February 12th, 2018)
	* Modify designs

* 3.0 (February 18th, 2018)
	* Addition remove command

* 3.1 (February 24th, 2018)
	* Modify designs

* 3.2 (March 3rd, 2018)
	* Modify designs

* 4.0 (March 4th, 2018)
	* Introduction effecient backup

* 5.0 (March 17th, 2018)
	* Apply effecient backup to directory backup

* 5.1 (March 18th, 2018)
	* Modify designs

* 5.2 (March 20th, 2018)
	* Modify designs

* 5.3 (March 28th, 2018)
	* Modify designs

* 5.4 (March 31st, 2018)
	* Modify designs

* 6.0 (April 6th, 2018)
	* Addition log feature

License
-------
Copyright 2018 Daiki Yoshida. All rights reserved.  
This program and its source file and header file are licensed by GNU-GPL v3.0.  
You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).  
