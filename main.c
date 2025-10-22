#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_VEHICLES 3
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0


int main()
{

    int choice;

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




    } while (choice != 0);


    return 0;
}


