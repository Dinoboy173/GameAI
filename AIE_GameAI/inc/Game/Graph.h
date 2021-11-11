#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

class IGraph
{
public:
    enum class SearchType
    {
        BFS,
        DIJKSTRA,
    };
};

template<class TNodeData, class TEdgeData>
class Graph : public IGraph
{
public:
    struct Node;
    struct Edge;

    struct Node
    {
        TNodeData data;
        std::vector<Edge> connections;
    };
    struct PFNode
    {
        Node* node;
        PFNode* parent = nullptr;

        int depth = 0;
        float gScore = 0;
        float hScore = 0;

        PFNode() {}
        PFNode(Node* n, PFNode* p) : node(n), parent(p) {}
    };
    struct Edge
    {
        Node* to;
        TEdgeData data;
    };

public:
    // ===========================================================================
    // Constructor
    // ===========================================================================
    Graph()
    {
    }
    // ===========================================================================
    // Destructor
    // ===========================================================================
    virtual ~Graph()
    {
        for (auto node : m_nodes)
        {
            delete node;
        }
        m_nodes.clear();
    }
    // ===========================================================================
    // Add Node
    // ===========================================================================
    Node* AddNode(const TNodeData& data)
    {
        Node* node = new Node();
        node->data = data;
        m_nodes.push_back(node);
        return node;
    }

    // ===========================================================================
    // AddEdge
    // ===========================================================================
    void AddEdge(Node* nodeA, Node* nodeB, const TEdgeData& data)
    {
        nodeA->connections.push_back({ nodeB, data });
    }
    // ===========================================================================
    // GetNodes
    // ===========================================================================
    const std::vector<Node*>& GetNodes()
    {
        return m_nodes;
    }

    // ===========================================================================
    // 
    // ===========================================================================
    void ForEachBFSPrint(Node* startNode, std::function<bool(Node*)> processNode)
    {
        // push sthe start node on the stack
        std::list<Node*> stack;
        stack.push_back(startNode);

        // list of visited nodes
        std::list<Node*> visited;

        while (stack.empty() == false)
        {
            // Get the node from the stack and remove it
            auto node = stack.front();
            stack.pop_front();
            
            // add the node to the visited list
            visited.push_back(node);

            // print the node
            //std::cout << node->data << std::endl;
            if (processNode(node) == false)
                return;

            // add children to the stack
            for (Edge& edge : node->connections)
            {
                // check if the node exists in the visited list
                // or if its on the stack
                if (std::find(visited.begin(), visited.end(), edge->to) == visited.end() &&
                    std::find(stack.begin(), stack.end(), edge->to) == stack.end())
                {
                    stack.push_back(edge->to);
                }
            }
        }
    }

    std::list<Node*> FindPath(SearchType type, Node* startNode, std::function<bool(Node* n)> processNode)
    {
        std::list<PFNode*> stack;       // open list
        std::list<PFNode*> visited;     // close list
        std::list<Node*> path;
        
        auto GetNodesInList = [&](Node* nodeToFind) -> PFNode*
        {
            for (auto& n : stack)
                if (n->node == nodeToFind)
                    return n;
            
            for (auto& n : visited)
                if (n->node == nodeToFind)
                    return n;
            
            return nullptr;
        };
        
        stack.push_back(new PFNode(startNode, nullptr));
        
        while (stack.empty() == false)
        {
            auto pfNode = stack.front();
            stack.pop_front();
             
            // add to visited list - we have processed it!
            visited.push_back(pfNode);
            
            // print the node
            // std::cout << node->data << std::endl;
            if (processNode(pfNode->node) == true)
            {
                // TODO: Calculate path
                PFNode* current = pfNode;
                while (current != nullptr)
                {
                    path.push_front(current->node);
                    current = current->parent;
                }
                
                break;
            }
            
            for (auto& edge : pfNode->node->connections)
            {
                auto childNode = edge.to;
                float gScore = (pfNode->parent ? pfNode->parent->gScore : 0) + edge.data;
                float hScore = 0; // we dont know the target node
                int depth = pfNode->depth + 1;

                // check that the conection node
                // does not exist in the visited or stack
                PFNode* childPFNode = GetNodesInList(edge.to);
                if (childPFNode == nullptr)
                {
                    childPFNode = new PFNode(edge.to, pfNode);
                    childPFNode->gScore = gScore;
                    childPFNode->hScore = hScore;
                    childPFNode->depth = depth;
                    stack.push_back(childPFNode);
                }
                else if (childPFNode->gScore > gScore)
                {
                    // child node on stack already
                    // but we can get to it easier
                    childNode->parent = pfNode;
                    childPFNode->gScore = gScore;
                    childPFNode->hScore = hScore;
                    childPFNode->depth = depth;
                }
            }

            // sort stack by gScore

            stack.sort( [&](PFNode* a, PFNode* b) -> bool
                {
                    switch (type)
                    {
                    case SearchType::DIJKSTRA: return a->gScore < b->gScore;
                    case SearchType::BFS: return a->depth < b->depth;
                    default: return a->gScore < b->gScore; // default dijksra
                    }
            });
        }
        
        // cleanup our PFNode
        for (auto& n : stack)
            delete n;
        
        for (auto& n : visited)
            delete n;
        
        return path;
    }

protected:
    std::vector<Node*> m_nodes;
private:
};