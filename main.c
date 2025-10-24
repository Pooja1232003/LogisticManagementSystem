#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_VEHICLES 3
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0


void addCities(int maxCities,char cityNames[][30],int *cityCount );
void listCities(char cityNames[][30],int cityCount);
void renameCity(char cityNames[][30],int cityCount);
void removeCity(char cityNames[][30],int *cityCount);

void inputDistance(int distance[][MAX_CITIES],int cityCount,char cityNames[][30]);
void displayDistanceTable(int distance[][MAX_CITIES],int cityCount,char cityNames[][30]);

int main()
{ char cityNames[MAX_CITIES][30];
  int distance[MAX_CITIES][MAX_CITIES]={0};

  char vehicleNames[MAX_VEHICLES][20]={"Van","Truck","Lorry"};
  int capacities[MAX_VEHICLES]={1000,5000,10000};
  float rates[MAX_VEHICLES]={30.0,40.0,80.0};
  float speeds[MAX_VEHICLES]={60.0,50.0,45.0};
  float efficiencies[MAX_VEHICLES]={12.0,6.0,4.0};

    int choice;

    int cityCount=0;

    do {
        printf("\n===== LOGISTICS MANAGEMENT MENU =====\n\n");
        printf("1. Add New Cities\n");
        printf("2. List of Cities\n");
        printf("3. Rename a City\n");
        printf("4. Remove a City\n");
        printf("5. Enter Distances\n");
        printf("6. Show Distance Table\n");
        printf("7. Display Vehicles\n");
        printf("8. Handle Delivery Request\n");
        printf("9. Show Completed Deliveries\n");
        printf("10. Reports\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

     switch(choice){
       case 1:addCities(MAX_CITIES,cityNames,&cityCount);
           break;
       case 2:listCities(cityNames,cityCount);
           break;
       case 3:renameCity(cityNames,cityCount);
           break;
       case 4:removeCity(cityNames,&cityCount);
           break;
       case 5:inputDistance(distance,cityCount,cityNames);
           break;
       case 6:displayDistanceTable(distance,cityCount,cityNames);
          break;

       case 0: printf("Exiting...\n");
           break;
        default: printf("Invalid choice! Try again.\n");
     }
    } while (choice != 0);


    return 0;
}


  //City Management
 void addCities(int maxCities,char cityNames[][30],int *cityCount ){
 int n;
 printf("How many cities do you want to add? :");
 scanf("%d",&n);

 if (*cityCount + n > maxCities){
    printf("Error");
    return;
 }
  for( int i=0 ;i<n ;i++){
    printf("Enter city name %d: ", *cityCount + 1);
    scanf("%s", cityNames[*cityCount]);
    (*cityCount)++;
  }
 printf("\n%d cities added.\n",n);

}


 void listCities(char cityNames[][30],int cityCount){
 if(cityCount == 0){
    printf("No cities available.\n");
    return;
 }
 printf("\nList Of Cities:\n");
 for(int i=0 ; i < cityCount ;i++){
    printf("%d.%s\n",i+1,cityNames[i]);
  }
}


 void renameCity(char cityNames[][30],int cityCount){
   listCities(cityNames,cityCount);

   if( cityCount == 0){
     printf("No cities.\n");
     return;
 }
 int index;
   printf("Enter city number to rename:");
   scanf("%d",&index);
   if( index <1 || index > cityCount){
    printf("Invalid city number\n");
    return;
   }
  printf("Enter new name for %s :",cityNames[index - 1]);
  scanf("%s",cityNames[index - 1]);
  printf("City renamed.\n");

 }


 void removeCity(char cityNames[][30],int *cityCount){
   if( *cityCount == 0){
    printf("No cities to remove.\n");
    return;
   }

   int index;
   printf("Enter city number to remove :");
   scanf("%d",&index);

   if(index < 1 || index >*cityCount){
    printf("Invalid city number.\n");
    return;
   }
   for(int i = index - 1; i < *cityCount - 1; i++){
    for(int j=0; j<30; j++){
   cityNames[i][j] = cityNames[i + 1][j];
    }
   }
   (*cityCount)--;
   printf("City removed.\n");
 }



     // Distance Management

 void inputDistance(int distance[][MAX_CITIES],int cityCount,char cityNames[][30]){
    if( cityCount < 2){
        printf("Add at least 2 cities.\n");
        return;
    }

    for( int i=0; i < cityCount; i++){
      for(int j = i + 1; j < cityCount; j++) {
        printf("Distance between %s and %s in (km) :",cityNames[i],cityNames[j]);
        scanf("%d",&distance[i][j]);
        distance[j][i] = distance[i][j];
      }
      distance[i][i]=0;
    }
   printf("Distance entered.\n");
}


 void displayDistanceTable(int distance[][MAX_CITIES],int cityCount,char cityNames[][30]){
   if(cityCount == 0){
     printf("No cities to display.\n");
     return;
   }

  printf("\n==== DISTANCE TABLE (km) ====\n");
  printf("%-15s","");
  for (int i = 0; i < cityCount; i++){
    printf("%-15s",cityNames[i]);
  }
    printf("\n");

    for (int i = 0; i < cityCount; i++){
        printf("%-15s",cityNames[i]);
        for (int j = 0; j < cityCount; j++){
            printf("%-15d",distance[i][j]);
        }
        printf("\n");
    }
}
