INCLUDES = /I "E:\QT5.14\Qt\Qt-5.14.0\include"

LIBS     = /LIBPATH:"E:\QT5.14\Qt\Qt-5.14.0\lib" \
           /DYNAMICBASE  \
	         "Qt5Widgetsd.lib"  \
		     "Qt5Guid.lib" \
		     "Qt5Cored.lib"
CL_ARGS  = /EHsc \
           /MDd \
		   /source-charset:utf-8 \
		   /execution-charset:utf-8 \
		   /nologo
LINK_ARGS = /MACHINE:X64  /NOLOGO 

main:main.cpp thapp.cpp thdialog.cpp thfish.cpp
	@cl /c $(CL_ARGS) /Fo:main.obj  $(INCLUDES) main.cpp
	@cl /c $(CL_ARGS) /Fo:app.obj  $(INCLUDES) thapp.cpp
	@cl /c $(CL_ARGS) /Fo:dialog.obj  $(INCLUDES) thdialog.cpp
	@cl /c $(CL_ARGS) /Fo:fish.obj  $(INCLUDES) thfish.cpp
	@cl /c $(CL_ARGS) /Fo:moc_fish.obj  $(INCLUDES) moc_thfish.cpp
	@link $(LINK_ARGS) $(LIBS) /OUT:main.exe  main.obj app.obj dialog.obj fish.obj moc_fish.obj

moc:
	@moc -o moc_thfish.cpp thfish.h

clean:
	@del *.exe *.obj *.exp moc_*.obj 2>/Nul

# 如果出现 qt.qpa.plugin: Could not find the Qt platform plugin "windows" in ""
# 解决办法：windeployqt  main.exe


# https://doc.qt.io/qt-5/stylesheet-reference.html