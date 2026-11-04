The iTBS Optogenetic Stimulator is an Arduino Nano–based electronic control system developed to generate precisely timed stimulation patterns based on the intermittent Theta Burst Stimulation (iTBS) protocol.

The prototype integrates electronic control, visual indicators, an audible notification system, and a manually operated push button into a compact, 3D-printed enclosure.

The Arduino controls the timing sequence, while the LEDs provide visual feedback to monitor protocol execution.
The system was designed as a programmable and portable controller for demonstrating and testing optogenetic stimulation timing.

Hardware Components
The prototype consists of the following components:

Component           Function

1. Arduino Nano:         Main microcontroller responsible for generating and controlling the iTBS sequence

2. White LED:            Visual representation of the stimulation pulses

3. Red LED:              Indicates the beginning and completion of the protocol

4. Push Button:          Starts, pauses, and resumes the stimulation sequence

5. Buzzer:               Provides audible notifications at the beginning and end

6. 330 Ω Resistor:       Limits current through the white LED

7. 220 Ω Resistor:        Limits current through the red LED

8. Mini Breadboard:       Supports circuit assembly and component connections

9. USB Cable:             Supplies power and allows Arduino programming

10. Jumper Wires:           Connect the electronic components

11. 3D-Printed Enclosure:   Houses and protects the prototype


iTBS Protocol
Parameter           Value
Pulses per burst:      3
Pulse duration:       10 ms
Pulse spacing:         50 ms
Bursts per train:       10
Inter-burst separation: 100 ms
Rest after train:     8 seconds
Trains per block:       20
Blocks per session:     5
Rest between blocks:    120 seconds
Target session duration: Approximately 27 minutes, subject to verification against the implemented timing.

System Operation
Controls
- At idle: one press starts. Red LED and buzzer pulse three times before stimulation.
- While running: one press pauses. All outputs turn off immediately.
- While paused: two presses within 400 ms resume the interrupted phase. One press while paused does nothing alone.
- At completion: Red LED and buzzer pulse three times, then the controller returns to idle.

Requested timing
- Each burst: 3 pulses of 10 ms at 50 ms between pulse starts (50 ms OFF between pulses).
- 10 bursts per train; 100 ms gap after the third pulse of a burst, except after the final burst in the train.
- 8 s rest after every train, including the last train in each block.
- 20 trains per block, 5 blocks, 120 s between blocks.
- Total: 3,000 pulses. With these explicit gap definitions, the calculated full sequence is 24 min 40 s, plus 3.6 s for the start/end markers; not 27 minutes. Pauses add time. Recheck the source protocol if the intended session is 27 minutes.
Physical Implementation

The circuit was assembled using an Arduino Nano and a mini breadboard, then integrated into a compact 3D-printed enclosure with accessible controls and LED indicators.
The white LED demonstrates the stimulation timing; it is not a calibrated 470 nm optogenetic light source.
