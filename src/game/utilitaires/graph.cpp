#include "graph.hpp"

#define INFINITY ((float)(1e+300 * 1e+300))



void Graph::WeightedGraph::add_vertex(int  id){
    auto it = adjacency_list.find(id);
    if(it == adjacency_list.end()){
        adjacency_list.insert(std::pair<const int, std::vector<Graph::WeightedGraphEdge>>{id, std::vector<Graph::WeightedGraphEdge>{}});
    }
}

void Graph::WeightedGraph::add_directed_edge(int  from, int  to, float  weight){
    
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

std::vector<std::pair<int,int>> dijkstra_search(Graph::WeightedGraph & graph, int start){
    std::vector<std::pair<int,int>> weightList;

    weightList.push_back(std::pair<int,int>{0,0});

    for(int i{1}; i < graph.adjacency_list.size(); ++i){
        weightList.push_back(std::pair<int,int>{0,100000});
    }

    

    std::vector<Graph::WeightedGraphEdge> first = graph.adjacency_list[start];

    

    auto compare_function = [weightList](const int l, const int r){return weightList[l] > weightList[r];};
    std::priority_queue<int, std::vector<int>, decltype(compare_function)>  nodeToVisit{compare_function} ;

    std::vector<int> nodeAlreadyVisited {start};

    for(Graph::WeightedGraphEdge & wg : first){
        weightList[wg.to].first = start;
        weightList[wg.to].second = wg.weight;
        nodeToVisit.push(wg.to);
    }


    while(!nodeToVisit.empty()){
        int actualNode = nodeToVisit.top();
        nodeToVisit.pop();
        nodeAlreadyVisited.push_back(actualNode);

        for(Graph::WeightedGraphEdge & element : graph.adjacency_list[actualNode]){
            if((std::find(nodeAlreadyVisited.begin(), nodeAlreadyVisited.end(), element.to) == nodeAlreadyVisited.end())){
                nodeToVisit.push(element.to);
                if(weightList[element.to].second > weightList[actualNode].second + element.weight){
                    weightList[element.to].second = weightList[actualNode].second + element.weight;
                    weightList[element.to].first = actualNode;
                }
            }
            
        }
    }

    return weightList;
}

std::vector<std::string> split_string(std::string const& str){

    // Permet de savoir si un element est un espace
    auto const is_space = [](char letter){ return letter == ' '; };

    std::vector<std::string> tab {};
    auto it_begin {str.begin()};
    auto it_end {std::find_if(str.begin(),str.end(), is_space)};
    while(it_begin != str.end()){
        std::string mot {};
        std::copy(it_begin, it_end, std::back_inserter(mot));
        tab.push_back(mot);
        if(it_end == str.end()){
            break;
        }
        it_begin = it_end + 1;
        it_end = std::find_if(it_begin,str.end(), is_space);
    }
    return tab;
}

//permet de découper le fichier .itd en ligne puis chaque ligne en mot
std::vector<std::vector<std::string>> splitItd(std::string path){
    std::vector<std::vector<std::string>> splitItdWord {};

    std::ifstream fichierItd(path); //on ouvre le fichier

    if(fichierItd){  //si on peut acceder au fichier
        std::string line; // pour stocker les lignes lues

        while(getline(fichierItd, line)){ // tant qu'on est pas a la fin du fichier 
            std::vector<std::string> splitItdLine {split_string(line)};  
            splitItdWord.push_back(splitItdLine);      
        }

    }else{
        std::cout << "Impossible d'ouvirer le fichier .itd" << std::endl;
    }
    fichierItd.close(); // ferme le fichier
    return splitItdWord;
    
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


Graph::WeightedGraph from_itd_to_graph(std::string path){
    std::vector<std::vector<std::string>> wordByWord {splitItd(path)};

    Graph::WeightedGraph finalGraph;
    std::vector<std::pair<int,int>> listClean;

    for(std::vector<std::string> line : wordByWord){
        if(line[0] == "node"){
            // finalGraph.add_vertex(std::stoi(line[1]));
            listClean.push_back(std::pair<int,int>{std::stoi(line[2]),std::stoi(line[3])});
        }
    }
    for(int y{0}; y < wordByWord.size()-1; ++y){
        std::vector<std::string> line {wordByWord[y]};
        if(line[0] == "node"){
            int from {std::stoi(line[1])};
            std::pair<int, int> pos {std::stoi(line[2]), std::stoi(line[3])};
            if(line.size() > 3){
                for(int i{4}; i < line.size(); ++i){
                    int to {std::stoi(line[i])};
                    std::pair<int,int> posTo {listClean[to-1]};
                    finalGraph.add_directed_edge(from, to, calculPoids(pos, listClean[to]));
                }
            }
        }
    }

    return finalGraph;
}

int calculPoids(std::pair<int,int> pos1, std::pair<int,int> pos2){
    if(pos1.first == pos2.first){
        // std::cout << pos1.second <<" et " << pos2.second << std::endl;
        return abs(pos1.second - pos2.second);
    }else{
        // std::cout << pos1.first <<" et " << pos2.first << std::endl;
        return abs(pos1.first - pos2.first);
    }
}

void displayAdjencyList( Graph::WeightedGraph G ){
    std::cout << "{" << std::endl;
    for(int i{0}; i < G.adjacency_list.size(); i++){
        std::cout <<"{" << i << ", {" ;
        for(Graph::WeightedGraphEdge edge : G.adjacency_list[i]){
            std::cout << "{" << edge.to << ", " << edge.weight << "}";
        }
        std::cout << "}}," << std::endl;
    }
    std::cout << "}" << std::endl;
}

