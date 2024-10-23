//Taymaa Nasser  1222640  Section 5.

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//type defining pointers of structs for easier use.
typedef struct DistrictNode* ptr;
typedef ptr LinkedList_D;
typedef struct TownNode* Tptr;
typedef Tptr LinkedList_T;


typedef struct DistrictNode //struct of Districts.
{
    char DName[51];
    int TotalPopulation;
    ptr next;
    ptr prev;
    Tptr firstTown; //pointer to the first town linked to every district.
} DistrictNode;

typedef struct TownNode //struct of Towns.
{
    char TName[51];
    int Population;
    Tptr next;
    Tptr prev;
} TownNode;

//declaring all functions used in project.
ptr createNode_District();
Tptr createNode_Town();
ptr SearchDistrict(ptr head, char district[]);
int isEmpty(ptr head);
int isExist(ptr head, char key[]);
void Insert_District(ptr head, char district[]);
void Insert_Town(ptr headD, char district[],char town[], int population);
void DisplayDistricts(ptr head);
void displayLinkedList(ptr head);
void Delete_Town(ptr headD, char district[],char town[]);
void Delete_District(ptr head, char district[]);
int getMax(ptr head);
void radixSorting(ptr head);
void bubbleSorting(ptr head);
void PalestineInfo(ptr head);
void ChangePopulation(ptr head,char district[],char town[],int population);
void displayMenu();
void loadDataFile(ptr head, int op);
void saveDataFile(ptr head);

int main()
{
    LinkedList_D L1=createNode_District(); //creating the head node of districts LL. (used in all function calls in menu)

    //declaring variables to store user-entered data in menu.
    char name[51],name1[51],name2[51], name3[51], name4[51],name5[51],name6[51],name7[51];
    int populationT,populationC;

    int func=0; //initializing flag to enter and end menu.(when func==14, exit menu).

    int loadFlag=0; //initializing flag to prevent loading of txt file more than once.
    while(func!=14)
    {
        displayMenu();
        scanf("%d",&func);
        getchar(); //to deal with special characters entered by user.
        switch(func)
        {
        case 1:
            if(loadFlag==0)
            {
                loadDataFile(L1,1);
                loadFlag=1;
            }
            else
                printf("You can not load the file more than once. Please select another operation. \n");
            break;
        case 2:
            if(loadFlag!=1) //forcing user to load file before printing it using the loadFlag.
            {
                printf("You must load file before printing it. Please select operation 1.\n");
            }
            else
                loadDataFile(L1,2);
            break;
        case 3:
            printf("Radix sorting the current districts...\n");
            radixSorting(L1);
            printf("Districts have been sorted!\n");
            break;
        case 4:
            printf("Bubble sorting the current towns in ascending order...\n");
            bubbleSorting(L1);
            printf("Towns have been sorted!\n");
            break;
        case 5:
            printf("Printing sorted information...\n"); //calling radix and bubble sorting functions in case user did not select functions 3 & 4 before 5.
            radixSorting(L1);
            bubbleSorting(L1);
            DisplayLinkedList(L1);
            break;
        case 6:
            printf("please insert new district name: \n");
            gets(name); //using gets instead of scanf to take care of spaces and special characters.
            Insert_District(L1,name);
            break;
        case 7:
            printf("please insert district of new town and its name and population: \n");
            gets(name1);
            gets(name2);
            scanf("%d",&populationT);
            getchar();
            Insert_Town(L1,name1,name2,populationT);
            break;
        case 8:
            printf("Please insert district of town to delete and its name: \n");
            gets(name3);
            gets(name4);
            Delete_Town(L1,name3,name4);
            break;
        case 9:
            printf("Please insert name of district to delete: \n");
            gets(name5);
            Delete_District(L1,name5);
            break;
        case 10:
            printf("Calculating total population of Palestine with max and min populations of towns...\n");
            PalestineInfo(L1);
            break;
        case 11:
            printf("Printing districts and their total populations...\n");
            DisplayDistricts(L1);
            break;
        case 12:
            printf("Please insert name of district and town to change its population and the new population: \n");
            gets(name6);
            gets(name7);
            scanf("%d",&populationC);
            getchar();
            ChangePopulation(L1,name6,name7,populationC);
            break;
        case 13:
            radixSorting(L1); //calling radix and bubble sorting functions in case user did not select functions 3 & 4 before saving to output file.
            bubbleSorting(L1);
            saveDataFile(L1);
            break;
        case 14:
            printf("Thank you for using My Radix Sorting of Linked Lists System! Goodbye.\n"); //exiting system.
            break;
        default:
            printf("No such operation! Please try again.\n"); //deals with user-entered data that is not a number from 1-14.
        }
    }

    return 0;
}

ptr createNode_District()  //creates new District node for insertion.
{
    ptr head=(ptr)malloc(sizeof(struct DistrictNode));
    head->firstTown=NULL;
    head->next= NULL;
    head->prev=NULL;
    if(head == NULL)
    {
        printf("Memory can not be allocated.\n");
        return NULL; //return NULL pointer in case of memory allocation failure.
    }
    return head;
}
Tptr createNode_Town()  //creates new Town node for insertion
{
    Tptr head=(Tptr)malloc(sizeof(struct TownNode));
    head->next= NULL;
    head->prev=NULL;
    if(head == NULL)
    {
        printf("Memory can not be allocated.\n");
        return NULL; //return NULL pointer in case of memory allocation failure.
    }
    return head;
}
ptr SearchDistrict(ptr head, char district[]) //searches for district node with specific data and returns it
{
    ptr temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->DName,district)==0)
        {
            return temp;
        }
        temp = temp->next;

    }
    return NULL;
}
int isEmpty(ptr head) //checks if there are any district nodes in LL.
{
    if(head!=NULL)
    {
        return head->next == NULL; // returns 1 if empty 0 if not.
    }
}

int isExist(ptr head, char key[]) //checks if specific district node exits in LL.
{
    ptr p;
    int flag=0;
    p= head->next;
    while(p!=NULL)
    {
        if(strcmp(p->DName,key)==0)
        {
            flag=1;
        }
        p=p->next;
    }
    return flag; //returns 0 if it does not exist.
}
int isExist_T(Tptr head, char key[]) //checks if specific town node exits in LL.
{
    Tptr p;
    int flag=0;
    p= head;
    while(p!=NULL)
    {
        if(strcmp(p->TName,key)==0)
        {
            flag=1;
        }
        p=p->next;
    }
    return flag; //returns 0 if it does not exist.
}


void Insert_District(ptr head, char district[]) //inserts District at end of Districts LL.
{
    int E=isExist(head,district); //calling isExist func to prevent insertion of duplicate districts.
    if(E==0)
    {
        ptr temp,hp; //declaring 2 district pointers. (temp points to new node and p points to head node)
        temp = createNode_District(); //creating and allocating memory for the new district node.
        strcpy(temp->DName,district); //assigning user-entered name to DName.
        temp->TotalPopulation=0; //initializing new district with 0 total population until new towns are inserted.
        if(head->next == NULL) //if the LL only has the head node, attach the new node after it.
        {
            head->next = temp;
            temp->prev=head;
        }
        else //if there are other nodes beside the head, traverse the list until the last node and insert new node after it.
        {
            hp=head;

            while(hp->next != NULL)
            {
                hp = hp->next;
            }
            hp->next=temp;
            temp->prev=hp;
        }
    }
    else printf("District %s already exists in list.\n",district);
}
void Insert_Town(ptr headD, char district[],char town[], int population) //inserts Town at end of Towns LL
{
    ptr Dis=SearchDistrict(headD,district); //assigns a pointer to the specific user-entered district if it exists in LL.
    if(Dis!=NULL)
    {
        int E=isExist_T(Dis->firstTown,town);
        if(E==0)
        {
            Tptr temp,hp; //declaring 2 district pointers. (temp points to new node and p points to firstTown node)
            temp = createNode_Town(); //creating and allocating memory for the new town node.
            strcpy(temp->TName,town);  //assigning user-entered name to TName.
            temp->Population=population;  //assigning user-entered population to Population.
            Dis->TotalPopulation+=population; //updating the total population of the district with every new town inserted.
            if(Dis->firstTown == NULL) //if the district has only the firstTown node, insert new town after it.
            {
                Dis->firstTown=temp;
                temp->prev=Dis->firstTown;
            }
            else //if there are other nodes beside the head, traverse the list until the last node and insert new node after it.
            {
                hp=Dis->firstTown;
                while(hp->next!= NULL)
                {
                    hp = hp->next;
                }
                hp->next=temp;
                temp->prev=hp;
            }
        }
        else
            printf("Town %s already exists in district %s.\n",town,district);
    }
    else
        printf("District %s does not exist in list. Please create it first then insert its towns.\n",district);
}
void DisplayDistricts(ptr head)  //prints out districts LL and their total population without town details.
{

    if (head == NULL || head->next == NULL) //checks if there exists any districts in LL.
    {
        printf("List of districts is empty.\n");
        return;
    }
    else
    {
        ptr temp=head;
        temp = temp->next;
        while(temp!= NULL)
        {
            printf("%s: %d <-> \t", temp->DName,temp->TotalPopulation);
            temp = temp->next;
        }
        printf("\n");
    }
}
void DisplayLinkedList(ptr head)
{
    if (head == NULL || head->next == NULL) //checks if there exists any districts in LL.
    {
        printf("No districts found.\n");
        return;
    }
    ptr tempD = head->next;
    while (tempD != NULL) //traversing the districts LL.
    {
        printf("%s District, Population= %d \n",tempD->DName,tempD->TotalPopulation);
        if (tempD->firstTown == NULL)
        {
            printf(" District has zero towns.\n");
        }
        else
        {
            Tptr tempT = tempD->firstTown;
            while (tempT != NULL) //traversing the towns in each district.
            {
                printf("%s, %d \n", tempT->TName,tempT->Population);
                tempT = tempT->next;
            }
        }
        printf("\n");
        tempD = tempD->next;
    }
}
void Delete_Town(ptr headD, char district[],char town[]) //deletes specific town from specific district.
{
    ptr Dis=SearchDistrict(headD,district); //assigns a pointer to the specific user-entered district if it exists in LL.
    if(Dis!=NULL)
    {
        Tptr temp,hp;
        temp=Dis->firstTown;
        int townFlag=0; //flag set up to check if the town entered exists in district.
        if(temp!=NULL && strcmp(temp->TName,town)==0) //in the case where the town to be deleted is the first town in the district.
        {
            Dis->firstTown=temp->next; //assigning the town after the first to become first in list.
            Dis->TotalPopulation-=temp->Population; //decrementing the total population of the district.
            if (Dis->firstTown != NULL)
                Dis->firstTown->prev=NULL;
            free(temp); //freeing memory that holds the deleted town.
            townFlag=1; //changing flag value=town was found and deleted.
        }
        else
        {
            hp = Dis->firstTown; //in the case where the town to be deleted is not the first town then traverse the towns until it is found.
            while(hp != NULL && hp->next != NULL)
            {
                if(strcmp(hp->next->TName,town)==0)
                {
                    temp = hp->next;
                    hp->next = temp->next;
                    if (temp->next != NULL)
                    {
                        temp->next->prev = hp; //skipping deleted town to free it from memory.
                    }
                    Dis->TotalPopulation-=temp->Population; //decrementing the total population of the district.
                    free(temp);//freeing memory that holds the deleted town.
                    townFlag=1; //changing flag value=town was found and deleted.
                    break;

                }
                else
                    hp = hp->next; //moving to the next town in district.
            }

            if(townFlag == 0)
            {
                printf("Town %s is not in District %s.\n",town,district);
            }
        }
    }

    else
        printf("District %s does not exist in list.\n",district);
}
void Delete_District(ptr head, char district[]) //deletes entire District by deleting all its towns too.
{
    ptr dis=SearchDistrict(head,district);
    if(dis==NULL)
    {
        printf("District %s does not exist in linked list.\n",district);
        return;

    }
    Tptr temp,nextTown;
    temp=dis->firstTown;
    dis->firstTown=NULL; //disconnecting towns LL from their district.
    while(temp!=NULL)
    {
        nextTown=temp->next; //uses pointer nextTown to keep track of the next town to be deleted
        free(temp); //freeing memory that holds each town in the district.
        temp=nextTown; //reassigns temp to the next town using the nextTown pointer.
    }
    if (dis->prev != NULL) //if the deleted district has a district before it, assign its next pointer to the district after the deleted one.
    {
        dis->prev->next = dis->next;
    }
    if (dis->next != NULL) //if the deleted district has a district after it, assign its previous pointer to the district before the deleted one.
    {
        dis->next->prev = dis->prev;
    }

    free(dis); //freeing memory that holds the deleted district.

}
int getMax(ptr head) // function that returns length of longest district name.
{
    if (isEmpty(head))
    {
        return 0; //if there are no districts in LL then return length of 0;
    }
    int maxString = 0; //initializing value that will hold the length of the longest name.
    ptr temp = head->next; //pointer that traverses through the districts.
    while (temp != NULL)
    {
        int lengthOfNode = strlen(temp->DName); //variable used to compare length of current district name with the max district name.
        if (lengthOfNode > maxString)
        {
            maxString = lengthOfNode;
        }
        temp= temp->next;
    }
    return maxString;
}
void radixSorting(ptr head) //function that radix sorts the districts alphabetically.
{
    if (head == NULL || head->next == NULL)
    {
        printf("List of districts is empty.\n");
        return;
    }

    int maxLength=getMax(head);
    if (maxLength == 0)
    {
        printf("No districts found.\n"); //no sorting needed.
        return;
    }
    ptr BucketsArray[54]; //declaring an array of buckets of size 54 (26 small letters, 26 capital letters, 1 null and 1 for other special chars)
    ptr LastIndexPtr[54]; //declaring an array of pointers that point to the end of every bucket.
    int lastIndex=maxLength-1;
    for (int i =0; i<maxLength; i++) //going through the characters from least sig to most sig (right to left).
    {
        for(int i=0; i<54; i++)
        {
            BucketsArray[i]=createNode_District(); //assigning  every index of the buckets array to an empty district nodes.
            LastIndexPtr[i]=BucketsArray[i]; //assigning every district in its correct bucket based on its char at the current position.
        }

        ptr temp=head->next; //traversing through all districts for every char at every position.
        while(temp!=NULL)
        {
            int pos;
            char currentChar=temp->DName[lastIndex];
            if (currentChar == '\0') //assigning first bucket for null chars.
            {
                LastIndexPtr[0]->next = temp; //assigning current district to the end of the corresponding bucket.
                LastIndexPtr[0] = temp; //updating the corresponding bucket to have temp as its new last element.
                temp = temp->next; //traversing to the next district.
                LastIndexPtr[0]->next = NULL; //assigning null to the last element (temp).


            }
            else if ('A' <= currentChar && currentChar <= 'Z') //calculating bucket index based on ASCII values.
            {
                pos = 1+ (currentChar-'A');
                LastIndexPtr [pos]->next = temp;
                LastIndexPtr [pos]=temp;
                temp=temp->next;
                LastIndexPtr [pos]->next = NULL;


            }
            else if ('a' <= currentChar && currentChar <= 'z') //calculating bucket index based on ASCII values.
            {
                pos = 27+ (currentChar-'a');
                LastIndexPtr[pos]->next = temp;
                LastIndexPtr [pos] = temp;
                temp=temp->next;
                LastIndexPtr [pos]->next = NULL;
            }
            else //assigning special chars to the last bucket.
            {
                LastIndexPtr[53]->next = temp;
                LastIndexPtr[53] = temp;
                temp = temp->next;
                LastIndexPtr[53]->next = NULL;
            }
        }

        lastIndex--; //decrementing lastIndex so we move to the previous character to the left.

        head->next = NULL; //disconnecting the original unsorted list.
        ptr temp2 = head; //pointer to connect sorted districts in order.

        for (int j=0; j< 54; j++) //going through all the 53 buckets.
        {
            temp = BucketsArray[j]->next;

            while(temp!=NULL) //traverse all the districts in the current bucket.
            {
                temp2->next = temp; //connecting the current district to the new sorted list.
                temp->prev = temp2;
                temp2 = temp; //assigning temp2 to point at the current district in the list (last one entered to sorted list).
                temp = temp->next; //going to the next district in the current bucket.
                temp2->next = NULL; //assigning the next pointer of last inserted district to null to mark end of list.

            }
        }
    }

}

void bubbleSorting(ptr head) //function that bubble sorts the towns of every district based on population. (in ascending order).
{
    ptr temp = head->next; //to traverse all districts.
    while (temp != NULL)
    {
        Tptr ptr1 = temp->firstTown; //start with the first town in a district.
        int swapFlag; //flag to check if any swapping occurs.
        if (ptr1 == NULL || ptr1->next == NULL)  //check if the district has zero or one town.
        {
            printf("District '%s' has zero or only one town.\n", temp->DName);
            temp = temp->next; //move to the next district.
            continue; //skip bubble sorting for this district.
        }
        do
        {
            swapFlag = 0; //resetting flag for each iteration.
            Tptr ptr2 = ptr1; //starting with the first town.
            while (ptr2->next != NULL) //to traverse all towns for comparison.
            {
                if (ptr2->Population > ptr2->next->Population) //comparing populations between each town and the next one. (swaps data of towns if current town has a bigger population than the next)
                {
                    //initializing variables to hold temp names and populations during swapping.
                    char tempName[50];
                    int tempPop;

                    tempPop = ptr2->Population;
                    strcpy(tempName, ptr2->TName);

                    ptr2->Population = ptr2->next->Population;
                    strcpy(ptr2->TName, ptr2->next->TName);

                    ptr2->next->Population = tempPop;
                    strcpy(ptr2->next->TName, tempName);

                    swapFlag = 1; //seting flag to indicate swapping occurred.
                }
                ptr2 = ptr2->next; //moving to the next town.
            }
        }
        while (swapFlag);   //continue until no more swaps occur.
        temp = temp->next; //move to the next district.
    }
}

void PalestineInfo(ptr head) //function that calculates and prints information about total population of palestine with the min and max towns.
{
    if (head == NULL || head->next == NULL)
    {
        printf("List of districts is empty.\n");
        return;
    }
    int PalPop=0; //initializing population variable to zero.
    ptr temp=head->next; //pointer to the first district.
    int tempMax=0; //initialized to min possible number.
    int tempMin=10000000; //initialized to max possible number.
    char MaxTown[50];
    char MinTown[50];
    while(temp!=NULL) //traversing all districts.
    {
        PalPop+=temp->TotalPopulation; //incrementing population of palestine by the total populations of every district.
        Tptr temp2=temp->firstTown;
        while(temp2 !=NULL) //traversing all towns in every district.
        {
            if(tempMax < temp2->Population) //comparing to see if the tempMax should be replaced with a greater town population.
            {
                tempMax=temp2->Population;
                strcpy(MaxTown,temp2->TName); //to return the name of town with the max population.
            }
            if(tempMin > temp2->Population) //comparing to see if the tempMin should be replaced with a lesser town population.
            {
                tempMin=temp2->Population;
                strcpy(MinTown,temp2->TName); //to return the name of town with the min population.
            }

            temp2=temp2->next; //move to the next town.
        }

        temp=temp->next; //move to the next district.
    }
    printf("The total population of Palestine: %d\n",PalPop);
    printf("The town that has the max population in Palestine is %s (%d)\n",MaxTown,tempMax);
    printf("The town that has the min population in Palestine is %s (%d) \n",MinTown,tempMin);


}
void ChangePopulation(ptr head,char district[],char town[],int population) //function that changes population of a given town.
{
    if (head == NULL || head->next == NULL)
    {
        printf("List of districts is empty.\n");
        return;
    }
    ptr Dis=SearchDistrict(head,district); //assigning a pointer to the district that contains the town needed.
    int flagTown=0; //flag set up to check if the town entered exists in district.
    if(Dis!=NULL)
    {
        Tptr temp=Dis->firstTown;
        while(temp!=NULL) //traversing all the towns until the one entered is found.
        {
            if(strcmp(temp->TName,town)==0)
            {
                if(temp->Population > population) //calculations to update the total population of the district.
                {
                    Dis->TotalPopulation-=(temp->Population - population);
                }
                else if(temp->Population < population)
                {
                    Dis->TotalPopulation+=(population -temp->Population);
                }
                else
                    printf("New population equals the original population.\n");

                temp->Population=population; //updating town population.
                flagTown=1;
                break;
            }
            temp=temp->next;
        }
        if(flagTown==0)
        {
            printf("this town is not in district %s.\n", district);
        }
    }
    else
    {
        printf("District '%s' not found.\n", district);
    }
}

void displayMenu() //function to display main menu.
{
    printf("Please select one functionality to run (1-14):\n\n");
    printf("1. Load the input file.\n");
    printf("2. Print the loaded information before sorting.\n");
    printf("3. Sort the districts alphabetically using Radix sorting.\n");
    printf("4. Sort the towns for each district based on population in ascending order.\n");
    printf("5. Print the sorted information.\n");
    printf("6. Add a new district to the list of sorted districts.\n");
    printf("7. Add a new town to a certain district.\n");
    printf("8. Delete a town from a specific district.\n");
    printf("9. Delete an entire district.\n");
    printf("10 Calculate the population of Palestine, the max and min town population.\n");
    printf("11. Print the districts and their total population.\n");
    printf("12. Change the population of a town.\n");
    printf("13. Save to the output file.\n");
    printf("14. Exit System.\n");
}

void loadDataFile(ptr head, int op) //function that loads input file districts.txt and prints loaded info.
{
    FILE *fp; //declaring a file pointer fp.
    fp = fopen("districts.txt","r"); //using fp to open districts.txt file in read mode.
    if (fp == NULL)
    {
        printf("Input file failed to load!\n");
        return;
    }
    char FullString[51],District[51],Town[51]; //declaring variables to contain the tokenized strings read from file.
    int Population;
    char* token;
    while(!feof(fp)) //read lines until end of file.
    {
        fgets(FullString,50,fp); //read until end of line.
        token = strtok(FullString, "|"); //tokenise the full string at the pipe | char.
        while(token != NULL )
        {
            strcpy(District,token); //save that token in variable District.

            token = strtok(NULL, "|"); //tokenise the leftover string at the pipe | char.
            strcpy(Town,token); //save that token in variable Town.

            token = strtok(NULL, "|"); //tokenise the leftover string at the pipe | char.
            Population=atoi(token); //save that token in variable Population after converting the string into intger.

            token = strtok(NULL, "|"); //tokenise the leftover string at the pipe | char.

            int E=isExist(head,District); //calling function to check if current district exits to prevent duplicate districts.
            if(E==0)
            {
                Insert_District(head,District); //inserting the current district into the LL.
            }
            Insert_Town(head,District,Town,Population); //inserting the town and population to the current district LL.



            if(op==2) //printing loaded information if op entered was 2.
            {
                printf("%s|%s|%d \n",District,Town,Population);
            }
        }
    }
    if(op!=2)
    {
        printf("Loading data input file ...\n");
        printf("Data file Loaded!\n\n");
    }


    fclose(fp); //closing the file.
}



void saveDataFile(ptr head) //function that saves all changes to output file sorted_districts.txt
{
    printf("Updating output data file ...\n");
    FILE *fp; //declaring a file pointer fp.
    fp = fopen("sorted_districts.txt","w"); //using fp to open sorted_districts.txt file in write mode.
    if (fp == NULL)
    {
        printf("Output file failed to load! \n");
    }

    ptr temp = head->next; //traversing all districts.
    while (temp != NULL)
    {
        fprintf(fp,"%s District, Population= %d \n",temp->DName,temp->TotalPopulation);
        Tptr temp2 = temp->firstTown;
        while (temp2 != NULL) //traversing all towns in current district.
        {
            fprintf(fp,"%s, %d \n", temp2->TName,temp2->Population);
            temp2 = temp2->next; //moving to the next town after printing the current one into the output file.
        }

        fprintf(fp,"\n");
        temp = temp->next; //moving to the next district after printing the current one into the output file.
    }
    fprintf(fp,"\n");
    fclose(fp); //closing the file.

    printf("Data file saved!\n\n");
}


