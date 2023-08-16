1. sleep:
    1.1 code structure:
        1.1.1 kernel: contains implementation of kernel code.
        1.1.2 user: contains all user level apps, e.g. cat, echo, ls, the shell etc.[note: on a real linux os, "ls" and "vscode" are both user level apps, although one is easy the other one is complex]
    1.2 app working flow:
        1.2.1 you enter a string into shell(which is a app itself). [e.g. enter "sleep" to shell]
        1.2.2 the shell recognize the string, then run for you the corresponding app code (file of .c)[e.g. it runs sleep.c file in /user/sleep.c] 
        1.2.3 the real app is on and do the work. [the app sleep.c pauses the os for some time]
    1.3 working mechanism
        1.3.1 inside the app source file, system call is invoked [e.g. inside sleep.c there is a system call wrapper function "sleep(time)"]
        1.3.2 the system calls which can be used in app source code are listed in user/user.h, for convenience of app source code developers. [e.g. it declares the system call wrapper int sleep(int); telling developers infos like input parameters]
        1.3.3 once a system call is invoked by this wrapper, it is executed in kernel mode. For this, a mode switch is done by executing a switching assembler code in user/usys.S, in order to switch executing mode from user mode(limited resource access) to kernel mode(all resource access)
