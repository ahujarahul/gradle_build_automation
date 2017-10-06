#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int status, child_pid, isCurrDirChanged;
	pid_t pid;
  char *projectDirectory = "/Users/rahulahuja/AndroidProjects/gonogo-android";
  isCurrDirChanged = chdir (projectDirectory);

  if (isCurrDirChanged == 0) {
    printf("Inside project directory\n");

    //clean project
    system("./gradlew clean");

    child_pid = fork();
    if(child_pid == 0)
  	{
      //provide build variant to build
  		system("./gradlew assembledmiDebugPreProd");
      printf("End of child process\n");
  	}
  	else
  	{
  		pid = waitpid(child_pid , &status, 0);
  		printf("Child process having PID %d terminates with exit status %d\n",pid,status);
  		printf("Execution of parent process completed.\n");
  	}

  }else{
    printf("Could not access project directory\n");
  }

	return 0;
}
