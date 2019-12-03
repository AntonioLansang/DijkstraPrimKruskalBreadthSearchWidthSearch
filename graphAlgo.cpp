#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <climits>


using namespace std;

class graph
{
        public:
                graph();
                graph( int x );              // constructor, x is # of nodes
                void bfs( int x );           // breadth-first node order
                void bfssp( int x );         // breadth-first spanning tree
                void dfs( int x );           // depth-first node order
                void dfssp( int x );         // depth-first spanning tree
                void PrintArr();               // print matrix
                void fill( ifstream& file ); // fill graph from data file
                void Dijkstra(int x);
                void DijkstraMatrix();
                void Prim(int x);
                void Kruskal();

        private:
                int DJMatrix[101][101];
                int Array[101][101];
                int y;//Properly sizes array
                int ECount;
};


//Default Consttructor
graph:: graph()
{


        //Sets up the Matrix
        //Array[101][101];
        y = 101;
        for(int k=0;k<101;k++)
                {
                        for(int j=0;j<101;j++)
                        {
                                Array[k][j]=0;
                        }
                }


}

//Constructor given an int
graph::graph(int x)
{

        y=x+1;

        //Sets up the Matrix
        Array[y][y];
        for(int k=0;k<(y);k++)
                {
                        for(int j=0;j<(y);j++)
                        {
                                Array[k][j]=0;
                        }
                }


}

void graph::fill(ifstream& ifp)
{
        // reading in number of nodes
   // int ECount=0;
    int FirstNum=0;
    int SecondNum=0;
    int Weight=0;

        ifp >> ECount;


        //create graph with an an adjadceny matrix of
    // size = num of nodes x num of nodes

          for(int k=1;k<=ECount;k++)
        {
                ifp >> FirstNum;
                ifp >> SecondNum;
                ifp >> Weight;

                        Array[FirstNum][SecondNum]=Weight;
                        Array[SecondNum][FirstNum]=Weight;

        }

                return;
}



void graph::bfs(int StartingNode)
{


        //1 for marked. 0 for not
        int MarkArray[y]={0};
        queue <int> D;

        D.push(StartingNode);

        int v;
        while(!D.empty())
        {
                v = D.front();
                D.pop();
                if(MarkArray[v]!=1)
                {
                        printf(" %d ", v);
                        MarkArray[v]=1;
                }

                        //i=y-1 and i>=1 for dfs
                        for(int i=1;i< y;i++)
                        {
                                if(Array[v][i] && MarkArray[i]!=1)
                                        D.push(i);
                        }
        }

        printf("\n");
        return;
}

void graph::bfssp(int StartingNode)
{
        printf("BFS SP: \n");
        int MarkArray[y]={0};
        queue <int> D;
        queue<int> P;

        int v,x;
        D.push(StartingNode);

        while(!D.empty())
        {
                v=D.front();
                D.pop();

                if(!P.empty())
                {
                        x=P.front();
                        P.pop();
                }

                if(!P.empty()&&(MarkArray[v]==0||MarkArray[x]==0))
                {
                        printf("%d-%d\n", x,v);
                }

                if(MarkArray[v]==0)
                {
                //      printf(" %d ",v);
                        MarkArray[v]=1;
                }

                if(MarkArray[x]==0)
                {
                        MarkArray[x]=1;
                }


                for(int i=1;i<y; i++)
                {
                        if(Array[v][i] && MarkArray[i]==0)
                        {

                                D.push(i);
                                P.push(v);
                        }

                }
        }

}

void graph::dfs(int StartingNode)
{
        printf("Depth: ");
        int MarkArray[y]={0};
        stack <int> D;

        int v;
        D.push(StartingNode);


        while(!D.empty())
        {
                v=D.top();
                D.pop();
                if(MarkArray[v]==0)
                {
                        printf(" %d ", v);
                        MarkArray[v]=1;

                }

                for(int i=y;i>=1;i--)
                {
                        if(Array[v][i]&&MarkArray[i]==0)
                        {
                                D.push(i);
                        }

                }

        }

        printf("\n");
}

void graph::dfssp(int StartingNode)
{
        printf("DFS SP: \n");
        int MarkArray[y]={0};
        stack <int> D;//Future Node?:
        stack <int> P;//Prev node


        int v,x;
        int Prev=0;
        D.push(StartingNode);


        while(!D.empty())
        {

                v=D.top();
                D.pop();

                if(!P.empty())
                {
                        x=P.top();
                        P.pop();
                }

//              printf("\nPOP AT BEGIN: %d removed from stack D\n", v);



                if(!P.empty()&&(MarkArray[v]==0||MarkArray[x]==0))
                {
                        //printf("%d popped off stack p\n", x);
                        printf("%d-%d\n", x,v);
                }






                if(MarkArray[v]==0)
                {
                        MarkArray[v]=1;
                }


                if(MarkArray[x]==0)
                {
                        //Something up here with previous Array
                        //Pop here? I think we need a pop to similar to line 232-233.
                        MarkArray[v]=1;
                //      printf("%d has been marked\n", v);

                }

                for(int i=y;i>=1;i--)
                {
                        if(Array[v][i]&&MarkArray[i]==0)
                        {
                        //      Something over here with the assigning the prev stack

                                P.push(v);
                        //      printf("%d added to stack p\n", v);
                                D.push(i);
                        //      printf("%d added to stack d\n",i);
                        }
                }




        }


}

void graph::Dijkstra(int StartingNode)
{
        printf("Dijkstra: \n");


        //Sets all the weights of unknown verts to infin
        int DistArray[y];
        for(int j=0;j<y;j++)
        {
                DistArray[j]=20000000;
        }



        int TrackerArray[y];
        for(int j=0;j<y;j++)
        {
                TrackerArray[j]=0;
        }

        //Sets up our starting node to be the lowest vertex
        DistArray[StartingNode]=0;

        int MinIndex;
        int Min;

        for(int k=1;k<ECount;k++)
        {


                Min=20000000;

                //Finds the closest vertex
                for(int k=1;k<y;k++)
                {
                        //1st Param checks if it's been processed
                        //
                        if(TrackerArray[k]==0&&DistArray[k]<Min)
                        {
                                Min=DistArray[k];
                                MinIndex=k;
                        }

                }//End of the for loop that finds closest

                TrackerArray[MinIndex]=1;

                //This for loop Reveals other nodes and finds smalles
                //distance
                for(int k=1;k<y;k++)
                {

                        //3 parameters
                        //1. Checks if it hasn't already been processed
                        //2. Checks if there is an actual edge
                        //3. Checks if the current distance in the distance array is greater than the calculated distance


                        if(TrackerArray[k]==0&&Array[MinIndex][k]&&
                         DistArray[MinIndex]!=200000000 && DistArray[MinIndex]+Array[MinIndex][k]<=DistArray[k])
                                {


                                        DistArray[k]=DistArray[MinIndex]+Array[MinIndex][k];
                                }

                }


        }//End of the main for loop
        printf("%d : ", StartingNode);
        for(int k=1;k<y;k++)
                {
                        printf(" %d ", DistArray[k]);
                }
                printf("\n");


        //Print the Distance Array
        /*
        for(int k=1;k<y;k++)
        {
                printf("%d to node %d is %d\n",StartingNode, k, DistArray[k]);
        }*/

}


void graph::DijkstraMatrix()
{
        printf("Begin the DJ Matrix: \n");

        //Properly allocates the array
        DJMatrix[y][y];
        for(int k=0;k<y;k++)
        {
                for(int j=0;j<y;j++)
                {
                        DJMatrix[k][j]=0;
                }
        }



        for(int row=0;row<y;row++)
        {

                //Start of the code ripped from Dijkstra
                int DistArray[y];
                for(int j=0;j<y;j++)
                {
                        DistArray[j]=20000000;
                }



                int TrackerArray[y];
                for(int j=0;j<y;j++)
                {
                        TrackerArray[j]=0;
                }

                //Sets up our starting node to be the lowest vertex
                DistArray[row]=0;

                int MinIndex;
                int Min;

                for(int k=1;k<ECount;k++)
                {


                        Min=20000000;

                        //Finds the closest vertex
                        for(int k=1;k<y;k++)
                        {
                                //1st Param checks if it's been processed
                                //
                                if(TrackerArray[k]==0&&DistArray[k]<Min)
                                {
                                        Min=DistArray[k];
                                        MinIndex=k;
                                }

                        }//End of the for loop that finds closest

                        TrackerArray[MinIndex]=1;

                        //This for loop Reveals other nodes and finds smalles
                        //distance
                        for(int k=1;k<y;k++)
                        {

                                //3 parameters
                                //1. Checks if it hasn't already been processed
                                //2. Checks if there is an actual edge
                                //3. Checks if the current distance in the distance array is greater than the calculated distance


                                if(TrackerArray[k]==0&&Array[MinIndex][k]&&
                                DistArray[MinIndex]!=200000000 && DistArray[MinIndex]+Array[MinIndex][k]<=DistArray[k])
                                        {


                                                DistArray[k]=DistArray[MinIndex]+Array[MinIndex][k];
                                        }

                        }


                }//End of the main for loop
                for(int k=1;k<y;k++)
                        {
                                 DJMatrix[row][k]=DistArray[k];
                        }
        //End of the code ripped from dijkstra
        }



                for(int k=1;k<y;k++)
                {
                        printf("%2d: ", k);
                        for(int j=1;j<y;j++)
                        {
                                printf(" %4d", DJMatrix[k][j]);
                        }

                        printf("\n");
                }

                int ans=1;
                int RowReq;
                int ColReq;

                while(ans!=0)
                {
                        printf("Give me the order pair of the distance you want! (row/col)\n");
                        cin >> RowReq >> ColReq;

                        printf("Distance is: %d\n", DJMatrix[RowReq][ColReq]);
                        printf("0 to break out");
                        cin >> ans;
                }

}

void graph::Prim(int StartingNode)
{
        printf("Prim:\n");

        //Keeps track of the edges that are now in a forest
        int TrackEdgeArray[y][y];
        for(int k=0;k<y;k++)
        {
                for(int j=0;j<y;j++)
                {
                        TrackEdgeArray[k][j]=0;//Will be turned to 1 after processing and handling
                }
        }

        //Keeps track of if a given node is even in a forest
        int TrackNodeArray[y];
        for(int k=0;k<y;k++)
        {
                TrackNodeArray[k]=0;
        }

        TrackNodeArray[StartingNode]=1;

        //Keeps track of which forest a node is in. Starts off as each node is in their own tree
        int TrackForestArray[y];
        for(int k=0;k<y;k++)
        {
                TrackForestArray[k]=k;
        }

        int ModifyThis=0;

        int MinIndex;
        int Min;

        int RowProc;
        int ColProc;

        int Sum=0;
        int LoopCount=0;
        while(LoopCount<y-2)
        {

                int MinEdge=1000000;

                //This outer for loop iterates through the tracker array finding those that are now in the set

                //This entire thing finds minimum edges that are attached to a node in the array
                for(int a=0;a<y;a++)
                {
                        //This if statement determines if it is now in the set
                        if(TrackNodeArray[a]!=0)
                        {
                                //This for loop tries to find all the connections to each node in
                                for(int b=0; b<y;b++)
                                {
                                        //This if statmenet makes sure they are not in the same forest
                                        //Prevents cycles
                                        if(TrackForestArray[a]!=TrackForestArray[b])
                                        {
                                                if(Array[a][b]<MinEdge&&Array[a][b]!=0
                                                                &&Array[b][a]!=0&&TrackEdgeArray[a][b]==0&&TrackEdgeArray[b][a]==0)
                                                {
                                                        MinEdge=Array[a][b];
                                                        RowProc=a;
                                                        ColProc=b;
                                                }
                                        }//End of the Cycle Prreventer
                                }
                        }//End of if it is even in the set of nodes

                }//End of the minimum  edge finder




                //This is where we mark and update our TrackEdgeArray and our TrackForestArray, and our TrackEdgeArray


                //Mark the TrackEdgeArray so they will no longer be considered a minimum edge
                TrackEdgeArray[RowProc][ColProc]=1;
                TrackEdgeArray[RowProc][ColProc]=1;

                printf("%d-%d with a weight of %d\n", RowProc, ColProc, MinEdge);
                Sum=Sum+MinEdge;

                //Adds the other node to the set of visited nodes
                TrackNodeArray[ColProc]=1;


                //Updates the forest of each node
                if(TrackForestArray[RowProc]>TrackForestArray[ColProc])
                {
                        ModifyThis=TrackForestArray[ColProc];
                //      printf("In Row>Col\n");
                        //This For loop hunts down all nodes that equal ColProc
                        for(int  k=0;k<y;k++)
                        {
                                if(TrackForestArray[k]==ModifyThis)
                                {
                                        TrackForestArray[k]=TrackForestArray[RowProc];
                                }

                        }

                }
                else if(TrackForestArray[ColProc]>TrackForestArray[RowProc])
                {
                        ModifyThis=TrackForestArray[RowProc];
                //      printf("In Col>Row\n");
                        for(int k=0; k<y; k++)
                        {
                                if(TrackForestArray[k]==ModifyThis)
                                {
                                        TrackForestArray[k]=TrackForestArray[ColProc];
                                }
                        }
                }

                /*
                for(int k=0;k<y;k++)
                {
                        printf(" %d ", TrackForestArray[k]);
                }
                printf("\n"); */

        LoopCount++;
        }//End of the main while loop


        printf("Prim's cost:%d\n", Sum);

}

void graph::Kruskal()
{
        printf("Kruskal\n");
        //Keeps track of the edges that are now in a forest
        int TrackEdgeArray[y][y];
        for(int k=0;k<y;k++)
        {
                for(int j=0;j<y;j++)
                {
                        TrackEdgeArray[k][j]=0;//Will be turned to 1 after shipping and handling
                }

        }

        //Use this for finding the cost
        int Sum=0;

        //Used when modifying
        int ModifyThis=0;

        //Keeps track of the nodes that are in a forest
        int TrackNodeArray[y];
        for(int j=0;j<y;j++)
        {
                TrackNodeArray[j]=j;
        }

        //Variables for processing
        int RowProc=0;
        int ColProc=0;

        int LoopCount=0;
        while(LoopCount<y-2)
        {

        //Selection sort to keep finding the smallest edge
        int MinEdge=100000;
        int a;
        int b;


        //This double for traverses the 2D array
        for(a=1;a<y;a++)
        {
                for(b=1;b<y;b++)
                {
                        //This if statement makes sure that a and b are not already in the same forest
                        //If this if(no pun intended) was not here, it would cause a cycle
                        if(TrackNodeArray[a]!=TrackNodeArray[b])
                        {
                                //This if statement tries to see if there's a smaller edge
                                //The 2nd and 3rd param make sure that the edge hasn't already been processed
                                if(Array[a][b]<MinEdge&&Array[a][b]!=0&&Array[b][a]!=0&&TrackEdgeArray[a][b]==0&&TrackEdgeArray[b][a]==0)
                                {
                                        MinEdge=Array[a][b];
                                        RowProc=a;
                                        ColProc=b;
                                }
                        }
                }
        }


        //Marking the edge as Processed section
        //2nd line
        TrackEdgeArray[RowProc][ColProc]=1;
        TrackEdgeArray[ColProc][RowProc]=1;

        printf("%d-%d with a weight of %d\n", RowProc, ColProc, MinEdge);
        Sum=Sum+MinEdge;

        //Marking the indexes

        //If Both Nodes are already in their own forests


        //Cases when the nodes are both free
        if(TrackNodeArray[RowProc]>TrackNodeArray[ColProc])
        {
                ModifyThis=TrackNodeArray[ColProc];

//              printf("In Row>Col\n");
                //This for loop hunts down all nodes that equal ColProc
                for(int k=1;k<y;k++)
                {
                        if(TrackNodeArray[k]==ModifyThis)
                        {
                                TrackNodeArray[k]=TrackNodeArray[RowProc];
                        }
                }

        }
        else if(TrackNodeArray[ColProc]>TrackNodeArray[RowProc])
        {

        //      printf("In col>row\n");

                ModifyThis=TrackNodeArray[RowProc];
                //This for loop hunts down all nodes that equal RowProc
                for(int k=1;k<y;k++)
                {
                        if(TrackNodeArray[k]==ModifyThis)
                        {
                                TrackNodeArray[k]=TrackNodeArray[ColProc];
                        }

                }

        }

        for(int k=1;k<y;k++)
        {
        //      printf(" %d ", TrackNodeArray[k]);
        }

        printf("\n");
        LoopCount++;
        }//End of the loop to capture all the edges

        printf("Kruskal Cost: %d\n", Sum);


}

void graph::PrintArr()
{
        printf("Now Printing Matrix: \n");

        for(int k=1;k<y;k++)
        {
                for(int j=1;j<y;j++)
                {
                        printf("%4d", Array[k][j]);
                }
                printf("\n");
        }

        printf("Done printing\n");

        return;
}

int main( int argc, char *argv[] )
{

        int location;
        ifstream ifp;

        //checking to see if file was entered on command line
        if ( argc != 2 )
        {
                cout << "File was not entered\n";
                return 2;
        }

        ifp.open( argv[1] );

        // checking to see if file was opened successfully
        if( ! ifp.is_open() )
        {
                cout << "File could not be opened\n";
                return 3;
        }

        int VCount=0;


        ifp >>VCount;
        graph g( VCount );

        g.fill(ifp);


        int StartingNode=0;
        cout << "Please give node you want to start with";
        cin >> StartingNode;

        g.PrintArr();

        printf("Breadth: ");
        g.bfs(StartingNode);
        g.dfs(StartingNode);
        g.bfssp(StartingNode);
        g.dfssp(StartingNode);
        g.Dijkstra(StartingNode);
        g.Kruskal();
        g.Prim(StartingNode);
        g.DijkstraMatrix();


        /*
        //ask for starting location
        cout << "Enter the starting location: ";
        cin >> location;

        //fill adjacency matrix
        g.fill( ifp );

        //print the matrix
        g.mprint();
        cout << endl << endl;

        //ask for starting location
        cout << "Enter the starting location: ";
        cin >> location;

        // calculate DFS
        g.dfs( location );
        cout << endl << endl;

        //calculate DFS-SP
        g.dfssp( location );
        cout << endl << endl;

        //calculate BFS
        g.bfs( location );
        cout << endl << endl;

        //calculate BFS-SP
        g.bfssp( location );
        cout << endl << endl;
*/
        return 0;
}
