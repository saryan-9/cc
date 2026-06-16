#include<stdio.h>
#include<stdlib.h>


struct data{
	int room;
	char name[50];
	int pax;
};


FILE *fp, *temp;
struct data r;

void add();
void display();
void removeData();
void search();

int main()
{
	int o;
	printf("\t\t\t\t\t\tPROJECT\n\t\t\t\t\tHotel Management System\n");
	
	mark:
	printf("\n\n------------Menu----------\n");
	printf("\n1.Add record\n");
	printf("2.Remove record\n");
	printf("3.Display available rooms\n");
	printf("4.Display all rooms\n");
	printf("5.Search rooms\n");
	printf("6.Exit\n");
	printf("\nEnter your option (1-6): ");
	scanf("%d",&o);
	switch(o){
		case 1:
			add();
			goto mark;
			break;
		case 2:
			removeData();
			goto mark;
			break;
		case 3:
			break;
		case 4:
			display();
			goto mark;
			break;
		case 5:
			search();
			goto mark;
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

void add()
{
	fp=fopen("C:\\C project\\occupancy.dat","ab");
	
	if(fp == NULL)
	{
	    printf("File cannot be opened!");
	    return;
	}
	
	printf("Enter room no: ");
	scanf("%d",&r.room);
	fflush(stdin);
	
	printf("Enter guests name: ");
	gets(r.name);
	fflush(stdin);
	
	printf("Enter pax: ");
	scanf("%d",&r.pax);
	fflush(stdin);
	
	fwrite(&r,sizeof(r),1,fp);
	
	fclose(fp);
}

void display()
{
	fp=fopen("occupancy.dat","rb");
	 if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    
  	printf("\n-----------------------------------------");
    printf("\n%-10s %-20s %-5s", "Room NO", "Guest Name", "Pax");
    printf("\n-----------------------------------------");
	while(fread(&r,sizeof(r),1,fp)==1)
	{
		printf("\n%-10d %-20s %-5d", r.room, r.name, r.pax);
	}
	fclose(fp);
}


void removeData(){
	int roomNo;
	int found = 0;
		
	printf("\nEnter room no to remove: ");
	scanf("%d", &roomNo);
		
	fp = fopen("occupancy.dat", "rb");
	temp = fopen("temp.dat", "wb");
	
	if(fp == NULL){
		printf("File cannot be opened.");
		return;
	}

	while(fread(&r, sizeof(r), 1, fp) == 1){
		if(roomNo != r.room){
			fwrite(&r, sizeof(r), 1, temp);
		}
		else{
			found = 1;
		}
	}

	fclose(fp);
	fclose(temp);

	remove("occupancy.dat");
    rename("temp.dat", "occupancy.dat");
    
	if(found) {
        printf("Record for room %d removed successfully.\n", roomNo);
    } else {
        printf("Room %d not found in the records.\n", roomNo);
    }
}

void search(){
	int found = 0;
	int searchRoom = 0;
	
	printf("Enter room no to search: ");
	scanf("%d", &searchRoom);
	
	fp = fopen("occupancy.dat", "rb");
	
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



