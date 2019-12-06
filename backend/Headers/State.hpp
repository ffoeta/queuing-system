#ifndef ITERATION_HPP
#define ITERATION_HPP

#include <vector>

class State {
public:
    State(std::vector<float> average_probability_of_failure,
                std::vector<float> average_waited_on_buffer_per_source,
                std::vector<float> average_spend_on_device, 
                std::vector<float> average_spend_in_system);

    std::vector<float> getDroppProbability();
    std::vector<float> getAverageWaitTime();
    std::vector<float> getAverageDeviceTime();
    std::vector<float> getAverageInSystem();

private:
    std::vector<float> average_probability_of_failure_;
    std::vector<float> average_waited_on_buffer_per_source_;
    std::vector<float> average_spend_on_device_;
    std::vector<float> average_spend_in_system_;
};


#endif
