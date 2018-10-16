/*
	+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	Compilation Instructions (G++):
	g++ main.cpp --std=c++17 -O3 -Wall -o out

	Execute via:
	./out

	===================================================

	Original code credit goes to:
	Mahmut Bulut on 11/11/13
	https://gist.github.com/vertexclique/7410577

	===================================================


	This code has been re-made for use for CSCI-3200 by AWildTeddyBear:
	https://github.com/AWildTeddyBear


	+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
*/

#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

class Graph {
	std::unordered_map<std::string, const std::unordered_map<std::string, float>> vertices;

	public:
		void add_vertex(std::string name, const std::unordered_map<std::string, float>& edges) {
			vertices.insert(std::unordered_map<std::string, const std::unordered_map<std::string, float>>::value_type(name, edges));
		}

		std::vector<std::string> shortest_path(std::string start, std::string finish) {
			std::unordered_map<std::string, float> distances;
			std::unordered_map<std::string, std::string> previous;

			std::vector<std::string> nodes;
			std::vector<std::string> path;

			auto comparator = [&](std::string left, std::string right) { return distances[left] > distances[right]; };

			for (auto& vertex : vertices) {
				distances[vertex.first] = vertex.first == start ? 0 : std::numeric_limits<int>::max();

				nodes.push_back(vertex.first);

				push_heap(begin(nodes), end(nodes), comparator);
			}

			while (!nodes.empty()) {
				pop_heap(begin(nodes), end(nodes), comparator);
				std::string smallest = nodes.back();
				nodes.pop_back();

				std::cout << "Open list: ";
				for (std::vector<std::string>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) std::cout << *i << ' ';
				std::cout << std::endl;

				if (smallest == finish) {
					while (previous.find(smallest) != end(previous)) {
						path.push_back(smallest);
						smallest = previous[smallest];

						std::cout << "Closed list: ";
						for (std::vector<std::string>::const_iterator i = path.begin(); i != path.end(); ++i) std::cout << *i << ' ';
						std::cout << std::endl;
					}

					break;
				}

				if (distances[smallest] == std::numeric_limits<float>::max()) break;

				for (auto& neighbor : vertices[smallest]) {
					float alt = distances[smallest] + neighbor.second;

					if (alt < distances[neighbor.first]) {
						distances[neighbor.first] = alt;
						previous[neighbor.first] = smallest;

						make_heap(begin(nodes), end(nodes), comparator);
					}
				}
			}

			return path;
		}
};

int main() {
	int seq = 0;
	std::string init_node = "AuburnUniversityMontgomery";
	std::string dest_node = "StripBar9";

	// Format is graphClass.add_vertex("String name of new location", {{"Name of other vertex location", int distance to newly created name}, etc})
	// graphClass.add_vertext("test", {}) means this node is entirely isolated and has no other connections to any other nodes
	// Distance is perceived in miles as a float
	Graph locationVectorGraph;

	// Inital location, this is our start. It's perceieved that the distance to itself is 0.00 (same with other created nodes)
	locationVectorGraph.add_vertex("AuburnUniversityMontgomery", {
		{"StripBar1", 1.00},
		{"StripBar2", 4.00},
		{"StripBar6", 2.00},
		{"StripBar8", 6.00}
	});

	// Add the rest of our nodes (9 minimum)
	locationVectorGraph.add_vertex("StripBar1", {
		{"StripBar4", 2.00}
	});
	locationVectorGraph.add_vertex("StripBar2", {
		{"StripBar6", 2.00},
		{"StripBar3", 4.00}
	});
	locationVectorGraph.add_vertex("StripBar3", {
		{"StripBar8", 1.00}
	});
	locationVectorGraph.add_vertex("StripBar4", {
		{"StripBar3", 3.00}
	});
	locationVectorGraph.add_vertex("StripBar5", {
		{"StripBar2", 1.00},
		{"StripBar6", 4.00}
	});
	locationVectorGraph.add_vertex("StripBar6", {
		{"StripBar1", 5.00}
	});
	locationVectorGraph.add_vertex("StripBar7", {
		{"StripBar2", 3.00}
	});
	locationVectorGraph.add_vertex("StripBar8", {
		{"StripBar3", 1.00},
		{"StripBar6", 4.00},
		{"StripBar1", 6.00},
		{"AuburnUniversityMontgomery", 6.00}
	});
	locationVectorGraph.add_vertex("StripBar9", {
		{"StripBar4", 5.00},
		{"StripBar6", 2.00}
	});


	std::cout << "As initial node: " << init_node << std::endl;
	std::cout << "As goal node: " << dest_node << std::endl;

	for (auto vertex : locationVectorGraph.shortest_path(init_node, dest_node))
		std::cout << "Solution path from goal sequence: " << seq++ << "\tNode: " << vertex << std::endl;

	std::cout << "Solution path from goal sequence: " << seq << "\tNode: " << init_node << std::endl;

	return 0;
}