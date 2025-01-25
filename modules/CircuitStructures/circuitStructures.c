#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "circuitStructures.h"
#include "../Util/util.h"
#include "./../../settings.h"


// ======================================================================================================================================================================================================================
// ======================== ADT Initializers =====================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief create a new circuit ADT. Does not assume ownership.
 * @return a pointer to the newly created circuit
 */
Circuit * createNewCircuit() {
    Circuit * out = malloc(sizeof(Circuit));
    return out;
}

/** 
 * @brief Create a blank, un-initialized, circuit component
 * @return A pointer to the new component
*/
CircuitComponent * _newComponent() {
    CircuitComponent * out = malloc(sizeof(CircuitComponent));

    out->capacitance = -1;
    out->inductance = -1;
    out->resistance = -1;
    
    out->voltageAcross = -1;
    out->currentThrough = -1;

    out->isClosed = true;

    return out;
}

/** 
 * @brief Create a blank, un-initialized, circuit Node
 * @return A pointer to the new Node
*/
CircuitNode * _newNode() {
    CircuitNode * out = malloc(sizeof(CircuitNode));
    
    out->V = -1;

    return out;
}


/**
 * @brief Creates a new resistor circuit component and returns a pointer to it
 * @param ohm The resistance of the new resistor in ohms
 * @return A pointer to that resistor ADT
 */
CircuitComponent * createResistor(float ohm) {
    CircuitComponent * out = _newComponent();
    out->isResistor = true;
    out->resistance = ohm;
    return out;
}

/**
 * @brief Creates a new inductor circuit component and returns a pointer to it
 * @param henry The inductance of the new inductor in henries
 * @return A pointer to that inductor ADT
 */
CircuitComponent * createInductor(float henry) {
    CircuitComponent * out = _newComponent();
    out->isInductor = true;
    out->inductance = henry;
    return out;
}

/**
 * @brief Creates a new capacitor circuit component and returns a pointer to it
 * @param faraday The capacitance of the new capacitor in faradays
 * @return A pointer to that capacitor ADT
 */
CircuitComponent * createCapacitor(float faraday) {
    CircuitComponent * out = _newComponent();
    out->isCapacitor = true;
    out->capacitance = faraday;
    return out;
}

/**
 * @brief Creates a new resistor circuit component and returns a pointer to it
 * @param v The voltage of the new source in volts
 * @return A pointer to that source ADT
 */
CircuitComponent * createSourceDC(float v) {
    CircuitComponent * out = _newComponent();
    out->isVoltageSource = true;
    out->voltageAcross = v;
    return out;
}

// ======================================================================================================================================================================================================================
// ========================== ADT Free-ers =======================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Frees all memory associated with a circuit and its components
 * @param circuit Pointer to the circuit to free
 * @return none
 */
void freeCircuit(Circuit * circuit) {
    for (int i = 0; i < circuit->numComponents; i++) {
        freeComponent(circuit->components[i]);
    }

    free(circuit->components);

    for (int i = 0; i < circuit->numNodes; i++) {
        freeNode(circuit->nodes[i]);
    }

    free(circuit->nodes);

    free(circuit);
}

/**
 * @brief Frees all memory associated with a component
 * @param component Pointer to the component to free
 * @return none
 */
void freeComponent(CircuitComponent * component) {
    free(component->connections);
    free(component);
}

/**
 * @brief Frees all memory associated with a node
 * @param node Pointer to the node to free
 * @return none
 */
void freeNode(CircuitNode * node) {
    free(node->renderLines);
    free(node->components);
    free(node);
}


// ======================================================================================================================================================================================================================
// ======================== Circuit Linkers ======================================================================================================================================================================
// ======================================================================================================================================================================================================================


/**
 * @brief Registers a new component with the circuit
 * @param circuit Pointer to the circuit to register the component with
 * @param component Pointer to the component to register with the circuit
 * @return none
 */
void addComponent(Circuit * circuit, CircuitComponent * component) {
    if (circuit->numComponents >= circuit->allocatedComponents) {
        int toAdd = 0;
        while (circuit->numComponents >= circuit->allocatedComponents + toAdd) {
            toAdd += ARRAY_SIZE_INCREMENT;
        }

        circuit->allocatedComponents += toAdd;
        CircuitComponent ** newComponents = calloc(circuit->allocatedComponents, sizeof(CircuitComponent *));
        if (newComponents == NULL) {
            printf("ERROR: Get more ram, lol\n");
            exit(-1);
        }

        for (int i = 0; i < circuit->numComponents; i++) {
            newComponents[i] = circuit->components[i];
        }

        free(circuit->components);
        circuit->components = newComponents;
    }

    circuit->components[circuit->numComponents] = component;
    component->circuit = circuit;
    component->componentIndex = circuit->numComponents;

    circuit->numComponents++;
}

/**
 * @brief Registers a new node with the circuit
 * @param circuit Pointer to the circuit to register the node with
 * @param node Pointer to the node to register with the circuit
 * @return none
 */
void addNode(Circuit * circuit, CircuitNode * node) {
    if (circuit->numNodes >= circuit->allocatedNodes) {
        int toAdd = 0;
        while (circuit->numNodes >= circuit->allocatedNodes + toAdd) {
            toAdd += ARRAY_SIZE_INCREMENT;
        }

        circuit->allocatedNodes += toAdd;
        CircuitNode ** newNodes = calloc(circuit->allocatedNodes, sizeof(CircuitNode *));
        if (newNodes == NULL) {
            printf("ERROR: Get more ram, lol\n");
            exit(-1);
        }

        for (int i = 0; i < circuit->numNodes; i++) {
            newNodes[i] = circuit->nodes[i];
        }

        free(circuit->nodes);
        circuit->nodes = newNodes;
    }

    circuit->nodes[circuit->numNodes] = node;
    node->circuit = circuit;
    node->nodeIndex = circuit->numNodes;

    circuit->numNodes++;
}

/**
 * @brief Creates a node linking two circuit components and adds it to the circuit
 * @param a Pointer to the first component 
 * @param b Pointer to the second component
 * @return Pointer to the new connecting node
 */
CircuitNode * linkComponents(CircuitComponent * a, CircuitComponent * b) {
    CircuitNode * node = _newNode();
    assert(a->circuit != NULL);

    addNode(a->circuit, node);

    linkComponentToNode(a, node);
    linkComponentToNode(b, node);

    return node;
}

/**
 * @brief Link a single component and a single node together
 * @param a Pointer to the circuit component
 * @param b Pointer to the circuit node
 * @return none
 */
void linkComponentToNode(CircuitComponent * a, CircuitNode * b) {
    if (a->allocatedConnections <= a->numConnections) {
        int newSize = (a->numConnections - a->allocatedConnections) + ARRAY_SIZE_INCREMENT;
        a->connections = expandIntArray(a->connections, newSize, a->allocatedConnections);
        a->allocatedConnections = newSize;
    }

    if (b->allocatedComponents <= b->numComponents) {
        int newSize = (b->numComponents - b->allocatedComponents) + ARRAY_SIZE_INCREMENT;
        b->components = expandIntArray(b->components, newSize, b->allocatedComponents);
        b->allocatedComponents = newSize;
    }

    a->connections[a->numConnections] = b->nodeIndex;
    a->numConnections++;

    b->components[b->numComponents] = a->componentIndex;
    b->numComponents++;
}

// ======================================================================================================================================================================================================================
// ========================= Circuit Checks ======================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Check if a circuit has a valid loop in it and isn't shorted
 * @param circuit Pointer to the circuit to check
 * @return true or false, depending on whether the circuit is valid
 */
bool checkIsValidCircuit(Circuit * circuit) {
    return false;
}

/**
 * @brief Check if a circuit is shorted anywhere
 * @param circuit Pointer to the circuit to check
 * @return true or false, depending on whether the circuit is shorted
 */
bool checkIsShorted(Circuit * circuit) {
    return false;
}

/**
 * @brief Remove and free any elements in a circuit that are not connected to anything
 * @param circuit Pointer to the circuit to cull
 * @return none
 */
void _cullCircuit(Circuit * circuit) {

}

// ======================================================================================================================================================================================================================
// ============================== Misc ===========================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Procedurally name all Components in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllComponents(Circuit * circuit) {
    int resistorNum = 1;
    int capacitorNum = 1;
    int inductorNum = 1;


    for (int i = 0; i < circuit->numComponents; i++) {
        CircuitComponent * component = circuit->components[i];
        if (component->isCapacitor) {
            sprintf(component->label, "C%d", capacitorNum);
            capacitorNum++;
        } else if (component->isInductor) {
            sprintf(component->label, "I%d", inductorNum);
            inductorNum++;
        } else if (component->isResistor) {
            sprintf(component->label, "R%d", resistorNum);
            resistorNum++;
        } else if (component->isVoltageSource) {
            sprintf(component->label, "%.1fV", component->voltageAcross);
        }
    }
}

/**
 * @brief Procedurally name all Nodes in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllNodes(Circuit * circuit) {
    char currentName = 'A';
    for (int i = 0; i < circuit->numNodes; i++) {
        if (currentName > 'Z') {
            printf("WARNING: Too many nodes. Node naming is only supported up to 26 nodes.\n");
        }

    
        CircuitNode * node = circuit->nodes[i];
        sprintf(node->label, "%c", currentName);
        currentName++;
    }
}

/**
 * @brief Procedurally name all elements in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllElements(Circuit * circuit) {
    nameAllComponents(circuit);
    nameAllNodes(circuit);
}

/**
 * @brief Name a circuit
 * @param circuit Pointer to the circuit to name
 * @param name String to name the circuit as
 * @return none
 */
void nameCircuit(Circuit * circuit, char * name) {
    strncpy(circuit->name, name, LABEL_SIZE);
}