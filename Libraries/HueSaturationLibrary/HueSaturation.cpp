// Including necessary header files
#include "HueSaturation.h"
#include "../Pixel.h"
#include <vector>
#include <cmath>
#include <algorithm>

// Function to apply hue and saturation adjustments to an image
void applyHueSaturation(std::vector<std::vector<Pixel>>& image, float saturationValue, float hueValue) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            // Extracting normalized RGB values from the pixel
            float red = pixel.r / 255.0f;
            float green = pixel.g / 255.0f;
            float blue = pixel.b / 255.0f;

            // Calculating maximum and minimum color components
            float cmax = std::max({red, green, blue});
            float cmin = std::min({red, green, blue});
            float delta = cmax - cmin;

            // Variables to store hue, saturation, and value
            float hue, saturation, value;

            // Calculating hue based on the color components
            if (delta == 0) {
                hue = 0;
            } else if (cmax == red) {
                hue = 60 * fmod((green - blue) / delta, 6);
            } else if (cmax == green) {
                hue = 60 * ((blue - red) / delta + 2);
            } else {
                hue = 60 * ((red - green) / delta + 4);
            }

            // Adjusting hue and handling wrap-around
            hue += hueValue;
            if (hue < 0) hue += 360;
            if (hue >= 360) hue -= 360;

            // Calculating saturation based on the color components
            if (cmax == 0) {
                saturation = 0;
            } else {
                saturation = delta / cmax;
            }

            // Adjusting saturation based on user input
            float saturationFactor = (saturationValue >= 50) ? ((saturationValue - 50) / 50.0f) : (-saturationValue / 50.0f);
            saturation = saturation + saturationFactor;
            saturation = std::max(0.0f, std::min(1.0f, saturation));


            value = cmax;

            // Calculating chroma, hue difference, and intermediate values
            float chroma = value * saturation;
            float hueDiff = hue / 60.0f;
            float x = chroma * (1 - std::abs(fmod(hueDiff, 2) - 1));

            // Calculating RGB components based on hue difference
            float r2, g2, b2;
            if (hueDiff < 1) {
                r2 = chroma;
                g2 = x;
                b2 = 0;
            } else if (hueDiff < 2) {
                r2 = x;
                g2 = chroma;
                b2 = 0;
            } else if (hueDiff < 3) {
                r2 = 0;
                g2 = chroma;
                b2 = x;
            } else if (hueDiff < 4) {
                r2 = 0;
                g2 = x;
                b2 = chroma;
            } else if (hueDiff < 5) {
                r2 = x;
                g2 = 0;
                b2 = chroma;
            } else {
                r2 = chroma;
                g2 = 0;
                b2 = x;
            }

            // Calculating final RGB values and clamping them to [0, 255]
            float m = value - chroma;
            pixel.r = static_cast<int>((r2 + m) * 255);
            pixel.g = static_cast<int>((g2 + m) * 255);
            pixel.b = static_cast<int>((b2 + m) * 255);

            pixel.r = std::max(0, std::min(255, pixel.r));
            pixel.g = std::max(0, std::min(255, pixel.g));
            pixel.b = std::max(0, std::min(255, pixel.b));
        }
    }
}


