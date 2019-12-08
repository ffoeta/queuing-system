#include "../headers/State.hpp"

    State::State(std::vector<float> average_probability_of_failure,
                        std::vector<float> average_waited_on_buffer_per_source,
                        std::vector<float> average_spend_on_device,
                        std::vector<float> average_spend_in_system) :
        average_probability_of_failure_(average_probability_of_failure), average_waited_on_buffer_per_source_(average_waited_on_buffer_per_source),
        average_spend_on_device_(average_spend_on_device), average_spend_in_system_(average_spend_in_system)
    {};

    std::vector<float> State::_getDroppProbability() 
    {
        return this -> average_probability_of_failure_;
    }

    std::vector<float> State::_getAverageWaitTime() 
    {
        return this -> average_waited_on_buffer_per_source_;
    }

    std::vector<float> State::_getAverageDeviceTime() 
    {
        return this -> average_spend_on_device_;
    }

    std::vector<float> State::_getAverageInSystem() 
    {
        return this -> average_spend_in_system_;
    }
    