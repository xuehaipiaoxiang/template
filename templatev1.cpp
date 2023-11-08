//*****************************************************trie****************************
/*
字典树
对字符串出现次数计数
*/
const int N = 10010;

char table1[N][26];
int idx1; // index 始终增加
bool visited[N]; // 可以改成计数

void insert( char  str1[])
{
    int cur = 0;
    for(int i = 0; str1[i] != '\0'; ++i)
    {
        int tmp = str1[i] - 'a';
        if(table1[cur][tmp] == 0) 
            table1[cur][tmp] = ++idx1;
        cur = table1[cur][tmp]
    }
    visited[cur] = true;
}

bool find ( char str1[])
{
    int cur = 0;
    for(int i = 0; str1[i] != '\0'; ++i)
    {
        int tmp = str1[i] - 'a';
        if(table1[cur][tmp] == 0) 
            return false
        cur = table1[cur][tmp]
    }
    return visited[cur];
}
