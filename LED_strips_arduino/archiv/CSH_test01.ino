#include <Adafruit_NeoPixel.h>

// Define the pins that the LED strips are connected to and the number of LEDs in each strip
#define NUM_STRIPS 11
const int LED_PINS[NUM_STRIPS] = {2,3,4,5,6,7,8,9,10,11,12};
const int NUM_LEDS[NUM_STRIPS] = {7,2,2,2,8,9,7,6,9,8,11};

// Define individual parameters for each strip
int intensity[NUM_STRIPS] = {1,2,3,1,1,3,5,1,7,1,1};  // Number of LEDs to light up at the same time
int delayTime[NUM_STRIPS] = {100,200,50,50,50,100,100,100,50,50,50};  // Speed parameter (lower is faster)

// Create an array of NeoPixel objects
//Adafruit_DotStar strips[NUM_STRIPS] = {
  // Korea pos6 num8
  //Adafruit_DotStar(NUM_LEDS[0], DATA_PINS[0], CLOCK_PINS[0], DOTSTAR_BRG),

Adafruit_NeoPixel strips[NUM_STRIPS] = { 
    Adafruit_NeoPixel(NUM_LEDS[0], LED_PINS[0], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[1], LED_PINS[1], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[2], LED_PINS[2], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[3], LED_PINS[3], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[4], LED_PINS[4], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[5], LED_PINS[5], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[6], LED_PINS[6], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[7], LED_PINS[7], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[8], LED_PINS[8], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUM_LEDS[9], LED_PINS[9], NEO_GRB + NEO_KHZ800),
    //Adafruit_NeoPixel(NUM_LED[10], LED_PINS[10], NEO_GRB + NEO_KHZ800)
};

// Define the colors for each direction
uint32_t color_1 = strips[0].Color(255, 0, 0);  // Red color for left-to-right
uint32_t color_2 = strips[0].Color(0, 0, 255);  // Blue color for right-to-left

// Function to run animations on all strips independently based on max LED count
void runAnimation() {
    // Keep track of the direction and position for each strip
    bool direction[NUM_STRIPS];  // false = left-to-right, true = right-to-left
    int positions[NUM_STRIPS] = {0};  // Starting positions for each strip

    // Initialize all strips to left-to-right direction initially
    for (int k = 0; k < NUM_STRIPS; k++) {
        direction[k] = false;
    }

    // Continue running animations until stopped
    while (true) {
        for (int k = 0; k < NUM_STRIPS; k++) {
            strips[k].clear();  // Clear current strip

            // Determine current color based on direction
            uint32_t currentColor = direction[k] ? color_2 : color_1;

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

        // Use the minimum delay time to keep the timing consistent across all strips
        int minDelay = delayTime[0];
        for (int k = 1; k < NUM_STRIPS; k++) {
            if (delayTime[k] < minDelay) {
                minDelay = delayTime[k];
            }
        }
        delay(minDelay);  // Delay based on the fastest strip
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