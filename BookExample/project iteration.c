/*
 Judah Small
 CS2060-001 (TTh)
 OS: Windows
 HW-05
 Due: 03/15/2022
 Description: This is a step in the development of our ticket sales project this
 itteration focuses on the admin setup sequence
 the block validates the pin, assigns the charity percentage, and prices for each
 seat type. The validation of the completion of
 this sequence lets main decide if it should continue on ( in this case print the
 info tha the admin set up) or should it exit the
 program. This itteration is a test and continued exploration of utilizing pointers
 and passing by reference.
 */

#include <stdlib.h> //including of librairies for functions needed
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


#define PACKAGETYPES 4
#define YN 3 //options for acceptable yes or no values
#define SEATTYPES 4 //(number of choices plus admin escape)
#define ADMIN 4932 //admin pin
#define CHARITY_MIN 5.0 //min percentage
#define CHARITY_MAX 25.0 //max percentage
#define ADMIN_TRIES 3 //number of tries admin has to enter pin
#define CHARITY_EVENT "charity" //name of charity
#define EVENT_NAME "Nuggets Game" //name of event
#define CURRENCY_TYPE "$"

//The below 5 const MUST!!! all be in order so that when a user selects a seatchar(which returns an index value)
//the data from multiple different arrays can be easily accessible to myimplementation of the program.
const double min[] = {10.00, 75.01, 200.01};
const double max[] = {75.00, 200.00, 500.00};
//since there were some ranges that were not inclusive (< vs <=) and we are dealing with US$
//a case like x<i  meant that i was anything higher than the smallest denomination of incrimentation within the currency (in this case a penny)
const int PACKAGES[] = { 1, 2, 3, 4 };
const char* PACKAGENAMES[] = {"Single Pack", "Double Pack", "Triple Pack", "Family Pack"};
const char YNarray[] = { 'Y', 'N', 'Q' };
const char SEATCHAR[] = { 'U', 'M', 'C', 'Q' }; // letter codes for types
const char* SEATNAMES[] = { "(U)pper", "(M)id-Level", "(C)ourtside" }; // character array pointing to character arrays(/strings) for seat types

//function prototypes
bool adminSetup(double* charityPercentPtr, double priceArrayFill[]); //returns a bool and accepts a ptr to a double and a ptr to an array holding doubles
void ticketDisplayPrint(double charPercent, const double priceArrayFill[]);
bool adminPinValidate(void);
int charValidate(int validateType, int arraySize, const char validateArray[]);
int ticketSelection(const double setPrice[]);
int packageSelect(void);

int main(void)
{
    double prices[SEATTYPES - 1] = { 0.0, 0.0, 0.0 }; //seat types -1 because we do not want to include the Q value in the price array
    double charityPercent = 0.0; //initialization of charitypercentage
    bool isSetup = false; // initialization of the value returned from the completion of admin setup
    int selecVal = -2;
    int packageSel = 0;
    bool quit = 0;
    
    isSetup=(adminSetup(&charityPercent, prices)); // stored return of adminsetup func
    
    if (isSetup == true)
    {
        ticketDisplayPrint(charityPercent, prices);
        
        while (quit == 0)
        {
            selecVal = (ticketSelection(prices)); // can all be put in tix sales function like admin setup
        
            if (selecVal == -1)
            {
                //puts("gotta quit");
                quit = true; //admin validate pin
            }
            
            else
            {
                printf("%s%s\n", "Seat selection is: ", SEATNAMES[selecVal]);
                packageSel=(packageSelect());
                
                if (packageSel == -1)
                {
                    //puts("gotta quit");
                    quit = true; //admin validate pin
                }
                
                else
                {
                    puts("Receipt?");
                }
                
            }
            


        }
    }
    

    puts("Exiting");
    
    
    return 0; //ends main
    
    
    
}
///////////////////////////////////////// USER FUNCTION DEFINITIONS //////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////ADMIN////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to keep main clear uses 3 functions in one
bool adminSetup(double* charityPercentPtr, double priceArrayFill[])
{
    void charityAssign(double* charityptr); //includes the function prototypes because this is the only function that will use these funcs
    void priceAssign(double priceFill[]);
    bool pinSuccess = false; //initialize validation as false
    pinSuccess = (adminPinValidate()); //call for validation of pin and return if successful
    if (pinSuccess == true) //runs only if pin is true
    {
        priceAssign(priceArrayFill); //gets passed ptrs to values in main
        charityAssign(charityPercentPtr);
    }
    return pinSuccess;
}

//function to print what values the admin used in the setup
void ticketDisplayPrint(double charPercent, const double priceArrayFill[])
{
    //puts("\n\t-----------Admin Input---------\n ");
    printf("%.2lf%s%s\n", charPercent, "% of sales will be donated to ", CHARITY_EVENT); //displays percentage that will be donated
    for (size_t i = 0; i < (SEATTYPES - 1); i++)
    {
        printf("%s%s%s%.2lf%s\n", SEATNAMES[i], " tickets are ", CURRENCY_TYPE, priceArrayFill[i], " per person."); //prints prices next to each seattype
    }

}

//function to validate admins pin
bool adminPinValidate(void)
{
    bool numeric = false;
    int success = 0;
    int pin = 0;
    for (size_t i = 0; i < ADMIN_TRIES; i++)
    {
        puts("Enter the ADMIN Pin:");
        numeric = (scanf("%d", &pin));
        if (numeric == false)
        {
            while ((getchar()) != '\n');
        }
        else if (pin == ADMIN)
        {
            success = true;
            i = ADMIN_TRIES; //allows for loop to exit when a successful entry is entered
            puts("\nPin validated Succesfully\n");
        }
        else
        {
            while ((getchar()) != '\n'); //clears buffer
            if (i == (ADMIN_TRIES - 2))
            {
                puts("\nLast Attempt!\n"); //warns user that single attempt remains
            }
            else if (i == (ADMIN_TRIES - 1))
            {
                puts("\nPin validation Failure\n"); //indicator that the attempts were used up
            }
            else
            {
                puts("\nWarning incorrect pin, try again:\n"); // first incorrect entry
            }
        }
    }
    return success;
}

//function to assign prices to  price array
void priceAssign(double priceFill[])
{
    size_t listVal = 0; // value for display of seat types
    double priceEntered = 0.0;
    bool priceValid = 0; // if price falls within range
    bool validEntry = 0; //if price is numerical
    puts("Enter prices for the " EVENT_NAME ", the following seat types available for this event are: ");
    for (size_t i = 0; i < (SEATTYPES - 1); i++) //prints seattypes
    {
        listVal = i + 1;
        printf("%zu%s%s\n", listVal, ") ", SEATNAMES[i]);
    }
    puts(" "); //newline for formatting
    for (size_t j = 0; j < (SEATTYPES-1); j++)
    {
        while (priceValid == false) //starts loop assuming invalid
        {
            printf("%s", "Enter a price for ");
            printf("%s", SEATNAMES[j]);
            printf("%s%s%.2lf%s%s%.2lf%s\n", " (", CURRENCY_TYPE, min[j], " - ", CURRENCY_TYPE, max[j], ")"); //prints seatnames and range
            validEntry = (scanf("%lf", &priceEntered));
            puts(" ");
            if (validEntry == 0)
            {
                while ((getchar()) != '\n'); //clears buffer
                puts("Try again invalid input\n");
            }
            else if ((priceEntered >= min[j]) && (priceEntered <= max[j]))
            {
                priceFill[j] = priceEntered;
                while ((getchar()) != '\n'); //clears buffer if there were any extra chars
                priceValid = true; //escapes while because a valid value has been found
            }
            else
            {
                while ((getchar()) != '\n');
                puts("Try again outside of range\n");
            }
        }
        priceValid = false; // reinitializes price false so it re loops after the for increment for the next seat type
    }
}

//function to assign charity percent
void charityAssign(double* charityptr)
{
    double adminEntry = 0.0;
    bool validNum = 0;
    bool validEntry = 0;
    
    while (validNum == 0)
    {
        puts("Enter the percentage of sales to be donated to " CHARITY_EVENT);
        validEntry = (scanf("%lf", &adminEntry)); //return of result admin puts in for char
        if (validEntry == 0)
        {
            while ((getchar()) != '\n');
            puts("Invalid entry!\n");
        }
        
        else
        {
            if  (adminEntry <= 1.0) // I decided I wanted to include valid percents as .2 or 20
            {
                adminEntry = adminEntry*100;
                if ((CHARITY_MIN <= adminEntry) && (adminEntry<=CHARITY_MAX)) //checks to make sure its in range
                {
                    validNum = true;
                    while ((getchar()) != '\n'); //clears excess out of buffer
                }
                else
                {
                    while ((getchar()) != '\n');
                    puts("Invalid entry!\n"); //informs invalid and loops back to top of while
                }
            }
            
            else if ((CHARITY_MIN <= adminEntry) && (adminEntry <=CHARITY_MAX)) //this is the check on numbers above 1
            {
                validNum = true;
                while ((getchar()) != '\n');
            }
            
            else
            {
                while ((getchar()) != '\n'); //clears buffer if it is not in the range
                puts("Invalid entry!\n");
            }
        }
    }
        *charityptr = adminEntry; //fills the charity percent value in main with what admin enters if and only if validation has occured
}

//////////////////////////////////////////////////////////////////////SALES///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ticketSales(void) //ticket selection
{
//display types with prices
//call ticket selection
//call package selection

    return 0;
    
}


int ticketSelection(const double setPrice[])
{
    int customerIndexValue = 0; // initialization of the returned value to main
    bool confirmed = 0; //possibly bool but need to accept yes no or q
    int yesNo = 0;

    while (confirmed == 0) // this is the escape value at the end of the array q
    {

        customerIndexValue = (charValidate(0, SEATTYPES, SEATCHAR)); // calls the char validate function in order to allow for input to happen until a valid input occurs
        
        if (customerIndexValue == (SEATTYPES - 1)) // if admin escape is entered
        {
            customerIndexValue = -1;
            confirmed = 1;//break out of while to return what selection was made
        }
        
        else
        {
            printf("%s%s\n%s%s%.2lf\n%s\n", "You have selected ", SEATNAMES[customerIndexValue], "Ticket price is: ", CURRENCY_TYPE, setPrice[customerIndexValue], "Do you wish to continue with this selection?"); // this is the call to print the string contained within the SEATNAMES array at the element returned
            
            yesNo = (charValidate(1, YN, YNarray));
            
            if (yesNo == (YN - 1))//if admin escape is entered
            {
                customerIndexValue = -1;
                confirmed = 1;//break out of while to return what selection was made
            }

            
            else if (yesNo == 0)
            {
                confirmed = 1;
            }
            
        }
        

    }
    
    return customerIndexValue;
}


int charValidate(int validateType, int arraySize, const char validateArray[]) // passing a key to unlock print message  the array to iterate through and its size
{
    char entry = ' '; // initialize char as a blank value
    bool valid = 0;// bool loops to allow affirmation of validity
    bool charinput = 0;
    int indexVal = -1; // setting number outside of the array to tell if the index value has been manipulated or not
    
    if(validateType==0) //logic for seat level
    {
        printf("%s", "Enter your seat Level (C)ourtside (M)id - level or (U)pper\n");
    }
     
    else if(validateType==1) // logic for yes no
    {
        printf("%s", "Enter y for yes or n for no\n");
    }
    
    while (valid == 0) // runs until the input is valid
    {
    
        charinput = (scanf("%c", &entry)); // return value to ensure that a char was entered

        if (charinput == 0)
        {
            while ((getchar()) != '\n'); // clears the buffer
        }

        else
        {
            entry = toupper(entry); // converts input to an uppercase letter

            for (int i = 0; i < arraySize; i++)
            {
                if (entry == validateArray[i])  //loops through the entire array checking for equivalency at each index of the array
                {
                    indexVal = i; // takes the value of the index that was equivalent
                    valid = true; // sets valid to true to be able to escape loop
                    while ((getchar()) != '\n'); // clears the buffer
                    i = arraySize;  //sets it to the end of the array in order for the loop to end once the value has found equivalency
                }
            }
                
            if (indexVal == -1) // this means the index was never manipulated
                    // it was a valid integer but it was not an available option
            {
                while ((getchar()) != '\n'); // clears the buffer
            }
        }// end else
    }//end while
    
    return indexVal; // value returned to main that allows for the manipulation of all the constant arrays
    
 } //end charValidate

int packageSelect(void)
{
    
    int package = 0;
    int indexVal = -1;
    int yesNo = 0;
    bool validEntry = 0;
    bool validType =0;
    
    
    while(validType==0)
        
    {
        puts("Package options are: ");
        
        for (size_t i = 0; i < PACKAGETYPES; i++)
        {
            printf("%d%s\t%s\n", PACKAGES[i], ")", PACKAGENAMES[i]); //prints prices next to each seattype
        }
        
        puts("Enter your package selection:");
        
        validEntry=(scanf("%d", &package));
    
        if (validEntry == 0)
        {
            while ((getchar()) != '\n');
        }
        
        else
        {
            for (int i = 0; i < PACKAGETYPES; i++)
            {
                if (package == PACKAGES[i])  //loops through the entire array checking for equivalency at each index of the array
                {
                    indexVal = i; // takes the value of the index that was equivalent
                    //validType = true; // sets valid to true to be able to escape loop
                    while ((getchar()) != '\n'); // clears the buffer
                    i = PACKAGETYPES;  //sets it to the end of the array in order for the loop to end once the value has found equivalency
                }
            }
            
            if (indexVal == -1) // this means the index was never manipulated
                    // it was a valid integer but it was not an available option
            {
                while ((getchar()) != '\n'); // clears the buffer
            }
            
            else
            {
                printf("%s%d%s%s\n%s\n", "You have selected ", PACKAGES[indexVal], ") ", PACKAGENAMES[indexVal], "Do you wish to continue with this selection?");
                yesNo = (charValidate(1, YN, YNarray));
                
                if (yesNo == (YN - 1))//if admin escape is entered
                {
                    indexVal = -1;
                    validType = 1;//break out of while to return what selection was made
                }

                
                else if (yesNo == 0)
                {
                    validType = 1;
                }
                
            }
        }
         // check entry in accordance with packegetypes if it exists yes no validate else repeat if no repeat only valid on yes
    }
    
    return indexVal;
    
}


