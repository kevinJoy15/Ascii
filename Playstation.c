#include <stdio.h>
#include <string.h>
#include <math.h>

int atoi_ex(const char *s, int *error) 
{
    int sign = 1;
    int integer = 0;

    // this is to gauge the sign of the integer value
    int startVal = 0;

    for (int i = 0; i < strlen(s); i++)   // cycles through to find the sign
    {
        if(s[i] == ' ')     // if whitespace ignore
        {
            sign = 1;
        }
        else if(s[i] == '-')        // '-' indicating negative assigns sign 
        {
            sign = -1;
            startVal = i+1;             // tells us also the 1st non white space character
            break;
        }
        else if(s[i] == '+')
        {
            sign = 1;
            startVal = i+1;
            break;
        }
        else                // no sign to be found hence positive
        {
            startVal = i;
            break;
        }
    }

    // this checks for all false starts including no vlaue, and starting with a non digit value
    if((s[startVal] - '0') < 0 || (s[startVal] - '0') > 9)     
    {
        printf("wrong start value");
        error = 0;
        return 0;
    }

    // this checks for all hexadecimal values
    else if(s[0] == '0' && s[1] == 'x' && strlen(s) <= 6)
    {
        int endVal = 0;
        int letterVal;
        int numberVal;

        for(int i = 2; i < strlen(s);i++)           // to check till which character is a right value and trim it till the either a false value of the end of the string
        {
            letterVal = (int)s[i];      // gets the ascii value of the character
            numberVal = s[i] - '0';         // gets the integer vvalue of the character

            if(letterVal >= 97 && letterVal <= 102 || letterVal >= 65 && letterVal <= 70 || numberVal >= 0 && numberVal <= 9)   // checks valid characters
            {
                endVal = i; 
            }
            else  
            {
                break;
            }
        }
        
        if(endVal == 0)    
        {
            printf("wrong input value");
            error = 0;
            return 0;
        }

        //printf("perform hexadecimal");
        int cnt = 0;            // counter vasriable that tracks the number of multiplications that are to be needed  
        int chk = 0;            // checks if its a first occurance of a non digit or alphabet from 'A' to 'F'
        
        for(int i = endVal; i>1; i--)         // cycles the string backwards
        {
            // checks fo the current value
            letterVal = (int)s[i];
            numberVal = s[i] - '0';

            if(letterVal >= 97 && letterVal <= 102)                     // checks for small 'a' to 'f'
            {
                integer = integer +  ((letterVal - 87)*pow(16,(double)cnt));
                chk = 1; 
            }
            else if(letterVal >= 65 && letterVal <= 70)                 // checks for capital 'A' to 'F' 
            {
                integer = integer +  ((letterVal - 55)*pow(16,(double)cnt));
                chk = 1; 
            }
            else if(numberVal >= 0 && numberVal <= 9)         // checks for numbers from 0 to 9
            {
                integer = integer + (numberVal*pow(16,(double)cnt));
                chk = 1;
            }
            cnt = cnt +1;               // incrementing the counter
        }

        printf("hex value: %d", integer);
        return integer;             // returns the value
    }

    integer = 0;            // reasseing the value to 0 for integer
    for (int i = startVal; i < strlen(s); i++)    // cycles through the string
    {
        int val = s[i] - '0';           // gets the integer value of the character 

        if(val >=0 && val <= 9)         // checks bounds
        {
            integer = integer*10 + val;         // if so multiplies 10 with the existing integer and adds the integer character value to it
        }
        else if(s[i] != ' ')        // white - space
        {
            break;
        }
    }

    integer = sign * integer;           // multiples the sign to the end integer

    if(integer >= 2147483647)       // cant be above this value for an integer
    {
        return 2147483647;
    }
    return integer;             // returns the integer
}


int main()      // main method to test
{

  char str[] = "0xffff";
  int error = 0;
  atoi_ex(str, &error);
  return 0;
}
