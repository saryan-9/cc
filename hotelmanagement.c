#include<stdio.h>
#include<stdlib.h>
struct data{
	int room;
	char name[50];
	int pax;
};
void add();
void display();
int main()
{
	int o;
	printf("\t\t\t\t\t\tPROJECT\n\t\t\t\t\tHotel Management System\n");
	mark:
	printf("Menu\n");
	printf("1.Add record\n");
	printf("2.Remove record\n");
	printf("3.Display all rooms\n");
	printf("4.Display available rooms\n");
	//printf("5.Edit rooms");
	printf("6.Exit\n");
	printf("enter your option\n");
	scanf("%d",&o);
	switch(o){
		case 1:
			add();
			break;
		case 2:
			break;
		case 3:
			display();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			exit(0);
			break;
		default:
			printf("\nInvalid option!\nTry again!!\n");
			goto mark;
			
	return 0;
	}
}
FILE *fp;
struct data r;
void add()
{
	
	
	fp=fopen("C:\\C project\\occupancy.dat","ab");
	if(fp == NULL)
	{
    printf("File cannot be opened!");
    return;
	}
	printf("enter room no");
	scanf("%d",&r.room);
	fflush(stdin);
	printf("enter guests name");
	gets(r.name);
	fflush(stdin);
	printf("enter pax");
	scanf("%d",&r.pax);
	fflush(stdin);
	fwrite(&r,sizeof(r),1,fp);
	fclose(fp);
}
void display()
{
	fp=fopen("C:\\C project\\occupancy.dat","rb");
	 if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
	while(fread(&r,sizeof(r),1,fp)==1)
	{
	printf("%d %s %d",r.room,r.name,r.pax);
	}
	fclose(fp);
}
