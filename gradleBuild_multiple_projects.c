#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void buildProject(int buildVariant, char *projectDir);

int main()
{
	int buildVariant;
  char *projectDirectoryDMI = "/Users/rahulahuja/AndroidProjects/gonogo-android";
  char *projectDirectoryHDBFS = "/Users/rahulahuja/AndroidProjects/hdbfs_android";

  printf("Choose from below options :\n 10. HDBFS SIT\n 11. HDBFS UAT\n 12. HDBFS Testing UAT\n 13. HDBFS Pre Prod\n 14. HDBFS Production\n 100. DMI SIT\n 101. DMI UAT\n 102. DMI Pre Prod\n 103. DMI Production\n");

  scanf("%d", &buildVariant);

  if (buildVariant >= 10 && buildVariant <= 14) {
    buildProject(buildVariant, projectDirectoryHDBFS);
  }
  else if (buildVariant >= 100) {
    buildProject(buildVariant, projectDirectoryDMI);
  }

	return 0;
}//main


void buildProject(int buildVariant, char *projectDir){
  int isCurrDirChanged, child_pid, status;
  pid_t pid;

  isCurrDirChanged = chdir(projectDir);
  printf("%s\n", projectDir);

  if (isCurrDirChanged == 0) {

    system("./gradlew clean");
    printf("CLEAN SUCCESSFUL\n");

    child_pid = fork();
    if(child_pid == 0)
  	{
      if (buildVariant >= 10 && buildVariant <= 14) {
        //HDBFS build
        switch (buildVariant) {
            case 10:
              system("./gradlew assemblesitTestingDebug");
              printf("BUILD SUCCESSFUL\n");
              break;

            case 11:
              system("./gradlew assembleuatDebug");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 12:
              system("./gradlew assembleuatTestingDebug");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 13:
              system("./gradlew assemblepreProductionURLDebug");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 14:
              system("./gradlew assembleserviceURLDebug");
							printf("BUILD SUCCESSFUL\n");
              break;

						default:
							printf("BUILD VARIANT NOT FOUND. FAILURE\n");
							break;
        }
      }
      else if (buildVariant >= 100) {
        //DMI build
        switch (buildVariant) {
            case 100:
              system("./gradlew assembledmiDebugSIT");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 101:
              system("./gradlew assembledmiDebugUAT");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 102:
              system("./gradlew assembledmiDebugPreProd");
							printf("BUILD SUCCESSFUL\n");
              break;

            case 103:
              system("./gradlew assembledmiDebugProduction");
							printf("BUILD SUCCESSFUL\n");
              break;

						default:
							printf("BUILD VARIANT NOT FOUND. FAILURE\n");
							break;
        }
      }
  	}
  	else
  	{
  		pid = waitpid(child_pid , &status, 0);
  	}
  }else{
    printf("Could not access project directory\n");
  }
}//buildProject
