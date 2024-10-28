#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 9999

int numPlaces = 11;
char places[MAX][50] = {
    "Chennai Central Railway Station",
    "Marina Beach",
    "Kapaleeshwarar Temple",
    "Fort St. George",
    "Valluvar Kottam",
    "Guindy National Park",
    "Government Museum",
    "Elliot's Beach",
    "Arignar Anna Zoological Park",
    "Birla Planetarium",
    "Santhome Cathedral Basilica"
};

int adjMatrix[MAX][MAX];

void initializeGraph();
void addEdge(const char* place1, const char* place2, double distance);
int findPlaceIndex(const char* place);
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

        int start = findPlaceIndex(source);
        int end = findPlaceIndex(destination);

        if (start == -1 || end == -1) {
            printf("Invalid places entered!\n");
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
            adjMatrix[i][j] = INF;
        }
    }
}

void addEdge(const char* place1, const char* place2, double distance) {
    int index1 = findPlaceIndex(place1);
    int index2 = findPlaceIndex(place2);
    if (index1 == -1 || index2 == -1) {
        printf("Error: Invalid place name provided for the route.\n");
    } else {
        adjMatrix[index1][index2] = distance;
        adjMatrix[index2][index1] = distance; // Since it is an undirected graph
    }
}

int findPlaceIndex(const char* place) {
    for (int i = 0; i < numPlaces; i++) {
        if (strcmp(places[i], place) == 0) {
            return i;
        }
    }
    return -1;
}

void createGraph() {
    addEdge("Chennai Central Railway Station", "Marina Beach", 5.0);
    addEdge("Chennai Central Railway Station", "Fort St. George", 2.5);
    addEdge("Marina Beach", "Kapaleeshwarar Temple", 4.0);
    addEdge("Kapaleeshwarar Temple", "Valluvar Kottam", 6.0);
    addEdge("Valluvar Kottam", "Guindy National Park", 8.0);
    addEdge("Guindy National Park", "Arignar Anna Zoological Park", 15.0);
    addEdge("Government Museum", "Santhome Cathedral Basilica", 5.5);
    addEdge("Santhome Cathedral Basilica", "Elliot's Beach", 3.0);
    addEdge("Elliot's Beach", "Birla Planetarium", 7.0);
    addEdge("Birla Planetarium", "Guindy National Park", 4.5);
    addEdge("Fort St. George", "Government Museum", 3.0);
    addEdge("Arignar Anna Zoological Park", "Birla Planetarium", 10.0);
}

void displayLocations() {
    printf("---------------Welcome to Travel Planner of Bhubaneswar---------------\nThese are our famous locations : ");
    printf("\nList of available locations:\n");
    for (int i = 0; i < numPlaces; i++) {
        printf("%d. %s\n", i + 1, places[i]);
    }
}

void dijkstra(int start, int end) {
    int dist[MAX], visited[MAX], parent[MAX];
    for (int i = 0; i < numPlaces; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < numPlaces - 1; count++) {
        int min = INF, u;

        for (int i = 0; i < numPlaces; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < numPlaces; v++) {
            if (!visited[v] && adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
        printf("No path found from %s to %s.\n", places[start], places[end]);
    } else {
        printf("Shortest path from %s to %s is %.2f km.\n", places[start], places[end], (double)dist[end]);
        printf("Path: ");
        
        int path[MAX], pathIndex = 0;
        for (int v = end; v != -1; v = parent[v]) {
            path[pathIndex++] = v;
        }

        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("%s", places[path[i]]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}
