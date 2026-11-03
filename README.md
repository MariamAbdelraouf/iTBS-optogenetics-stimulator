The iTBS Optogenetic Stimulator is an Arduino Nano–based electronic control system developed to generate precisely timed stimulation patterns based on the intermittent Theta Burst Stimulation (iTBS) protocol.

The prototype integrates electronic control, visual indicators, an audible notification system, and a manually operated push button into a compact, 3D-printed enclosure.

The Arduino controls the timing sequence, while the LEDs provide visual feedback to monitor protocol execution.
The system was designed as a programmable and portable controller for demonstrating and testing optogenetic stimulation timing.

Hardware Components
The prototype consists of the following components:

Component           Function

Arduino Nano:         Main microcontroller responsible for generating and controlling the iTBS sequence
White LED:            Visual representation of the stimulation pulses
Red LED:              Indicates the beginning and completion of the protocol
Push Button:          Starts, pauses, and resumes the stimulation sequence
Buzzer:               Provides audible notifications at the beginning and end
330 Ω Resistor:       Limits current through the white LED
220 Ω Resistor:        Limits current through the red LED
Mini Breadboard:       Supports circuit assembly and component connections
USB Cable:             Supplies power and allows Arduino programming
Jumper Wires:           Connect the electronic components
3D-Printed Enclosure:   Houses and protects the prototype

------------------

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

1. Press the button to start the protocol.
2. Red LED and buzzer activate three times.
3. White LED follows the programmed iTBS pulse sequence.
4. The system automatically executes stimulation and rest intervals.
3. Press the button to pause or resume.
4. Red LED and buzzer signal session completion.

Physical Implementation

The circuit was assembled using an Arduino Nano and a mini breadboard, then integrated into a compact 3D-printed enclosure with accessible controls and LED indicators.
The white LED demonstrates the stimulation timing; it is not a calibrated 470 nm optogenetic light source.
