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

// Opens a new window in the manager by creating a new node and adding it to the linked list
void openWindow(WindowManager* manager, int windowID){
    // Create a new node
    WindowNode* new = createNewWindow(windowID);

    // Add the new node to the end of the linked list if existing, or head if list is empty
    if(manager->tail){
        manager->tail->next = new; // Link new
        new->previous = manager->tail; // Set previous pointer
    }
    else{
        manager->head = new;
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

// Main chain of command (main function)
int main(void){
    // LOCAL VARIABLES
    WindowManager manager;

    // EXECUTABLE STATEMENTS
    // Initialize Window Manager to NULL
    manager.head = NULL;
    manager.tail = NULL;

    return 0;
}