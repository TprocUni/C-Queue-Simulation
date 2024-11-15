# C-Queue-Simulation
This project implements a **C-based traffic simulation system** using queue data structures to model vehicle behavior and diagnostic functions to evaluate traffic efficiency. The system tracks vehicle arrival, waiting, and clearance times, simulating traffic flow under varying conditions such as arrival rates and traffic light timings. 


### System Design and Implementation

#### 1. Queue Management

Queues are central to the simulation, representing vehicles arriving at traffic lights. A custom queue implementation was developed using arrays with a fixed size (`SIZE`) and two pointers:

1. **emptyQueue**:
   - Clears residual data in memory by populating the array with `-1`, ensuring consistent simulation behavior.

2. **enqueue**:
   - Appends new vehicles to the queue. FIFO (First-In-First-Out) behavior is enforced by updating the rear pointer, which tracks the end of the queue.

3. **dequeue**:
   - Removes vehicles from the front of the queue by incrementing the front pointer.

4. **printQ**:
   - Debugging tool that prints the queue contents with indices for monitoring simulation states.

By maintaining individual queues for left and right lanes, the system can simulate independent traffic flows for each direction.

#### 2. Vehicle Representation

Vehicles are represented as numerical values in the queue, tracking their waiting time:

- Each vehicle starts with a value of `0`, incrementing by `1` for every simulation iteration it spends in the queue.
- A helper function, **turnIncrement**, ensures all vehicles in the queue have their waiting times updated in each iteration.

#### 3. Traffic Lights

Traffic lights are modeled using an enumerated type (`lightColours`) with states `Red` and `Green`:

1. **swapLights**:
   - Toggles the light states for both lanes simultaneously, simulating real-world traffic light changes.

2. **printLights**:
   - Outputs the current state of the lights for debugging purposes.

The use of enums instead of integers improves code readability and allows for future expansion, such as the addition of an amber light state.

#### 4. Diagnostics

Diagnostic functions provide insights into traffic flow and efficiency for each queue:

1. **Number of Vehicles**:
   - Counts the total number of vehicles processed in a queue by iterating until a `-1` marker is found.

2. **Average Waiting Time**:
   - Calculates the average time vehicles spend in the queue by summing their waiting times and dividing by the total vehicle count.

3. **Maximum Waiting Time**:
   - Finds the vehicle with the longest waiting time in the queue.

4. **Clearance Time**:
   - Measures the number of iterations required to clear the queue after vehicles stop arriving.

These diagnostics allow the system to assess traffic performance under different scenarios.

---

### Experimentation

#### Simulation Setup

A secondary program, **runSimulations**, automates 100 iterations of the simulation and aggregates the results for both left and right queues. Key parameters include:

- **Arrival Rate**: The frequency of vehicle arrivals.
- **Traffic Light Period**: The duration each light remains green before switching.

The data from individual runs is stored in a text file, processed to calculate average diagnostic values.

#### Key Findings

1. **Balanced Arrival Rates**:
   - Arrival rates between 3 and 6 provided optimal performance, minimizing waiting times and balancing traffic flow.
   - When one lane had significantly higher traffic, extending the green light duration for that lane improved efficiency.

2. **Light Period Optimization**:
   - Longer intervals (e.g., 10 iterations) reduced average waiting times in high-traffic scenarios by minimizing the time wasted during light transitions.

---

### Testing and Results

The system was tested under various parameter configurations, demonstrating its flexibility and robustness:

1. **Scenario 1**:
   - Parameters: Arrival rate = 0.5, Light period = 5.
   - Result: Moderate traffic efficiency with balanced waiting times.

2. **Scenario 2**:
   - Parameters: Arrival rate = 0.6, Light period = 10.
   - Result: Improved clearance and reduced average waiting times for higher traffic volumes.

3. **Scenario 3**:
   - Parameters: Arrival rate = 0.6 (left), 1.0 (right), Light period = 10.
   - Result: Optimized performance with adaptive light periods for the heavier traffic side.

---

### Conclusion

This traffic simulation system models real-world scenarios effectively by leveraging custom queue structures, diagnostic functions, and adjustable parameters. It offers a flexible framework for studying traffic patterns and optimizing light periods and arrival rates to improve flow efficiency. The modular design and comprehensive diagnostics make it a practical tool for analyzing and managing traffic systems in simulated environments.
