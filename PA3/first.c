#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 5128

//hash table code is referenced from https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm

int cnt=0, nu=0; //cnt - num of cases, nu - num of users 

struct user{
    int key;
    int wing; //how many users this user follows
    int wer; //how many users are following this user
};

struct user* hashArray[SIZE];
struct user* dummyItem;
struct user* item;

int hashCode(int key){
    return key % SIZE;
}

struct user *search(int key) {
   int hashIndex = hashCode(key);  
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
      ++hashIndex;
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(int key,int wing, int wer) {
    if(search(key)){
        search(key)->wing=wing;
        search(key)->wer=wer;
    }else{
        nu++;
        struct user *item = (struct user*) malloc(sizeof(struct user));
        item->wing = wing;  
        item->wer = wer;
        item->key = key;
        int hashIndex = hashCode(key);
        while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
            ++hashIndex;
            hashIndex %= SIZE;
        }
            
        hashArray[hashIndex] = item;
    }

   
}

struct user* delete(struct user* item) {
   int key = item->key;
   int hashIndex = hashCode(key);
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key) {
         struct user* temp = hashArray[hashIndex]; 
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
      ++hashIndex;
      hashIndex %= SIZE;
   }      
	
   return NULL;        
}


void average() {
    int i = 0;
    int sumwer=0, sumwing=0;
    float avwer, avwing;
   for(i = 0; i<SIZE; i++) {
       if(hashArray[i] != NULL){
           sumwing+=hashArray[i]->wing;
           sumwer+=hashArray[i]->wer;
        }else{
            printf("hmmmm~~~\n");
        }
   }

   //printf("sumwer = %d, sumwing = %d\n", sumwer, sumwing);

   avwer=sumwer/(float)SIZE;
   avwing=sumwing/(float)SIZE;

    printf("num of cases: %d\n", cnt);
    printf("num of users: %d\n", nu);

   printf("average twitter user has %.2f followers and follows %.2f users\n\n", avwer, avwing);
}

int main(){
    FILE *fp;
    
    fp = fopen("twitter_sampled.txt", "r");
    
    if(!fp){
        cnt++;
        printf("couldn't open file\n");
        exit(1);
    }

    int fwer, fwee;
    int num=-1;
    
    while(!feof(fp)){
        cnt++;
        fscanf(fp, "%d %d\n", &fwer, &fwee);
        //printf("%d %d\n", fwer, fwee);
        if(search(fwer)){
            insert(fwer, (search(fwer)->wing)+1, search(fwer)->wer);
        }else{
            insert(fwer, 1, 0);
        }
        if(search(fwee)){
            insert(fwee, search(fwee)->wing, (search(fwee)->wer)+1);
        }else{
            insert(fwee, 0, 1);
        }
    }

    while(num!=0){
        printf("\n\nWhat do you want to know? :) \n");
        printf("1.Specific user's number of followers\n");
        printf("2.Specific user's number of following\n");
        printf("3.Average number of followers and following\n");
        printf("0.Exit\n");
        printf("Enter number: ");
        scanf("%d", &num);

        if(num==1){
            printf("Enter user: ");
            scanf("%d", &fwee);
            printf("User %d has %d followers\n\n", fwee, search(fwee)->wer);
        }else if(num==2){
            printf("Enter user: ");
            scanf("%d", &fwer);
            printf("User %d has %d followers\n\n", fwer, search(fwer)->wing);
        }else if(num==3){
            average();
        }
    }



    return 0;

}