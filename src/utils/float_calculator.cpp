#include "float_calculator.h"

float FloatCalculator::CalculateWear(int quality) {
    switch (quality) {
        case 0: return 0.01f;  // Factory New
        case 1: return 0.15f;  // Minimal Wear
        case 2: return 0.37f;  // Field-Tested
        case 3: return 0.45f;  // Well-Worn
        case 4: return 0.80f;  // Battle-Scarred
        default: return 0.5f;
    }
}

int FloatCalculator::CalculateQuality(float wear) {
    if (wear < 0.07f) return 0;
    if (wear < 0.27f) return 1;
    if (wear < 0.40f) return 2;
    if (wear < 0.60f) return 3;
    return 4;
}
