#pragma once

// Standard C++ includes
#include <fstream>

//----------------------------------------------------------------------------
// SpikeCSVRecorder
//----------------------------------------------------------------------------
class SpikeCSVRecorder
{
public:
    SpikeCSVRecorder(const char *filename, const unsigned int *spkCnt, const unsigned int *spk)
    : m_Stream(filename), m_SpkCnt(spkCnt), m_Spk(spk)
    {
        // Set precision 
        m_Stream.precision(16);

        m_Stream << "Time [ms], Neuron ID" << std::endl;
    }

    //----------------------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------------------
    void record(double t)
    {
        for(unsigned int i = 0; i < m_SpkCnt[0]; i++)
        {
            m_Stream << t << "," << m_Spk[i] << std::endl;
        }
    }
private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    std::ofstream m_Stream;
    const unsigned int *m_SpkCnt;
    const unsigned int *m_Spk;
};
