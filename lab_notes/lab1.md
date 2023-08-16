# 1. sleep:

## 1.1 code structure:
    
1.1.1 kernel: contains implementation of kernel code.  
1.1.2 user: contains all user level apps, e.g. cat, echo, ls, the shell etc.[note: on a real linux os, "ls" and "vscode" are both user level apps, although one is easy the other one is complex]
## 1.2 app working flow:
1.2.1 you enter a string into shell(which is a app itself). [e.g. enter "sleep" to shell]  
1.2.2 the shell recognize the string, then run for you the corresponding app code (file of .c)[e.g. it runs sleep.c file in /user/sleep.c]   
1.2.3 the real app is on and do the work. [the app sleep.c pauses the os for some time]
## 1.3 working mechanism
1.3.1 inside the app source file, system call is invoked [e.g. inside sleep.c there is a system call wrapper function "sleep(time)"]    
![image](https://github.com/youya199/xv6_exercise/assets/94166804/0a3fdc1b-a8fe-4a74-8914-f60c0410cdac)

1.3.2 the system calls which can be used in app source code are listed in user/user.h, for convenience of app source code developers. [e.g. it declares the system call wrapper int sleep(int); telling developers infos like input parameters]   
![image](https://github.com/youya199/xv6_exercise/assets/94166804/7ce74a10-65db-4691-b452-a9d396927927)


1.3.3 once a system call is invoked by this wrapper, it first goes to kernel mode then execute system call code in kernel. 
First, a mode switch is done by executing a switching assembler code in user/usys.S, in order to switch executing mode from user mode(limited resource access) to kernel mode(all resource access)  
![image](https://github.com/youya199/xv6_exercise/assets/94166804/2aab7869-bb88-4416-924f-7575213f6b9f)   
Second, execute system call in kernel.[the sleep function in this code is different from the system call wrapper which is listed in user/user.h, but rather it is a kernel function, only execute in kernel mode!]  
![image](https://github.com/youya199/xv6_exercise/assets/94166804/24535fd8-8927-4914-9b6a-2733a5e3c306)
