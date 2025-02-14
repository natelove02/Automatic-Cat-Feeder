/**
 * @file Lab9.c
 * @author your name (you@domain.com), Jonathan Valvano, Matthew Yu
 *    <TA NAME and LAB SECTION # HERE>
 * @brief
 *    Possible main programs to test Lab 9. Feel free to edit this to match your
 *    specifications.
 * 
 *    For this lab, the students must implement the following communication pipeline:
 *     - Input -> Encoder -> DAC -> Speaker -> AIR GAP -> Microphone -> ADC ->
 *       Decoder -> Display.
 *     Teams are allowed to choose an encoding scheme to transmit their
 *     information over the speaker. They need to be able to discuss and profile
 *     the execution latency, bandwidth, and SNR of their implementation.
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022
 * @note Modify __MAIN__ on L23 to determine which main method is executed.
 *   __MAIN__ = 0 - Test the input task.
 *              1 - Test the encoder.
 *              2 - Test the transmitting FIFO.
 *              3 - Test the DAC.
 *   CHECKPOINT 4 - Test integration of the input to the DAC speaker.
 *              5 - Test the ADC input software for the microphone.
 *              6 - Test the decoder.
 *              7 - Test the receiving FIFO.
 *              8 - Test the display.
 *   CHECKPOINT 9 - Test integration of the microphone ADC to the display.
 */
#define __MAIN__ 0

#include <stdbool.h>
#include <stdint.h>

#include "inc/RegDefs.h"

void assert(bool result) {
    /* Initialize PF1 (Red) or PF3 (Green) based on result and turn it on. */
    if (!result) {
        uint32_t portOffset = (((41 - (1 << 5)) >> 3) << 12) + (1 << 17);
        uint8_t pinAddress = 1 << 41 % 8;

        /* Activate the clock for Port F. */
        GET_REG(SYSCTL_BASE + SYSCTL_RCGCGPIO_OFFSET) |=
            1 << (41 / 8); /* 8 pins per port. */

        /* Stall until clock is ready. */
        while ((GET_REG(SYSCTL_BASE + SYSCTL_PRGPIO_OFFSET) &
           (1 << (41 / 8))) == 0);

        /* Allow changes to selected pin. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_CR_OFFSET) |= pinAddress;

        /* Set pin to output. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_DIR_OFFSET) |= pinAddress;

        /* Set as digital pin. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_AMSEL_OFFSET) &= ~pinAddress;
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_DEN_OFFSET) |= pinAddress;

        /* Turn pin on. */
        GET_REG(0x40025008) = 1 << 1;
    } else {
        uint32_t portOffset = (((43 - (1 << 5)) >> 3) << 12) + (1 << 17);
        uint8_t pinAddress = 1 << 43 % 8;

        /* Activate the clock for Port F. */
        GET_REG(SYSCTL_BASE + SYSCTL_RCGCGPIO_OFFSET) |=
            1 << (43 / 8); /* 8 pins per port. */
        
        /* Stall until clock is ready. */
        while ((GET_REG(SYSCTL_BASE + SYSCTL_PRGPIO_OFFSET) &
           (1 << (43 / 8))) == 0);

        /* Allow changes to selected pin. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_CR_OFFSET) |= pinAddress;

        /* Set pin to output. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_DIR_OFFSET) |= pinAddress;

        /* Set as digital pin. */
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_AMSEL_OFFSET) &= ~pinAddress;
        GET_REG(GPIO_PORT_BASE + portOffset + GPIO_DEN_OFFSET) |= pinAddress;

        GET_REG(0x40025020) = 1 << 3;
    }
}

#if __MAIN__ == 0
/* TODO: Set up the required data structures here. Globals and consts only. */
bool result = false;

/**
 * @brief Main 0 tests the input task. The students should develop code to test
 * entering in some data into their program through external input hardware and
 * checking to see if it matches the expected input.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    while (1) {
        /* TODO: Poll for user input. */

        /* TODO: Check if user input matches as expected. */

        /* Turn on green LED if we pass this test. Turn on red LED if we fail
           this test. */
        assert(result);
    }
}
#elif __MAIN__ == 1
/* TODO: Set up the required data structures here. Globals and consts only. */
bool result = true;

/**
 * @brief Main 1 tests the encoder task. Students should develop code that takes
 * some arbitrary data and feeds it into the encoder, and check to see if the
 * encoded data matches the expected output.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    /* TODO: Create your arbitrary data to encode here. */

    while (1) {
        /* TODO: Feed the input data into the encoder. */

        /* TODO: Check if encoder output matches as expected. */

        /* Turn on green LED if we pass this test. Turn on red LED if we fail
           this test. */
        assert(result);
    }
}
#elif __MAIN__ == 2
/* TODO: Set up the required data structures here. Globals and consts only. */
bool result = false;

/**
 * @brief DACTask executes at a fixed rate and grabs an entry from the FIFO. If
 * it gets an entry, output to the speaker.
 */
void DACTask(void) {
    /* TODO: Check to see after X calls that all encoded data shows up here. */

    /* Turn on green LED if we pass this test. Turn on red LED if we fail
        this test. */
    assert(result);
}

/**
 * @brief Main 2 tests the streaming of the encoder to the DAC task. The encoder
 * loads encoded data into a FIFO, and the DACTask should retrieve that data at
 * a fixed rate.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    /* TODO: Create your arbitrary data to encode here. */

    while (1) {
        /* TODO: Feed the input data into the encoder. */

        /* TODO: Feed the encoded data into a FIFO. */
    }
}
#elif __MAIN__ == 3
/* TODO: Set up the required data structures here. Globals and consts only. */
const uint8_t sineWave[32] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,
    24,25,26,27,28,29,30,31
};

/**
 * @brief DACTask executes at a fixed rate and outputs a sine wave to the
 * speaker.
 */
void DACTask(void) {
    static uint8_t sineWaveIdx = 0;
    /* TODO: output sineWave[sineWaveIdx] to the DAC. */

    sineWaveIdx = (sineWaveIdx + 1) % 32;
}

/**
 * @brief Main 3 tests the DAC and speaker operation. A sine wave is fed into
 * the DAC and should be audible over the speaker.
 */
int main(void) {
    while (1) {
        bool _ = true;
    }
}
#elif __MAIN__ == 4
/* TODO: Set up the required data structures here. Globals and consts only. */

/**
 * @brief DACTask executes at a fixed rate and grabs an entry from the FIFO. If
 * it gets an entry, output to the speaker.
 */
void DACTask(void) {
    /* TODO: Grab encoded data from the FIFO. */

    /* TODO: Output encoded data to the speaker. */
}

/**
 * @brief Main 4 tests the transmit pipeline of the lab. The user inputs some
 * data, the encoder loads the encoded data into a FIFO, and the DACTask should
 * retrieve that data at a fixed rate and output it to the speaker.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    /* TODO: Create your arbitrary data to encode here. */

    while (1) {
        /* TODO: Poll for user input. */

        /* TODO: Feed the input data into the encoder. */

        /* TODO: Feed the encoded data into a FIFO. */
    }
}
#elif __MAIN__ == 5
/* TODO: Set up the required data structures here. Globals and consts only. */
#define BUFFER_SIZE 512
uint16_t captureBuffer[512] = { 0 };
uint16_t captureIdx = 0;
bool result = false;

/**
 * @brief ADCTask executes at a fixed rate to capture the analog voltage from
 * the electret microphone. The task should perform an FFT on the data and see
 * if the frequency plot matches the expectation.
 * 
 */
void ADCTask(void) {
    /* TODO: Capture ADC values from the microphone and add it to the
       captureBuffer. */

    captureIdx = (captureIdx + 1) % BUFFER_SIZE;
}

/**
 * @brief Main 5 tests capturing audio output into the speaker. The students
 * should develop code to capture and log some frequency input into a buffer.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    while (1) {
        if (captureIdx == BUFFER_SIZE - 1) {
            /* TODO: Perform FFT on captureBuffer and evaluate results. */

            /* Turn on green LED if we pass this test. Turn on red LED if we fail
                this test. */
            assert(result);
        }
    }
}
#elif __MAIN__ == 6
/* TODO: Set up the required data structures here. Globals and consts only. */
bool result = true;

/**
 * @brief Main 6 tests the decoder task. Students should develop code that takes
 * some arbitrary waveform data and feeds it into the decoder, and check to see
 * if the decoded data matches the expected output.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    /* TODO: Create your arbitrary data to decode here. */

    while (1) {
        /* TODO: Feed the input data into the decoder. */

        /* TODO: Check if decoder output matches as expected. */

        /* Turn on green LED if we pass this test. Turn on red LED if we fail
           this test. */
        assert(result);
    }
}
#elif __MAIN__ == 7
/* TODO: Set up the required data structures here. Globals and consts only. */
#define BUFFER_SIZE 512
uint16_t captureBuffer[512] = { 0 };
uint16_t captureIdx = 0;
bool result = false;

/**
 * @brief ADCTask executes at a fixed rate to capture some arbitrary data. The
 * task should decode the data. 
 */
void ADCTask(void) {
    /* TODO: Load into captureBuffer some arbitrary waveform data. (Ideally with
       fake pseudonoise) */

    captureIdx = (captureIdx + 1) % BUFFER_SIZE;

    /* TODO: If we hit some condition, decode the buffer of data. */

    /* TODO: Feed the decoded data into a FIFO. */

}

/**
 * @brief Main 7 tests capturing arbitrary waveform data, decoding it, and
 * sending it to the main thread.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    while (1) {
            /* TODO: Capture decoded data from a FIFO. */

            /* TODO: Check to see if each piece of decoded data is expected. */
            
            /* Turn on green LED if we pass this test. Turn on red LED if we fail
                this test. */
            assert(result);
    }
}
#elif __MAIN__ == 8
/* TODO: Set up the required data structures here. Globals and consts only. */

/**
 * @brief Main 8 tests outputting decoded data to the LCD TFT.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    /* TODO: Create your arbitrary data to display here. */

    while (1) {
        /* TODO: Feed the decoded data into the LCD. Visually inspect the
            display to see if it looks correct. */
    }
}
#elif __MAIN__ == 9
/* TODO: Set up the required data structures here. Globals and consts only. */
#define BUFFER_SIZE 512
uint16_t captureBuffer[512] = { 0 };
uint16_t captureIdx = 0;

/**
 * @brief ADCTask executes at a fixed rate to capture the analog voltage from
 * the electret microphone. The task should decode the waveform and output the
 * decoded data to a FIFO.
 */
void ADCTask(void) {
    /* TODO: Capture ADC values from the microphone and add it to the
       captureBuffer. */

    captureIdx = (captureIdx + 1) % BUFFER_SIZE;

    /* TODO: If we hit some condition, decode the buffer of data. */

    /* TODO: Feed the decoded data into a FIFO. */

}

/**
 * @brief Main 9 tests the receive pipeline of the lab. The user captures some
 * audio in ADCTask, the decoder decodes the waveform and puts the decoded data
 * into a FIFO, and the main thread takes decoded data from the FIFO and outputs
 * it to the display.
 */
int main(void) {
    /* TODO: Set up the required initializations here.*/

    while (1) {
        /* TODO: Capture decoded data from a FIFO. */

        /* TODO: Feed the decoded data into the LCD. Visually inspect the
            display to see if it looks correct. */
    }
}
#endif