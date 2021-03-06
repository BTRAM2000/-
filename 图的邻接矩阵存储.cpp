#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

#define MVNum 100 //最大顶点数
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef string VerTexType; //假设顶点的数据类型为字符串
typedef int ArcType;             //假设边的权值类型为整型

typedef int QElemType;    //队列
typedef int Status;

//------------图的邻接矩阵------------------
typedef struct {
	VerTexType vexs[MVNum];            //顶点表
	ArcType arcs[MVNum][MVNum];      //邻接矩阵
	int vexnum, arcnum;                //图的当前点数和边数
} Graph;

//- - - - - 队列的链式存储结构- - - - -
typedef struct QNode {
	QElemType data;
	struct QNode *next;
} QNode, *QueuePtr;
typedef struct {
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针
} LinkQueue;

//得到顶点i的数据
VerTexType Vertexdata(const Graph &g, int i) {
	return g.vexs[i];
}

int LocateVex(const Graph &g, VerTexType v) {
	//确定点v在G中的位置
	for(int i = 0; i < g.vexnum; ++i)
		if(g.vexs[i] == v)
			return i;
	return -1;
}//LocateVex

int FirstAdjVex(const Graph &g, int v) {
	//返回v的第一个邻接点编号，没有返回-1
	int i;
	for(i=0; i<g.vexnum; ++i) {
		if(g.arcs[v][i] == 1)
			return i;
	}
	return -1;
}//FirstAdjVex

int NextAdjVex(const Graph &g, int v, int w) {
	//返回v相对于w的下一个邻接点，没有返回-1
	/****在此下面完成代码***************/
	int i;
	for(i=w+1; i<g.vexnum; ++i) {
		if(g.arcs[v][i] == 1)
			return i;
	}
	return -1;

	/***********************************/
}//NextAdjVex

void CreateUDG(Graph &g) {
	//采用邻接矩阵表示法，创建无向图G
	/****在此下面完成代码***************/
	int i,j,k;
	VerTexType v1,v2;
	cin>>g.vexnum>>g.arcnum;//输入总定点数，总边数
	for(i=0; i<g.vexnum; i++)
		cin>>g.vexs[i];
	for(i=0; i<g.vexnum; i++)//初始化邻接矩阵，边的权值均设置为0
		for(j=0; j<g.vexnum; j++)
			g.arcs[i][j] = 0;
	for(k=0; k<g.arcnum; k++) {
		cin>>v1>>v2;
		i = LocateVex(g,v1);
		j = LocateVex(g,v2);
		g.arcs[i][j] = g.arcs[j][i] =1;
	}
	/***********************************/
}//CreateUDN

bool visited[MVNum];

void DFS(Graph g, int v) {
	cout << g.vexs[v] <<' ';
	visited[v] = true;
	int w;
	for(w = FirstAdjVex(g, v); w >= 0; w = NextAdjVex(g, v, w)) {
		if(!visited[w]) {
			DFS(g,w);
		}
	}
}

void DFSTraverse(Graph g) {
	ArcType v;
	for(v=0; v<g.vexnum; v++) {
		visited[v] = false;
	}
	for(v=0; v<g.vexnum; v++) {
		if(!visited[v]) {
			DFS(g,v);
		}
	}
	cout<<endl<<endl;
}

Status InitQueue(LinkQueue &q) { //构造一个空队列Q
	q.front = q.rear = new QNode; //生成新结点作为头结点，队头和队尾指针指向此结点
	q.front->next = NULL; //头结点的指针域置空
	return OK;
}//链队的初始化

Status EnQueue(LinkQueue &q, QElemType e) {

	QNode *p = new QNode;
	p->data = e;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
	return OK;
}//　链队的入队

Status QueueEmpty(LinkQueue q) {
	return q.front == q.rear ;
}

Status DeQueue(LinkQueue &q, QElemType &e) {
	if(q.front == q.rear )
		return ERROR;
	QueuePtr p = q.front ->next;
	e = p->data ;
	q.front->next = p->next ;
	if(q.rear == p)
		q.rear = q.front ;
	delete p;
	return OK;
}//链队的出队

QElemType GetHead(LinkQueue q) {
	return q.front->next->data;
}//取链队的队头元素

bool Visited[MVNum];

void BFSTraverse(Graph g, int v) {
	int u, w;
	LinkQueue q;

	cout << Vertexdata(g, v) << " ";
	Visited[v] = true;
	InitQueue(q);
	EnQueue(q,v);
	while(!QueueEmpty(q)) {
		DeQueue(q, u);
		for(w=FirstAdjVex(g,u); w>=0; w=NextAdjVex(g,u,w)) {
			if(!Visited[w]) {
				cout << Vertexdata(g, w) << " ";
				Visited[w] = true;
				EnQueue(q,w);
			}
		}
	}
	cout<<endl;
}

void PrintUDG(const Graph& g) {
	int i, j;
	cout << "    ";
	for(i = 0; i < g.vexnum; i++) {
		cout << setw(4) << g.vexs[i] ;
	}
	cout << endl;
	for(i = 0; i < g.vexnum; i++) {
		cout << setw(4) << g.vexs[i];
		for(j = 0; j < g.vexnum; j++) {
			cout << setw(4) << g.arcs[i][j];
		}
		cout << endl;
	}
	cout<<endl;
}//输出邻接矩阵

void PrintDian(Graph g) {
	for(int i = 0; i < g.vexnum; i++) {
		cout << Vertexdata(g, i) << ":";
		for(int w = FirstAdjVex(g, i); w >= 0; w = NextAdjVex(g, i, w)) {
			cout << ' ' << Vertexdata(g, w);
		}
		cout << endl;
	}
	cout << endl;
}//输出各个顶点的邻接点

void DestroyUDG(Graph &g) {
	//you should do this
}
int main() {
	Graph g;
	CreateUDG(g);      //创建邻接矩阵 
	PrintDian(g);	   //打印各邻接点 
	PrintUDG(g);       //打印邻接矩阵 
	cout << "深度优先搜索: ";
	DFSTraverse(g);    //深度优先搜索 
	cout << "广度优先搜索: "; 
	BFSTraverse(g,0);  //广度优先搜索 
	DestroyUDG(g);     //销毁图 
	return 0;
}//main
