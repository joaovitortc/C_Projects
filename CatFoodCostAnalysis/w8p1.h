
//MACROS

#define MAX_PROD 3
#define NUM_GRAMS 64

// ----------------------------------------------------------------------------
// structures

struct CatFoodInfo {
    int sku;
    double price;
    int calories;
    double weight; //pounds (lbs)
};



// ----------------------------------------------------------------------------
// function prototypes

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int *wholeNum);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double *floatNum);

// 3. Opening Message (include the number of products that need entering)

void openingMessage(const int numProducts);

// 4. Get user input for the details of cat food product

struct CatFoodInfo getCatFoodInfo(int sequence);


// 5. Display the formatted table header

void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data

void displayCatFoodData(int sku, double price, double weight, int calories);

// 7. Logic entry point

void start(void);
