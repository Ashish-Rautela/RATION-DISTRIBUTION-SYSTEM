#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX_NAME 50
#define MAX_ADDRESS 100
#define MAX_ID 20
#define MAX_PRODUCTS 5

// Structure for beneficiary
struct Beneficiary
{
    char id[MAX_ID];
    char name[MAX_NAME];
    char address[MAX_ADDRESS];
    int familySize;
};

// Structure for product
struct Product
{
    char name[MAX_NAME];
    float price;
    float quantity;
};

// Structure for distribution transaction
struct Distribution
{
    char beneficiaryId[MAX_ID];
    char productName[MAX_NAME];
    float quantity;
    char date[20];
};
// structure for user
struct user
{
    int userid;
    char name[50];
    char password[15];
    char role[15];
};
//main
int admin();

// Function prototypes
void usermenu();
void productmenu();
void distributionmenu();
void reportmenu();

// Beneficiary functions
void adduser();
void viewuser();
void searchuser();
void updateuser();
void deleteuser();

// Product functions
void addprod();
void viewprods();
void updatestock();

// Distribution functions
void distribute();
void viewdist();

// Report functions
void benereport();
void prodreport();
void datereport();

// // Helper functions
int checkuser(char id[]);
int checkproduct(char name[]);
void saveDate(char date[]);
void clearScreen();
void pressAnyKey();



//                                                                  MAIN LOGIN AND ADMIN FUNCTION
int login()
{
    int inputID;
    char inputPassword[15];
    struct user u;
    int loginsucess = 0;
    char ch;
    int index;
    int attempts = 0;
    while (attempts < 3)
    {
        system("cls");
        printf("\n-----WECLOME TO RATION MANAGEMENT SYSTEM-----\n");
        printf("======================================\n");
        printf("Enter User ID : ");
        scanf("%d", &inputID);

        printf("Enter Password : ");
        index = 0;
        while (1)
        {
            ch = getch();
            if (ch == 13)
            {
                inputPassword[index] = '\0';
                break;
            }
            else if (ch == 8)
            {
                if (index > 0)
                {
                    index--;
                    printf("\b \b");
                }
            }
            else
            {
                inputPassword[index++] = ch;
                printf("*");
            }
        }
        FILE *fp = fopen("user.txt", "r");
        if (fp == NULL)
        {
            printf("!!!---ERROR in Opening file---!!!");
            return 0;
        }
        loginsucess = 0;
        while (fscanf(fp, "%d %s %s %s", &u.userid, u.name, u.password, u.role) != EOF)
        {
            if (u.userid == inputID && strcmp(u.password, inputPassword) == 0)
            {
                loginsucess = 1;
                printf("\nLogin sucessfull\n");
                printf("Welcome %s (%s)\n", u.name, u.role);

                if (strcmp(u.role, "Admin") == 0)
                {
                    printf("Opening Admin Menu...\n");
                    system("cls");
                    admin();
                }
                else
                {
                    printf("Opening Customer Menu...\n");
                }
                break;
            }
        }
        fclose(fp);
        if (loginsucess)
            return 1;
        attempts++;
        printf("\nINvalid user ID or Password. Attemptd %d of 3.\n", attempts);
    }

    printf("\nToo many attempts .program will n ow exit.\n");
    exit(0);
}

int admin()
{
    int choice;
    do
    {
        clearScreen();
        printf("\n=== RATION DISTRIBUTION MANAGEMENT SYSTEM ===\n");
        printf("1. Beneficiary Management\n");
        printf("2. Product Management\n");
        printf("3. Distribution Management\n");
        printf("4. Reports\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            usermenu();
            break;
        case 2:
            productmenu();
            break;
        case 3:
            distributionmenu();
            break;
        case 4:
            reportmenu();
            break;
        case 0:
            printf("Exiting the system. Thank you!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            pressAnyKey();
        }
    } while (choice != 0);

    return 0;
}

int main()
{
    login();
}

//                                      ------------------------------FUNCTIONS FOR MENU------------------------------


void usermenu(){
    int choice;

    do
    {
        clearScreen();
        printf("\n=== BENEFICIARY MANAGEMENT ===\n");
        printf("1. Add New Beneficiary\n");
        printf("2. View All Beneficiaries\n");
        printf("3. Search Beneficiary\n");
        printf("4. Update Beneficiary\n");
        printf("5. Delete Beneficiary\n");
        printf("0. Back to Main Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            adduser();
            break;
        case 2:
            viewuser();
            break;
        case 3:
            searchuser();
            break;
        case 4:
            updateuser();
            break;
        case 5:
            deleteuser();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            pressAnyKey();
        }
    } while (choice != 0);
}


void productmenu()
{
    int choice;

    do
    {
        clearScreen();
        printf("\n=== PRODUCT MANAGEMENT ===\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update\n");
        printf("0. Back to Main Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 1:
            addprod();
            break;
        case 2:
            viewprods();
            break;
        case 3:
            updatestock();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            pressAnyKey();
        }
    } while (choice != 0);
}


void distributionmenu()
{
    int choice;

    do
    {
        clearScreen();
        printf("\n=== DISTRIBUTION MANAGEMENT ===\n");
        printf("1. Distribute Ration\n");
        printf("2. View All Distributions\n");
        printf("0. Back to Main Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 1:
            distribute();
            break;
        case 2:
            viewdist();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            pressAnyKey();
        }
    } while (choice != 0);
}

void reportmenu(){
    int choice;

    do
    {
        clearScreen();
        printf("\n=== REPORTS ===\n");
        printf("1. Beneficiary-wise Report\n");
        printf("2. Product-wise Report\n");
        printf("3. Date-wise Report\n");
        printf("0. Back to Main Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice)
        {
        case 1:
            benereport();
            break;
        case 2:
            prodreport();
            break;
        case 3:
            datereport();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            pressAnyKey();
        }
    } while (choice != 0);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------




//                                -------------------------------FUNCTIONS THAT WORK ON FILES-------------------------------



//------------------------------Functions for manipulating beneficiary data---------------------------------
void adduser(){
    clearScreen();
    struct Beneficiary ben;
    FILE *fp;
    printf("\n=== ADD NEW BENEFICIARY ===\n");

    printf("Enter Beneficiary ID: ");
    scanf("%s",ben.id);
    getchar();
    if(checkuser(ben.id)){
        printf("Beneficiary with ID %s already exists!\n",ben.id);
        getchar();
        pressAnyKey();
        return;
    }
    
    printf("Enter Beneficiary Name: ");
    scanf("%s",ben.name);
    getchar();
    printf("Enter Address: ");
    scanf("%s",ben.address);
    getchar();
    printf("Enter Family Size: ");
    scanf("%d",&ben.familySize);


    fp = fopen("beneficiaries.dat","ab");
    if(fp==NULL){
        printf("Error opening file\n");
        pressAnyKey();
        return;
    }
    fwrite(&ben,sizeof(struct Beneficiary),1,fp);
    fclose(fp);
    getchar();
    printf("\nBeneficiary added successfully\n");
    pressAnyKey();
}

int checkuser(char id[]){
    struct Beneficiary ben;
    FILE *fp;
    fp = fopen("beneficiaries.dat","rb");
    if(fp==NULL){
        return 0;
    }
    while(fread(&ben,sizeof(struct Beneficiary),1,fp)==1){
        if(strcmp(id,ben.id)==0){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void viewuser(){
    clearScreen();
    struct Beneficiary ben;
    FILE *fp;
    int count=0;
    printf("\n===ALL BENEFICIARIES ===\n");
    printf("%-10s %-20s %-30s %-10s\n", "ID", "Name", "Address", "Family Size");
    printf("------------------------------------------------------------\n");

    fp = fopen("beneficiaries.dat","rb");
    if(fp==NULL){
        printf("No beneficiaries found or error opening file\n");
        fclose(fp);
        pressAnyKey();
        return;
    }
    while(fread(&ben,sizeof(struct Beneficiary),1,fp)==1){
        printf("%-10s %-20s %-30s %-10d\n",ben.id,ben.name,ben.address,ben.familySize);
        count++;
    }
    if(count==0){
        printf("No Beneficiaries Found\n");
    }
    fclose(fp);
    pressAnyKey();
}

void searchuser(){
    clearScreen();
    struct Beneficiary ben;
    FILE *fp;
    char SearchId[MAX_ID];
    int found=1;
    printf("\n=== SEARCH BENEFICIARY ===\n");

    printf("Enter Beneficiary ID to search: ");
    scanf("%s",SearchId);
    getchar();
    fp = fopen("beneficiaries.dat","rb");
    if(fp==NULL){
        printf("Error Opening The File!\n");
        pressAnyKey();
        return;
    }
    
    while(fread(&ben,sizeof(struct Beneficiary),1,fp)==1){
        if(strcmp(ben.id,SearchId)==0){
            printf("\nBeneficiary Found:\n");
            printf("ID: %s\n",ben.id);
            printf("Name: %s\n",ben.name);
            printf("Address: %s\n",ben.address);
            printf("Family Size: %d\n",ben.familySize);
            found =0;
            break;
        }
    }
    fclose(fp);
    if(found){
        printf("\nBeneficiary with ID %s not found!\n",SearchId);
    }
    pressAnyKey();
}


void updateuser(){
    clearScreen();
    struct Beneficiary ben;
    FILE *fp, *tempfp;
    char searchid[MAX_ID];
    int found =0;
    printf("\n=== UPDATE BENEFICIARY ===\n");

    printf("Enter Beneficiary ID to update: ");
    scanf("%s",searchid);
    fp = fopen("beneficiaries.dat","rb");
    if(fp==NULL){
        printf("Error Opening file!\n");
        pressAnyKey();
        return;
    }
    tempfp = fopen("temp.dat","wb");
    if(tempfp==NULL){
        printf("Error creating temprary file!\n");
        fclose(fp);
        pressAnyKey();
        return;
    }
    while(fread(&ben,sizeof(struct Beneficiary),1,fp)==1){
        if(strcmp(ben.id,searchid)==0){
            found=1;
            printf("\nCurrent Details:\n");
            printf("ID: %s\n", ben.id);
            printf("Name: %s\n", ben.name);
            printf("Address: %s\n", ben.address);
            printf("Family Size: %d\n", ben.familySize);
            printf("\nEnter New Details:\n");

            printf("Enter Name: ");
            scanf("%s",ben.name);
            printf("Enter Address: ");
            scanf("%s",ben.address);
            printf("Enter Family Size: ");
            scanf("%d",&ben.familySize);
            getchar();
        }
        fwrite(&ben,sizeof(struct Beneficiary),1,tempfp);
    }
    fclose(fp);
    fclose(tempfp);
    if(found){
        remove("beneficiaries.dat");
        rename("temp.dat","beneficiaries.dat");
        printf("\nBeneficiary updated successfully!\n");
    }else{
        remove("temp.dat");
        printf("\nBeneficiary with ID %s not found!\n",searchid);
    }
    pressAnyKey();
}


void deleteuser(){
    clearScreen();
    struct Beneficiary ben;
    char searchid[MAX_ID];
    int found=0;
    printf("\n=== DELETE BENEFICIARy ===\n");
    printf("Enter the Beneficiary Id to delete: ");
    scanf("%s",searchid);
    int c; while ((c = getchar()) != '\n' && c != EOF);
    FILE *fp,*tempfp;
    fp = fopen("beneficiaries.dat","rb");
    if(fp==NULL){
        printf("Error Opening The File\n");
        pressAnyKey();
        return;
    }
    tempfp = fopen("temp.dat","wb");
    if(tempfp==NULL){
        printf("Error Opening The File\n");
        pressAnyKey();
        return;
    }
    while(fread(&ben,sizeof(struct Beneficiary),1,fp)==1){
        if(strcmp(ben.id,searchid)==0){
            found=1;
            printf("\nBeneficiary with ID %s will be deleted.\n", searchid);
        }else{
            fwrite(&ben,sizeof(struct Beneficiary),1,tempfp);
        }
    }
    fclose(fp);
    fclose(tempfp);
    if (found){
    printf("Beneficiary deleted successfully!\n");
}
else{
    remove("temp.dat");
    printf("\nBeneficiary with ID %s not found!\n", searchid);
}
    pressAnyKey();
}
//-----------------------------------------------------------------------------------------------------------------------------------------



//                     ------------------------------Functions for manipulating product data---------------------------------

void addprod(){
    clearScreen();
    struct Product prod;
    FILE *fp;

    printf("=== ADD PRODUCT MENU ===\n");
    printf("ENTER PRODUCT'S NAME: ");
    scanf("%s",prod.name);
    if(checkproduct(prod.name)){
        printf("%s is already present in the inventory");
        pressAnyKey();
        return;
    }

    printf("Enter price per unit(in ruppees): ");
    scanf("%f",&prod.price);
    printf("Enter Initial Stock Quantity:");
    scanf("%f",&prod.quantity);
    getchar();


    fp = fopen("products.dat","ab");
    if(fp==NULL){
        printf("ERROR OPENING THE FILE");
        pressAnyKey();
        return;
    }
    fwrite(&prod,sizeof(struct Product),1,fp);
    fclose(fp);
    printf("Product Successfully Added");
    pressAnyKey();
}

int checkproduct(char name[]){
    struct Product prod;
    FILE *fp = fopen("products.dat","rb");
    while(fread(&prod,sizeof(struct Product),1,fp)==1){
        if(strcmp(prod.name,name)==0){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void viewprods(){
    clearScreen();
    struct Product prod;
    FILE *fp;
    printf("=== ALL PRODUCTS ===\n");
    printf("%-20s %-15s %-15s\n", "Product Name", "Price (Rs.)", "Stock Qty");
    printf("--------------------------------------------------\n");
    fp = fopen("products.dat","rb");
    if(fp==NULL){
        printf("ERROR OPENING THE FILE");
        pressAnyKey();
        return;
    }
    int count=0;
    while(fread(&prod,sizeof(struct Product),1,fp)==1){
        printf("%-20s %-15f %-15f\n",prod.name,prod.price,prod.quantity);
        count++;
    }
    fclose(fp);
    if(count==0){
        printf("NO PRODUCTS FOUND");
    }
    pressAnyKey();
}

void updatestock(){
    clearScreen();
    struct Product prod;
    FILE *fp,*tempfp;
    char name[MAX_NAME];
    int found=0;
    printf("\n=== UPDATE PRODUCT MENU ===\n");
    printf("ENTER THE PRODUCT NAME:");
    scanf("%s",name);
    getchar();
    if(!checkproduct(name)){
        printf("THIS PRODUCT DOES NOT EXIST");
        pressAnyKey();
        return;
    }
    fp = fopen("products.dat","rb");
    tempfp = fopen("temp.dat","wb");
    printf("WHAT DO YOU WANT TO CHANGE\n");
    int check;
    printf("ENTER 1 FOR QUANTITY\nENTER 2 FOR PRICE\nENTER 3 FOR BOTH\n");
    scanf("%d",&check);
    getchar();
    if(check==1){
        while(fread(&prod,sizeof(struct Product),1,fp)){
        if(strcmp(prod.name,name)==0){
            found=1;
            printf("Enter the new Quantity: ");
            scanf("%f",&prod.quantity);
            getchar();
        }
        fwrite(&prod,sizeof(struct Product),1,tempfp);
    }
}
    if(check==2){
        while(fread(&prod,sizeof(struct Product),1,fp)){
        if(strcmp(prod.name,name)==0){
            found=1;
            printf("Enter the new price: ");
            scanf("%f",&prod.price);
            getchar();
        }
        fwrite(&prod,sizeof(struct Product),1,tempfp);
    }
}
    if(check==3){
        while(fread(&prod,sizeof(struct Product),1,fp)){
        if(strcmp(prod.name,name)==0){
            found=1;
            printf("Enter the new price: ");
            scanf("%f",&prod.price);
            printf("Enter the new Quantity: ");
            scanf("%f",&prod.quantity);
            getchar();
        }
        fwrite(&prod,sizeof(struct Product),1,tempfp);
    }
    }else{
        printf("please enter the correct choice");
        pressAnyKey();
        return;
    }

    fclose(fp);
    fclose(tempfp);
    printf("reached here");
    if (found)
    {
        remove("products.dat");
        rename("temp.dat", "products.dat");
        printf("\nStock updated successfully!\n");
    }
    else
    {
        remove("temp.dat");
        printf("\nProduct %s not found!\n", name);
    }

    pressAnyKey();
}
//-------------------------------------------------------------------------------------------------------------------------



//------------------------------Functions for ration distribution---------------------------------

void distribute(){
    clearScreen();
    struct Distribution dist;
    struct Beneficiary ben;
    struct Product prod;
    FILE *fpBen, *fpProd, *fpDist, *tempFp;
    int found = 0;
    char searchId[MAX_ID];
    char searchName[MAX_NAME];
    float requestQty;
    float productPrice = 0.0f;

    printf("\n=== DISTRIBUTE RATION ===\n");

    printf("Enter Beneficiary ID: ");
    scanf("%s", searchId);
    getchar();

    fpBen = fopen("beneficiaries.dat", "rb");
    if (fpBen == NULL) {
        printf("Error opening beneficiaries file!\n");
        pressAnyKey();
        return;
    }

    found = 0;
    while (fread(&ben, sizeof(struct Beneficiary), 1, fpBen) == 1) {
        if (strcmp(ben.id, searchId) == 0) {
            found = 1;
            printf("Beneficiary: %s (Family Size: %d)\n", ben.name, ben.familySize);
            break;
        }
    }
    fclose(fpBen);

    if (!found) {
        printf("Beneficiary with ID %s not found!\n", searchId);
        pressAnyKey();
        return;
    }

    printf("Enter Product Name: ");
    scanf("%s", searchName);
    getchar();

    fpProd = fopen("products.dat", "rb");
    if (fpProd == NULL) {
        printf("Error opening products file!\n");
        pressAnyKey();
        return;
    }

    found = 0;
    while (fread(&prod, sizeof(struct Product), 1, fpProd) == 1) {
        if (strcmp(prod.name, searchName) == 0) {
            found = 1;
            productPrice = prod.price; 
            printf("Product: %s (Available Stock: %.2f, Price: Rs. %.2f per unit)\n",
                   prod.name, prod.quantity, prod.price);
            break;
        }
    }
    fclose(fpProd);

    if (!found) {
        printf("Product %s not found!\n", searchName);
        pressAnyKey();
        return;
    }

    printf("Enter Quantity to Distribute: ");
    scanf("%f", &requestQty);
    getchar();

    if (requestQty > prod.quantity) {
        printf("Insufficient stock! Only %.2f units available.\n", prod.quantity);
        pressAnyKey();
        return;
    }

    fpProd = fopen("products.dat", "rb");
    if (fpProd == NULL) {
        printf("Error opening products file for update!\n");
        pressAnyKey();
        return;
    }
    tempFp = fopen("temp.dat", "wb");
    if (tempFp == NULL) {
        printf("Error opening temporary file!\n");
        fclose(fpProd);
        pressAnyKey();
        return;
    }

    while (fread(&prod, sizeof(struct Product), 1, fpProd) == 1) {
        if (strcmp(prod.name, searchName) == 0) {
            prod.quantity -= requestQty;
        }
        fwrite(&prod, sizeof(struct Product), 1, tempFp);
    }

    fclose(fpProd);
    fclose(tempFp);

    remove("products.dat");
    rename("temp.dat", "products.dat");

    fpDist = fopen("distributions.dat", "ab");
    if (fpDist == NULL) {
        printf("Error opening distributions file!\n");
        pressAnyKey();
        return;
    }

    strcpy(dist.beneficiaryId, searchId);
    strcpy(dist.productName, searchName);
    dist.quantity = requestQty;
    saveDate(dist.date);

    fwrite(&dist, sizeof(struct Distribution), 1, fpDist);
    fclose(fpDist);

    printf("\nRation distributed successfully!\n");
    printf("Total Cost: Rs. %.2f\n", requestQty * productPrice);
    pressAnyKey();
}


void viewdist()
{
    clearScreen();
    struct Distribution dist;
    FILE *fp;
    int count = 0;

    printf("\n=== ALL DISTRIBUTIONS ===\n");
    printf("%-15s %-20s %-15s %-15s\n", "Date", "Beneficiary ID", "Product", "Quantity");
    printf("-----------------------------------------------------------------\n");

    fp = fopen("distributions.dat", "rb");
    if (fp == NULL)
    {
        printf("No distributions found or error opening file!\n");
        pressAnyKey();
        return;
    }

    while (fread(&dist, sizeof(struct Distribution), 1, fp) == 1)
    {
        printf("%-15s %-20s %-15s %-15.2f\n", dist.date, dist.beneficiaryId,
               dist.productName, dist.quantity);
        count++;
    }

    fclose(fp);

    if (count == 0)
    {
        printf("No distributions found!\n");
    }

    pressAnyKey();
}
//------------------------------------------------------------------------------------------------------------------------------------



//------------------------------Functions for Report Generation---------------------------------

void benereport(){
    struct Beneficiary ben;
    struct Distribution dis;
    FILE *fpben, *fpdis;
    int found=0;
    float totalq =0;
    printf("\n=== BENEFICIARY REPORT GENERATION MENU ===\n");
    char id[MAX_ID];
    printf("Enter Beneficiary id: \n");
    scanf("%s",id);
    getchar();
    if(!checkuser(id)){
        printf("This user does'nt exist");
        pressAnyKey();
        return;
    }
    fpben = fopen("beneficiaries.dat","rb");
    fpdis = fopen("distributions.dat","rb");
    while (fread(&ben, sizeof(struct Beneficiary), 1, fpben) == 1)
    {
        if (strcmp(ben.id, id) == 0)
        {
            found = 1;
            printf("\nBeneficiary Details:\n");
            printf("ID: %s\n", ben.id);
            printf("Name: %s\n", ben.name);
            printf("Address: %s\n", ben.address);
            printf("Family Size: %d\n\n", ben.familySize);
            break;
        }
    }

    fclose(fpben);

    if (!found)
    {
        printf("Beneficiary with ID %s not found!\n", id);
        pressAnyKey();
        return;
    }

    printf("Distribution History:\n");
    printf("%-15s %-20s %-15s\n", "Date", "Product", "Quantity");
    printf("--------------------------------------------\n");

    fpdis = fopen("distributions.dat", "rb");
    if (fpdis == NULL)
    {
        printf("No distribution records found!\n");
        pressAnyKey();
        return;
    }

    found = 0;
    while (fread(&dis, sizeof(struct Distribution), 1, fpdis) == 1)
    {
        if (strcmp(dis.beneficiaryId, id) == 0)
        {
            printf("%-15s %-20s %-15.2f\n", dis.date, dis.productName, dis.quantity);
            totalq += dis.quantity;
            found = 1;
        }
    }

    fclose(fpdis);

    if (!found)
    {
        printf("No distribution records for this beneficiary!\n");
    }
    else
    {
        printf("\nTotal Quantity Distributed: %.2f units\n", totalq);
    }

    pressAnyKey();
}

void prodreport()
{
    clearScreen();
    struct Distribution dist;
    struct Product prod;
    FILE *fpDist, *fpProd;
    char searchName[MAX_NAME];
    int found = 0;
    float totalQty = 0;

    printf("\n=== PRODUCT-WISE REPORT ===\n");

    printf("Enter Product Name: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = 0; 

    fpProd = fopen("products.dat", "rb");
    if (fpProd == NULL)
    {
        printf("Error opening products file!\n");
        pressAnyKey();
        return;
    }

    while (fread(&prod, sizeof(struct Product), 1, fpProd) == 1)
    {
        if (strcmp(prod.name, searchName) == 0)
        {
            found = 1;
            printf("\nProduct Details:\n");
            printf("Name: %s\n", prod.name);
            printf("Price: Rs. %.2f per unit\n", prod.price);
            printf("Current Stock: %.2f units\n\n", prod.quantity);
            break;
        }
    }

    fclose(fpProd);

    if (!found)
    {
        printf("Product %s not found!\n", searchName);
        pressAnyKey();
        return;
    }

    printf("Distribution History:\n");
    printf("%-15s %-20s %-15s\n", "Date", "Beneficiary ID", "Quantity");
    printf("--------------------------------------------\n");

    fpDist = fopen("distributions.dat", "rb");
    if (fpDist == NULL)
    {
        printf("No distribution records found!\n");
        pressAnyKey();
        return;
    }

    found = 0;
    while (fread(&dist, sizeof(struct Distribution), 1, fpDist) == 1)
    {
        if (strcmp(dist.productName, searchName) == 0)
        {
            printf("%-15s %-20s %-15.2f\n", dist.date, dist.beneficiaryId, dist.quantity);
            totalQty += dist.quantity;
            found = 1;
        }
    }

    fclose(fpDist);

    if (!found)
    {
        printf("No distribution records for this product!\n");
    }
    else
    {
        printf("\nTotal Quantity Distributed: %.2f units\n", totalQty);
    }

    pressAnyKey();
}

void datereport()
{
    clearScreen();
    struct Distribution dist;
    FILE *fpDist;
    char searchDate[20];
    int found = 0;
    float totalQty = 0;

    printf("\n=== DATE-WISE REPORT ===\n");

    printf("Enter Date (DD/MM/YYYY): ");
    fgets(searchDate, 20, stdin);
    searchDate[strcspn(searchDate, "\n")] = 0; 

    printf("\nDistribution Records for %s:\n", searchDate);
    printf("%-20s %-20s %-15s\n", "Beneficiary ID", "Product", "Quantity");
    printf("--------------------------------------------\n");

    fpDist = fopen("distributions.dat", "rb");
    if (fpDist == NULL)
    {
        printf("No distribution records found!\n");
        pressAnyKey();
        return;
    }

    while (fread(&dist, sizeof(struct Distribution), 1, fpDist) == 1)
    {
        if (strcmp(dist.date, searchDate) == 0)
        {
            printf("%-20s %-20s %-15.2f\n", dist.beneficiaryId, dist.productName, dist.quantity);
            totalQty += dist.quantity;
            found = 1;
        }
    }

    fclose(fpDist);

    if (!found)
    {
        printf("No distribution records for this date!\n");
    }
    else
    {
        printf("\nTotal Quantity Distributed: %.2f units\n", totalQty);
    }

    pressAnyKey();
}
//---------------------------------------------------------------------------------------------------------------------------------------



//------------------------------Helping Functions---------------------------------

void saveDate(char date[])
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);

    sprintf(date, "%02d/%02d/%04d",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

void pressAnyKey()
{
    printf("\nPress Enter to continue...");
    getchar();
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}