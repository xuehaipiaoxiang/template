//************************************积累的常用宏和定义*******************************
#define fdbg  std::cout<<"*********************************"<<std::endl;
#define fas(i,a,b) for(int i=a;i<b;++i)  //[小 大)
#define fdes(i,b,a) for(int i=b;i>=a;--i) //[大 小]
#define mm memset
typedef pair<int,int> PII;
//*********************************end积累的常用宏和定义*******************************

// *************************************加快cin/cout速度*******************************
/*
c++中常用打印
printf("%lld",long long ) 对应 long long
printf("lf",double)
scanf("%d",&n1) 把缓冲区的值放入n1地址对应的变量中
值得一提的是，scanf会自动忽略空格，Tab指标和回车。
但是scanf(" %c",&c1)例外，它会读取'\n'到字符c1中。所有一般在模式前面加上空格
即为“空格%c”
*/
ios::sync_with_stdio(false);//取消cin/cout和printf/scanf之间的绑定
cin.tie(0);//取消cin和cout之间的绑定

//*******************************************加快cin/cout速度****************************




//********************************快速排序实现quickSort*************************************


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
// ***********************************end quickSort*******************************




// ****************************************mergeSort归并排序***********************
int nums[1000];
int nums2[1000];
void fmerge(int nums[],int lo,int mid,int hi) //[lo,mid] [mid+1,hi]
{
    //int nums2[hi-lo+1]; 如果这样那么k对应的位置要从0开始，不好计算
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

//*********************************************************end quickSort**************************



//********************************************* 二叉堆以及堆排序的实现***********************************************
/*
以大顶堆和非严格递增序列为例
*/
const int MAXN=1000+10;

// [1,nsize]
int nums[MAXN];

void heapify(int nums[],int p,int nsize);

void insert_h(int nums[],int &nsize,int x);//基于逐个插入的方法建堆

void build_heap(int nums[],int nsize);//floyd 快速建堆

void sort_h(int nums[],int nsize);// 大顶堆最终可以形成递增序列  小顶堆最终可以形成递减序列 
//因为具体做法是每次弹出堆顶元素，同时堆的规模从尾部减一

fas(i,0,n)
{
    cin>>nums[i+1];
}
insert_h(nums,n,100);//build_heap(nums,100);
sort_h(nums,n);


void heapify(int nums[],int p,int nsize)
{//注意区间[p,nsize]
    int largest=p,left=p<<1,right=(p<<1)+1;
    if(left<=nsize && nums[p]<nums[left])
    {
        largest=left;
    }
    if(right<=nsize && nums[largest]<nums[right])
    {
        largest=right;
    }               //此时largest为最大元素下表
    if(largest==p) //当根节点p 为最大时，已经满足大顶堆性质
        return;     //递归基
    swap(nums[largest],nums[p]);
    heapify(nums,largest,nsize); //交换后递归下一层

}

void build_heap(int nums[],int nsize)
{
    fdes(i,(nsize>>1),1) //注意从后往前，从最后一个非叶节点调用heaptify
    {
        heapify(nums,i,nsize);
    }
}

void sort_h(int nums[],int nsize)
{
    build_heap(nums,nsize);
    fdes(i,nsize,2) // 其他元素都在应该的位置上时第一个元素也在应该的位置
    {
        swap(nums[1],nums[nsize--]);//每次把首元素(最大元素)和最后元素交换，同时规模减一
        heapify(nums,1,nsize);//其他元素都满足堆，首元素向下交换
    }
}

void insert_h(int nums[],int &nsize,int x)
{
    nums[++nsize]=x;//最后的插入元素不满足堆性质
    int i=nsize,p;
    while(1<i) //只要当前位置i不是根
    {
        p=i>>1; //找到i的父亲p，p最后一次可能指向根(1)
        if(nums[i]<=nums[p])
            break;
        swap(nums[p],nums[i]);
        i=p;
    }
}
//*********************************************end heapSort堆排序****************************************

//********************************************** 二分查找Bsearch的规范写法**********************************
int findLow(int nums[],int lo,int hi,int x) //[lo,hi]
{
    //所有大于等于x中最小的

    while (lo<hi)
    {
        int mid=(lo+hi)>>1;//如果lo和hi相邻，那么mid的值为lo
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
        int mid=(lo+hi+1)>>1; //如果lo和hi相邻，那么mid的值为hi
        if(nums[mid]<=x)
            lo=mid;         // 此时mid的值是hi，再赋值给lo就能在下次跳出循环。
        else
            hi=mid-1;
    }
    if(nums[lo]==x) return lo;
    return -1;    
}
//*****************************************************end二分查找Bsearch********


//***********************************字符串表示的大数进行计算*********************

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
//**************************big integer add********************************88
string fsubCore(const string&a,const string&b);

string fsubString(const string&a,const string&b)
{ // 相减是调用fsubCore 实现的。这个函数本身只负责应对特殊情况(a=b和b=0)和保证a>b

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
//*******************************end 字符串表示的大数进行计算*****************************


//********************************统计数字的二进制表示中“1”的个数************8
/*
有多种做法
*/
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
// 方法二

//****************************统计数字的二进制表示中“1”的个数******************************8

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

//************************************************双指针常用方式**************************

/*
一般双指针 j->i 或p->q
1. p->q同向 
实现unique函数，该函数返回去重后的下一个位置
2. p q反向
实现reverse函数，该函数使得数组反转
*/
vector<int>::iterator funique(vector<int> &nums)
{
    int i,j;
    for(i=0,j=0;i<nums.size();++i)
    {
        if(i==0|| nums[i]!=nums[i-1])
            nums[j++]=nums[i];
    }
    return nums.begin()+j;
}

//*****************************************双指针进阶****单调栈或单调队列
/*
单调栈
例子：当前元素x左边，比x小的前提下，更近的元素
维护一个递增栈
放入栈中的元素，要么距离x更近，要么更小
*/
using namespace std;
const int N=10010;
int rsp=0;
int e1[N];

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        int tmp;cin>>tmp;
        while(rsp&&e1[rsp-1]>=tmp)
            --rsp;
        if(rsp)
            cout<<e1[rsp-1]<<" ";
        else 
            cout<<-1<<" ";
        e1[rsp++]=tmp;
    }
}
/*
单调队列
实则是双端队列，队尾也要出队满足单调性
例子：窗口区最大值 满足递减序列
要么更大，要么寿命长
*/
const int N=10010;
int nums[N];
int queue1[N]; //下标
int hh,tt;
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;++i) scanf("%d",nums+i);
    for(int i=0;i<n;++i)
    {
        if(hh<tt&&queue1[hh]<i-k+1) ++hh;
        while(hh<tt&&nums[i]<=nums[queue1[tt-1]]) --tt;
        queue1[tt++]=i;
        if(i>=2) printf("%d ",nums[queue1[hh]]);
    }
    puts("");
    hh=tt=0;
    for(int i=0;i<n;++i)
    {
        if(hh<tt&&queue1[hh]<i-k+1) ++hh;
        while(hh<tt&&nums[queue1[tt-1]]<=nums[i]) --tt;
        queue1[tt++]=i;
        if(i>=2) printf("%d ",nums[queue1[hh]]);
    }
}

//*******************************************************************end 双指针常用方式*********************************


//***********************************区间合并 返回合并后的新区间**********************
typedef pair<int,int> PII;// nums1中的区间用pair表示。
vector<PII> nums1;
vector<PII> fsegMerge(vector<PII>& nums1)
{
    if(nums1.size()<=1) return nums1;
    vector<PII> ans1;
    int lo=nums1[0].first,hi=nums1[0].second;
    for(int i=1;i<nums1.size();++i)
    {
        if(nums1[i].first>hi)
        {
            ans1.push_back({lo,hi});
            lo=nums1[i].first,hi=nums1[i].second;
        }
        else
        {
            hi=max(hi,nums1[i].second);
        }
    }
    ans1.push_back({lo,hi});
    return ans1;
}
//***********************************end区间合并************************************************************************

//***********************************************  数组模拟链表********************************
/*
平时使用单链表的方法一般：
    strcut Node
    {
        Node* next;
        int val;
    }
同时定义一个头节点head，该节点不存放数据。头指针则是始终指向链表的头部
每次新插入元素需要new struct()
数组模拟链表不用new malloc函数，避免了超时
*/
const int N=10000;
int e1[N];
//e1存放元素
int ne1[N];
//ne1存放下一个元素的指针
//其中 ne1和e1的索引是对应的
int head1,idx;
//head存放头节点；idx指向当前可用的位置，每次使用后idx=idx+1

void finitialize()
{
    head1=-1; //此时head指向空
    idx=0;
}
//在逻辑上把元素插在头部
void faddHead(int x)
{
    e1[idx]=x;
    ne1[idx]=head1;
    head1=idx;
    ++idx;
}
//插入的元素在K的后面
void faddK(int k,int x)
{
    e1[idx]=x;
    ne1[idx]=ne1[k];
    ne1[k]=idx;
    ++idx;
}
// 删除K后面的一个元素
void fremove(int k)
{
    ne1[k]=ne1[ne1[k]];
}

//*******************************************************数组模拟双链表
//注意 元素和指针的下标都是对齐的
const int N=10010;
int e1[N];
int nl[N];// 存放左指针
int nr[N];
int idx1;//存放当前可以用的空间

void finitialize()
{
    idx1=2;
   // e1[0]=e1[1]=0;
   // nl[0]=nr[1]=-1;
    nr[0]=1;nl[1]=0;
}

void fadd(int  k,int x) //插入的元素x在K的后面
{
    e1[idx1]=x;
    nl[idx1]=k;
    nr[idx1]=nr[k];
    nl[nr[idx1]]=idx1;
    nr[nl[idx1]]=idx1;
    ++idx1;
}

int fremove(int k)
{
    int tmp=e1[k];
    nl[nr[k]]=nl[k];
    nr[nl[k]]=nr[k];
    return tmp;
}
//****************************************数组模拟栈
/*
[0,]
int rsp是模拟指针,rsp指向栈顶的下一个可用位置
rsp=[0,]
*/
const int N=10010;
int e1[N];
int rsp;
void finitial()
{
    rsp=0;
}
void push(int x)
{
    e1[rsp++]=x;
}
void  pop()
{
    --rsp;
}
int top()
{
    return e1[rsp];
}
/*
消耗一个额外空间区分循环队列情况
rear指向队列可用位置的下一个位置
front指向队列最前排可用位置
front1==rear1 时 队列为空
(rear1+1)%MAXSIZE==front 是 队满
(rear-front+MAXSIZE)%MAXSIZE 是元素个数

push 先检测队不满  e1[rear++]=x
pop 先检测队不空  ++front;
*/
const int N=10010;
int e1[N];
int front1,rear1;



//*************************************************************end数组模拟链表********************************

const int MAXN=1000;
class UF
{
private:
    int _n;
    int _rank[MAXN];
    int _uf[MAXN];
protected:
    virtual void finitialize(int n);
public:
    UF(int n):_n(n){finitialize(n);}
    int findx(int x);
    int fgetN();
    void fmerge(int x,int y);
};

void UF::finitialize(int n)
{//初始化：每个节点以自己为根同时它的秩设置为一
//秩：根节点对应集合的最长路径
    for(int i=0;i<n;++i)
    {
        _rank[i]=1;
        _uf[i]=i;
    }
}
int UF::findx(int x)
{   //路径压缩
    //在返回过程中使路径上的所有结点指向根节点
    if(_uf[x]==x)
        return x;
    return _uf[x]=mfind(_uf[x]);
}
int UF::fgetN()
{//返回现存的集合数量
    return _n;
}
void UF::fmerge(int x,int y)
{   //按秩合并
    //把x和y分别位于的集合进行合并
    int tx=mfind(x);
    int ty=mfind(y);
    if(tx==ty) return;
    --_n;
    if(_rank[tx]<_rank[ty])
    {
        _uf[tx]=ty;
    }
    else if(_rank[ty]<_rank[tx])
    {
        _uf[ty]=tx;
    }
    else
    {//_rank[tx]==_rank[ty]
        _uf[tx]=ty;
        ++_rank[ty];
    }
}
//其实rank可以用负数在_uf中表示
//****************************************************************并查集*******************

//**************通过统计DFS的调用次数来确定连通分量(极大连通子图)的数目
vector<vector<bool>> matrix(n,vector<bool>(n,false));//用邻接矩阵存储图
//matrix[x-1][y-1]=matrix[y-1][x-1]=true;
int n;      //节点数目
vector<bool> visited(n,false);//visited数组用bool存储节点是否访问过
for(int i=0;i<n;++i)
{
    if(visited[i]==false)
    {
        dfs(matrix,i,visited);
        ++counter;// 连通分量数目
    }
}
// const vector<vector<bool>>& matrix,int x,vector<bool>& visited 
void dfs(int x)
{
    //if(visited[x]==true) return; 也可以这样显式定义递归基
    int nsize=matrix.size();
    visited[x]=true;
    for(int i=0;i<nsize;++i)
    {
        if(matrix[x][i]==true&&visited[i]==false) 
        {//有当前节点还有边，并且边连接的节点为没有访问过
            dfs(i);
        }
    }
}

/*
连通分量=极大连通子图
极小连通子图&&所有点::=生成数
MST最小生成树::=生成数集合中边的和最小的一类

PRIM普里姆prim  和   kruskal 克鲁斯卡尔 都适用于求解MST
一般prim适合节点少，其时间复杂度为O(N^2)。kruskal适合边少,其时间复杂度为O(E*log(E))。
O(N^2)围绕节点数N，直接二重循环
O(E*log(E)::=E是遍历所有边的一次，log(E)是从优先队列(小根堆)中选出当前最短边的消耗
*/




//*****************************************prim*************************prim*************************
//实战中适合求解问题直接给出每个点的坐标，而不是给出边的长度
const int MAXN = 100;
enum Mflag {R, U};  //定义枚举类型
// Remain-set and Used -set 
// U Used集合表示最终形成 MST节点的集合
// R Remain集合表示当前还剩下未选用的元素
struct Point {
    double x, y; //每个点的坐标
    Mflag flag1;// 枚举类型和枚举变量 其值为R 和U
};
Point r[MAXN];//在初始化时应定位REMAIN，即所有节点都还没有被选用

bool isempty(int n, Point s[]);// 谓词：判断Remain集合是否为空
inline double calculateD(Point &a, Point &b); //计算两个点的距离

bool isempty(int n, Point s[]) {
    for (int i = 0; i < n; ++i) {
        if (s[i].flag1 == R)
            return false;
    }
    return true;
}
inline double calculateD(Point a, Point b) {
    //其实都不开方也能比较大小
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// 读入节点x，y 于Point r[MAXN],并且所有点的标记Mflag应初始化时应REMAIN::=即所有节点都还没有被选用
//核心步骤   On^2 计算R和U 集合最近元素距离
r[0].flag1 = U;   // 随机选用一个点归为MST的预备中
while (!isempty(n, r)) {
    double minv = 100000;// 画家策略 求覆盖
    int keepi;
    for (int i = 0; i < n; ++i) {
        if (r[i].flag1 == R) {
            for (int j = 0; j < n; ++j) {
                if (r[j].flag1 == U) {
                    double dst = calculateD(r[i], r[j]);
                    if (dst < minv) {// 找分别位于两个集合中距离最近的点和位于Remain集合中的节点的下标
                        minv = dst;
                        keepi = i;
                    }
                }
            }
        }
    }
    ans += kmin;// 累加R和U集合最近的边
    r[keepi].flag1 = U;//R节点数目减一，也意味着U集合加一
}


//**************************************************************kruskal 算法******************************
/*
需要 用到并查集来判断当前选用边的两个节点是否属于两个不同的集合,若是，则选用。
kruskal 适用于问题给出每个点和每对点的距离。譬如 给出节点下标为0，1，2 && 给出节点0-1的距离 w。
而不是给出每个点的具体坐标 x，y
*/
void kruskal(){};
struct Edge
{
    int point1,point2,weight;
    Edge(int p1,int p2,int w):point1(p1),point2(p2),weight(w){}; //节点下标0和1还有距离
    Edge(){};
    
};
bool cmp(const Edge & e1,const Edge & e2) 
{
    return e1.weight<e2.weight;
}
int n;// n为节点数
int numE=n*(n-1)/2; //numE为最多可能的边数
Edge edge[numE];

//***********************************************并查集(C形式版本)****************************************
const int MAXN=100;
int _rank[MAXN];
int father[MAXN];
void intialize(int n)
{
    for(int i=0;i<n;++i)
    {
        father[i]=i;
        _rank[i]=1;
    }
}

int find(int x)
{
    if(x==father[x])
        return x;
    return father[x]=find(father[x]);
}
void _union(int x,int y)
{
    x=find(x);
    y=find(y);
    if(_rank[x]<_rank[y])
        father[x]=y;
    else if(_rank[y]<_rank[x])
        father[y]=x;
    else
    {
        father[x]=y;
        ++_rank[y];
    }
}

//********************************end 并查集(C形式版本)
// 读入数据于Edge edge[numE];
sort(edge,edge+numE,cmp); // 按边的长度递增排序
for(int i=0;i<numE;++i)
{
    Edge tedge=edge[i];
    if(find(tedge.point1)!=find(tedge.point2)) 
    {//用到并查集来判断当前选用边的两个节点是否属于两个不同的集合,若是，则选用。
        ans+=tedge.weight;
        _union(tedge.point1,tedge.point2);//同时两个不同点对应的集合合并为同一集合
    }
}
// 返回||输出MST对应的值ans



//*****************************************************Huffman哈夫曼数****************
/*
记录树的性质：
1.节点数比边数多一。把每个点和头上的边组合，唯独根节点没有边

记录二叉树的性质
树中，节点的度就是指向孩子节点的分支数目。定义 n0为度0，以此类推 n1 n2
1.二叉树满足 
2*n2+1*n1+1=n2+n1+n0 边数加1等于节点数
--->推出 n0=n2+1
这个性质对Huffman树也成立，因为Huffman树没有n1节点

Huffman树应用于对元素进行不固定长度的编码
譬如字符a出现的频率高编码为01 字符b出现的频率低编码为00001
且满足前缀编码(任意一个短编码不是长编码的前缀)

1.Huffman树对应的最短路径长度 求和 所有叶节点的路径长度*叶节点的值
性质：树对应的最短路径长度= 非叶节点(n2)的和

*/
#include<queue>
#include <functional>
priority_queue<int,vector<int>,greater<int>> pq;
// 大顶堆对应小于符号 小顶堆对应大于符号
// 大顶堆最终可以形成递增序列  小顶堆最终可以形成递减序列 
for(int i=0;i<n;++i)
{
    cin>>temp;
    pq.push(temp); //读入数据建堆
}
while(pq.size()!=1) //优队中只有一棵树，符合终止条件
{
    int t1=pq.top();pq.pop();
    int t2=pq.top();pq.pop();
    ans=ans+(t1+t2); //非叶节点(n2)的和
    pq.push(t1+t2);
}
//返回ans 即为Huffman树对应的最短路径长度

//*****************************************************Dijstra


//**************************************************topoSort 拓扑排序*******************

int matrix[MAXN][MAXN];
int inDegree[MAXN];//下标对应节点，存放值对应节点入度

const int MAXN=100;
const int INF=0x7fffffff;
int topoSort(int n)
{
    Mstack<int> ms;
    int counter=0;
    for(int i=0;i<n;++i)
    {
        if(inDegree[i]==0)
            ms.mpush(i);
    }
    while(ms.getSize()!=0)
    {
        ++counter;
        int x=ms.mfront();ms.pop();
        for(int i=0;i<n;++i)
        {
            if(matrix[x][i]!=INF)
            {
                --inDegree[i];
                if(inDegree[i]==0)
                {
                    ms.mpush(i);
                }
            }

        }

    }
    return counter;
}
//***********************************************************快速幂******************
/*
注意：K为负数时，需要转化成1/(n^k)  k转为正
任意一个自然数(0,正整数)都可以表示成 m0*2^0+m1*2^1+m2*2^2... 其中mn表示bool常量
2^5=2^(2^0+2^2)=2^(1+4)=(2^1）*（2^4）
*/
 double n,k;// 浮点数n的K次方
 //快速幂
  double fpow(double n,int k)
 {
    double ans=1;
    while(k)
    {
        if(k&1) ans*=n;
        k>>=1;
        n*=n;
    }
    return ans;
 }

//*********************************************************矩阵快速幂*****************
 int n,k;// n阶矩阵的K次方
vector<vector<int>> multiply(const vector<vector<int>>&m1 ,const vector<vector<int>>&m2)
{
    int nsize=m1.size(),temp;
    vector<vector<int>> ans(nsize,vector<int>(nsize,0));
    for(int i=0;i<nsize;++i)
    {
        for(int j=0;j<nsize;++j)
        {
            temp=0;
            for(int k=0;k<nsize;++k)
            {
                temp+=m1[i][k]*m2[k][j];
            }
            ans[i][j]=temp;   
        }
    }
    return ans;
}
    while(cin>>n>>k)
    {
        vector<vector<int>> e(n,vector<int>(n,0));//单位矩阵E
        vector<vector<int>> m0(n,vector<int>(n,0));
        for(int i=0;i<n;++i)
            e[i][i]=1;//单位矩阵E
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                cin>>m0[i][j];
        //******************核心
        while(k!=0)
        {
            if((k&1)==1)
                e=multiply(e,m0);
            k=k>>1;
            m0=multiply(m0,m0);
        }
        //******************end核心

        for(int i=0;i<n;++i)// 输出结果
        {
            for(int j=0;j<n;++j)
            {
                cout<<e[i][j]<<" ";
            }
            cout<<endl;
        }
    }
//***********************************************************end快速幂***********************************************************

//***********************************************素数筛选&&分解|| 回文数判定*****************
int n;
bool fprime(int n)  //判断是否为素数
{
    int sqrtn=sqrt(n); // 在[2，sqrt(n)]中搜索集合即可。因为若存在大于sqrtn的因子，其对应的因子必定小于等于sqrtn
    for(int i=2;i<=sqrtn;++i)
    {
        if(n%i==0)
            return false;
    }
    return true;
}
int freverse(int n) //判断是否为回文数
{
    int ans=0;
    while (n)
    {
        ans=ans*10;
        ans+=n%10;
        n/=10;
    }
    return ans;
} 
if(n==freverse(n));
/*
任意一个非素数必定至少有一个素数因数
故从2开始，把素数的倍数置为非素数
*/
const int N=10010;
bool numsp[N];
// 0::= 素数(prime)  1:: 非素数  全局区默认为0
vector<int> alls;//收集素数
for(int i=2;i<N;++i)
{
    if(numsp[i]==1) continue; //如果是非素数 那么跳过
    alls.push_back(i);//收集素数
    for(int j=i*2;j<N;j+=i)
        numsp[j]=1;
}

//***********************************************end素数筛选和分解************************************************************

//*****************************************用字符串表示式子进行四则运算*************************
/*
前缀表达式(波兰表达式)
中缀表达式

后缀表达式(逆波兰表达式)
*/
//*****************************************end字符串表示式子进行四则运算*******************************************************

//***********************************brute force&&strcut Node构建一棵树********************
/*
前序，中序，后续遍历
用前+中||后+中||中+层 构建一棵树
*/

//******************************************************KMP****************************************
/*
KMP
*/
/*
定义主串，模式串，next数组都从1开始
p:abaabac
  1122321
p:aaa
  123
next 存放匹配前缀的下一个位置
每次for结尾时 j指向匹配前缀的下一个位置,i指向后缀本位.
下次for开始i++，此时ij都指向新位置
*/
const int N=10010,M=1000010;
char p1[N],s1[M];// p是模式pattern ,s是待匹配字符串
int next1[N];
int n,m;
next1[1]=1;// 1初始化
for(int i=2,j=1;i<=n;++i)//从2开始
{
    while(j>1&&p1[i]!=p1[j]) j=next1[j-1];
    if(p1[i]==p1[j]) ++j;
    next1[i]=j;
}
for(int i=1,j=1;i<=m;++i)
{
    while(j>1&&s1[i]!=p1[j]) j=next1[j-1];
    if(s1[i]==p1[j])
    {
        ++j;
        if(j==n+1)
        {
            printf("%d ",i-n);//i-n+1是从1开始的索引下标
            j=next1[j-1];
        }
    } 
}







