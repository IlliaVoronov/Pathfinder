#include "pathfinder.h"

#define MAX 500
#define TEMPORARY 1
#define PERMANENT 2
#define NIL -1
#define INFINITY 99999
#define MAX_STR_LEN 50

struct Vertex
{
    char name[50];
    int status;
    int predecessor;
    int pathLength;
};

struct Vertex vertexList[MAX];

double sumOfBridges = 0;
int adj[MAX][MAX]; /* Adjacency Matrix */
int n = 0;         /* Number of vertices in the graph */
int numOfVertexes;
int e = 0; /* Number of edges in the graph */
int delimCount;
int vertexCount = 0;
void deleteVertex(char s[]);
void deleteEdge(char s1[], char s2[]);
void deleteAllVertices(void);
void deleteAllEdges(void);

void insertEdge(char s1[], char s2[], int wt, int line);
void insertVertex(char s[]);
int getIndex(char s[]);
char *read_file(const char *filename);
int countRows(const char *line);

char *mx_strtok(char *str, const char *delim, int row);
char *mx_strchr(const char *s, int c, int row);
int mx_isdigit(int c);
int mx_atoi(const char *str);
void print_error(const char *error_message);

void findPaths(char source[], int compareArr[], int *count);
void findPath(int s, int v);
void dijkstra(int s, int isMultPaths[]);
void altDijkstra(int s);
int tempVertexMinPL(void);

char *read_first_line(const char *filename);
int custom_atoi(const char *str);
int isValidNumber(const char *str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_error("usage: ./pathfinder [filename]");
    }

    char *file_content = read_file(argv[1]);
    char *origin = file_content;
    int rowCount = countRows(file_content);
    int zero = 0;
    char *token = mx_strtok((char *)file_content, "\n", zero);

    char *firstLine = read_first_line(argv[1]);
    numOfVertexes = custom_atoi(firstLine);



    for (int i = 0; i <= rowCount || token != NULL; i++)
    {
        char *island1 = mx_strtok(NULL, "-, \n", i);
        char *island2 = mx_strtok(NULL, "-, \n", i);
        char *length_str = mx_strtok(NULL, "-, \n", i);

        if (island1 == NULL || island2 == NULL || length_str == NULL)
        {
            break;
        }
        double length_of_bridge = mx_atoi(length_str);

        insertVertex(island1);
        insertVertex(island2);
        insertEdge(island1, island2, length_of_bridge, i);
        sumOfBridges += length_of_bridge;

        if (sumOfBridges >= INT_MAX || sumOfBridges < 0)
        {
            mx_printstr("error: sum of bridges lengths is too big\n");
            exit(EXIT_FAILURE);
        }
    }

    token = mx_strtok(origin, "\n", zero);
    

    if (token == NULL || !isValidNumber(token))
    {
        mx_printstr("error: line 1 is not valid\n");
        free(origin);
        exit(EXIT_FAILURE);
    }
    int compareArr[100000];

    int count = 0;

    for (int i = 0; i < mx_atoi(token); i++)
    {
        findPaths(vertexList[i].name, compareArr, &count);
    }

    deleteAllEdges();
    deleteAllVertices();
    free(file_content);

    return 0;
}

void findPaths(char source[], int compareArr[], int *count)
{
    int s, v;
    s = getIndex(source);
    int isMultPaths[n];
    for (int i = 0; i < n; i++)
    {
        isMultPaths[i] = 0;
    }

    if (s == -1)
    {
        return;
    }

    for (v = 0; v < n; v++)
    {
        dijkstra(s, isMultPaths);

        int skip = 0;

        for (int i = 1; i <= *count; i += 2)
        {
            int j = i + 1;

            if ((compareArr[i] == s) && (compareArr[j] == v))
            {
                skip = 1;
                break;
            }
        }

        if (v != s)
        {
            if (skip != 1)
            {
                mx_printstr("========================================");
                mx_printstr("\n");
                mx_printstr("Path: ");
                mx_printstr(source);
                mx_printstr(" -> ");
                mx_printstr(vertexList[v].name);
                mx_printstr("\n");

                if (vertexList[v].pathLength == INFINITY)
                    mx_printstr("There is no path");
                else
                {
                    findPath(s, v);
                    if (isMultPaths[v] != 0)
                    {
                        altDijkstra(s);
                        mx_printstr("========================================");
                        mx_printstr("\n");
                        mx_printstr("Path: ");
                        mx_printstr(source);
                        mx_printstr(" -> ");
                        mx_printstr(vertexList[v].name);
                        mx_printstr("\n");
                        findPath(s, v);
                    }
                }
                compareArr[*count] = s;
                (*count)++;
                compareArr[*count] = v;
                (*count)++;
            }
        }
    }
}

void findPath(int s, int v)
{
    int i, u;
    int path[MAX];
    int sd = 0;
    int count = 0;

    while (v != s)
    {
        count++;
        path[count] = v;
        u = vertexList[v].predecessor;
        sd += adj[u][v];
        v = u;
    }

    count++;
    path[count] = s;

    mx_printstr("Route: ");
    for (i = count; i > 1; i--)
    {
        mx_printstr(vertexList[path[i]].name);
        mx_printstr(" -> ");
    }
    mx_printstr(vertexList[path[1]].name);
    mx_printstr("\n");

    mx_printstr("Distance: ");
    if (count != 2)
    {
        for (i = count; i > 1; i--)
        {
            int bridgeLength = adj[path[i - 1]][path[i]];
            mx_printstr(mx_itoa(bridgeLength));
            if (i > 2)
            {
                mx_printstr(" + ");
            }
        }

        mx_printstr(" = ");
    }
    mx_printstr(mx_itoa(sd));
    mx_printstr("\n");
    mx_printstr("========================================");
    mx_printstr("\n");
}

void dijkstra(int s, int isMultPaths[])
{
    int v, c;
    int simP = 0;

    for (v = 0; v < n; v++)
    {
        vertexList[v].status = TEMPORARY;
        vertexList[v].pathLength = INFINITY;
        vertexList[v].predecessor = NIL;
    }

    vertexList[s].pathLength = 0;

    while (1)
    {
        c = tempVertexMinPL();

        if (c == NIL)
            return;

        vertexList[c].status = PERMANENT;

        for (v = 0; v < n; v++)
        {
            if (adj[c][v] != 0 && vertexList[v].status == TEMPORARY)
            {

                if (vertexList[c].pathLength + adj[c][v] <= vertexList[v].pathLength)
                {
                    if (vertexList[c].pathLength + adj[c][v] == vertexList[v].pathLength)
                    {
                        simP++;
                    }

                    vertexList[v].predecessor = c;
                    vertexList[v].pathLength = vertexList[c].pathLength + adj[c][v];
                    if (simP != 0)
                    {
                        isMultPaths[v] = simP;
                    }
                }
            }
        }
    }
}

void altDijkstra(int s)
{
    int v, c;

    for (v = 0; v < n; v++)
    {
        vertexList[v].status = TEMPORARY;
        vertexList[v].pathLength = INFINITY;
        vertexList[v].predecessor = NIL;
    }

    vertexList[s].pathLength = 0;

    while (1)
    {
        c = tempVertexMinPL();

        if (c == NIL)
            return;

        vertexList[c].status = PERMANENT;

        for (v = 0; v < n; v++)
        {
            if (adj[c][v] != 0 && vertexList[v].status == TEMPORARY)
            {

                if (vertexList[c].pathLength + adj[c][v] < vertexList[v].pathLength)
                {
                    vertexList[v].predecessor = c;
                    vertexList[v].pathLength = vertexList[c].pathLength + adj[c][v];
                }
            }
        }
    }
}

int tempVertexMinPL(void)
{
    int min = INFINITY;
    int v, x = NIL;

    for (v = 0; v < n; v++)
    {
        if (vertexList[v].status == TEMPORARY && vertexList[v].pathLength < min)
        {
            min = vertexList[v].pathLength;
            x = v;
        }
    }
    return x;
}

void insertVertex(char s[])
{
    // Check if the vertex already exists
    for (int i = 0; i < n; i++)
    {

        if (mx_strcmp(vertexList[i].name, s) == 0)
        {
            
            return;
        }
    }

    // Check if the number of vertices exceeds the maximum limit
    if (n >= MAX)
    {
        return;
    }

    vertexCount++;
    // check if there to many vertexes
    // printf("vertexCount -> %i\n", vertexCount);
    // printf("b -> %i\n", n);
    
    if (vertexCount > numOfVertexes)
    {
        mx_printstr("error: invalid number of islands\n");
        exit(EXIT_FAILURE);
    }

    // Add the new vertex
    mx_strcpy(vertexList[n].name, s);
    vertexList[n].status = TEMPORARY;
    vertexList[n].predecessor = NIL;
    vertexList[n].pathLength = INFINITY;

    // Increment the number of vertices
    n++;
}

void insertEdge(char s1[], char s2[], int wt, int line)
{
    int v1 = -1, v2 = -1;

    // Find the indices of the vertices
    for (int i = 0; i < n; i++)
    {
        if (mx_strcmp(vertexList[i].name, s1) == 0)
            v1 = i;
        else if (mx_strcmp(vertexList[i].name, s2) == 0)
            v2 = i;

        // Break the loop if both vertices are found
        if (v1 != -1 && v2 != -1)
            break;
    }

    // Check if both vertices exist
    if (v1 == -1 || v2 == -1)
    {
        mx_printstr("error: line ");
        mx_printint(line + 2);
        mx_printstr(" is not valid\n");
        exit(EXIT_FAILURE);
        return;
    }

    // Check if the edge already exists
    if (adj[v1][v2] != 0 || adj[v2][v1] != 0)
    {
        mx_printstr("error: duplicate bridges\n");
        exit(EXIT_FAILURE);
        return;
    }

    // Insert the edge
    adj[v1][v2] = wt;
    adj[v2][v1] = wt;

    // Increment the number of edges
    e++;
}

int getIndex(char s[])
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (mx_strcmp(vertexList[i].name, s) == 0)
        {
            return i;
        }
    }
    return -1; // If the vertex is not found
}

char *read_file(const char *filename)
{
    // Open the file
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        mx_printstr("error: file ");
        mx_printstr(filename);
        mx_printstr(" does not exist\n");
        exit(EXIT_FAILURE);
    }   

    char *content = mx_file_to_str(filename);

    if (content == NULL) {
        mx_printstr("error: file ");
        mx_printstr(filename);
        mx_printstr(" is empty\n");
        exit(EXIT_FAILURE);
    }
    

    close(fd);

    return content;
}

char *mx_strtok(char *str, const char *delim, int row)
{
    static char *lastToken = NULL; // keeps track of the last token

    // If str is not NULL, set lastToken to str
    if (str != NULL)
    {
        lastToken = str;
    }
    else if (lastToken == NULL)
    {
        // If both str and lastToken are NULL, return NULL
        return NULL;
    }

    // Find the beginning of the token (skip leading delimiters)
    while (*lastToken != '\0' && mx_strchr(delim, *lastToken, row) != NULL)
    {
        ++lastToken;
    }

    // If the end of the string is reached, return NULL
    if (*lastToken == '\0')
    {
        lastToken = NULL;
        return NULL;
    }

    // Save the start of the token
    char *tokenStart = lastToken;

    // Find the end of the token
    while (*lastToken != '\0' && mx_strchr(delim, *lastToken, row) == NULL)
    {
        ++lastToken;
    }

    // If this is not the end of the string, set lastToken to the next character
    if (*lastToken != '\0')
    {
        *lastToken++ = '\0';
    }
    else
    {
        // If this is the end of the string, set lastToken to NULL
        lastToken = NULL;
    }

    // Return the token
    return tokenStart;
}

char *mx_strchr(const char *s, int c, int row)
{
    while (*s != '\0' && *s != c)
    {
        s++;
    }

    if (*s == c)
    {
        if (delimCount == c) {
            mx_printstr("error: line ");
            mx_printint(row + 2);
            mx_printstr(" is not valid\n");
            exit(EXIT_FAILURE);
        }
        delimCount = c;

        return (char *)s;
    }
    else
    {
        return NULL;
    }
}

int mx_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int mx_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    // Skip leading whitespaces
    while (mx_isspace(*str))
        str++;

    // Handle optional sign
    if (*str == '-' || *str == '+')
    {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }

    // Process digits
    while (mx_isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}

void print_error(const char *error_message)
{
    mx_printstr(error_message);
    mx_printstr("\n");
    exit(EXIT_FAILURE);
}

void deleteVertex(char s[])
{
    int v = getIndex(s);

    if (v == -1)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        adj[v][i] = 0;
        adj[i][v] = 0;
    }

    for (int i = v; i < n - 1; i++)
    {
        vertexList[i] = vertexList[i + 1];
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = adj[i + 1][j];
            adj[j][i] = adj[j][i + 1];
        }
    }

    // Update the number of vertices
    n--;
}

void deleteEdge(char s1[], char s2[])
{
    int v1 = getIndex(s1);
    int v2 = getIndex(s2);

    if (v1 == -1 || v2 == -1 || adj[v1][v2] == 0)
    {

        return;
    }

    // Remove the edge
    adj[v1][v2] = 0;
    adj[v2][v1] = 0;
}

void deleteAllVertices(void)
{
    while (n > 0)
    {
        deleteVertex(vertexList[0].name);
    }
}

void deleteAllEdges(void)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] != 0)
            {
                deleteEdge(vertexList[i].name, vertexList[j].name);
            }
        }
    }
}

int countRows(const char *line)
{
    int count = 0;

    // Iterate through each character in the line
    for (int i = 0; line[i] != '\0'; ++i)
    {
        // Check for newline character
        if (line[i] == '\n')
        {
            ++count;
        }
    }

    // If the last line doesn't end with a newline, increment count
    if (line[0] != '\0' && line[mx_strlen(line) - 1] != '\n')
    {
        ++count;
    }

    return count;
}

int isValidNumber(const char *str)
{
    while (*str)
    {
        if (!mx_isdigit(*str))
        {
            return 0; // Not a digit
        }
        str++;
    }
    return 1; // All characters are digits
}

int custom_atoi(const char *str) {
    int result = 0;
    int sign = 1;

    // Handle optional sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Process digits
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}


char *read_first_line(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_error("Error opening file");
        return NULL;
    }

    // Read the first line into a buffer
    char buffer[1024];
    int bytesRead = read(fd, buffer, 1024 - 1);
    if (bytesRead == -1) {
        print_error("Error reading file");
        close(fd);
        return NULL;
    }

    // Null-terminate the buffer
    buffer[bytesRead] = '\0';

    // Close the file
    close(fd);

    // Return the first line as a dynamically allocated string
    char *firstLine = mx_strdup(buffer);
    return firstLine;
}



