#pragma once

#include <stdbool.h>
#include "./../../settings.h"

#define ComponentIndex int
#define NodeIndex int

// ======================================================================================================================================================================================================================
// ===================== Structure Definitions ===================================================================================================================================================================
// ======================================================================================================================================================================================================================

// A single point in a circuit
typedef struct {
    float x;
    float y;
} CircuitPoint;

// For rendering purposes only, a single line to be rendered in a circuit node
typedef struct {
    CircuitPoint a;
    CircuitPoint b;
} CircuitLine;

// a single component in a circuit
typedef struct {
    NodeIndex * connections;
    int numConnections;
    int allocatedConnections;

    void * circuit; // a pointer to the circuit that this component is a part of

    float currentThrough;
    float voltageAcross;


    float resistance;
    float capacitance;
    float inductance;

    bool isResistor; // what type of component this component is, determines some of the way it interacts with other circuits
    bool isCapacitor;
    bool isInductor;
    bool isVoltageSource;
    bool isClosed;

    char label[LABEL_SIZE]; // a label for this part of the circuit


    int componentIndex; // the index of the component in its circuit
} CircuitComponent;

// A node in a circuit
typedef struct {
    float V; // the voltage of this node in relation to the ground of its circuit

    CircuitLine * renderLines;
    int numRenderLines;
    int allocatedRenderLines;

    void * circuit; // a pointer to the circuit that this node is a part of

    ComponentIndex * components;
    int numComponents;
    int allocatedComponents;

    char label[LABEL_SIZE]; // a label for this part of the circuit

    int nodeIndex; // the index of the node in its circuit
} CircuitNode;

typedef struct {
    char name[LABEL_SIZE];

    CircuitComponent ** components; // list with pointers to all of the components in this circuit
    int numComponents;
    int allocatedComponents;

    CircuitNode ** nodes; // list with pointers to all of the nodes in this circuit
    int numNodes;
    int allocatedNodes;

    CircuitNode * ground; // this will still be in the node list, this is just a pointer to its location in memory
} Circuit;

// ======================================================================================================================================================================================================================
// ======================== ADT Initializers =====================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief create a new circuit ADT. Does not assume ownership.
 * @return a pointer to the newly created circuit
 */
Circuit * createNewCircuit();

/** 
 * @brief Create a blank, un-initialized, circuit component
 * @return A pointer to the new component
*/
CircuitComponent * _newComponent();

/** 
 * @brief Create a blank, un-initialized, circuit Node
 * @return A pointer to the new Node
*/
CircuitNode * _newNode();


/**
 * @brief Creates a new resistor circuit component and returns a pointer to it
 * @param ohm The resistance of the new resistor in ohms
 * @return A pointer to that resistor ADT
 */
CircuitComponent * createResistor(float ohm);

/**
 * @brief Creates a new inductor circuit component and returns a pointer to it
 * @param henry The inductance of the new inductor in henries
 * @return A pointer to that inductor ADT
 */
CircuitComponent * createInductor(float henry);

/**
 * @brief Creates a new capacitor circuit component and returns a pointer to it
 * @param faraday The capacitance of the new capacitor in faradays
 * @return A pointer to that capacitor ADT
 */
CircuitComponent * createCapacitor(float faraday);


/**
 * @brief Creates a new resistor circuit component and returns a pointer to it
 * @param v The voltage of the new source in volts
 * @return A pointer to that source ADT
 */
CircuitComponent * createSourceDC(float v);

// ======================================================================================================================================================================================================================
// ========================== ADT Free-ers =======================================================================================================================================================================
// ======================================================================================================================================================================================================================


/**
 * @brief Frees all memory associated with a circuit and its components
 * @param circuit Pointer to the circuit to free
 * @return none
 */
void freeCircuit(Circuit * circuit);

/**
 * @brief Frees all memory associated with a component
 * @param component Pointer to the component to free
 * @return none
 */
void freeComponent(CircuitComponent * component);

/**
 * @brief Frees all memory associated with a node
 * @param node Pointer to the node to free
 * @return none
 */
void freeNode(CircuitNode * node);

// ======================================================================================================================================================================================================================
// ======================== Circuit Linkers ======================================================================================================================================================================
// ======================================================================================================================================================================================================================


/**
 * @brief Registers a new component with the circuit
 * @param circuit Pointer to the circuit to register the component with
 * @param component Pointer to the component to register with the circuit
 * @return none
 */
void addComponent(Circuit * circuit, CircuitComponent * component);

/**
 * @brief Registers a new node with the circuit
 * @param circuit Pointer to the circuit to register the node with
 * @param node Pointer to the node to register with the circuit
 * @return none
 */
void addNode(Circuit * circuit, CircuitNode * node);

/**
 * @brief Creates a node linking two circuit components and adds it to the circuit
 * @param a Pointer to the first component 
 * @param b Pointer to the second component
 * @return Pointer to the new connecting node
 */
CircuitNode * linkComponents(CircuitComponent * a, CircuitComponent * b);

/**
 * @brief Link a single component and a single node together
 * @param a Pointer to the circuit component
 * @param b Pointer to the circuit node
 * @return none
 */
void linkComponentToNode(CircuitComponent * a, CircuitNode * b);

// ======================================================================================================================================================================================================================
// ========================= Circuit Checks ======================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Check if a circuit has a valid loop in it and isn't shorted
 * @param circuit Pointer to the circuit to check
 * @return true or false, depending on whether the circuit is valid
 */
bool checkIsValidCircuit(Circuit * circuit);

/**
 * @brief Check if a circuit is shorted anywhere
 * @param circuit Pointer to the circuit to check
 * @return true or false, depending on whether the circuit is shorted
 */
bool checkIsShorted(Circuit * circuit);

/**
 * @brief Remove and free any elements in a circuit that are not connected to anything
 * @param circuit Pointer to the circuit to cull
 * @return none
 */
void _cullCircuit(Circuit * circuit);

// ======================================================================================================================================================================================================================
// ============================== Misc ===========================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Procedurally name all Components in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllComponents(Circuit * circuit);

/**
 * @brief Procedurally name all Nodes in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllNodes(Circuit * circuit);

/**
 * @brief Procedurally name all elements in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllElements(Circuit * circuit);

/**
 * @brief Name a circuit
 * @param circuit Pointer to the circuit to name
 * @param name String to name the circuit as
 * @return none
 */
void nameCircuit(Circuit * circuit, char * name);