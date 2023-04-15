
// Nicholas Mistry
// Torosdagli 
// Lab Assignment 9

#include <stdio.h>
#include <stdlib.h>


// TA Faramaz is the goat

struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType *next; // add next pointer (for linkedlist structure)
};

// Fill out this structure
struct HashType {
    struct RecordType * records; // add pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize) {
    return x % tableSize; // hash function is x % tableSize
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData) {
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }
        fclose(inFile);
    }
    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize) {


    int index = hash(record->id, tableSize); // Find the index using da hash function
   
    if (hashTable[index].records == NULL) { // Check for null
      hashTable[index].records = record; // if null then use index and set record
    } else { // traverse to end and set record there
      struct RecordType *temp = hashTable[index].records;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = record;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize) {
    int i;
  // each index of HashTable stores a linked list
  // so use a temp variable to traverse the list and print it out
  
  
    for (i = 0; i < tableSize; ++i) {
        printf("index %d -> ", i);
        struct RecordType *temp = hashTable[i].records;
        if (temp == NULL) {
            printf("NULL\n"); // in the case that the list is empty
        } else {
            while (temp != NULL) {
                printf("%d, %c, %d -> ", temp->id, temp->name, temp->order);
                temp = temp->next;
            }
            printf("NULL\n"); // terminates the end of the linked list
        }
    }
    printf("\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    int hashTableSize = 11; // There are 10 indexes 
    struct HashType *hashTable = calloc(hashTableSize, sizeof(struct HashType));
    if (hashTable == NULL) {
      printf("Cannot allocate memory\n");
      exit(-1);
    }

    for (int i = 0; i < recordSz; i++) {
      insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    displayRecordsInHash(hashTable, hashTableSize); // Display all the linked lists

    
    free(hashTable);
    free(pRecords);

    return 0;
}

   
