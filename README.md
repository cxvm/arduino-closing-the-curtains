# Clap-Activated Stepper Motor

Control a stepper motor with claps: two claps in a row toggle the motor on/off. Status is shown via an RGB LED.

## How it works

- A microphone module (digital output) detects sound spikes.
- If exactly 2 claps are detected within a 400 ms window (with at least 50 ms between them, to filter out bounce/echo), the motor state toggles (`status_lights`).
- While the motor is on, it rotates through an 8-step half-step sequence with a `dl = 2` ms delay between steps.
- The LED shows the current state: red — motor off, green — motor running.

## Hardware

| Component | Connection |
|---|---|
| Microphone module (digital output) | Pin 8 |
| Stepper motor driver (4-phase) | Pins 2, 3, 4, 5 |
| RGB LED — red | Pin 9 |
| RGB LED — green | Pin 10 |
| RGB LED — blue | Pin 11 |

## Configuration

- `dl` — delay between motor steps (ms). Lower value = faster rotation.
- `detection_range >= 50` — minimum interval between claps, to avoid counting one clap twice.
- `detection_range_start >= 400` — time window within which both claps must occur.

## Uploading

Open the `.ino` file in Arduino IDE, select your board and port, then Upload.

## Possible improvements

- Use claps to control rotation direction (e.g., 1 clap — forward, 3 claps — reverse).
- Add speed control via a potentiometer.
- The blue LED channel is currently unused — could be repurposed for error indication.
