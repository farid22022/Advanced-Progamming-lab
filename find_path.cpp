#include <iostream>
using namespace std;

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int addNode(Node* p, int nid, int count)
{
    int i = 0, ncount = count;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent(Node* p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

int added(int* list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}

void findpath(Node* p, int count, int start, int end, int* list, int* clist, int lcount)
{
    int index = 0, i = 0;

    //check if list contains the end node
    if (list[lcount - 1] == end)
    {
        int tcost = 0;
        cout << endl;
        for (i = 0; i < lcount; i++)
        {
            cout << " " << list[i] << " ";
            tcost += clist[i];
        }
        cout << " cost = " << tcost;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main()
{
    // Write C++ code here
    //cout << "Hello world" << endl;

    Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    while (true)
    {
        cout << "n1, n2, cost ? ";
        cin >> n1 >> n2 >> c;
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        nodecount = addNode(nodes, n1, nodecount);
        nodecount = addNode(nodes, n2, nodecount);

        addAdjacent(nodes, n1, n2, c, nodecount);
        addAdjacent(nodes, n2, n1, c, nodecount);
    }

    int start, end;
    cout << "start, end ? ";
    cin >> start >> end;
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    findpath(nodes, nodecount, start, end, list, clist, lcount);

    return 0;
}
