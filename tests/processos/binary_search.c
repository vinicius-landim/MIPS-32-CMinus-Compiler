int bin_search(int nums[], int numsSize, int target){
    int low;
    int high;
    int mid;

    low = 0;
    high = numsSize-1;

    while(low<=high){
        mid = (low+high)/2;
        if(nums[mid] == target) {
            return mid;
        }
        if(nums[mid] < target) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }

    return -1;
}

void main(void){
    int vet[5];
    int target;
    int search;
    int i;

    while(i<5){
        vet[i] = input();
        i = i+1;
    }
    
    target = input();
    search = bin_search(vet, 5, target);
    
    output(search);
}