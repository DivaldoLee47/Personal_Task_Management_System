
#include "Functions.h"

int main() //main function
{
    int option;
    while (option != 5) {
        printf("================================\n");
        printf("     Personal Task Management\n");
        printf("================================\n");
        printf("\n(1) Add new task\n(2) View all tasks\n(3) Update tasks\n(4) Delete tasks\n(5) Exit Program\n");
        printf("\nSelect option >> ");
        scanf("%d", &option);

        if (option == 1)
            addNewTask();
        else if (option == 2)
            viewAllTasks();
        else if (option == 3)
            updateTasks();
        else if (option == 4)
            deleteTasks();
        else if (option == 5) {
            printf("See you next time!\n");
            break;
        }
        else {
            printf("\nThis option is currently not available. Please try again.\n");
        }
    }
    return 0;
}

void taskStatus(int dueDay, int dueMonth, int dueYear, char *status){
    time_t systime;
    struct tm *curTime;
    time(&systime);
    curTime = localtime(&systime);
    sprintf(viewdate.today, "%d/%02d/%02d", curTime->tm_year+1900, curTime->tm_mon+1, curTime->tm_mday);
    sprintf(viewdate.due, "%d/%02d/%02d", dueYear, dueMonth, dueDay);   

    if(strcmp(viewdate.due, viewdate.today)>0){
        strcpy(status, "Pending");
    }
    else if(strcmp(viewdate.due, viewdate.today)==0){
        strcpy(status, "Due Today");
    }
    else if(strcmp(viewdate.due, viewdate.today)<0){
        strcpy(status, "Late");
    }
}

void viewAllTasks(){
    int choice;
    while (choice != 4) {
        printf("================================\n");
        printf("            View Tasks\n");
        printf("================================\n");
        printf("\n(1) View Tasks Based on Due Date\n(2) View Completed Tasks\n(3) View Ongoing Tasks\n(4) Back\n");
        printf("\nSelect option >> ");
        scanf("%d", &choice);

        if (choice == 1)
            sortTaskDate();
        else if (choice == 2)
            viewDoneTasks();
        else if (choice == 3)
            viewIncompleteTasks();
        else if (choice == 4)
            main();
        else {
            printf("\nThis option is currently not available. Please try again.\n");
        }
    }
}

void sortTaskDate(){
    char sortedDate[100][5][100];
    char temp[5][100];
    char status[100];
    int x=0, y, z;
    int a, b, i, j, k;

    FILE * filep;
    filep = fopen("mytask.txt", "r");

    while(fscanf(filep,"%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^\n]\n", 
                rec.taskID, rec.taskName, rec.category, &rec.dueDay, &rec.dueMonth, &rec.dueYear, rec.status, rec.completedIncomplete) != EOF)
    {
        strcpy(sortedDate[x][0], rec.taskID);
        strcpy(sortedDate[x][1], rec.taskName);
        strcpy(sortedDate[x][2], rec.category);
        strcpy(sortedDate[x][3], rec.completedIncomplete);
        sprintf(sortedDate[x][4], "%d/%02d/%02d", rec.dueYear, rec.dueMonth, rec.dueDay);
        x++;
    }
    
    for(y = 0; y < x; y++)
    {
        for(z = y+1; z < x; z++)
        {
            if(strcmp(sortedDate[y][4], sortedDate[z][4]) > 0)
            {
                for(i = 0; i < 5; i++)
                {
                    strcpy(temp[i], sortedDate[y][i]);
                }
                for(j = 0; j < 5; j++)
                {
                    strcpy(sortedDate[y][j], sortedDate[z][j]);
                }
                for(k = 0; k < 5; k++)
                {
                    strcpy(sortedDate[z][k], temp[k]);
                }
            }
        }
    }

    printf("=========================================================================================\n");
    printf("%-15s\t %-15s\t %-15s %-15s\t%-15s\n", "Task ID", "Task Name", "Category", "Due Date", "Status");
    printf("=========================================================================================\n");

    for(a = 0; a < x; a++)
    {
        sscanf(sortedDate[a][4], "%d/%d/%d\n", &rec.dueYear, &rec.dueMonth, &rec.dueDay);
        taskStatus(rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
        if (strcmp(sortedDate[a][3], "Completed") == 0)
        {
            strcpy(rec.status,"Completed");          
        }
        printf("%-15s\t %-15s\t %-15s %02d/%02d/%d\t        %-15s", 
                sortedDate[a][0], sortedDate[a][1], sortedDate[a][2], rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
        printf("\n\n");
    }
    system("pause");
}

void viewDoneTasks(){
    char sortedDone[100][5][100];
    char temp[5][100];
    char status[100];
    int x=0;
    int a;
    FILE * filep;
    filep = fopen("mytask.txt", "r");
    while(fscanf(filep,"%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^\n]\n", 
                        rec.taskID, rec.taskName, rec.category, &rec.dueDay, &rec.dueMonth, &rec.dueYear, rec.status, rec.completedIncomplete) != EOF)
    {
        strcpy(sortedDone[x][0], rec.taskID);
        strcpy(sortedDone[x][1], rec.taskName);
        strcpy(sortedDone[x][2], rec.category);
        strcpy(sortedDone[x][3], rec.completedIncomplete);
        sprintf(sortedDone[x][4], "%d/%02d/%02d", rec.dueYear, rec.dueMonth, rec.dueDay);
        x++;
    }

    printf("=========================================================================================\n");
    printf("%-15s\t %-15s\t %-15s %-15s\t%-15s\n", "Task ID", "Task Name", "Category", "Due Date", "Status");
    printf("=========================================================================================\n");

    for(a = 0; a < x; a++){
        sscanf(sortedDone[a][4], "%d/%d/%d\n", &rec.dueYear, &rec.dueMonth, &rec.dueDay);
        taskStatus(rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
        if (strcmp(sortedDone[a][3], "Completed") == 0){
            strcpy(rec.status,"Completed"); 
            printf("%-15s\t %-15s\t %-15s %02d/%02d/%d\t        %-15s", 
                sortedDone[a][0], sortedDone[a][1], sortedDone[a][2], rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
            printf("\n\n");         
        }
    }
    system("pause");
}

void viewIncompleteTasks(){
    char sortedDone[100][5][100];
    char temp[5][100];
    char status[100];
    int x=0, y, z;
    int a, b, i, j, k;
    FILE * filep;
    filep = fopen("mytask.txt", "r");
    while(fscanf(filep,"%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^\n]\n", 
                        rec.taskID, rec.taskName, rec.category, &rec.dueDay, &rec.dueMonth, &rec.dueYear, rec.status, rec.completedIncomplete) != EOF)
    {
        strcpy(sortedDone[x][0], rec.taskID);
        strcpy(sortedDone[x][1], rec.taskName);
        strcpy(sortedDone[x][2], rec.category);
        strcpy(sortedDone[x][3], rec.completedIncomplete);
        sprintf(sortedDone[x][4], "%d/%02d/%02d", rec.dueYear, rec.dueMonth, rec.dueDay);
        x++;
    }

    for(y = 0; y < x; y++){
        for(z = y+1; z < x; z++){
            if(strcmp(sortedDone[y][4], sortedDone[z][4]) > 0){
                for(i = 0; i < 5; i++){
                    strcpy(temp[i], sortedDone[y][i]);
                }
                for(j = 0; j < 5; j++){
                    strcpy(sortedDone[y][j], sortedDone[z][j]);
                }
                for(k = 0; k < 5; k++){
                    strcpy(sortedDone[z][k], temp[k]);
                }
            }
        }
    }

    printf("=========================================================================================\n");
    printf("%-15s\t %-15s\t %-15s %-15s\t%-15s\n", "Task ID", "Task Name", "Category", "Due Date", "Status");
    printf("=========================================================================================\n");

    for(a = 0; a < x; a++){
        sscanf(sortedDone[a][4], "%d/%d/%d\n", &rec.dueYear, &rec.dueMonth, &rec.dueDay);
        taskStatus(rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
        if (strcmp(sortedDone[a][3], "Incomplete") == 0){
            strcpy(rec.status,"Incomplete"); 
            printf("%-15s\t %-15s\t %-15s %02d/%02d/%d\t        %-15s", 
                sortedDone[a][0], sortedDone[a][1], sortedDone[a][2], rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);
            printf("\n\n");         
        }
    }
    system("pause");
}

void addNewTask(){
    FILE * filep;
    filep = fopen("mytask.txt", "a+");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("             NEW TASK          \n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    printf("\nNew Task ID: ");
    fflush(stdin);
    gets(rec.taskID);

    printf("New Task Name: ");
    fflush(stdin);
    gets(rec.taskName);

    printf("Task Category: ");
    fflush(stdin);
    gets(rec.category);

    printf("Task Due Date (DAY): ");
    fflush(stdin);
    scanf("%d",&rec.dueDay);

    printf("Task Due Date (MONTH): ");
    fflush(stdin);
    scanf("%d",&rec.dueMonth);

    printf("Task Due Date (YEAR): ");
    fflush(stdin);
    scanf("%d",&rec.dueYear);

    taskStatus(rec.dueDay, rec.dueMonth, rec.dueYear, rec.status);

    strcpy(rec.completedIncomplete, "Incomplete");

    fprintf(filep,"%s|%s|%s|%02d/%02d/%d|%s|%s\n", 
            rec.taskID, rec.taskName, rec.category, rec.dueDay, rec.dueMonth, rec.dueYear, rec.status, rec.completedIncomplete);
    fclose(filep);

    printf("\n>>>>Task Successfully Added!<<<<\n\n");
    system("pause");
}

void updateTasks(){
    system("cls");
    int opt,f=0;
    FILE *filep, *newrec;
    filep = fopen("mytask.txt", "r");
    newrec = fopen("temp.txt", "w");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("           UPDATE TASK          \n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    printf("\nEnter TaskID: ");
    fflush(stdin); gets(check.taskID);

    while(fscanf(filep,"%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^\n]\n", 
                        rec.taskID, rec.taskName, rec.category, &rec.dueDay, &rec.dueMonth, &rec.dueYear, rec.status, rec.completedIncomplete) != EOF)
    {
        if(strcmp(check.taskID,rec.taskID) == 0){
            f=1;
            do{
                system("cls");
                printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("           UPDATE TASK          \n");
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                printf("1. Task Name\n");
                printf("2. Task Category\n");
                printf("3. Task Due Date\n");
                printf("4. Task Status\n");
                printf("\nSelect which option need to be updated >>\n");
                scanf("%d",&opt);

                switch(opt){
                    case 1:
                        printf("Updated Task Name: ");
                        fflush(stdin);
                        gets(rec.taskName); 
                        printf("\nTask Successfully Updated!\n");
                        break;
                    case 2:
                        printf("Updated Task Category: ");
                        fflush(stdin);
                        gets(rec.category);
                        printf("\nTask Successfully Updated!\n");
                        break;
                    case 3:
                        printf("Task Due Date (DAY): ");
                        fflush(stdin);
                        scanf("%d",&rec.dueDay);
                     
                        printf("Task Due Date (MONTH): ");
                        fflush(stdin);
                        scanf("%d",&rec.dueMonth);
                        
                        printf("Task Due Date (YEAR): ");
                        fflush(stdin);
                        scanf("%d",&rec.dueYear);
                        printf("\nTask Successfully Updated!\n");
                        break;
                    case 4:
                        char choice[3];
                        printf("Mark Task as Completed? [Y/N]");
                        fflush(stdin);
                        scanf("%s", choice);
                        if (strcmp(choice,"Y") == 0){
                            strcpy(rec.completedIncomplete, "Completed");
                        }
                        else {
                            strcpy(rec.completedIncomplete, "Incomplete");
                        }
                        printf("\nTask Successfully Updated!\n");
                        break; 
                    default: 
                        printf("Incorrect Option. Please Try Again.\n");
                        break;
                }

                fprintf(newrec,"%s|%s|%s|%02d/%02d/%d|%s|%s\n", 
                        rec.taskID, rec.taskName, rec.category, rec.dueDay, rec.dueMonth, rec.dueYear, rec.status, rec.completedIncomplete);
                break;

            }while(opt != 0);
        }
        else{
            fprintf(newrec,"%s|%s|%s|%02d/%02d/%d|%s|%s\n", 
                    rec.taskID, rec.taskName, rec.category, rec.dueDay, rec.dueMonth, rec.dueYear, rec.status, rec.completedIncomplete);
        }
    }
    fclose(filep);
    fclose(newrec);
    remove("mytask.txt");
    rename("temp.txt","mytask.txt");
    if(f == 0){
        printf("TaskID Not Found\n\n");
    }
    system("pause");
}

void deleteTasks(){
    int opt,f=0;
    FILE *filep, *newrec;
    filep = fopen("mytask.txt", "r");
    newrec = fopen("temp.txt", "w");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("           DELETE TASK          \n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    printf("\nEnter TaskID: ");
    fflush(stdin); gets(check.taskID);

    while(fscanf(filep,"%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^\n]\n", 
                        rec.taskID, rec.taskName, rec.category, &rec.dueDay, &rec.dueMonth, &rec.dueYear, rec.status, rec.completedIncomplete) != EOF)
    {
        if (strcmpi(check.taskID,rec.taskID) == 0){
            f=1;
            printf("\nDeleting TaskID (%s)...\n", check.taskID);
            continue;
        }
        else{
            fprintf(newrec,"%s|%s|%s|%02d/%02d/%d|%s|%s\n", 
                    rec.taskID, rec.taskName, rec.category, rec.dueDay, rec.dueMonth, rec.dueYear, rec.status, rec.completedIncomplete);
        }
    }
    fclose(filep);
    fclose(newrec);
    remove("mytask.txt");
    rename("temp.txt","mytask.txt");
    if(f == 0){
        printf("TaskID Not Found\n\n");
        system("pause");
    }
    else{
        printf("\nTask Successfully Deleted!\n\n");
        system("pause");
    }
}

