    struct Box* tempPtr = *boxPtr; // Store the pointer in a temporary variable
        *boxPtr = NULL; // Set the original pointer to NULL
        free(tempPtr); // Free the memory using the temporary pointer
        numBoxes = 0;
        return;
    }