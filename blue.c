#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 9
int roomList[max]={101,102,103,201,202,203,301,302,303};
int roomRate[max]={2000,2500,2000,2000,2500,2000,2000,2500,2000};
struct data{
    int room;
    char name[50];
    int pax;
    char status[20];
    int rate;
    int nights;
    int bill;
};
void add();
void removeRoom();
void display();
int valid(int roomNo);
void available();
void search();

FILE *fp,*tp;
struct data r;
struct data temp;

int main()
{
    int o;
    printf("\t\t\t\t\t\tPROJECT\n\t\t\t\t\tHotel Management System\n");
    mark:
    printf("\nMenu\n");
    printf("1.Add record\n");
    printf("2.Remove record\n");
    printf("3.Display all rooms\n");
    printf("4.Display available rooms\n");
    printf("5.Search room detail\n");
    printf("6.Exit\n");
    printf("Enter your option: ");
    scanf("%d",&o);
    fflush(stdin);
    switch(o){
        case 1:
            add();
            goto mark;
            break;
        case 2:
            removeRoom();
            goto mark;
            break;
        case 3:
            display();
            goto mark;
            break;
        case 4:
            available();
            goto mark;
            break;
        case 5:
        	search();
        	goto mark;
        case 6:
            exit(0);
            break;
        default:
            printf("\nInvalid option!\nTry again!!\n");
            goto mark;
    }
    return 0;
}

void add()
{
    int booked=0;
    int i;
    //memset(&r, 0, sizeof(r));   // clear garbage values

    printf("Enter room no: ");
    scanf("%d",&r.room);
    fflush(stdin);

    if(!valid(r.room))
    {
        printf("Invalid room\n");
        return;
    }

    fp=fopen("C:\\C project\\page.dat","rb");
    if(fp!=NULL)
    {
        while(fread(&temp,sizeof(temp),1,fp)==1)
        {
            if(temp.room==r.room)
            {
                booked=1;
                break;
            }
        }
        fclose(fp);
    }

    if(booked)
    {
        printf("The room is already booked!\n");
        return;
    }

    // match respective roomno with rate from array
    for(i=0; i<max; i++)
    {
        if(roomList[i]==r.room)
        {
            r.rate=roomRate[i];
            break;
        }
    }

    printf("Enter guest's name: ");
    fgets(r.name,sizeof(r.name),stdin);
    r.name[strcspn(r.name, "\n")] = '\0';//enter clear garne
    fflush(stdin);

    printf("Enter pax: ");
    scanf("%d",&r.pax);
    fflush(stdin);

    printf("Enter number of nights: ");
    scanf("%d",&r.nights);
    fflush(stdin);

    r.bill = r.rate * r.nights;
    strcpy(r.status,"Occupied");

    fp=fopen("C:\\C project\\page.dat","ab");
    if(fp==NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }
    fwrite(&r,sizeof(r),1,fp);
    fclose(fp);
    printf("Room %d booked successfully!\n", r.room);
}

void display()
{
    struct data booked[max];
    int bookedCount=0;
    int i,j;

    fp=fopen("C:\\C project\\page.dat","rb");
    if(fp!=NULL)
    {
        while(fread(&booked[bookedCount],sizeof(struct data),1,fp)==1)
        {
            bookedCount++;
        }
        fclose(fp);
    }

    printf("\n%-6s %-20s %-5s %-7s %-7s %-7s %-10s\n",//%ns -:left aligh n:width
           "Room","Name","Pax","Rate","Nights","Bill","Status");
    printf("------------------------------------------------------------------\n");

    for(i=0; i<max; i++)
    {
        int found=0;
        for(j=0; j<bookedCount; j++)//show all booked records
        {
            if(booked[j].room==roomList[i])
            {
                printf("%-6d %-20s %-5d %-7d %-7d %-7d %-10s\n",
                       booked[j].room,
                       booked[j].name,
                       booked[j].pax,
                       booked[j].rate,
                       booked[j].nights,
                       booked[j].bill,
                       booked[j].status);
                found=1;
                break;
            }
        }
        if(!found)//not boooked records print garne
        {
            printf("%-6d %-20s %-5s %-7d %-7s %-7s %-10s\n",
                   roomList[i],
                   "-",
                   "-",
                   roomRate[i],
                   "-",
                   "-",
                   "Available");
        }
    }
}

int valid(int roomNo)//check if user input room is a vaid room
{
    int i;
    for(i=0;i<max;i++)
    {
        if(roomNo==roomList[i])
            return 1;
    }
    return 0;
}

void available()//booked or not dekhaune
{
    int i;
    int occupied[max]={0};
    fp=fopen("C:\\C project\\page.dat","rb");
    if(fp!=NULL)
    {
        while(fread(&r,sizeof(r),1,fp)==1)//goes through all rooms to check if records for each room exits 
        {
            for(i=0;i<max;i++)
            {
                if(roomList[i]==r.room)
                {
                    occupied[i]=1;
                    break;
                }
            }
        }
        fclose(fp);
    }
    printf("\nAvailable Rooms\n");
    printf("-----------------\n");
    int found=0;
    for(i=0;i<max;i++)
    {
        if(occupied[i]==0)
        {
            printf("Room %d (Rate: Rs.%d/night)\n",roomList[i],roomRate[i]);
            found=1;
        }
    }
    if(!found)
    {
        printf("No available rooms!\nSorry\n");
    }
}

void removeRoom()
{
    int roomNo, found=0;
    printf("Enter room no to remove: ");
    scanf("%d", &roomNo);
    fflush(stdin);

    if(!valid(roomNo))
    {
        printf("Invalid room number!\n");
        return;
    }
    fp=fopen("C:\\C project\\page.dat","rb");
    tp=fopen("C:\\C project\\temp.dat","wb");
    if(fp==NULL)
    {
        printf("No records found.\n");
        fclose(tp);
        return;
    }
    while(fread(&r,sizeof(r),1,fp)==1)
    {
        if(r.room!=roomNo)
            fwrite(&r,sizeof(r),1,tp);//if roomno is not the entered roomno then write
        else
            found=1;//if roomno and entered roomno is same then instead of writing,,found=1
    }
    fclose(fp);
    fclose(tp);
    remove("C:\\C project\\page.dat");
    rename("C:\\C project\\temp.dat","C:\\C project\\page.dat");//so we make temp and all records except the roomno to be deleted is copied into temp and then we rename temp into main file
    if(found)
        printf("Room %d is now Available.\n", roomNo);
    else
        printf("Room not found.\n");
}

void search()
{
	int found = 0;
	int searchRoom = 0;
	
	printf("Enter room no to search: ");
	scanf("%d", &searchRoom);
	
	fp = fopen("page.dat", "rb");
	
	if(fp == NULL){
		printf("File cannot be found.");
		return;
	}
	

	while(fread(&r, sizeof(r), 1, fp) == 1){
        if(r.room == searchRoom){
            printf("\n\n----------Room Details----------\n");
            printf("Room NO :%d\n", r.room);
            printf("Guest Name : %s\n", r.name); 
            printf("Pax: %d\n", r.pax);        
            
            found = 1;
            break; 
        }
    }

	fclose(fp);
	
	if(found == 0){
		printf("The room %d does not exist.\n", searchRoom);
	}
}
