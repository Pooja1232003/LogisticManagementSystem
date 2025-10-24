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
void displayVehicles(char vehicleNames[][20],int capacities[],float rates[],float speeds[],float efficiencies[],int vehicleCount);
void handleDelivery(int distance[][MAX_CITIES], char cityNames[][30], int cityCount,char vehicleNames[][20], int capacities[], float rates[],float speeds[],
                     float efficiencies[], int vehicleCount, int deliverySource[], int deliveryDestination[], int deliveryVehicle[],
                    float deliveryFinalCharge[], int *deliveryCount);
float findShortestPath(int source, int dest, int n, int roads[MAX_CITIES][MAX_CITIES],char cityNames[][30]);

int main(){

 char cityNames[MAX_CITIES][30];
  int distance[MAX_CITIES][MAX_CITIES]={0};

  char vehicleNames[MAX_VEHICLES][20]={"Van","Truck","Lorry"};
  int capacities[MAX_VEHICLES]={1000,5000,10000};
  float rates[MAX_VEHICLES]={30.0,40.0,80.0};
  float speeds[MAX_VEHICLES]={60.0,50.0,45.0};
  float efficiencies[MAX_VEHICLES]={12.0,6.0,4.0};

  int deliverySource[MAX_DELIVERIES];
  int deliveryDestination[MAX_DELIVERIES];
  int deliveryVehicle[MAX_DELIVERIES];
  float deliveryFinalCharge[MAX_DELIVERIES];

    int choice;

    int cityCount=0,deliveryCount=0;

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
       case 7:displayVehicles(vehicleNames,capacities,rates,speeds,efficiencies,MAX_VEHICLES);
         break;
        case 8:handleDelivery(distance, cityNames, cityCount,
                               vehicleNames, capacities, rates, speeds, efficiencies, MAX_VEHICLES,
                               deliverySource, deliveryDestination, deliveryVehicle, deliveryFinalCharge, &deliveryCount);
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


 void displayVehicles(char vehicleNames[][20],int capacities[],float rates[],float speeds[],float efficiencies[],int vehicleCount){

   printf("\n====VEHICLE INFORMATION====\n");
   printf("%s\t  %s\t\t  %s\t  %s\t  %s\t\t  %s\n", "ID", "Type", "Cap(kg)", "Rate/km", "Speed", "Eff(km/1)");
   printf("----------------------------------------------------------------------------\n");
   for(int i = 0; i < vehicleCount; i++){
    printf("%d\t  %s\t\t  %d\t\t  %.2f\t\t  %.2f\t\t  %.2f\n",i+1, vehicleNames[i], capacities[i], rates[i], speeds[i], efficiencies[i]);
   }
}



 void handleDelivery(int distance[][MAX_CITIES], char cityNames[][30], int cityCount,char vehicleNames[][20], int capacities[], float rates[],float speeds[],
                     float efficiencies[], int vehicleCount, int deliverySource[], int deliveryDestination[], int deliveryVehicle[],
                    float deliveryFinalCharge[], int *deliveryCount){

  int source,destination,vehicleIndex;
  float weight;
    if(cityCount < 2){
        printf("Add at least 2 cities and distance first\n");
        return;
    }


    listCities(cityNames,cityCount);

    printf("\n\nEnter source city number:");
    scanf("%d", &source);
    printf("Enter destination city number:");
    scanf("%d", &destination);

    if (source <1 || source > cityCount || destination < 1 || destination > cityCount || source == destination){
        printf("Invalid source or destination.\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%f", &weight);


    displayVehicles(vehicleNames,capacities,rates,speeds,efficiencies,MAX_VEHICLES);
    printf("\n\nSelect vehicle type (1-3): ");
    scanf("%d", &vehicleIndex);
    vehicleIndex -= 1;

    if(weight > capacities[vehicleIndex]){
        printf("weight exceeds vehicle capacity.\n");
        return;
    }

    int dist = findShortestPath(source - 1, destination - 1, cityCount, distance, cityNames);
    printf("\nMinimum Distance Found: %d km\n", dist);

    if (dist <= 0 || dist >= 1e9) {
       printf("Invalid or missing distance data.\n");
       return;
    }

       float deliveryCost = dist * rates[vehicleIndex] * (1 + (weight / 10000.0));
       float time = dist / speeds[vehicleIndex];
       float fuelUsed = dist / efficiencies[vehicleIndex];
       float fuelCost = fuelUsed * FUEL_PRICE;
       float totalCost = deliveryCost + fuelCost;
       float profit =  totalCost * 0.25;
       float finalCharge = totalCost + profit;


    printf("\n---------------------------------\n");
    printf("----[ DELIVERY COST ESTIMATION ]----");

    printf("From: %s\n", cityNames[source - 1]);
    printf("To: %s\n",cityNames[destination - 1]);
    printf("Minimum Distance: %d km\n", dist);
    printf("Vehicle: %s\n", vehicleNames[vehicleIndex]);
    printf("Weight:%.2f kg\n",weight);
    printf("---------------------------------\n");
    printf("Delivery Cost: LKR %.2f\n", deliveryCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost:%.2f LKR \n", fuelCost);
    printf("Total Operational Cost:%.2f LKR \n", totalCost);
    printf("Profit (25%%):%.2f LKR \n", profit);
    printf("Final Charge to Customer:%.2f LKR \n", finalCharge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("---------------------------------");


    deliverySource[*deliveryCount] = source - 1;
    deliveryDestination[*deliveryCount] = destination - 1;
    deliveryVehicle[*deliveryCount] = vehicleIndex;
    deliveryFinalCharge[*deliveryCount] = finalCharge;
    (*deliveryCount)++;

}














 float findShortestPath(int source, int dest, int n, int roads[MAX_CITIES][MAX_CITIES],char cityNames[][30]){
  int dist[MAX_CITIES];
  int visited[MAX_CITIES] = {0};
  int prev[MAX_CITIES];

  for(int i = 0; i < n; i++){
    dist[i]= 1e9;
    prev[i]= -1;
  }
  dist[source] = 0;

  for( int count = 0; count < n-1; count++){
    int u = -1;
    int minDist = 1e9;


  for ( int i = 0; i < n; i++)
    if (!visited[i] && dist[i] < minDist)
        minDist = dist[i],u = i;

    if (u == -1)
        break;
    visited[u]=1;


    for (int v = 0; v < n; v++) {
       if (!visited[v] && roads[u][v] > 0 && dist[u] + roads[u][v] < dist[v]) {
           dist[v] = dist[u] + roads[u][v];
           prev[v] = u;
    }
  }
}

  printf("\nShortest path from %s to %s  :", cityNames[source], cityNames[dest]);
  int path[MAX_CITIES], len = 0, v = dest;

  while (v != -1){
    path[len++]=v;
    v = prev[v];
  }

  for (int i= len -1; i >=0; i--){
    printf("%s", cityNames[path[i]]);
    if (i > 0)printf("->");
  }

  return dist[dest];
}
