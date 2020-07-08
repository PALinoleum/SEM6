@echo off
REM Это комментарий.
REM %название переменной% - обращение к переменной.

REM ---------------------------------------------
REM Эти переменные можно и нужно менять.
REM ---------------------------------------------
REM project_name - имя исполняемого файла
REM tc_path - абсолютный путь к папке с Turbo C++ (смотри в .conf файлы)
REM source_files - исходные .c файлы через пробел
REM obj_files - файлы который получаются после компиляции, у меня совпали с .c файлами
REM ---------------------------------------------
set project_name=test
set tc_path=d:\tc
set source_files=ipx.c main.c 
set obj_files=ipx_init.obj ipx.obj main.obj

REM ---------------------------------------------
REM Эти переменные менять не стоит.
REM ---------------------------------------------
REM tc_bin_path - путь к папке bin, Turbo C++
REM tc_lib_path - путь к папке lib, Turbo C++
REM tc_inc_path - путь к папке include, Turbo C++
REM cxx_flags - флаги компиляции tcc
REM link_flags - флаги линковки tlink
REM ---------------------------------------------
set tc_bin_path=%tc_path%\bin
set tc_lib_path=%tc_path%\lib
set tc_inc_path=%tc_path%\include
set cxx_flags=-I%tc_bin_path% -c -mt %source_files%
set link_flags=-L%tc_lib_path% %tc_lib_path%\c0t.obj %obj_files%,%project_name%.com,%project_name%.map,cs.lib 

REM ---------------------------------------------
REM Непосредственно скрипт сборки.
REM ---------------------------------------------

%tc_bin_path%\tcc %cxx_flags% 
%tc_bin_path%\tlink %link_flags% 
if errorlevel 0 echo Сборка завершена успешно. Исполняемый файл - %project_name%.com