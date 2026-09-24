#define MAX(a,b) ( ((a) > (b)) ? (a)  : (b) )

typedef struct NN_T
{
    int *children;
    int size;
    int indegree;
} NN, *PNN;



int dfsMax(PNN *adjList, int start, int *memo)
{
    if(adjList[start]->size == 0)
    {
        memo[start] = 1;
        return 1;
    }

    if(memo[start] != -1)
    {
        return memo[start];
    }

    int max = INT_MIN;
    int childMax = 0;
    for(int i = 0 ; i < adjList[start]->size; i++)
    {
        childMax = dfsMax(adjList, adjList[start]->children[i], memo);
        //memo[adjList[start]->children[i]] = childMax;
        max = MAX(max,  1 + childMax);
    }

    memo[start] = max;

    return max;
}

int maxJumps(int* arr, int arrSize, int d)
{
    int max = INT_MIN;

    int *memo = (int*)malloc(sizeof(int) * arrSize);
    for(int i = 0 ; i < arrSize ; i++)
    {
        memo[i] = -1;
    }

    PNN *adjList = (PNN*)malloc(sizeof(PNN) * arrSize);

    for(int i = 0 ; i < arrSize ; i++)
    {
        adjList[i] = (PNN)malloc(sizeof(NN));
        adjList[i]->children = (int*)malloc(sizeof(int) * arrSize);
        adjList[i]->size = 0;
        adjList[i]->indegree = 0;
    }

    // build the adjacency list
    for(int i = 0 ; i < arrSize ; i++)
    {
        PNN currNode = adjList[i];

        // check right direction
        for(int j = 1; j <= d ; j++)
        {
            if(((i + j) < arrSize) && (arr[i + j] < arr[i]))
            {
                // insert i+j to children of i
                currNode->children[currNode->size] = (i+j);
                currNode->size++;

                // update indegree of (i+j)
                adjList[i+j]->indegree++;
            }
            else
            {
                break;
            }
        }

        // check left direction
        for(int j = 1; j <= d ; j++)
        {
            if(((i - j) >= 0) && (arr[i - j] < arr[i]))
            {
                // insert i-j to children of i
                currNode->children[currNode->size] = (i-j);
                currNode->size++;
                
                // update indegree of (i-j)
                adjList[i-j]->indegree++;
            }
            else
            {
                break;
            }
        }
    }

    // now for each node with indegree 0, do DFS and calculate MAX path length
    for(int i = 0 ; i < arrSize ; i++)
    {
        if(adjList[i]->indegree == 0)
        {
            max = MAX(max, dfsMax(adjList, i, memo)); 
        }
    }


    for(int i = 0 ; i < arrSize ; i++)
    {
        free(adjList[i]->children);
        free(adjList[i]);
    }

    free(adjList);
    free(memo);
    return max;
}