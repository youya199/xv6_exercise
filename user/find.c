#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void
find(char *path, char* name_entry)//path is a directory, not a concrete file(although in linus all is file)
{
  char buf[512], *p;//buf used as base path string "path/", p points to the byte after '/' as a starting point for adding further path names
  int fd,fd2;//fd is for current directory, fd2 is for the directory entries
  struct dirent de;
  struct stat st;

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
	  printf("ls: path too long\n");
	  exit(1);
  }
  if((fd = open(path, 0)) < 0){
	  fprintf(2, "ls: cannot open %s\n", path);
	  return;
  }//fd is assigned, directory is open
  
  strcpy(buf, path);
  p = buf + strlen(buf);//p points to the '\0' place
  *p++ = '/';//now buffer is "path/" without '\0', p points to the place after '/'

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
	  if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
		  continue;
	  memmove(p, de.name, DIRSIZ) ;//now buffer is a string of "path/entry_x"
	  if((fd2 = open(buf, 0)) < 0){
		  fprintf(2, "inside swich: cannot open %s\n", buf);
		  return;
	  }//now open the this entry file, assign fd2

	  if(fstat(fd2, &st) < 0){
		  fprintf(2, "ls: cannot stat %s\n", buf);
		  close(fd2);
		  return;
	  }//retrieve info about this entry file, save it in st
	  close(fd2);
	  switch(st.type){
		  case T_DEVICE:
		  case T_FILE:
			  if(!strcmp(de.name, name_entry))printf("%s\n",buf);
			  break;

		  case T_DIR:
			  find(buf, name_entry);	
			  break;
	  }

  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc <= 2){
    find(".", argv[1]);
    exit(0);
  }
  find(argv[1], argv[2]);
  exit(0);
}
