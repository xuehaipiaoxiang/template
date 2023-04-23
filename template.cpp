
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

// *************************************mergeSort
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
string faddString(const string&a,const string&b)
{
    string c;
    int i=a.size()-1,j=b.size()-1;
    int carry1=0;
    while (i>=0&&j>=0)
    {
        int tmp=(a[i--]-'0')+(b[j--]-'0')+carry1;
        c.push_back(tmp%10+'0');
        carry1=tmp/10;
    }
    while (i>=0)
    {
        int tmp=(a[i--]-'0')+carry1;
        c.push_back(tmp%10+'0');
        carry1=tmp/10;
    }
    while (j>=0)
    {
        int tmp=(b[j--]-'0')+carry1;
        c.push_back(tmp%10+'0');
        carry1=tmp/10;
    }
    if(carry1) c.push_back('1');
    reverse(c.begin(),c.end());
    return c;
}
//**************************big integer add
string fsubCore(const string&a,const string&b);
string fsubString(const string&a,const string&b)
{           
    if(a.size()>b.size())
        return fsubCore(a,b);
    else if(b.size()>a.size())
        return "-"+fsubCore(b,a);
    else
    {
        for(int i=0;i<a.size();++i)
        {
            if(a[i]>b[i])
                return fsubCore(a,b);
            else if(b[i]>a[i])
                return "-"+fsubCore(b,a);
        }
        return "0";
    }

}
string fsubCore(const string&a,const string&b)
{                   // assert a>=b
    int tcarry=0;
    string c1;
    int i=a.size()-1,j=b.size()-1;
    while(i>=0&&j>=0)
    {
        int tmp=(a[i--]-'0')-tcarry-(b[j--]-'0');
        c1.push_back((tmp+10)%10+'0');
        if(tmp>=0)  tcarry=0;
        else tcarry=1;
    }
    while (i>=0)
    {
        int tmp=(a[i--]-'0')-tcarry;
        c1.push_back((tmp+10)%10+'0');
        if(tmp>=0)  tcarry=0;
        else tcarry=1;
    }
    reverse(c1.begin(),c1.end());
    while (c1[0]=='0')
    {
        c1.erase(0,1);
    }
    
    return c1;

}
//**************************end big integer substract

string fmulString(const string&a,const int b)
{
    string c1;
    int carry=0,i=a.size()-1;
    while (i>=0||carry>0)
    {
        if(i>=0)carry=carry+(a[i--]-'0')*b;
        c1.push_back(carry%10+'0');
        carry/=10;
    }
    reverse(c1.begin(),c1.end());
    while(c1.size()>1&&c1[0]=='0') c1.erase(0,1);
    return c1;
}
//*************************end string X interger

string fdivString(string& a1,int b1)
{
    if(b1==0) return "NaN";
    int r=0;string c1;
    for(int i=0;i<a1.size();++i)
    {
        r=r*10+(a1[i]-'0');
        c1.push_back(r/b1+'0');
        r=r%b1;
    }
    //r ::=reminder
    while(c1.size()>1&&c1[0]=='0') c1.erase(c1.begin());
    return c1;
}
//*******************************big interger substract

    int lowbit(int n){ return n&(-n);}
    int NumberOf1(int n) {
        int ans=0;
        while(n)
        {
            ++ans;
            n-=lowbit(n);
        }
        return ans;
    }
//****************************统计数字的二进制表示中“1”的个数

int findX(int x,const vector<int>& alls)
{
    int lo=0,hi=alls.size()-1;
    while (lo<hi)
    {
        int mid=(lo+hi)>>1;
        if(x<=alls[mid]) hi=mid;
        else lo=mid+1;
    }
    return lo;  
}
int numsa[N];vector<int> alls;
sort(alls.begin(),alls.end());
alls.erase(unique(alls.begin(),alls.end()),alls.end());
//距离很大的坐标当作元素存放在alls中，
//对应元素本身存放在numsa中
//每次使用a[findx[x,alls]]读取元素
//**************************************离散化