
#define _CRT_SECURE_NO_WARNINGS


// System Libraries
#include <stdio.h>

// User Libraries
#include "w8p2.h"

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
struct CatFoodInfo getCatFoodInfo(int i) {

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



// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg (divide by 2.20462)

double convertLbsKg(double* weightLbs, double* weightKg) {
	double temp;

		temp = *weightLbs / LBS_TO_KG;

		if (weightKg != NULL) {
			*weightKg = temp;
		}

	return temp;
}

// 9. convert lbs: g (call convertKG, then * 1000)

int convertLbsG(double* weightLbs, int* weightGrams){
	int temp;

	temp = (int)(convertLbsKg(weightLbs, NULL) * 1000);

	if (weightGrams != NULL) {
		*weightGrams = temp;
	}

	return temp;
}

// 10. convert lbs: kg and g
void convertLbs(double* weightLbs, double* weightKg, int* weightGrams) {
	int tempInt;
	double tempDouble;

	tempDouble = convertLbsKg(weightLbs, NULL);
	tempInt = convertLbsG(weightLbs, NULL);

	*weightKg = tempDouble;
	*weightGrams = tempInt;
}

// 11. calculate: servings based on gPerServ

double calculateServings(int serving, int grams, double* totalServings) {
	double tempServings;

	tempServings = (double)grams / (double)serving;

	if (totalServings != NULL) {
		*totalServings = tempServings;
	}

	return tempServings;
}

// 12. calculate: cost per serving

double calculateCostPerServing(double price, double servings, double* costPerServing) {
	double tempCost;

	tempCost = price / servings;

	if (costPerServing != NULL) 
		*costPerServing = tempCost;
	
	return tempCost;
}

// 13. calculate: cost per calorie

double calculateCostPerCal(double price, double calories, double* costPerCalorie){
	double tempCost;

	tempCost = price / calories;

	if (costPerCalorie != NULL)
		*costPerCalorie = tempCost;

	return tempCost;
}
// 14. Derive a reporting detail record based on the cat food product data

struct ReportData calculateReportData(struct CatFoodInfo a) {
	struct ReportData temp;

	temp.sku = a.sku;
	temp.calories = a.calories;
	temp.price = a.price;
	temp.weightLbs = a.weight;
	convertLbsKg(&temp.weightLbs, &temp.weightKg);                                         //Just using different methods: function called with address of variable AND
	convertLbsG(&temp.weightLbs, &temp.weightGrams);                                       //      variable assigned with function returning value passing NULL pointer
	temp.totalServings = calculateServings(NUM_GRAMS, temp.weightGrams,  NULL);
	temp.costPerServing = calculateCostPerServing(temp.price, temp.totalServings, NULL);
	temp.caloriesPerServing = calculateCostPerCal(temp.costPerServing, temp.calories, NULL);

	return temp;
}
// 15. Display the formatted table header for the analysis results
void displayReportHeader(void)
{
	printf("\nAnalysis Report (Note: Serving = %dg)\n", NUM_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. Display the formatted data row in the analysis table

void displayReportData(struct ReportData Reports, int isCheapest) {
	printf("%07d % 10.2lf % 10.1lf % 10.4lf % 9d % 8d % 8.1lf % 7.2lf %7.5lf",
		Reports.sku, Reports.price, Reports.weightLbs, Reports.weightKg, Reports.weightGrams, Reports.calories, 
		Reports.totalServings, Reports.costPerServing, Reports.caloriesPerServing);

	if (isCheapest == 1)
		printf(" ***");
	printf("\n");
}


// 17. Display the findings (cheapest)

void displayFinalAnalysis(struct ReportData Cheapest) {
	printf("\nFinal Analysis\n");
	printf("--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d Price: $%.2lf\n", Cheapest.sku, Cheapest.price);
	printf("\nHappy shopping!\n");
}

// ----------------------------------------------------------------------------

// 7. Logic entry point
void start(void)
{

//part 1: 
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
//part 2:

	struct ReportData Reports[MAX_PROD];
	int cheapest = 0;
	
	for (i = 0; i < MAX_PROD; i++) {
		Reports[i] = calculateReportData(members[i]);
	}

	double temp = Reports[0].costPerServing;
	for (i = 0; i < MAX_PROD; i++) {
		if (Reports[i].costPerServing <= temp) {
			temp = Reports[i].costPerServing;
			cheapest = i;
		}	
	}

	displayReportHeader();
	
	for (i = 0; i < MAX_PROD; i++) {
		displayReportData(Reports[i], (i == cheapest));
	}

	displayFinalAnalysis(Reports[cheapest]);
}
