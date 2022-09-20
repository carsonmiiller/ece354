/******************************************************************************
 * @file: functions.c
 *
 * cmiller77
 * Carson Miller
 * 9081473028
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Carson Miller
 * @modified: SUBMISSION DATE
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

/*
 * This method returns 1 if the input char is a letter (A-Z, a-z) and 0
 * if not.
 *
 * @param letter : char being evaluated
 * @return 1 if letter, 0 if not
 */
int IsLetter(char letter){
    if((65 <= letter && letter <= 90) || (97 <= letter && letter <= 122))
        return 1;
    return 0;
}

/*
 * This method return 1 if the input char is a digit (0-9) and 0
 * if it is not a digit.
 *
 * @param digit : char being evaluated for digit or not
 * @return 1 if digit, 0 if not
 */
int IsDigit(char digit){
	if(48 <= digit && digit <= 57)
		return 1;
	return 0;
}

/*
 * This method returns the length of a char array in terms of the number
 * of chars in the array, not memory space taken up by the array.
 *
 * @param user : char array of which we are trying to find the length of
 * @return length of string represented by char array
 */ 
int Length(char user[]){
	int i = 0;
	while(user[i] != '\0')
		i++;
	return i;
}

/*
 * This method iterates through a char array to find a specified char.
 * If the char is found within the char array, the method returns a
 * pointer to the char find
 *
 * @param find : char desired to be found in array
 * @param str : char array being searched through
 * @return pointer to the char find
 */
char * Find(char find, char str[]){
	char * find_pointer = "";
	int i = 0;
	if(find == '\0'){
		find_pointer = str + Length(str) - 1;
		return find_pointer;
	}
	while(str[i] != '\0'){
		if(str[i] == find)
			find_pointer =  str + i;
		i++;
	}
	return find_pointer;
}

/*
 * This method iterates through a char array to find a specified char.
 * If the char is found within the char array, the method returns the first index
 * of the char in the array. If the char is not found, the method returns -1.
 *
 * @param find : char desired to be found in array
 * @param str : char array being searched through
 * @return last index of 'find' in 'str' if 'str' contains 'find', -1 otherwise
 */
int FindIndex(char find, char str[]){
	char findIndex = -1;
	int i = 0;
	while(str[i] != '\0'){
		if(str[i] == find)
			findIndex =  i;
		i++;
	}
	return findIndex;
}

/*
 * This method finds invalid chars in a given string, but differs from FindInvalid
 * because this method is meant for finding invalid chars in the domain of the email
 * so it doesn't count '.' as an invalid char
 *
 * @param str : char array being evaluated for invalid chars
 * @return 1 if invalid chars found, 0 otherwise
 */
int FindInvalidDomain(char str[]){
	// iterate through each char in user
	for(int i = 0; str[i] != '\0'; i++){
		// check to make sure char isn't a letter, digit, or underscore
		if(!IsLetter(str[i]) && !IsDigit(str[i]) && str[i] != 46)
			return 1; // 1 indicates not a valid char
	}
	return 0; // 0 indicates all chars are valid
}

/*
 * This method finds invalid chars in a given string, but differs from FindInvalid
 * because this method is meant for finding invalid chars in the name of the email
 * Valid chars for this case are letters and digits.
 *
 * @param str : char array being evaluated for invalid chars
 * @return 1 if invalid chars found, 0 otherwise
 */
int FindInvalidEmailName(char str[]){
	// iterate through each char in user
	for(int i = 0; str[i] != '\0'; i++){
		// check to make sure char isn't a letter, digit, or underscore
		if(!IsLetter(str[i]) && !IsDigit(str[i]))
			return 1; // 1 indicates not a valid char
	}
	return 0; // 0 indicates all chars are valid
}

/*
 * This method checks to see if any invalid characters are used
 * in the input char array. Invalid characters are any characters other
 * than a letter, digit, or underscore. It returns 1 if any invalid
 * characters are found and 0 otherwise.
 *
 * @param user : input string being tested for invalid characters
 * @return 1 if invalid, 0 otherwise
 */
int FindInvalid(char user[]){
	// iterate through each char in user
	for(int i = 0; user[i] != '\0'; i++){
		// check to make sure char isn't a letter, digit, or underscore
		if(!IsLetter(user[i]) && !IsDigit(user[i]) && user[i] != 95)
			return 1; // 1 indicates not a valid char
	}
	return 0; // 0 indicates all chars are valid
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
	
    dbgprintf("This line only prints if DEBUG is set to 1\n");
	
	// if first char in user isn't a letter, print error message and return 0
	if(!IsLetter(user[0])){
		printf(ERROR_01_USER_START_INVALID);
		return 0;
	}
	
	// if length of username is greater than 32, print error message and return 0
	if(Length(user) > 32){
		printf(ERROR_02_USER_LEN_INVALID);
		return 0;
	}
	
	// if invalid characters are found in username, print error message and return 0
	if(FindInvalid(user)){
		printf(ERROR_03_USER_CHARS_INVALID);
		return 0;
	}
	
	printf(SUCCESS_1_USER);
    return 1;
    /* END MODIFYING CODE HERE */
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
	
	// if index 0 in email array is @ char, print error and return 0
	if(FindIndex('@',email) == 0){
		printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
		return 0;
	}
	
	// if index 0 in email array isn't a letter, print error and return 0
	if(!IsLetter(email[0])){
		printf(ERROR_05_EMAIL_START_INVALID);
		return 0;
	}
	
	// find and store email name in char array
	int at_index = FindIndex('@',email);
	char EmailName[at_index];
	// email name is found in email char array before '@' symbol
	for(int i = 0; i < at_index; i++){
		EmailName[i] = email[i];
	}
	EmailName[at_index] = '\0';
	
	// if length of email name is greater than 32, print error and return 0
	if(Length(EmailName) > 32){
		printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
		return 0;
	}
	
	// if part of email before '@' symbol has invalid characters, print error and return 0
	if(FindInvalidEmailName(EmailName)){
		printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
		return 0;
	}

	// if email doesn't contain an '@' char, print error and return 0
	if(FindIndex('@',email) == -1){
		printf(ERROR_08_EMAIL_MISSING_SYMBOL); // example mike.wisc.edu
		return 0;
	}
	
	// find and store domain in char array
	// Length(email) is much too long and corrupts domain char array by adding trash to end
	char longDomain[Length(email)];
	int k = 0;
	for(int i = 0; i < Length(email); i++){
		// domain is found after '@' symbol but before last index of '.'
		if(i > FindIndex('@',email) && i <= FindIndex('.',email)){
			longDomain[k] = email[i];
			k++;
		}
	}
	// transers meaningful part of longDomain to a shorter char array domain
	int stop = FindIndex('.',longDomain);
	char domain[stop];
	for(int i = 0; i < stop; i++)
		domain[i] = longDomain[i];
	domain[stop] = '\0';
	
	// if domain doesn't exist (length equals 0), print error and return 0
	if(Length(domain) == 0){
		printf(ERROR_09_EMAIL_MISSING_DOMAIN); // example mike@.edu
		return 0;
	}
	
	// if domain length is greater than 64, print error and return 0
	if(Length(domain) > 64){
		printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
		return 0;
	}
	
	// if domain starts with a char that is not a letter, print error and return 0
	if(!IsLetter(domain[0])){
		printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
		return 0;
	}
	// if any char besides a letter follows a '.' char in the domain, print error and return 0
	for(int i = 0; i < Length(domain); i++){
		if(domain[i] == '.'){
			if(!IsLetter(domain[(i + 1)])){
				printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
				return 0;
			}
		}
	}
	
	// if domain contains any invalid chars, print error and return 0		
	if(FindInvalidDomain(domain)){
		printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
		return 0;
	}
	
	// find and store top-level domain in char array
	char TLdomain[4];
	int x = 0;
	for(int i = 0; i < Length(email); i++){
		// top-level domain is found starting with last index of '.' and goes to end of email
		if(i >= FindIndex('.',email)){
			TLdomain[x] = email[i];
			x++;
		}
	}
	// if top-level domain is not equal to any of the allowed top-level domains, print error and return 0
	if(!(TLdomain[0] == '.' && TLdomain[1] == 'e' && TLdomain[2] == 'd' && TLdomain[3] == 'u')
		&& !(TLdomain[0] == '.' && TLdomain[1] == 'c' && TLdomain[2] == 'o' && TLdomain[3] == 'm')
		&& !(TLdomain[0] == '.' && TLdomain[1] == 'n' && TLdomain[2] == 'e' && TLdomain[3] == 't')){
		printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
		return 0;
	}

    /* END MODIFYING CODE HERE */
    
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
	// if password contains a space char, print error and return 0
	if(FindIndex(' ',pwd) != -1){
		printf(ERROR_14_PWD_SPACES_INVALID);
		return 0;
	}
	
	// if password length is less than 8, print error and return 0
	if(Length(pwd) < 8){
		printf(ERROR_15_PWD_MIN_LEN_INVALID);
		return 0;
	}
	
	// if password length is greater than 16, print error and return 0;
	if(Length(pwd) > 16){
		printf(ERROR_16_PWD_MAX_LEN_INVALID);
		return 0;
	}
	
	// if password doesn't contain an uppercase char, print error and return 0
	int upperCaseCount = 0;
	for(int i = 65; i < 91; i++){
		if(FindIndex((char)i,pwd) != -1)
			upperCaseCount++; // only increments above 0 if uppercase letter is found
	}
	if(upperCaseCount == 0){
		printf(ERROR_17_PWD_MIN_UPPER_INVALID);
		return 0;
	}
	
	// if password doesn't contain a lowercase char, print error and return 0
	int lowerCaseCount = 0;
	for(int i = 97; i < 123; i++){
		if(FindIndex((char)i,pwd) != -1)
			lowerCaseCount++; // only increments above 0 if lowercase letter is found
	}
	if(lowerCaseCount == 0){
		printf(ERROR_18_PWD_MIN_LOWER_INVALID);
		return 0;
	}
    
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
	// find which password is longer
	int maxLength = 0;
	if(Length(pwd1) > Length(pwd2))
		maxLength = Length(pwd1);
	else
		maxLength = Length(pwd2);
	
	// iterate through both passwords and compare char by char to see if they match
	for(int i = 0; i < maxLength; i++){
		if(pwd1[i] != pwd2[i]){
			printf(ERROR_19_PWD_MATCH_INVALID);
			return 0;
		}
	}
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */
	int i = 0;
	while(data[i] != '\n')
		i++;
	data[i] = '\0';
    /* END MODIFYING CODE HERE */
    return;
}
