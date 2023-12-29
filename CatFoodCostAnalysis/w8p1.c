#define _CRT_SECURE_NO_WARNINGS


// System Libraries
#include <stdio.h>

// User Libraries
#include "w8p1.h"

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* wholeNum) {
	int tempInt;
	int done = 0;
	do {
			scanf(" %d", &tempInt);
			if (tempInt <= 0)
				printf("ERROR: Enter a positive value: ");
			else {
				done = 1;
			}

			if (wholeNum != NULL && tempInt > 0) {
				*wholeNum = tempInt;
			}

	} while (done == 0);

	return tempInt;
}

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* floatNum) {
	double tempDouble;
	int done = 0;
	do {
		scanf(" %lf", &tempDouble);
		if (tempDouble <= 0.0)
			printf("ERROR: Enter a positive value: ");
		else {
			done = 1;
		}

		if (floatNum != NULL && tempDouble > 0) {
			*floatNum = tempDouble;
		}

	} while (done == 0);

	return tempDouble;
}

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int numProducts) {
	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n");
	printf("Enter the details for %d dry food bags of product data for analysis.\n", MAX_PROD);
	printf("NOTE: A 'serving' is %dg\n", NUM_GRAMS);

}


// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(int i){

	struct CatFoodInfo product;

	printf("\n");
	printf("Cat Food Product #%d\n", i + 1);
	printf("--------------------\n");
	printf("SKU           : ");
	product.sku = getIntPositive(NULL);
	printf("PRICE         : $");
	product.price = getDoublePositive(NULL);
	printf("WEIGHT (LBS)  : ");
	product.weight = getDoublePositive(NULL);
	printf("CALORIES/SERV.: ");
	product.calories = getIntPositive(NULL);

	return product;
}

// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("\nSKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Display a formatted record of cat food data

void displayCatFoodData(int sku, double price, double weight, int calories) {
	printf("%07d %10.2lf %10.1lf %8d\n", sku, price, weight, calories);
}

// 7. Logic entry point

void start(void) {
	int i;
	struct CatFoodInfo members[MAX_PROD];

	openingMessage(MAX_PROD);
	for (i = 0; i < MAX_PROD; i++) {
		members[i] = getCatFoodInfo(i);
	}
	displayCatFoodHeader();
	for (i = 0; i < MAX_PROD; i++) {
		displayCatFoodData(members[i].sku, members[i].price, members[i].weight, members[i].calories);
	}
}