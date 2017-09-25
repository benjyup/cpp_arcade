# cpp_arcade
In this project, you will have to create a gaming platform. This platform must include at least two games and must be able to run with three different GUIs. Games and GUIs will be in dynamicly loaded libraries. You must have a small set of games to choose from, as well as a small set of graphics libraries.

For your own culture, it is very important to know several graphic libraries. This is why your final project must provide 3
different graphic libraries. The point of this project being to make you handle dynamic libraries at run-time, the graphic
rendering as well as output must be located within a dynamic library. In order to improve your software design, you
will also have to put your games in dynamic libraries. The body of your program must interact the same way with all
of your libraries.

Each GUI available for the program must be used as a shared library that will be loaded and used dynamically by the main program. It is strictly FORBIDDEN to refer to one graphic library or another in your main program. Only your dynamic libraries can do it! This also applies to your games.

You must use your dynamic libraries at run-time. This means that you MUST use the
dlopen
,
dlclose
,
dlsym
and
dlerror
functions to handle your dynamic libraries. Dependency to your libraries will not appear when passing your
program as parameter to the command
ldd
.
These dynamic libraries can be seen as plug-ins providing various capabilities for your main program. In NO CASE
must graphic libraries influence the game logic. Game libraries must not contain any information about screen ren-
dering or low level events.
