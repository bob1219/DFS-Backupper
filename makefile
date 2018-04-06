# macro
COMP = cl
LINK = link
OPTIONS = /EHsc /I.
EXE = backup.exe

# suffix rule
.cpp.obj:
	$(COMP) /Fe$@ /c $< $(OPTIONS)

$(EXE): FileSetting.obj DirSetting.obj setting.obj main.obj commands.obj CommandProcess.obj copy_directory.obj copy_file.obj LogFile.obj
	$(LINK) /out:$@ $** /LIBPATH:.\boost

FileSetting.obj: FileSetting.cpp FileSetting.h
DirSetting.obj: DirSetting.cpp DirSetting.h
setting.obj: setting.cpp setting.h exception.h constant.h
main.obj: main.cpp function.h exception.h
commands.obj: commands.cpp function.h constant.h FileSetting.h DirSetting.h exception.h
CommandProcess.obj: CommandProcess.cpp function.h exception.h
copy_directory.obj: copy_directory.cpp function.h constant.h
copy_file.obj: copy_file.cpp function.h
LogFile.obj: LogFile.cpp LogFile.h constant.h exception.h
