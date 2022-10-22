#include <stdio.h>

#define MAX_N 100
typedef struct {
	int n, m;
	int A[MAX_N][MAX_N];
}Graph;

void init_Graph (Graph *G, int n){
	G->n= n;
	G->m=0;
	int i, j;
	for (i=1; i<=G->n; i++){
		for (j=1; j<=G->n; j++){
			G->A[i][j]=0;
		}
	}
}

void add_edge (Graph *G, int u, int v){
	G->A[u][v]++;

	G->m++;
}

int adjacent( Graph *G, int u, int v){
	return G->A[u][v];
}

//Queue


typedef struct {
	int data[MAX_N];
	int front, rear;
}Queue;

void make_null_Queue (Queue *Q){
	Q->front=0;
	Q->rear=-1;
}

void enqueue (Queue *Q, int u){
	Q->rear++;
	Q->data[Q->rear]= u;
	
}

int front (Queue *Q){
	return Q->data[Q->front];
}

void dequeue(Queue *Q){
	Q->front++;
	
}

int empty_Queue(Queue *Q){
	return Q->front> Q->rear;
}


//List 
typedef struct {
	int data[MAX_N];
	int size;
}List;

void make_null_List(List *L){
	L->size=0;
}

void push_back (List *L, int u){
	L->data[L->size]=u;
	L->size++;
}

int element_at (List *L, int i){
	return L->data[i-1];
}

int count_List (List *L){
	return L->size;
}


//TOPO
int d[MAX_N];
#define oo 9999999
List topo_sort (Graph *G){
	int d[MAX_N];
	
	int i,u,v;
	for (i=1; i<=G->n; i++){
		d[i]=0;
		int j;
		for (j=1; j<=G->n; j++){
			if (G->A[j][i]!=0)
				d[i]++;
				//printf("%d \n", d[i]);
		}
	}
	Queue Q;
	make_null_Queue(&Q);
	for (u=1; u<=G->n; u++){
		if (d[u]==0)
			enqueue(&Q, u);
			
	}
	List L;
	make_null_List(&L);
	while (!empty_Queue(&Q)){
		int u= front(&Q);
		dequeue(&Q);
		push_back(&L,u);
		for (v=1; v<=G->n; v++){
			if (G->A[u][v]!=0){
				d[v]--;
				if (d[v]==0)
					enqueue(&Q, v);
			}
		}
	}
	return L;

}

int max (int a, int b){
	if (a>b)
		return a;
	else return b;
}

int min (int a, int b){
	if (a<b)
		return a;
	else return b;
}
int main (){
	//freopen("data.txt", "r", stdin);
	Graph G;
	int n;
	scanf("%d", &n);
	init_Graph(&G, n+2);
	int alpha = n+1;
	int beta = n +2;
	d[alpha]=0;
	
	int i, u, v,j;
	for (i=1; i<=n; i++){
		scanf("%d", &d[i]);
		while(1){
			scanf("%d", &v);
			if (v==0)
				break;
			else add_edge(&G,v,i );
		//	printf("%d ", v);
		}
	//	printf("\n");
	}
	int e, x;
	for (e=1; e<=n; e++){
		int deg_vao =0;
		int deg_ra= 0;
		
		for (x=1; x<=n; x++){
			if(G.A[x][e]>0)
				deg_vao++;
			if(G.A[e][x]>0)
				deg_ra++;
				
		}
		if (deg_vao==0)
			add_edge(&G, alpha, e);
		if (deg_ra==0)
			add_edge(&G, e, beta);
	}
		List L;
		L= topo_sort(&G);
		
		int t[MAX_N];
		t[alpha]=0;
		for (j=2;  j<=L.size ;j++){
			 u =  element_at(&L, j);
			t[u]=-oo;
			for(x=1;x<=G.n;x++){
				if(G.A[x][u]>0)
					t[u]= max(t[u], t[x]+d[x]);
			}
		}
		
		int T[MAX_N];
		T[beta]= t[beta];
		for (j=L.size-1;  j>=1 ;j--){
			 u =  element_at(&L, j);
			T[u]=+oo;
			for(x=1;x<=G.n;x++){
				if(G.A[u][x]>0)
					T[u]= min(T[u], T[x]-d[u]);
			}
		}
		
	

	for (e=1; e<=n; e++){
		printf("t[%d] = %d\n", e, t[e]);
	}
	for (e=1; e<=n; e++){
		printf("T[%d] = %d\n", e, T[e]);
	}


	return 0;
}
