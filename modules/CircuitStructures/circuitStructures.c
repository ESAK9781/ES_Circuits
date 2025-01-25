#include <stdlib.h>

#include "circuitStructures.h"
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
}

// ======================================================================================================================================================================================================================
// ========================== ADT Free-ers =======================================================================================================================================================================
// ======================================================================================================================================================================================================================


/**
 * @brief Frees all memory associated with a circuit and its components
 * @return none
 */
void freeCircuit();

/**
 * @brief Frees all memory associated with a component
 * @return none
 */
void freeComponent();

/**
 * @brief Frees all memory associated with a node
 * @return none
 */
void freeNode();

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
 * @brief Creates a node linking two circuit components and adds it to the circuit
 * @param a Pointer to the first component 
 * @param b Pointer to the second component
 * @return none
 */
void linkComponents(CircuitComponent * a, CircuitComponent * b);

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
 * @brief Check if a circuit has a valid loop in it
 * @param circuit Pointer to the circuit to check
 * @return true or false, depending on whether the circuit is valid
 */
bool checkIsValidCircuit(Circuit * circuit);

/**
 * @brief Remove and free any components in a circuit that are not connected to anything
 * @param circuit Pointer to the circuit to cull
 * @return none
 */
void _cullCircuit(Circuit * circuit);

// ======================================================================================================================================================================================================================
// ============================== Misc ===========================================================================================================================================================================
// ======================================================================================================================================================================================================================

/**
 * @brief Procedurally name all nodes in a circuit
 * @param circuit Pointer to the circuit
 * @return none
 */
void nameAllNodes(Circuit * circuit);

