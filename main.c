#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doubly Linked-List Node Structure Representing a Window
typedef struct WindowNode{
    int windowID; // ID of the window
    struct WindowNode* next; // Pointer to next window
    struct WindowNode* previous; // Pointer to previous window
}WindowNode;

// Window Manager Structure (overall linked-list structure)
typedef struct WindowManager{
    WindowNode* head; // Pointer to head of list
    WindowNode* tail; // Pointer to tail of list
}WindowManager;

// Create a new window node
WindowNode* createNewWindow(int windowID){
    WindowNode* new = (WindowNode*)malloc(sizeof(WindowNode)); // Allocate memory for new node

    // Assign values for new nodes
    new->windowID = windowID;
    new->next = NULL;
    new->previous = NULL;
    return(new); // return new node
} 

// Opens a new window in the manager by creating a new node and adding it to the front (focus position)
// of the linked list
void openWindow(WindowManager* manager, int windowID){
    // Create a new node
    WindowNode* new = createNewWindow(windowID);
    new->next = manager->head; // Point new node's next to current head

    // Add the new node to the front of the linked list if existing, or head if list is empty
    if(manager->head){
        manager->head->previous = new; // Update current head's previous
    }
    manager->head = new; // New node becomes head
    if(!manager->tail){
        manager->tail = new; // If first node, node is also the tail
    }
    manager->tail = new; // Update tail
}

// Find window by looking for matching ID
WindowNode* findWindow(WindowManager *manager, int windowID){
    WindowNode* current = manager->head; // Current node being searched for
    
    // Search for matching id (matching node)
    while(current){
        if(current->windowID == windowID){
            return(current); // Return current node if found
        }
        current = current->next;
    }
    return(NULL); // Return NULL if not found
}

// Close a window in the manager by finding the node & deleting it
void closeWindow(WindowManager* manager, int windowID){
    WindowNode* current = findWindow(manager, windowID); // Find window in manager (node in list)
    if(!current) return; // Do nothing if window is not found

    // For found window, update list to remove node
    if(current->previous){
        current->previous->next = current->next; // Bypass current
    }
    else{
        manager->head = current->next; // Update head if first node
    }

    if(current->next){
        current->next->previous = current->previous; // Bypass current
    }
    else{
        manager->tail = current->previous; // Update tail if last node
    }

    free(current); // Free memory of closed window
}

// Switch focus to a specific window by moving to the front of the linked list
void switchFocus(WindowManager* manager, int windowID){
    // Find window in the list
    WindowNode* current = findWindow(manager, windowID);
    if(!current || current == manager->head) return; // If not found or already at front return

    // Move current window from original position
    if(current->previous){
        current->previous->next = current->next; // Bypass current
    }
    if(current->next){
        current->next->previous = current->previous; // Bypass current
    }

    // If current is tail, update tail
    if(current == manager->tail){
        manager->tail = current->previous;
    }

    // Insert current at the front
    current->next = manager->head;
    current->previous = NULL;
    if(manager->head){
        manager->head->previous = current; // Old head's previous pointer now points to current
    }
    manager->head = current;
}

// Get ID of current focused window
int getCurrentFocus(WindowManager* manager){
    if(!manager->head) return -1; // No open windows
    return manager->head->windowID; // Return window in focus (first window)
}

void freeManager(WindowManager* manager){
    WindowNode* current = manager->head;
    
    // Free memory node by node
    while(current){
        WindowNode* next = current->next;
        free(current);
        current = next;
    }

    // Set head and tail to NULL
    manager->head = NULL;
    manager->tail = NULL;
}

// Main chain of command (main function)
int main(void){
    // LOCAL VARIABLES
    WindowManager manager;
    char command[10]; // String command input
    int windowID; // Window ID input
    int currentFocus; // Window currently in focus

    // EXECUTABLE STATEMENTS
    // Initialize Window Manager to NULL
    manager.head = NULL;
    manager.tail = NULL;

    // Get input and call corresponding function
    while(scanf("%s %d", command, &windowID) != EOF){
        if(strcmp(command, "open") == 0){
            openWindow(&manager, windowID);
        }
        else if(strcmp(command, "close") == 0){
            closeWindow(&manager, windowID);
        }
        else if(strcmp(command, "switch") == 0){
            switchFocus(&manager, windowID);
        }

        // Output currently focused window or terminate if none
        currentFocus = getCurrentFocus(&manager);
        if(currentFocus != -1){
            printf("%d\n", currentFocus);
        }
        else{
            freeManager(&manager);
            return 0;
        }
    }

    freeManager(&manager); // Clean up memory
    return 0;
}
