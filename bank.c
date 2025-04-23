
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
  char name[100];
  unsigned int age : 8; 
  long long int contact_no;
  long long int aadhar_no;
}Customer_Info;

typedef struct {
  int account_no;
  Customer_Info customer;
  char account_type[10]; 
  float initial_balance;
}BankAccount;

BankAccount accounts[100];
BankAccount *ptrAcc[100];

int numC = 0;

void createAccount(int n) {
  for (int i = 0; i < n; i++) {
    printf("\nEnter details for customer %d\n", i + 1);

    printf(" Enter customer name: ");
	scanf(" %[^\n]s", accounts[numC].customer.name);

    printf("Enter age: ");
	unsigned tmp;
    scanf("%u", &tmp);
    accounts[numC].customer.age = tmp;

    printf("Enter contact number: ");
    scanf("%lld", &accounts[numC].customer.contact_no);

    printf("Enter aadhar number: ");
    scanf("%lld", &accounts[numC].customer.aadhar_no);

    printf("Enter account type (Savings/Current): ");
    scanf("%s", accounts[numC].account_type);

    accounts[numC].account_no = rand() % 1001;

    printf("\nYou have created %s account successfully.\n",
           strcmp(accounts[numC].account_type, "Current") == 0 ? "Current" : "Savings");

    printf("Your Account number is %d. Do you want to make an Initial Deposit(Y/N)? ",
           accounts[numC].account_no);
    char ch;
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y') {
      float depositAmount;
      printf("\nEnter the amount to be deposited (in Rupees): ");
      scanf("%f", &depositAmount);
      accounts[numC].initial_balance = depositAmount;
      printf("Rs. %.2f has been successfully deposited into your account.\n", depositAmount);
      printf("Your Account balance is Rs. %.2f\n", accounts[numC].initial_balance);
    }
    ptrAcc[numC] = &accounts[numC];
    numC++;
  }
  printf("\n********** Thank You**********\n");
}


int searchCustomer(){
	int accountNo;
	printf("Enter the account number: ");
	scanf("%d", &accountNo);
	int index = -1;
	for (int i = 0; i < numC; i++) {
		if (accounts[i].account_no == accountNo) {
			index = i;
			break;
		}
	}
	return index;
}

void displayDetails() {
  if (numC == 0) {
    printf("Create an account first\n");
    return;
  }

  for (int i = 0; i < numC; i++) {
    printf("Customer %d details:\n", i + 1);
    printf("Account number: %d\n", accounts[i].account_no);
    printf("Name: %s\n", accounts[i].customer.name);
    printf("Age: %u\n", accounts[i].customer.age);
    printf("Contact Number: %lld\n", accounts[i].customer.contact_no);
    printf("Aadhaar Number: %lld\n", accounts[i].customer.aadhar_no);
    printf("Account Type: %s\n", accounts[i].account_type);
    printf("Account balance Rs. %.2f\n\n", accounts[i].initial_balance);
  }
  printf("\n********** Thank You**********\n");
}

void BalanceDepositWithdraw(int customerIndex) {
  int ch;
  printf("\nYour Account balance is Rs. %.2f\n", accounts[customerIndex].initial_balance);
  printf("Enter 1 to make deposit or 2 to withdraw: ");
  scanf(" %d", &ch);

  if (ch == 1) {
    float depositAmount;
    printf("\nEnter the amount to be deposited: ");
    scanf("%f", &depositAmount);
    accounts[customerIndex].initial_balance += depositAmount;
    printf("Rs. %.2f has been successfully deposited into your account.\n", depositAmount);
    printf("Your Account balance is Rs. %.2f\n", accounts[customerIndex].initial_balance);
  } else if (ch == 2) {
    float withdrawAmount;
    printf("\nEnter the amount to be Withdrawn: ");
    scanf("%f", &withdrawAmount);
    if (withdrawAmount > accounts[customerIndex].initial_balance)
      printf("insufficient balance");
    else {
      accounts[customerIndex].initial_balance -= withdrawAmount;
      printf("Rs. %.2f has been successfully withdrawn from your account.\n", withdrawAmount);
      printf("Your Account balance is Rs. %.2f\n", accounts[customerIndex].initial_balance);
    }
  } else
    printf("invalid choice");

  printf("\n********** Thank You**********\n");
}


void updateCustomerRecord() {
  char name[100];
  int new_age;

  printf("\nEnter customer name to update age: ");
  scanf(" %[^\n]s", name);

  printf("Enter the new age: ");
  scanf("%d", &new_age);

  int found = 0;
  for (int i = 0; i < numC; i++) {
    if (strcmp(accounts[i].customer.name, name) == 0) {
      accounts[i].customer.age = new_age;
      found = 1;
      printf("Customer age updated successfully.\n");
      break;
    }
  }

  if (!found) {
    printf("Customer not found.\n");
  }

  printf("\n********** Thank You**********\n");
}

void displayCustomer(int customerIndex) {
  printf("\nCustomer details:\n");
  printf("Account number: %d\n", accounts[customerIndex].account_no);
  printf("Name: %s\n", accounts[customerIndex].customer.name);
  printf("Age: %u\n", accounts[customerIndex].customer.age);
  printf("Contact Number: %lld\n", accounts[customerIndex].customer.contact_no);
  printf("Aadhaar Number: %lld\n", accounts[customerIndex].customer.aadhar_no);
  printf("Account Type: %s\n", accounts[customerIndex].account_type);
  printf("Account balance Rs. %.2f\n\n", accounts[customerIndex].initial_balance);
  printf("\n********** Thank You**********\n");
}



void sortCustomerRecords() {
    BankAccount tempAccounts[100];
    BankAccount *tempPtrAcc[100];
    memcpy(tempAccounts, accounts, numC * sizeof(BankAccount));
    memcpy(tempPtrAcc, ptrAcc, numC * sizeof(BankAccount*));

    for (int i = 0; i < numC - 1; i++) {
        for (int j = 0; j < numC - i - 1; j++) {
            if (tempPtrAcc[j]->account_no > tempPtrAcc[j + 1]->account_no){
                BankAccount *tempPtr = tempPtrAcc[j];
                tempPtrAcc[j] = tempPtrAcc[j + 1];
                tempPtrAcc[j + 1] = tempPtr;

                BankAccount tempStruct = tempAccounts[j];
                tempAccounts[j] = tempAccounts[j + 1];
                tempAccounts[j + 1] = tempStruct;
            }
        }
    }
    
    memcpy(accounts, tempAccounts, numC * sizeof(BankAccount));
    memcpy(ptrAcc, tempPtrAcc, numC * sizeof(BankAccount*));

    printf("\nCustomer records successfully sorted by account number in ascending order:\n");
    printf("\n********** Thank You**********\n");
}


void deleteCustomerRecord(int deleteIndex) {
  if (deleteIndex < numC - 1) {
    for (int i = deleteIndex; i < numC - 1; i++) {
      accounts[i] = accounts[i + 1];
    }
  }
  numC--;
  printf("Customer record deleted successfully.\n");
  printf("\n********** Thank You**********\n");
}

int main() {
  int ch, n;

  printf("***********WELCOME TO HDFC BANK*************\n");

  do {
    printf("\n1. Create Account\n2. Display all Customer Details\n3. Check balance/deposit/withdraw amount\n4. Update customer age\n5. Search/display customer record by account number\n6. Sort customer records by account number\n7. Delete customer record\n8. Exit\n\nPlease enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
      case 1:
        printf("\nEnter the number of customers: ");
        scanf("%d", &n);
        createAccount(n);
        break;

      case 2:
        displayDetails();
        break;

      case 3:
        int accIndex = searchCustomer();
        if (accIndex > -1)
          BalanceDepositWithdraw(accIndex);
        else
          printf("Account not found/created.\n");
        break;

      case 4:
        updateCustomerRecord();
        break;

      case 5:
        accIndex = searchCustomer();
        if (accIndex > -1)
          displayCustomer(accIndex);
        else
          printf("Account not found/created.\n");
        break;

      case 6:
        sortCustomerRecords();
        break;

      case 7:
        accIndex = searchCustomer();
        if (accIndex > -1)
          deleteCustomerRecord(accIndex);
        else
          printf("Account not found/created.\n");
        break;

      case 8:
        printf("\n********** Thank You for Banking with HDFC! **********\n");
        break;

      default:
        printf("\nInvalid choice! Please enter a valid option.\n");
    }
  } while (ch != 8);

  return 0;
}
