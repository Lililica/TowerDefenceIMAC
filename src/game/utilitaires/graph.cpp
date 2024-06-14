#include "graph.hpp"

#define INFINITY ((float)(1e+300 * 1e+300))

#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <stack>
#include <queue>

void Graph::WeightedGraph::add_vertex(int const id){
    auto it = adjacency_list.find(id);
    if(it == adjacency_list.end()){
        adjacency_list.insert(std::pair<const int, std::vector<Graph::WeightedGraphEdge>>{id, std::vector<Graph::WeightedGraphEdge>{}});
    }
}

void Graph::WeightedGraph::add_directed_edge(int const from, int const to, float const weight){
    
    if(adjacency_list.find(from) != adjacency_list.end()){
        if(adjacency_list.find(to) != adjacency_list.end()){
            adjacency_list[from].push_back(Graph::WeightedGraphEdge{to, weight});
        }else{
            add_vertex(to);
            add_directed_edge(from, to, weight);
        }
    }else{
        add_vertex(from);
        add_directed_edge(from, to, weight);
    }
}

void Graph::WeightedGraph::add_undirected_edge(int const from, int const to, float const weight){
    add_directed_edge(from,to,weight);
    add_directed_edge(to,from,weight);
}

Graph::WeightedGraph Graph::build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix){
    Graph::WeightedGraph result;
    for(int x{0}; x < adjacency_matrix.size(); x++){
        result.add_vertex(x);
        for(int y{0}; y < adjacency_matrix[x].size(); y++){
            if(adjacency_matrix[x][y] != 0){
                result.add_directed_edge(x, y, adjacency_matrix[x][y]);
            }
        }
    }
    return result;
}



std::vector<int> Graph::WeightedGraph::list_DFS(int const start){
    std::vector<int> order_visit {};
    std::stack<int> stck {};
    stck.push(start);
    while(stck != std::stack<int>{}){
        order_visit.push_back(stck.top());
        stck.pop();
        for(Graph::WeightedGraphEdge edge : adjacency_list[order_visit[order_visit.size()-1]]){
            stck.push(edge.to);
        } 
    }
    return order_visit;
}

void Graph::WeightedGraph::print_DFS(int const start){
    std::vector<int> order_visit = list_DFS(start);
    std::cout << "[";
    for(int i{0}; i < order_visit.size(); i++){
        std::cout << order_visit[i];
        if(i != order_visit.size()-1){
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

std::vector<int> Graph::WeightedGraph::list_BFS(int const start){
    std::vector<int> order_visit {};
    std::queue<int> queue {};
    queue.push(start);
    while(queue != std::queue<int>{}){
        order_visit.push_back(queue.front());
        queue.pop();
        for(Graph::WeightedGraphEdge edge : adjacency_list[order_visit[order_visit.size()-1]]){
            queue.push(edge.to);
        } 
    }
    return order_visit;
}

void Graph::WeightedGraph::print_BFS(int const start){
    std::vector<int> order_visit = list_BFS(start);
    std::cout << "[";
    for(int i{0}; i < order_visit.size(); i++){
        std::cout << order_visit[i];
        if(i != order_visit.size()-1){
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

std::vector<int> dijkstra_search(Graph::WeightedGraph & graph){
    std::vector<int> weightList(graph.adjacency_list.size(),1000000);
    weightList[0] = 0;

    auto itFirstElement = graph.adjacency_list.begin();

    auto compare_function = [weightList](const int l, const int r){return weightList[l] > weightList[r];};
    std::priority_queue<int, std::vector<int>, decltype(compare_function)>  nodeToVisit{compare_function} ;

    std::vector<int> nodeAlreadyVisited {};

    nodeToVisit.push(itFirstElement->first);

    while(!nodeToVisit.empty()){
        int actualNode = nodeToVisit.top();
        nodeToVisit.pop();
        nodeAlreadyVisited.push_back(actualNode);

        for(Graph::WeightedGraphEdge element : graph.adjacency_list[actualNode]){
            if(std::find(nodeAlreadyVisited.begin(), nodeAlreadyVisited.end(), element.to) == nodeAlreadyVisited.end()){
                nodeToVisit.push(element.to);
                if(weightList[element.to] > weightList[actualNode] + element.weight){
                    weightList[element.to] = weightList[actualNode] + element.weight;
                }
            }
            
        }
    }

    return weightList;
}