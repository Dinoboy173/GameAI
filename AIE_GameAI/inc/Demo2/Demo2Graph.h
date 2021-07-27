#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

template<class TNodeData, class TEdgeData>
class Demo2Graph
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
    Demo2Graph()
    {
    }
    // ===========================================================================
    // Destructor
    // ===========================================================================
    virtual ~Demo2Graph()
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

    std::list<Node*> FindPath(Node* startNode, std::function<bool(Node* n)> processNode)
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
                // check that the conection node
                // does not exist in the visited or stack
                PFNode* childPFNode = GetNodesInList(edge.to);
                if (childPFNode == nullptr)
                {
                    stack.push_back(new PFNode(edge.to, pfNode));
                }
            }
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