
//********************************quickSort
void quickSort(int nums1[],int lo1,int hi1)
{
    if(hi1<=lo1) return;
    int mid1=partition(nums1,lo1,hi1);
    quickSort(nums1,lo1,mid1-1);
    quickSort(nums1,mid1+1,hi1);
}

int partition(int nums1[],int lo1,int hi1)
{
    int pivot=nums1[lo1];
    while (lo1<hi1)
    {
        while(lo1<hi1 &&pivot<=nums1[hi1]) --hi1;
            nums1[lo1]=nums1[hi1];
        while(lo1<hi1 &&nums1[lo1]<=pivot)  ++lo1;
            nums1[hi1]=nums1[lo1];
    }
    nums1[lo1]=pivot;
    return lo1;
}
// ***********************************end quickSort

// **********************************mergeSort
int nums[1000];
int nums2[1000];
void fmerge(int nums[],int lo,int mid,int hi) //[lo,mid] [mid+1,hi]
{
    //int nums2[hi-lo+1];
    
    int i=lo,j=mid+1,k=lo;
    while (i<=mid&&j<=hi)
    {
        if(nums[i]<=nums[j])
            nums2[k++]=nums[i++];
        else
            nums2[k++]=nums[j++];
    }
    while(i<=mid)
        nums2[k++]=nums[i++];
    while(j<=hi)
        nums2[k++]=nums[j++];
    for(int i=lo;i<=hi;++i)
        nums[i]=nums2[i];
    
}

void fmergeSort(int nums[],int lo,int hi)//[lo,hi]
{
    if(lo==hi)
        return;
    int mid=(lo+hi)>>1;
    fmergeSort(nums,lo,mid);
    fmergeSort(nums,mid+1,hi);
    fmerge(nums,lo,mid,hi);
}

//***********************end quickSort

int findLow(int nums[],int lo,int hi,int x) //[lo,hi]
{
    //所有大于等于x中最小的

    while (lo<hi)
    {
        int mid=(lo+hi)>>1;
        if(x<=nums[mid])
            hi=mid;
        else
            lo=mid+1;
    }
    if(nums[lo]==x) return lo;
    return -1;    
}

int findHigh(int nums[],int lo,int hi,int x) //[lo,hi]
{
    //所有小于等于x中最大的
    while (lo<hi)
    {
        int mid=(lo+hi+1)>>1;
        if(nums[mid]<=x)
            lo=mid;
        else
            hi=mid-1;
    }
    if(nums[lo]==x) return lo;
    return -1;    
}
//****************************end Bsearch