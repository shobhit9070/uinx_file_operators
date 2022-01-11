#include<stdio.h>      //baisc input output 
#include<sys/stat.h>   //stat file
#include<stdbool.h>    //bool type file
#include<unistd.h>     //for reading 
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

bool file_exists(char *filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0 );

}

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	if(file_exists(argv[1])){
		int fd = open(argv[1],O_RDONLY );
		//printf("fd = %d",fd);
		if(fd < 0 )
		{
			perror("Can not open file\n");
			exit(1);
		}

		char buf[1000];
		int sz = read(fd,buf,999);
		buf[sz] = '\0';
		printf("the bytes are as follows: %s \n",buf);

		
	}
	else
	{
		int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0755);
		if(fd < 0)
		{
			perror("can not open the file\n");
			exit(1);
		}

		int wr = write(fd,"hello world\n",strlen("hello world\n"));
		char buf2[100];
		int fd2 = open(argv[1],O_RDONLY);
		int sz2 = read(fd2,buf2,90);
		buf2[sz2] = '\0';
		printf("the bytes of the newly created file are as follow = %s\n",buf2);

	}

	struct stat fileStat;
	if(stat(argv[1],&fileStat) < 0 )
	{
		perror("stat error");
		exit(1);
	}

	printf("required information for the file %s\n ",argv[1]);
	printf("file size : \t\t %d bytes\n",fileStat.st_size);
	printf("File inode : \t\t %d \n", fileStat.st_ino);
	
		

	return 0;
}

