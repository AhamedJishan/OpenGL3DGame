#pragma once
#include <iostream>
#include <random>
#include <ctime>

class Random
{
public:
    // Delete copy constructor and assignment operator to prevent copying
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    // Static method to access the singleton instance
    static Random& GetInstance()
    {
        static Random instance;  // Initialized on first call
        return instance;
    }

    // Method to generate a random integer between min and max
    int RandomInt(int min, int max)
    {
        std::uniform_int_distribution<int> distrib(min, max);
        return distrib(m_rng);
    }

    // Method to generate a random float between min and max
    float RandomFloat(float min, float max)
    {
        if (min > max) std::swap(min, max);  // Swap if min > max
        std::uniform_real_distribution<float> distrib(min, max);
        return distrib(m_rng);
    }

private:
    // Private constructor
    Random()
    {
        // Seed the random number generator with the current time
        m_rng.seed(static_cast<unsigned>(std::time(nullptr)));
    }

    // Mersenne Twister random number engine
    std::mt19937 m_rng;
};