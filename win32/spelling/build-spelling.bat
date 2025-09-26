:: run this from a command prompt
:: TODO: change it to LocalAppdata when GLib is updated
@echo off

set DEPS_ROOT=C:\mozilla-build\rubirc
set SPELLING_DEST=..\build\spelling

rmdir /q /s %SPELLING_DEST%
mkdir %SPELLING_DEST%
xcopy /q /s /i %DEPS_ROOT%\myspell\dicts %SPELLING_DEST%\myspell
cd ..
echo [Setup] > build\spelling\rubirc-spelling.iss
echo WizardImageFile=%cd%\installer\wizardimage.bmp >> build\spelling\rubirc-spelling.iss
echo WizardSmallImageFile=%cd%\installer\wizardsmallimage.bmp >> build\spelling\rubirc-spelling.iss
cd ..\share\icons
echo SetupIconFile=%cd%\rubirc.ico >> win32\build\spelling\rubirc-spelling.iss
cd ..\..
type win32\spelling\rubirc-spelling.skel.iss >> win32\build\spelling\rubirc-spelling.iss
set PATH=%PROGRAMFILES(X86)%\Inno Setup 5
compil32 /cc win32\build\spelling\rubirc-spelling.iss
cd win32\spelling
pause
