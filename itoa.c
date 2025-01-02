
/**
 * @brief Converts an integer to a string
 *
 * @param x The integer to convert
 */
#include "LCD.h"

void myitoa2(int x)
{
	unsigned char str[5],temp;
	int rem=0,i=0,j=0,y;
	y=x;
	if(x<0)
	{
		// Make x positive
		x=-x;
	}
	while(x>0)
	{
		// Get the remainder of x divided by 10
		rem=x%10;
		// Convert the remainder to a character and store it in str
		str[i]=48+rem;
		// Divide x by 10
		x=x/10;
		// Increment i
		i++;
	}
	if(y<0)
	{
		// Add a negative sign to the string
		str[i]='-';
		i++;
	}
	// Null terminate the string
	str[i]='\0';
	// Reverse the string
	for(j=0;j<i;j++)
	{
		// Swap the characters at index j and i-j
		i--;
		temp=str[j];
		str[j]=str[i];
		str[i]=temp;
		
		 

	}
	// Print the string to the LCD
	lcd(str);

}
