#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

#define V 6
 
  int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{

    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v); 
                parent[v] = u;             //parent[0]=-1,[1]=0,[2]=0,[3]=1,[4]=2,[5]=3...
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
 
            
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;

    int rGraph[V][V]; 
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
 
    int parent[V];  
 
    int max_flow = 0;  

    while (bfs(rGraph, s, t, parent))
    {
  
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
       
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 

        max_flow += path_flow;
    }
 

    return max_flow;
}

int newfordFulkerson(int graph[V][V], int s, int t)
{
	  int y=0;
	int x=0,i=0; 
	int maxcapacity;
	 int n=0;
	int change;
	  int u=0, v=0;
   int j=0;
   int it;
   int k=0,f=0;
		

       
       int pa[V][V]={   {-1,-1,-1,-1,-1,-1},
                        {-1,-1,-1,-1,-1,-1},
                        {-1,-1,-1,-1,-1,-1},
                        {-1,-1,-1,-1,-1,-1},
                        {-1,-1,-1,-1,-1,-1},
                        {-1,-1,-1,-1,-1,-1}
                      };		 
   
    int a[V]={INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};
    int rGraph[V][V]; 
    for (int h = 0; h < V; h++)
        for (int l = 0; l < V; l++)
			  rGraph[h][l] = graph[h][l];
            
 
    int parent[V]; 
 
    int max_flow = 0;  
   
    
    while (bfs(rGraph, s, t, parent))  //O(E)
    {  
        int path_flow = INT_MAX;
        
        for (int v=t; v!=s; v=parent[v])
        {
            u = parent[v]; //Going back from 5 to 0
		   
            path_flow = min(path_flow, rGraph[u][v]); 
		     pa[k][j]= v;
          	 j++; 
                 
	    }
	    cout<<"j "<<j<<"\n";
          a[f]=path_flow;  // a contains all the minimum plathflow of a augmenting path
          f++;
          pa[k][j]=u;
         k++;
         
         j=0;
		        
        
        for (int v=t; v != s; v=parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
      
        max_flow += path_flow;
        
    }
    
     /*for(i=0;i<V;i++)
      cout<<"a= "<<a[i]<< " "<<"\n";*/
    /*for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
		{
			 cout<<"pa["<<i<<"]["<<j<<"]"<<pa[i][j]<<"\n";
		}*/
  
			 
	          cout<<"\n" << "The smallest element is " << *std::min_element(a,a+V) << "\n";
	          it=*std::min_element(a,a+V);

	          n = distance(a, find(a, a + V, it));
	         for (int j= 0; j < V; j++)
	      {
		     cout<<"pa"<<pa[n][j]<<"\n";
		     }
/*  for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
			 cout<<"r  "<<rGraph[u][v];*/
		     
	   for (int r=0; r<V; r++)
        {  
		    int q=pa[n][r];
            int p= pa[n][r+1];
            
            
		  if(rGraph[p][q]<=it&&q!=-1&&p!=-1)
			{
			      graph[p][q]++;
            }
         /* else if(graph[p][q]==it)
          {
		    graph[p][q]++;
		    cout<<"one"<<"\n";
          }//*/
          else{
		  }
	    } 
 

    return max_flow;
}


int main()
{   int y=0;
	int x=0,i=0; 
	int maxcapacity;
	 int n=0;
	int change;
	int s=0,t=5;
	  int u=0, v=0;
   int j=0;
   int it;
	
	int b=0;
   
    
    cout<<"enter the number x liters/sec";
	cin>>y;
	maxcapacity=fordFulkerson(graph, 0, 5);
	
	 for (u = 0; u < V; u++)
                   for (v = 0; v < V; v++)
                      cout<<"   "<<graph[u][v];
                      
                      cout<<"\n";
	
	if(y>maxcapacity)
	{
	   int loop=y-maxcapacity;
	   for(int b=0;b<loop;b++)
	    {
		     int gh=newfordFulkerson(graph, 0, 5);
		  
		      cout<<"new ford"<<gh<<"\n";                    
                  for (u = 0; u < V; u++)
                   for (v = 0; v < V; v++)
                      cout<<"   "<<graph[u][v];
                      cout<<"\n ";
                  int maxcap=fordFulkerson(graph, 0, 5);                                    
	              cout<<"maximum capacity "<<maxcap<<"\n";
     	}

     	
	    
   }
          else
        cout<<"No capacities have to be changed";

   
    return 0;
}

