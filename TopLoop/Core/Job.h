/** @file  Job.h
 *  @brief TL::Job class header
 *  @class TL::Job
 *  @brief Job handler.
 *
 *  This class handles the running of the TL::AlgBase algorithm.
 *
 *  @author Douglas Davis < douglas.davis@cern.ch >
 *  @author Kevin Finelli < kevin.finelli@cern.ch >
 */

#ifndef TL_Job_h
#define TL_Job_h

namespace TL {
  class AlgBase;
}

namespace TL {

  class Job {

  protected:
    TL::AlgBase* m_analysis;
    bool         m_particleLevelRun;

  public:
    Job() :
      m_analysis(nullptr),
      m_particleLevelRun(false)
    {}
    Job(TL::AlgBase* ab) :
      m_analysis(ab),
      m_particleLevelRun(false)
    {}
    virtual ~Job() {}

    void setParticleLevelRun();
    void run();

  };

}

inline void TL::Job::setParticleLevelRun() {
  m_particleLevelRun = true;
}

#endif
