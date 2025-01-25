#include <stdio.h>
#include <assert.h>
#include "./modules/CircuitStructures/circuitStructures.h"




int main(int argC, char ** args) {
    Circuit * circuit = createNewCircuit();
    nameCircuit(circuit, "Test Circuit");

    CircuitComponent * source = createSourceDC(5.f);
    CircuitComponent * resistor = createResistor(1000.f);

    addComponent(circuit, source);
    addComponent(circuit, resistor);

    linkComponents(resistor, source);
    linkComponents(source, resistor);

    nameAllElements(circuit);

    printf("Circuit: %s\n", circuit->name);
    printf("Resistor: %s    ----    Source: %s\n------------------------------------------------------\n", resistor->label, source->label);
    printf("Successful completion!\n\n");

    return 1;
}