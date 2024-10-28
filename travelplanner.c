#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100
#define INF 9999

int numCities = 11;
char cities[MAX][50] = {
    "Chennai Central Railway Station", 
    "Marina Beach", 
    "Fort St. George", 
    "Kapaleeshwarar Temple", 
    "Vandalur Zoo", 
    "Guindy National Park", 
    "Government Museum Chennai", 
    "San Thome Basilica", 
    "Thousand Lights Mosque", 
    "Elliot's Beach", 
    "Dakshinachitra Museum"
};
int graph[MAX][MAX];

// Function declarations
void initializeGraph();
void addRoute(const char* city1, const char* city2, int distance);
int findCityIndex(const char* city);
void displayLocations();
void dijkstra(int start, int end);
void createGraph();

int main() {
    initializeGraph();
    createGraph();
    
    displayLocations();
    char prompt[3];
    printf("Do you want to get the shortest path between your source and destination? Type Y or y to proceed: ");
    scanf("%s", prompt);

    while (strcmp(prompt, "Y") == 0 || strcmp(prompt, "y") == 0) {
        char source[50], destination[50];
        printf("Enter source location: ");
        scanf(" %[^\n]%*c", source); // Read input with spaces
        printf("Enter destination location: ");
        scanf(" %[^\n]%*c", destination);

        int start = findCityIndex(source);
        int end = findCityIndex(destination);

        if (start == -1 || end == -1) {
            printf("Invalid cities entered!\n");
        } else {
            dijkstra(start, end);
        }

        printf("Do you want to get the shortest path between your source and destination? (Y/N): ");
        scanf("%s", prompt);
    }

    printf("\nThanks for using our application.\n");
    return 0;
}

void initializeGraph() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = INF;
        }
    }
}

void addRoute(const char* city1, const char* city2, int distance) {
    int index1 = findCityIndex(city1);
    int index2 = findCityIndex(city2);
    if (index1 == -1 || index2 == -1) {
        printf("Error: Invalid city name provided for the route.\n");
    } else {
        graph[index1][index2] = distance;
        graph[index2][index1] = distance; // Since it is an undirected graph
    }
}

int findCityIndex(const char* city) {
    for (int i = 0; i < numCities; i++) {
        if (strcmp(cities[i], city) == 0) {
            return i;
        }
    }
    return -1;
}

void createGraph() {
    addRoute("Chennai Central Railway Station", "Marina Beach", 5);
    addRoute("Chennai Central Railway Station", "Fort St. George", 2);
    addRoute("Marina Beach", "Kapaleeshwarar Temple", 4);
    addRoute("Kapaleeshwarar Temple", "San Thome Basilica", 3);
    addRoute("Kapaleeshwarar Temple", "Thousand Lights Mosque", 5);
    addRoute("Vandalur Zoo", "Guindy National Park", 15);
    addRoute("Vandalur Zoo", "Kapaleeshwarar Temple", 22);
    addRoute("Guindy National Park", "Government Museum Chennai", 9);
    addRoute("Guindy National Park", "Marina Beach", 12);
    addRoute("Government Museum Chennai", "Thousand Lights Mosque", 3);
    addRoute("San Thome Basilica", "Marina Beach", 2);
    addRoute("San Thome Basilica", "Elliot's Beach", 7);
    addRoute("Elliot's Beach", "Dakshinachitra Museum", 20);
    addRoute("Dakshinachitra Museum", "Vandalur Zoo", 25);
    addRoute("Dakshinachitra Museum", "Guindy National Park", 23);
    addRoute("Marina Beach", "Fort St. George", 5);
    addRoute("Fort St. George", "Chennai Central Railway Station", 2);
    addRoute("Government Museum Chennai", "Chennai Central Railway Station", 3);
}

void displayLocations() {
    printf("\nList of available locations:\n");
    for (int i = 0; i < numCities; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

void dijkstra(int start, int end) {
    int dist[MAX], visited[MAX], parent[MAX];
    for (int i = 0; i < numCities; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < numCities - 1; count++) {
        int min = INF, u;

        // Find the city with the minimum distance that hasn't been visited
        for (int i = 0; i < numCities; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < numCities; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
        printf("No path found from %s to %s.\n", cities[start], cities[end]);
    } else {
        printf("Shortest path from %s to %s is %d km.\n", cities[start], cities[end], dist[end]);
        printf("Path: ");
        
        int path[MAX], pathIndex = 0;
        for (int v = end; v != -1; v = parent[v]) {
            path[pathIndex++] = v;
        }

        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("%s", cities[path[i]]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}
