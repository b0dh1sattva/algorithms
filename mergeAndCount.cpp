//Function Prototypes
void buildArray(int anArray[]);

void printArray(int anArray[], int start, int end);
void sortArray(int start, int end, int masterArray[], int tempArray[]);
void mergeArray(int start, int split, int end, int masterArray[], int tempArray[]);

void bruteCount(int masterArray[]);

//Globals BAD, but gets the job done here
long long INVERSIONS_SORT = 0;
long long INVERSIONS_BRUTE = 0;
const int size = 100000;


void main() {
  int masterArray[size];
  int tempArray[size];

  buildArray(masterArray);

  bruteCount(masterArray);
  cout << "Inversion from Brute: " << INVERSIONS_BRUTE << endl;
  cin.get();

  sortArray(0, size - 1, masterArray, tempArray);
  cout << "Inversions from Sort: " << INVERSIONS_SORT << endl;

  cin.get();
}

//Builds an array from a txt file
void buildArray(int anArray[]) {
  ifstream dataFile;
  dataFile.open("integerArray.txt", ios::in);

  for (int i = 0; i < size; i++)
    dataFile >> anArray[i];
}

//Prints the entire array
void printArray(int anArray[], int start, int end) {
  for (int i = start; i <= end; i++)
    cout << anArray[i] << " ";

  cout << endl;
}

//Recursive function to split the array into sub arrays for merging
void sortArray(int start, int end, int masterArray[], int tempArray[]) {
  int split = (start + end) / 2;

  if (start < end) {
    sortArray(start, split, masterArray, tempArray);
    sortArray(split + 1, end, masterArray, tempArray);
    mergeArray(start, split, end, masterArray, tempArray);
  }


}

//Master function to marge two arrays into the correct order, and track the number of inversions
void mergeArray(int start, int split, int end, int masterArray[], int tempArray[]) {
  int leftCount = start; //Counter for left array
  int rightCount = split+1; //Counter for right array
  int tempCount = start; //Counter for temporary array

  while ((leftCount <= split) && (rightCount <= end)) { //When there are still values in both arrays
    if (masterArray[leftCount] <= masterArray[rightCount]) { //If value of left array is lower
      tempArray[tempCount] = masterArray[leftCount];
      leftCount++;
    }
    else {
      tempArray[tempCount] = masterArray[rightCount];  //If value of right array is lower
      INVERSIONS_SORT = INVERSIONS_SORT + (split + 1 - leftCount);  //If value of the right array is lower, add how many left array values are higher (number of inversions) and add to count
      rightCount++;
    }
    tempCount++;
  }

  //Cleanup when either array is done
  if (leftCount > split) {
    for (int i = rightCount; i <= end; i++) {
      tempArray[tempCount] = masterArray[i];
      tempCount++;
    }
  }
  else {
    for (int i = leftCount; i <= split; i++) {
      tempArray[tempCount] = masterArray[i];
      tempCount++;
    }
  }

  //Copy back into master array
  for (int i = start; i <= end; i++)
    masterArray[i] = tempArray[i];

}


//Counts the number of inversions via brute force, here to check to see if MergeSort method is working correctly
void bruteCount(int masterArray[]) {
  int i, j;

  for (i = 0; i < size-1; i++)
    for (j = i + 1; j < size; j++)
      if (masterArray[i] > masterArray[j])
        INVERSIONS_BRUTE++; 
}
