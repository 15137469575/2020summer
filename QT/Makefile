INCULDE = /I "E:\QT5.14\Qt\Qt-5.14.0\include"

LIBS = /LIBPATH:"E:\QT5.14\Qt\Qt-5.14.0\lib" /DYNAMICBASE "Qt5Widgets.lib" "Qt5Gui.lib" "Qt5Core.lib"

CL_ARGS = /EHsc /MD /source-charset:utf-8 /execution-charset:utf-8 /nologo

LINK_ARGS = /MACHINE:X64 /NOLOGO

main:main.cpp
	@cl /c $(CL_ARGS) /Fo:main.obj $(INCULDE) main.cpp
	@link $(LINK_ARGS) $(LIBS) /OUT:main.exe main.obj

clean:
	@del *.exe *.obj *.exp 2>/Nul

