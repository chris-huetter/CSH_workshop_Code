#include <Adafruit_NeoPixel.h>

// Define the pins that the LED strips are connected to and the number of LEDs in each strip
#define NUM_STRIPS 11
const int LED_PINS[NUM_STRIPS] = {2,3,4,5,6,7,8,9,10,11,12};

                              // US, FR, SW, FI, KR, JP, CH, HK, PH, SG, AU
const int NUM_LEDS[NUM_STRIPS] = {7,2,2,2,8,9,7,6,9,8,11};

// Define individual parameters for each strip
int intensity[NUM_STRIPS] = {3,1,1,1,1,1,4,2,1,1,2};  // Number of LEDs to light up at the same time
int delayTime[NUM_STRIPS] = {50, 200, 500, 500, 70, 500, 30, 100, 500, 200, 500};  // Speed parameter (lower is faster)
 
// Create an array of NeoPixel objects
Adafruit_NeoPixel strips[NUM_STRIPS] = {
    Adafruit_NeoPixel(NUM_LEDS[0], LED_PINS[0], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[1], LED_PINS[1], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[2], LED_PINS[2], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[3], LED_PINS[3], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[4], LED_PINS[4], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[5], LED_PINS[5], NEO_GRB + NEO_KHZ800), 
    Adafruit_NeoPixel(NUM_LEDS[6], LED_PINS[6], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[7], LED_PINS[7], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[8], LED_PINS[8], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[9], LED_PINS[9], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[10], LED_PINS[10], NEO_GRB + NEO_KHZ800)
};

// Define the colors for each direction for each strip
uint32_t forwardColors[NUM_STRIPS] = {
    strips[0].Color(0,0,255),  // Red for strip 1
    strips[1].Color(0,0,255),  // Green for strip 2
    strips[2].Color(0,0,255),  // Blue for strip 3
    strips[3].Color(0,0,255),  // Yellow for strip 4
    strips[4].Color(0,0,255),  // Cyan for strip 5
    strips[5].Color(0,0,255), // Magenta for strip 6
    strips[6].Color(0,0,255),  // Green for strip 2
    strips[7].Color(0,0,255),  // Blue for strip 3
    strips[8].Color(0,0,255),  // Yellow for strip 4
    strips[9].Color(0,0,255),  // Cyan for strip 5
    strips[10].Color(0,0,255)   // Magenta for strip 6
};

uint32_t backwardColors[NUM_STRIPS] = {
    strips[0].Color(255, 0, 0),  // Cyan for strip 1
    strips[1].Color(255, 0, 0),  // Magenta for strip 2
    strips[2].Color(255, 0, 0),  // Yellow for strip 3
    strips[3].Color(255, 0, 0),  // Blue for strip 4
    strips[4].Color(255, 0, 0),  // Green for strip 5
    strips[5].Color(255, 0, 0),   // Red for strip 6
    strips[6].Color(255, 0, 0),  // Green for strip 2
    strips[7].Color(255, 0, 0),  // Blue for strip 3
    strips[8].Color(255, 0, 0),  // Yellow for strip 4
    strips[9].Color(255, 0, 0),  // Cyan for strip 5
    strips[10].Color(255, 0, 0)   // Magenta for strip 6
};

// Function to run animations on all strips independently based on max LED count
void runAnimation() {
    // Keep track of the direction and position for each strip
    bool direction[NUM_STRIPS];  // false = left-to-right, true = right-to-left
    int positions[NUM_STRIPS] = {0};  // Starting positions for each strip
    unsigned long previousMillis[NUM_STRIPS] = {0};  // Store the last time a strip was updated

    // Initialize all strips to left-to-right direction initially
    for (int k = 0; k < NUM_STRIPS; k++) {
        direction[k] = false;
    }

    // Continue running animations until stopped
    while (true) {
        for (int k = 0; k < NUM_STRIPS; k++) {
            unsigned long currentMillis = millis();

            // Update only if enough time has passed
            if (currentMillis - previousMillis[k] >= delayTime[k]) {
                previousMillis[k] = currentMillis;  // Save the last update time

                strips[k].clear();  // Clear current strip

                // Determine current color based on direction
                uint32_t currentColor = direction[k] ? backwardColors[k] : forwardColors[k];

                // Update the strip based on current position and direction
                for (int j = 0; j < intensity[k]; j++) {
                    int pos = direction[k] ? strips[k].numPixels() - 1 - (positions[k] - j) : (positions[k] - j);
                    if (pos >= 0 && pos < strips[k].numPixels()) {
                        strips[k].setPixelColor(pos, currentColor);
                    }
                }

                strips[k].show();  // Display the updated strip

                // Update the position for the next frame
                positions[k]++;
                if (positions[k] >= strips[k].numPixels() + intensity[k]) {
                    positions[k] = 0;  // Reset position
                    direction[k] = !direction[k];  // Switch direction
                }
            }
        }
    }
}

void setup() {
    for (int k = 0; k < NUM_STRIPS; k++) {
        strips[k].begin();  // Initialize each LED strip
        strips[k].show();   // Initialize all pixels to 'off'
    }
}

void loop() {
    runAnimation();  // Run the animation with individual settings
}