#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX_FILE 100000

//here we declare the Structure account
struct account{
	long int acc_no;
	char name[30];
	double balance;
	double amount;
	char transaction[9];
	int transactionid;
	struct account *next;
	struct account *prev;
};

//These are the prototypes of all the methods used in this project
double toDouble(char a[]);
void displayProfile(long int acc_no);
int readFile(const char fileName[], char textStr[]);
struct account *createNode(long int acc_no , char name[] , double balance , double amount , char transaction[], int transactionid);
void addAccount(long int acc_no , char name[] , double balance , double amount , char transaction[], int transactionid);
void printList(void);
void LoadFile(void);
bool isWord(char a[20]);
struct account* searchList(long int acc);
void dailyTransaction(long int accno);
void listAccounts(void);
void BubbleSort(void);
long int toLong(char acc[7]);
struct account * Searchlatestaccount(int long acc_no);
void displayCustomerRecord(long int acc_no);
void deleteAccount(void);
void updateAccount(int long accNo);
void QuickSort(void);
int cmpfunc(const void* a, const void* b);
//here we declare head and tail globally to null
struct account *head = NULL;
struct account *tail = NULL;


int main(int argc, char** argv){
	
	char name[20];
	double amount;
	int input;
	long int accNo;
	LoadFile();
	printf("Welcome to the Banking Application\nSelect any of the following steps to proceed-\n");
	bool Counter = true;
	while(Counter){
		printf("\nEnter 1 to Add account \n");
		printf("Enter 2 to Deposit or Withdraw\n");
		printf("Enter 3 to display the list of all accounts\n");
		printf("Enter 4 to search customer\n");
		printf("Enter 5 display customer record\n");
		printf("Enter 6 to update account\n");
		printf("Enter 7 to delete latest transaction or account\n");
		printf("Enter 8 to display the database\n");
		printf("Enter 9 to quit\n");
		fflush(stdin);
		scanf("%d",&input);			//here we get the input from the user to proceed
		switch(input){
			case 1:
				fflush(stdin);
				//here we invoke the function to read data from the user and add a student node in our linked list
				printf("\nEnter name of the Account Holder of length less than 21 characters - ");
				scanf("%s",name);
				if(strlen(name) < 21 && isWord(name)){		//here we validate the name
					printf("\nEnter the account number of length 7 digits - ");
					if((scanf("%ld",&accNo) == 1) && (accNo / 1000000) > 0 ){		//here we validate the account number
						printf("\nNew accounts cannot have 0 balance, so Enter the amount to Deposit in the new Account-");
						if((scanf("%lf",&amount)) == 1){				//here we validate the amount
						addAccount(accNo,name,0,amount,"Deposit_",1);
						}
						else{
							printf("\nAction terminated! Invalid input entered.\n\n");
							fflush(stdin);
						}
					}
					else{
						printf("\nAction terminated! account number should be of 7 numbers.\n\n");
						fflush(stdin);
					}
				}
				else{
					printf("\nAction terminated! Invalid input, the name should contain not more than 20 characters.\n\n");
					fflush(stdin);
				}
				break;
			case 2:
				fflush(stdin);
				printf("\nEnter Account number - \n");
				if(scanf("%ld",&accNo) == 1 && (accNo/1000000) > 0){		//here we validate the account number
					dailyTransaction(accNo);						//here we invoke the function to make a new transaction
				}
				else{
					printf("\nAction terminated! Invalid input\n\n");
					fflush(stdin);
				}
				break;
			case 3:
				fflush(stdin);
				listAccounts();					//here we invoke the function to list all the account numbers
				break;
			case 4:
				fflush(stdin);
				printf("\nEnter the account number : ");
				if((scanf("%ld",&accNo) == 1) && (accNo / 1000000) > 0 ){		//here we validate the account number
					displayProfile(accNo);				//here we invoke the function to display the customer profile
				}
				else{
					printf("\nInvalid Account number entered");
				}
				break;
			case 5:
				fflush(stdin);
				printf("\nEnter account number - \n");
				if((scanf("%ld",&accNo) == 1) && (accNo / 1000000) > 0 ){			//here we validate the account number
					displayCustomerRecord(accNo);					//here we invoke a function to display the customer statement
				}
				else{
					printf("\nAction terminated! Invalid input, the name should contain not more than 20 characters.\n\n");
					fflush(stdin);
				}
				break;
			case 6:
				fflush(stdin);
				printf("\nEnter account number - \n\n");
				if((scanf("%ld",&accNo) == 1) && (accNo / 1000000) > 0 ){		//here we validate the account number
					updateAccount(accNo);			//here we invoke the function to upadate account info
				}
				else{
					printf("\nAction terminated! Invalid input, the name should contain not more than 20 characters.\n\n");
					fflush(stdin);
				}
				break;
			case 7:
				fflush(stdin);
				printf("\n");
				deleteAccount();				//here we invoke the function to delete the latest transaction or account
				break;
			case 8:
				printf("\n");
				fflush(stdin);
				//BubbleSort();					//here we invoke a function to sort using bubble sort
				QuickSort();					//here we invoke a function to sort using qsort
				printList();
				break;
			case 9:
				printf("\nProgram Terminated, Have a Nice Day");
				Counter = false;				//here we quit the program
				break;
			default:
				printf("\nInvalid Input! Try again\n\n");
				break;
		}
	}
}//end of main method

void deleteAccount(){
	int long accNo;
	printf("Enter the account number : ");
	if((scanf("%ld",&accNo) == 1) && (accNo / 1000000) > 0 ){			//here we validate the account number
			struct account *acc = Searchlatestaccount(accNo);
			if(head == NULL || acc== NULL){					//here we check if head or searched account is NULL or not
				return;
			}
			if(acc == head){						//here we search if the account is the head
				head = acc->next;
			}
			if(acc->next != NULL){
				acc->prev->next = acc->prev;
			}
			if(acc->prev != NULL){
				acc->prev->next = acc->next;
			}
			free(acc);							//here we delete the account
			printf("\n Account deleted successfuly");
	}
	else
	{
		printf("Invalid input entered ");
		fflush(stdin);
	}
}

void displayProfile(long int acc_no){
	struct account *acc = Searchlatestaccount(acc_no);		//here we search the required account
	printf("\nAcc. Number\t");
	printf("Name\t\t");
	printf("Transaction\t");
	printf("Transaction Amount\t");
	printf("Balance\t");
	printf("TransactionID");
	printf("\n%ld\t\t",acc->acc_no);
	printf("%s\t\t",acc->name);
	printf("%s\t",acc->transaction);
	printf("%7.2lf\t\t\t",acc->amount);
	printf("%7.2lf\t\t\t\t",acc->balance);
	printf("%d\n",acc->transactionid);
}

void updateAccount(int long accNo){
	char name[20];
	printf("Enter the new Account holder name - ");
	scanf("%s",name);
	if(strlen(name) < 21 && isWord(name)){			//here we validate the account number
		struct account* acc = head;
		while(acc != NULL){
			if(acc->acc_no == accNo){
				strcpy(acc->name,name);				//here we update the account holder name
			}
			acc = acc->next;
		}
	}
	else{
		printf("\nAction terminated! Invalid input, the name should contain not more than 20 characters.\n\n");
		fflush(stdin);
	}
}

void displayCustomerRecord(long int acc_no){
	struct account *acc = head;
	int count = 0;
	while(acc != NULL){
		if(acc->acc_no == acc_no){
			count++;						//here we calculate the number of matching account entries
		}
		acc = acc->next;
	}
	struct account List[count];
	acc = head;
	int i= 0 ;
	while(acc != NULL){						//here we display all the entries for the same account
		if(acc->acc_no == acc_no){
			List[i].acc_no = acc->acc_no;
			List[i].amount = acc->amount;
			List[i].balance = acc->balance;
			List[i].transactionid = acc->transactionid;
			strcpy(List[i].name,acc->name);
			strcpy(List[i++].transaction,acc->transaction);
		}
		acc = acc->next;
	}
	printf("\nAcc. Number\t");
	printf("Name\t\t");
	printf("Transaction\t");
	printf("Transaction Amount\t");
	printf("Balance\t\t");
	printf("Transaction ID");
	for(int i = 0 ; i < count ; i++){			//here we display the result of the search
		printf("\n%ld\t\t",List[i].acc_no);
		printf("%s\t\t",List[i].name);
		printf("%s\t",List[i].transaction);
		printf("$%7.2f\t\t", List[i].amount);
		printf("$%.2f\t\t\t", List[i].balance);
		printf("%d", List[i].transactionid);
	}
	printf("\n");
}

struct account * Searchlatestaccount(int long acc_no){
	struct account *result = NULL;
	struct account *acc = head;
	int count = 0;
	while(acc != NULL){
		if(acc->acc_no == acc_no){
			count++;			//here we get the transactionid
		}
		acc = acc->next;
	}
	acc = head;
	while(acc != NULL){
		if(acc->transactionid == count && acc->acc_no ==acc_no){		//here we search for the required account
			result = acc;
		}
		acc = acc->next;
	}
	return result;
}

bool isWord(char a[]){			//here we check if the given string has only characters
	bool valid = true;
	for(int i = 0 ; i< strlen(a) ; i++){
		if(a[i] < 65){
			valid = false;
		}
		else if(a[i] > 90 && a[i] < 97){
			valid = false;
		}
		else if(a[i] > 122){
			valid = false;
		}
	}
	return valid;
}

struct account* searchList(long int acc) { 
	struct account* result = NULL; 
	struct account* temp = head; // Start at head node  
	while (temp != NULL) { 
		if (temp->acc_no == acc) { 
		// Found a match?  
			result = temp; // Return the current node  
			break; 
		} 
		temp = temp->next; // Go on to the next node 
	} 
	return result; 
} 

void dailyTransaction(long int accno){
	double amount;
	char transaction;
	struct account* acc = Searchlatestaccount(accno);
	if(acc != NULL){
		printf("\nEnter the transaction- 'd' for deposit or 'w' for withdraw - ");
		fflush(stdin);
		scanf("%c",&transaction);
		if(transaction == 'w'){			//here we validate the input
			printf("\nEnter the amount for transaction - ");
			if((scanf("%lf",&amount)) == 1){			//here we validate the amount
				//here we create a new transaction
				addAccount(acc->acc_no,acc->name,acc->balance,amount,"Withdraw",acc->transactionid + 1);
			}
			else{
				printf("\nAction terminated! Invalid input entered.\n\n");
				fflush(stdin);
			}
		}
		else if(transaction == 'd'){			//here we validate the input
			printf("\nEnter the amount for transaction - ");
			if((scanf("%lf",&amount)) == 1){				//here we validate the amount
				//here we create a new transaction
				addAccount(acc->acc_no,acc->name,acc->balance,amount,"Deposit_", acc->transactionid + 1);
			}
			else{
				printf("\nAction terminated! Invalid input entered.\n\n");
				fflush(stdin);
			}
		}
		else{
			printf("Invalid input entered!\n");
		}
	}
	else{
		printf("There is no account from this name\n");
	}
}

void LoadFile(void){		//this method uses a self-made algorithm to read the file
	int j = 0 , k = 0 , l = 0 , m = 0 , c = 0 , n = 0;
	char b[MAX_FILE], ano[7] , name[20], balance[13], amount[10], transaction[8];
	int size = readFile("BankingCustomer.dat",b);
	if(size > 0){
		for(int i = 0 ; i < size ; i++){
			if(b[i] == ','){
				c++;
				if(c%5 == 0	   &&	(strcmp(transaction,"")!=0)  &&	 (strcmp(ano,"")!=0) 
				&&	(strcmp(name,"")!=0)   &&	 (strcmp(balance,"")!=0)		
				&&	(strcmp(amount,"")!=0)){
					addAccount(toLong(ano),name,toDouble(balance),toDouble(amount),transaction,1);
					strcpy(ano,"");
					strcpy(balance,"");
					strcpy(name,"");
					strcpy(amount,"");
					strcpy(transaction,"");
					j = 0; k = 0; l = 0; m = 0; n = 0;
				}
				continue;
			}
			if(c%5 == 0 && n<8){
				ano[n++] = b[i];
			}
			else if(c%5 == 1 && j<21){
				name[j++] = b[i];
			}
			else if(c%5 == 2 && k<11){
				balance[k++] = b[i];
			}
			else if(c%5 == 3 && l<8){
				amount[l++] = b[i];
			}
			else if(c%5 == 4 && m<8){
				transaction[m++] = b[i];
			}
		}
	}
}

void printList(void){
	struct account *acc = head;
	printf("\nAcc. Number\t");
	printf("Name\t\t");
	printf("Transaction\t");
	printf("Transaction Amount\t");
	printf("Balance after Transaction\t");
	printf("TransactionID");
	while(acc != NULL){
		printf("\n%ld\t\t",acc->acc_no);
		printf("%s\t\t",acc->name);
		printf("%s\t",acc->transaction);
		printf("$%7.2f\t\t\t", acc->amount);
		printf("$%.2f\t\t", acc->balance);
		printf("\t%d", acc->transactionid);
		acc = acc->next;
	}
	printf("\n");
}

struct account *createNode(long int acc_no , char name[20] , double balance , double amount , char transaction[8], int transactionid){
	struct account *acc = (struct account*)malloc(sizeof(struct account));
	if(strcmp(transaction,"Depositw") == 0 || strcmp(transaction,"Deposit_") == 0){
		balance = balance + amount;
	}
	else if(strcmp(transaction,"Withdraw") == 0){
		balance = balance - amount;
	}
	acc->balance = balance;
	acc->acc_no = acc_no;
	acc->amount = amount;
	strcpy(acc->name,name);
	strcpy(acc->transaction,transaction);
	acc->transactionid = transactionid;
	acc->next = NULL;
	acc->prev = NULL;
	
	return acc;
}

void listAccounts(void){
	struct account* traverseDatabase = head;
	int size = 0;
	int i = 0;
	int j;
	while(traverseDatabase != NULL){			//here we calculate the size of the list
		size++;
		traverseDatabase = traverseDatabase->next;
	}
	//here we create an array of structure Student to store the information 
	//regarding all the Students in the database
	long int list[size];						
	traverseDatabase = head;				//here we set traverseDatabase again to head to traverse again
	while(traverseDatabase != NULL){
		list[i] = traverseDatabase->acc_no;
		traverseDatabase = traverseDatabase->next;
		i++;
	}
	int count = 0;
	for( i = 0 ; i < size - 1 ; i++ ){					//here we sort the array of structures 
		for( j = 0 ; j < size - i - 1 ; j++){
			if(list[j] == list[j+1]){
				list[j+1] = 0;
			}
		}
	}
	printf("S.No");
	printf("\tList of Account Numbers\n");
	for( i = 0 ; i < size ; i++ ){					//here we sort the array of structures 
		if(list[i] == 0){
			continue;
		}
		count++;
		printf("%d",count);
		printf("\t%ld\t\n",list[i]);
	}
}

void addAccount(long int acc_no , char name[] , double balance , double amount , char transaction[], int transactionid){
	struct account *acc = createNode(acc_no,name,balance,amount,transaction,transactionid);
	if(head == NULL){
		head = acc;
	}
	else{
		tail->next = acc;
		acc->prev = tail;
	}
	tail = acc;
}

double toDouble(char balance[]){		//thhis is a mehtod to convert char [] to double
	int size = strlen(balance);
	int digitsBeforeDecimal = 0;
	double result = 0;
	for(int i = 0 ; i < size ; i++){
		if(balance[i] == '.'){
			break;
		}
		digitsBeforeDecimal++;
	}
	for(int i = 0 ; i < digitsBeforeDecimal ; i++){
		result += ((double)balance[i] - 48) * pow(10,digitsBeforeDecimal-i-1);
	}
	for(int i = digitsBeforeDecimal+1 ; i < size ; i++){
		result += ((double)balance[i] - 48) * pow(10,digitsBeforeDecimal-i);
	}
	return result;
}

int readFile(const char fName[], char textStr[]){			//this is a method to read the file
	FILE *fPtr;
	char ch;
	int size = 0;
	
	if ((fPtr = fopen(fName, "r")) == NULL) {
		fprintf(stderr, "Error, failed to open %s: ", fName);
		perror("");
		return -1;
	}
	
	while ((ch = fgetc(fPtr)) != EOF) {
	    if (size >= MAX_FILE - 1)
	        break;
		textStr[size++] = ch;
    }
		
	textStr[size] = '\0';
	
	return size;	
}

long int toLong(char acc[7]){			//this is a method to convert char acc_No[] to long int
	int l = 0;
	for(int i=0 ; i < 7 ; i++){
		l += (int)(acc[i] - 48) * pow(10,7-i-1);
	}
	return l;
}

//here we sort the student info using bubble sort algorithm
void BubbleSort(void){
	struct account* traverseDatabase = head;
	int size = 0;
	int i = 0;
	int j;
	while(traverseDatabase != NULL){			//here we calculate the size of the list
		size++;
		traverseDatabase = traverseDatabase->next;
	}
	//here we create an array of structure account to store the information 
	//regarding all the accounts in the database
	struct account list[size];						
	traverseDatabase = head;				//here we set traverseDatabase again to head to traverse again
	while(traverseDatabase != NULL){
		strcpy(list[i].name,traverseDatabase->name);
		list[i].acc_no = traverseDatabase->acc_no;
		strcpy(list[i].transaction,traverseDatabase->transaction);
		list[i].amount = traverseDatabase->amount;
		list[i].balance = traverseDatabase->balance;
		list[i].next = NULL;
		list[i].transactionid = traverseDatabase->transactionid;
		traverseDatabase = traverseDatabase->next;
		i++;
	}
	for( i = 0 ; i < size - 1 ; i++ ){					//here we sort the array of structures using bubble sort
		for( j = 0 ; j < size - i - 1 ; j++){
			if( list[j].acc_no > list[j + 1].acc_no){
				struct account temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
	head = NULL;
	tail = NULL;
	for( i = 0 ; i < size ; i++ ){					//here we re-create the sorted database
		if(strcmp(list[i].transaction,"Depositw") == 0 || strcmp(list[i].transaction,"Deposit_") == 0){
			addAccount(list[i].acc_no,list[i].name,list[i].balance - list[i].amount,list[i].amount,list[i].transaction,list[i].transactionid);
		}
		else if(strcmp(list[i].transaction,"Withdraw") == 0){
		addAccount(list[i].acc_no,list[i].name,list[i].balance + list[i].amount,list[i].amount,list[i].transaction,list[i].transactionid);
		}	
	}	
}
int cmpfunc(const void* a, const void* b) {
    long int accA = ((struct account*)a)->acc_no;  // Get the price of item 'a'
    long int accB = ((struct account*)b)->acc_no;  // Get the price of item ''
    if (accA == accB) {
    	return 0;
	}
	else if (accA > accB) {
		return 1;
	}
	else {
		return -1;
	}
}
void QuickSort(void){				//here we sort the database using qsort
	struct account* traverseDatabase = head;
	int size = 0;
	int i = 0;
	while(traverseDatabase != NULL){			//here we calculate the size of the list
		size++;
		traverseDatabase = traverseDatabase->next;
	}
	//here we create an array of structure account to store the information 
	//regarding all the accounts in the database
	struct account list[size];						
	traverseDatabase = head;				//here we set traverseDatabase again to head to traverse again
	while(traverseDatabase != NULL){
		strcpy(list[i].name,traverseDatabase->name);
		list[i].acc_no = traverseDatabase->acc_no;
		strcpy(list[i].transaction,traverseDatabase->transaction);
		list[i].amount = traverseDatabase->amount;
		list[i].balance = traverseDatabase->balance;
		list[i].next = NULL;
		list[i].transactionid = traverseDatabase->transactionid;
		traverseDatabase = traverseDatabase->next;
		i++;
	}
	qsort(list, size, sizeof(struct account), cmpfunc);			//here we sort the array of structures by account number 
	
	head = NULL;
	tail = NULL;
	for( i = 0 ; i < size ; i++ ){					//here we re-create the sorted database
		if(strcmp(list[i].transaction,"Depositw") == 0 || strcmp(list[i].transaction,"Deposit_") == 0){
			addAccount(list[i].acc_no,list[i].name,list[i].balance - list[i].amount,list[i].amount,list[i].transaction,list[i].transactionid);
		}
		else if(strcmp(list[i].transaction,"Withdraw") == 0){
		addAccount(list[i].acc_no,list[i].name,list[i].balance + list[i].amount,list[i].amount,list[i].transaction,list[i].transactionid);
		}	
	}	
}
