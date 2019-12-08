#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

class State {
public:
    State(std::vector<float> average_probability_of_failure,
                std::vector<float> average_waited_on_buffer_per_source,
                std::vector<float> average_spend_on_device, 
                std::vector<float> average_spend_in_system);

    std::vector<float> _getDroppProbability();
    std::vector<float> _getAverageWaitTime();
    std::vector<float> _getAverageDeviceTime();
    std::vector<float> _getAverageInSystem();

private:
    std::vector<float> average_probability_of_failure_;
    std::vector<float> average_waited_on_buffer_per_source_;
    std::vector<float> average_spend_on_device_;
    std::vector<float> average_spend_in_system_;
};


#endif
