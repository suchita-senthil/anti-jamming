Demonstration of a simple anti-jamming communication system using ESP8266 modules. 

This prototype uses multiple Wi-Fi channels on the ESP8266 and performs dynamic channel switching whenever jamming is detected. A real-world implementation would extend this idea across multiple frequency bands, ensuring communication can continue even under stronger or wider-band jamming attacks.

Working of the System:
1. Transmitter sends packets over a chosen Wi-Fi channel.
2. Receiver monitors signal quality and identifies sudden drops (possible jamming).
3. If jamming is detected, the Transmitter and Receiver switch to a new channel.
4. Jammer ESP8266 continuously transmits noise on the target channel to simulate interference.
