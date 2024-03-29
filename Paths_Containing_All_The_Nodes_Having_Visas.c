//*******************************************************************
//** Title : Paths_Containing_All_The_Nodes_Having_Visas
//** Author : Nayon Mondol, Undergraduate student, Khulna University
//** N.B.: This code works only for those trees which don't have any
//** node having more than 10 adjacent nodes.
//*******************************************************************

#include <stdio.h>
#include <stdbool.h>
int visas[50] = {0}, size = 0;

struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int addNode (struct Node * p, int nid, int count) {
    int i =0, ncount = count;
    for (i=0;i<count;i++) {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count) {
    int i =0;
    for (i=0;i<count;i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;
           
            break;
        }
    }
}

int added (int * list, int lcount, int nid) {
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount) {
    int index = 0;
   
    if (list[lcount-1] == end) {
    // This condition being satisfied means we've found a potential path.
        bool flag = true;
        for (int i = 1; i < lcount; i++) {
            bool flag2 = true;
            for (int j = 0; j < size; j++) {
                if (list[i] == visas[j]) {
                    flag2 = false;
                    break;
                }
            }
            if (flag2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            int tcost = 0;
            printf ("\n");
            for (int i = 0; i < lcount; i++)
            {
                printf (" %d ", list[i]);
                tcost += clist[i];
            }
            printf (" cost = %d", tcost);
        }
        
        return;
    }
   
    for (int i = 0; i < count; i++) {
        if (p[i].nodeid == start) { index = i; break; }
    }
   
    for (int i = 0; i < p[index].adjcount; i++) {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
           
            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}


int main() {
    
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;
   
    while (1) {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);
       
        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }
   
    int start, end, n;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    printf("Enter the visas that you have(Enter -9 whenever complete) : ");
    while (1) {
        scanf("%d", &n);
        if (n == -9)
            break;
        visas[size++] = n;
    }
    
    int list[50], clist[50], lcount = 1;
    list[0] = start; clist[0] = 0;

    findpath (nodes, nodecount, start, end, list, clist, lcount);

    return 0;
}