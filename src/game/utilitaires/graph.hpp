#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <stack>
#include <queue>



#include <fstream>

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        // default ici permet de définit les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonction qu'en C++20, si vous n'avez pas accès à cette version je vous donne les implémentations des opérateurs plus bas
        bool operator==(WeightedGraphEdge const& other);
        bool operator!=(WeightedGraphEdge const& other);
    };

    struct WeightedGraph {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int id);

        void add_directed_edge(int from, int to, float weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other);
        bool operator!=(WeightedGraph const& other);

        void print_DFS(int const start);
        std::vector<int> list_DFS(int const start);
        void print_BFS(int const start);
        std::vector<int> list_BFS(int const start);
    
   

    };
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix);

} // namespace

std::vector<std::pair<int,int>> dijkstra_search(Graph::WeightedGraph & graph, int start);
std::vector<std::string> split_string(std::string const& str);
std::vector<std::vector<std::string>> splitItd(std::string path);

Graph::WeightedGraph from_itd_to_graph(std::string path);

void displayAdjencyList( Graph::WeightedGraph G );

int calculPoids(std::pair<int,int> pos1, std::pair<int,int> pos2);

std::unordered_map<int, std::pair<float, int>> Newdijkstra(Graph::WeightedGraph const &graph, int const &start, int const end);
