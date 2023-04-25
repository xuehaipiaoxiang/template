//********************************
#define fdbg  std::cout<<"*********************************"<<std::endl;
#define fas(i,a,b) for(int i=a;i<b;++i)  //[小 大)
#define fdes(i,b,a) for(int i=b;i>=a;--i) //[大 小]
#define mm memset
typedef pair<int,int> PII;
//*********************************积累的常用宏和定义

// **********************************
    ios::sync_with_stdio(false);//取消cin/cout和printf/scanf之间的绑定
    cin.tie(0);//取消cin和cout之间的绑定
//*******************************************加快cin/cout速度

/*
c++中常用打印
printf("%lld",long long ) 对应 long long
printf("lf",double)
scanf("%d",&n1) 把缓冲区的值放入n1地址对应的变量中
值得一提的是，scanf会自动忽略空格，Tab指标和回车。
但是scanf(" %c",&c1)例外，它会读取'\n'到字符c1中。所有一般在模式前面加上空格
即为“空格%c”
*/

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

// ***************************************************************mergeSort归并排序
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

//****************************************************************************end quickSort

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
//**************************************************************************end Bsearch
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

//***********************************************
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
//**************************************实现unique函数，返回去重后的下一个位置
typedef pair<int,int> PII;
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
//***********************************区间合并 nums1中的区间用pair表示。返回合并后的新区间

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
// 避免使用new malloc函数，防止超时
//**************************************数组模拟链表
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




//*****************************************prim*************
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


//**************************************************************kruskal 算法
/*
需要 用到并查集来判断当前选用边的两个节点是否属于两个不同的集合,若是，则选用。
kruskal 适用于问题给出每个点和每对点的距离。譬如 给出节点下标为0，1，2 && 给出节点0-1的距离 w。
而不是给出每个点的具体坐标 x，y
*/

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

//********************并查集(C形式版本)
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

//****************end 并查集(C形式版本)
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

//*****************************************************Huffman哈夫曼数
//*****************************************************Dijstra
//**************************************************topoSort 拓扑排序
//**********************************************快速幂
//*********************************************矩阵快速幂
//********************************************* 二叉堆



