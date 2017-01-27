#include <stdio.h>
#include <math.h>
#define MAX_NUM_ROWS 128
#define HIT 1
#define MISS 0

/**
  struct row - represents a cache line
  int valid - if it is valid or not
  int timeStamp - when it was last visited
**/
struct row {
  // timestamp of when it was last visited
  int timeStamp;
  // tag of the row
  int tag;
  // Is it valid
  int valid;
};

// Cache struct
struct row cache[MAX_NUM_ROWS];

/**
  int isHitOrMiss - returns if the set/tag/index is a hit (1) or a miss (0)
  int setNumber - current set we are on
  int tag - the tag of the cache row
  int index - the index of the cache set
**/
int isHitOrMiss(int setNumber, int index, int tag) {

  int i = 0; // Counter value
  int j = 0; // Row Index
  int currentHit = 0; // If we hit or not

  for (j = (setNumber*index); j < (setNumber + (setNumber*index)); j++) {
    if (cache[j].tag == tag && cache[j].valid) {
      return HIT;
    };
}
  for (j = (setNumber*index); j < (setNumber + (setNumber*index)); j++) {
    if (cache[j].valid) {
      i++;
    };
}
  for (j = (setNumber*index); j < (setNumber + (setNumber*index)); j++) {
    if (!cache[j].valid) {
      cache[j].valid = 1;
      cache[j].tag = tag;
      cache[j].timeStamp = i;
      return MISS;
    };
}

  for (j = (setNumber*index); j < (setNumber + (setNumber*index)); j++) {
    cache[j].timeStamp = cache[j].timeStamp  - 1;
}

  for (j = (setNumber*index); j < (setNumber + (setNumber*index)); j++) {
      if (cache[j].timeStamp == -1) {
        cache[j].timeStamp = i - 1;
        cache[j].tag = tag;
        cache[j].valid = 1;
        return MISS;
      };
  }

  return MISS;
};


int main() {

  // Associativity of the cache
  int assoc;
  // The size of the cahce
  int cacheSize;
  // The size of each block of cache
  int blockSize;
  // The test sequence of input values
  int testSeq[] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41 };

  printf("Cache Total Size (in bytes)?\n");
  scanf("%d", &cacheSize);
  printf("Bytes per block?\n");
  scanf("%d", &blockSize);
  printf("Enter value for either Direct-Mapped, Fully Associative, or the k value for Set Associative.\n");
  printf("Direct-Mapped = 1\n");
  printf("Fully Associative = %d\n", cacheSize / blockSize);
  scanf("%d", &assoc);

  // Number of sets in cache
  int numSets = (cacheSize/blockSize)/ assoc;

  // loop over all the sets and rows
  for (int i = 0; i < sizeof(testSeq)/sizeof(testSeq[0]); i++) {
    int getTag = (testSeq[i]/blockSize)/numSets;
    int currIndex = (testSeq[i] / blockSize) % numSets;
    int hitOrMiss = isHitOrMiss(assoc, currIndex, getTag);
    int offset = testSeq[i] % blockSize;
    hitOrMiss ? printf("%d:  HIT  (Tag/Set#/Offset: %d/%d/%d)\n", 
    	testSeq[i], getTag, currIndex, offset) : 
    printf("%d:  MISS  (Tag/Set#/Offset: %d/%d/%d)\n", 
    	testSeq[i], getTag, currIndex, offset);
  };

  return 0;
};