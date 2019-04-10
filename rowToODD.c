#include "listColoring.h"
#include "odd.h"
#include <stdlib.h>
#include <string.h>

void rowToODD(LCInstance *instance, int i, ODD *resultingODD);
void addTransitions(LCInstance *instance, int i, ODD *resultingODD);
void addTransitionsPerLayer(LCInstance *instance, int i, int j,
                            ODD *resultingODD);

void addTransitions(LCInstance *instance, int i, ODD *resultingODD) {
    for (int j = 0; j < resultingODD->nLayers; j++) {
        addTransitionsPerLayer(instance, i, j, resultingODD);
    }
}


void copyAlphabets(LCInstance *instance, int i, ODD *resultingODD) {
    AlphabetMap **map = instance->IntermediateColors;
    int cols = instance->nColumns;
    for (int j = 0; j <cols; ++j) {
        AlphabetMap currentMap = {.sizeAlphabet=map[i][j].sizeAlphabet,
                .N2S=malloc(sizeof(char*)*map[i][j].sizeAlphabet),
                .S2N=malloc(sizeof(int)*map[i][j].sizeAlphabet)};
        Layer currentLayer = resultingODD->layerSequence[j];
        for (int k = 0; k < map[i][j].sizeAlphabet; ++k) {
            currentMap.S2N[k] = map[i][j].S2N[k];
            currentMap.N2S[k] = malloc(strlen(map[i][j].N2S[k]));
            strcpy(currentMap.N2S[k], map[i][j].N2S[k]);
        }
        currentLayer.map = currentMap;
    }
}


void addLayerStatesAndEndStates(LCInstance *instance, int i, ODD *resultingODD) {
    AlphabetMap **map = instance->IntermediateColors;
    int cols = instance->nColumns;

    StateContainer leftStates1 = {.nStates = 1, .set = 0};
    StateContainer initialStates = {.nStates = 1, .set = 0};
    resultingODD->layerSequence[0].leftStates = leftStates1;
    resultingODD->layerSequence[0].initialFlag = 1;
    resultingODD->layerSequence[0].finalFlag = 0;

    for (int j = 1; j < cols; j++) {
        int alphSize = map[i][j-1].sizeAlphabet;
        int byteSize = sizeof(State) * alphSize;

        StateContainer leftStates2 = {.nStates = alphSize, .set = malloc(byteSize)};
        for (int k = 0; k < alphSize; ++k) {
            leftStates2.set[k] = k;
        }
        resultingODD->layerSequence[j].leftStates = leftStates2;
        resultingODD->layerSequence[j - 1].rightStates = leftStates2;
    }
    int alphSize = map[i][cols-1].sizeAlphabet;
    int byteSize = sizeof(State) * alphSize;
    StateContainer lastRigthState = {.nStates = alphSize, .set = malloc(byteSize)};
    resultingODD->layerSequence[cols-1].rightStates = lastRigthState;
    resultingODD->layerSequence[cols-1].finalStates = lastRigthState;

    int max =-1;
    for (int j = 0; j < cols; ++j) {
        Layer result = resultingODD->layerSequence[j];
        result.width = result.leftStates.nStates > result.rightStates.nStates ? result.leftStates.nStates : result.rightStates.nStates;
        if (result.width>max){
            max = resultingODD->width;
        }
    }

    resultingODD->width = max;

}

// TODO: What about final transitions
void addTransitionsPerLayer(LCInstance *instance, int i, int j,
                            ODD *resultingODD) {
    if (j == 0) { // Initial transitions goes from 0
        resultingODD->layerSequence[j].transitions.nTransitions =
                instance->IntermediateColors[i][j].sizeAlphabet;
        resultingODD->layerSequence[j].transitions.set =
                malloc(sizeof(Transition) *
                       resultingODD->layerSequence[j].transitions.nTransitions);

        for (int trans = 0; trans < instance->IntermediateColors[i][j].sizeAlphabet;
             trans++) {
            Transition transition;
            transition.s1 = 0;
            transition.a = trans;
            transition.s2 = trans;
            resultingODD->layerSequence[j].transitions.set[trans] = transition;
        }
    } else { // All other transitions
        resultingODD->layerSequence[j].transitions.nTransitions =
                instance->hConstraints[i][j].nConstraints;
        resultingODD->layerSequence[j].transitions.set =
                malloc(sizeof(Transition) *
                       resultingODD->layerSequence[j].transitions.nTransitions);

        for (int trans = 0;
             trans < resultingODD->layerSequence[j].transitions.nTransitions;
             trans++) {
            Transition transition;
            transition.s1 = instance->hConstraints[i][j].pairs[trans].color1;
            transition.a = instance->hConstraints[i][j].pairs[trans].color2;
            transition.s2 = instance->hConstraints[i][j].pairs[trans].color2;
            resultingODD->layerSequence[j].transitions.set[trans] = transition;
        }
    }
}

// Takes an instance of the List Coloring problem and constructs an
// ODD accepting precisely those sequences of colors which are
// horizontally compatible
void rowToODD(LCInstance *instance, int i, ODD *resultingODD) {
  resultingODD-> nLayers = instance->nRows;
  resultingODD->layerSequence = malloc(sizeof(Layer)*resultingODD->nLayers);
  addTransitions(instance, i, resultingODD);
  addLayerStatesAndEndStates(&instance, i, &resultingODD);
  copyAlphabets(&instance, i, &resultingODD);
}


