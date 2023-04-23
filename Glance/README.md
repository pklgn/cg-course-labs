# Notes
1. Выбирай Runtime Library Option значение равное Multi-threaded Debug (/MTd) и вместе с ним же собирай проект, использующий Glance
2. Input зависимости для Debug (но подойдут и для Release):
* glfw3.lib
* OpenGL32.lib
* shell32.lib
* glu32.lib
* glew32.lib
* bcrypt.lib
* Glance.lib
3. Из-за проблемы https://stackoverflow.com/questions/18612072/link-warning-lnk4098-defaultlib-msvcrt-conflicts-with-use-of-other-libs-us для Debug x64 версии проекта было принято решение прописать ~~чапалах~~ /NODEFAULTLIB:libcmt.lib в разделе Command Line у Linker'а
4. Для работы с vcpkg используется ```vcpkg install --triplet=x64-windows-static```
