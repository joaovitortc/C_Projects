
//MACROS

#define MAX_PROD 3
#define NUM_GRAMS 64
#define LBS_TO_KG 2.20462
// ----------------------------------------------------------------------------
// structures

struct CatFoodInfo {
    int sku;
    double price;
    int calories;
    double weight; //pounds (lbs)
};

struct ReportData {
    int sku;
    double price;
    int calories;
    double weightLbs;
    double weightKg;
    int weightGrams;
    double totalServings;
    double costPerServing;
    double caloriesPerServing;

};

// ----------------------------------------------------------------------------
// function prototypes

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* wholeNum);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* floatNum);

// 3. Opening Message (include the number of products that need entering)

void openingMessage(const int numProducts);

// 4. Get user input for the details of cat food product

struct CatFoodInfo getCatFoodInfo(int sequence);


// 5. Display the formatted table header

void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data

void displayCatFoodData(int sku, double price, double weight, int calories);


// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg

double convertLbsKg(double* weightLbs, double* weightKg);

// 9. convert lbs: g

int convertLbsG(double* weightLbs, int* weightGrams);

// 10. convert lbs: kg / g

void convertLbs(double* weightLbs, double* weightKg, int* weightGrams);

// 11. calculate: servings based on gPerServ

double calculateServings(int serving, int grams, double* totalServings);

// 12. calculate: cost per serving

double calculateCostPerServing(double price, double servings, double* costPerServing);

// 13. calculate: cost per calorie
double calculateCostPerCal(double price, double calories, double* costPerCalorie);

// 14. Derive a reporting detail record based on the cat food product data

struct ReportData calculateReportData(struct CatFoodInfo);
// 15. Display the formatted table header for the analysis results
void displayReportHeader(void);

// 16. Display the formatted data row in the analysis table
void displayReportData(struct ReportData Reports, int isCheapest);

// 17. Display the findings (cheapest)
void displayFinalAnalysis(struct ReportData Cheapest);

// ----------------------------------------------------------------------------

// 7. Logic entry point 

void start(void);
