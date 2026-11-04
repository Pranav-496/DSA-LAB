#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Item
{
    int profit;
    int weight;
};

struct Node
{
    int level;
    long long weight;
    long long profit;
    long double bound;
};

struct CompareBound
{
    bool operator()(const Node &first, const Node &second) const
    {
        return first.bound < second.bound;
    }
};

long double calculateBound(const Node &node, int capacity, const vector<Item> &items)
{
    if (node.weight > capacity)
        return 0;

    long long totalWeight = node.weight;
    long double bound = node.profit;
    int nextItem = node.level;

    while (nextItem < static_cast<int>(items.size()) &&
           totalWeight + items[nextItem].weight <= capacity)
    {
        totalWeight += items[nextItem].weight;
        bound += items[nextItem].profit;
        nextItem++;
    }

    if (nextItem < static_cast<int>(items.size()))
    {
        bound += static_cast<long double>(capacity - totalWeight) *
                 items[nextItem].profit / items[nextItem].weight;
    }

    return bound;
}

int main()
{
    int n, capacity;

    cout << "Enter number of items: ";
    if (!(cin >> n) || n < 0)
    {
        cerr << "Number of items must be a non-negative integer.\n";
        return 1;
    }

    cout << "Enter knapsack capacity: ";
    if (!(cin >> capacity) || capacity < 0)
    {
        cerr << "Capacity must be a non-negative integer.\n";
        return 1;
    }

    vector<Item> items(n);
    cout << "Enter profit and weight of each item:\n";
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> items[i].profit >> items[i].weight) ||
            items[i].profit < 0 || items[i].weight < 0)
        {
            cerr << "Profits and weights must be non-negative integers.\n";
            return 1;
        }
    }

    sort(items.begin(), items.end(), [](const Item &first, const Item &second)
         {
             if (first.weight == 0 || second.weight == 0)
                 return first.weight == 0 && second.weight != 0;
             return static_cast<long double>(first.profit) / first.weight >
                    static_cast<long double>(second.profit) / second.weight;
         });

    priority_queue<Node, vector<Node>, CompareBound> nodes;
    Node root{0, 0, 0, 0};
    root.bound = calculateBound(root, capacity, items);
    nodes.push(root);

    long long maximumProfit = 0;

    while (!nodes.empty())
    {
        Node current = nodes.top();
        nodes.pop();

        if (current.bound <= maximumProfit || current.level == n)
            continue;

        const Item &item = items[current.level];
        Node include{
            current.level + 1,
            current.weight + item.weight,
            current.profit + item.profit,
            0};

        if (include.weight <= capacity)
        {
            maximumProfit = max(maximumProfit, include.profit);
            include.bound = calculateBound(include, capacity, items);
            if (include.bound > maximumProfit)
                nodes.push(include);
        }

        Node exclude{
            current.level + 1,
            current.weight,
            current.profit,
            0};
        exclude.bound = calculateBound(exclude, capacity, items);
        if (exclude.bound > maximumProfit)
            nodes.push(exclude);
    }

    cout << "Maximum Profit = " << maximumProfit << endl;
    return 0;
}
