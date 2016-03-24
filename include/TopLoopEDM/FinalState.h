/** @file  FinalState.h
 *  @brief TL::EDM::FinalState class header
 *  @class TL::EDM::FinalState
 *  @brief A container of final state information
 *
 *  This class is part of the TopLoop event data model (EDM). It
 *  contains the information about a final state.
 *
 *  @author Douglas Davis < douglas.davis@cern.ch >
 */

#ifndef TL_EDM_FinalState_h
#define TL_EDM_FinalState_h

#include <TopLoopEDM/LeptonPair.h>
#include <TopLoopEDM/Jet.h>
#include <TopLoopEDM/MET.h>

namespace TL {
  namespace EDM {

    class FinalState : public TObject {
    private:
      std::vector<TL::EDM::Lepton> m_leptons;
      std::vector<TL::EDM::Jet>    m_jets;
      TL::EDM::MET                 m_MET;

      std::vector<TL::EDM::LeptonPair> m_leptonPairs;
      
      float  m_M;
      size_t m_llidx;
      size_t m_ljidx;
      
      ClassDef(FinalState,1);
      
    public:
      FinalState() :
	m_leptons(), m_jets(), m_MET(), m_leptonPairs(),
	m_M(0), m_llidx(0), m_ljidx(0)
      {}
      virtual ~FinalState() {}

      void addLepton(const TL::EDM::Lepton& lep);
      void addJet(const TL::EDM::Jet& jet);
      void setMET(const TL::EDM::MET& met);

      void addLeptonPair(const TL::EDM::LeptonPair& lp);

      void addLeptonPairs(const std::initializer_list<TL::EDM::LeptonPair>& lps);

      void evaluateLepPairs();
      void evaluateSelf();
      void clear();
      
      const std::vector<TL::EDM::Lepton>&     leptons()     const;
      const std::vector<TL::EDM::Jet>&        jets()        const;
      const std::vector<TL::EDM::LeptonPair>& leptonPairs() const;
      
      float M() const;

      size_t leadingLeptonIdx() const;
      size_t leadingJetIdx()    const;
      
    };

  }
}

inline void TL::EDM::FinalState::addLepton(const TL::EDM::Lepton& lep) { m_leptons.emplace_back(lep); }
inline void TL::EDM::FinalState::addJet(const TL::EDM::Jet& jet)       { m_jets.emplace_back(jet);    }
inline void TL::EDM::FinalState::setMET(const TL::EDM::MET& met)       { m_MET = met;                 }

inline void TL::EDM::FinalState::addLeptonPair(const TL::EDM::LeptonPair& lp) {
  m_leptonPairs.emplace_back(lp);
}

inline void TL::EDM::FinalState::addLeptonPairs(const std::initializer_list<TL::EDM::LeptonPair>& lps) {
  for ( auto const& lp : lps ) {
    m_leptonPairs.emplace_back(lp);
  }
}

inline void TL::EDM::FinalState::clear() {
  m_leptons.clear();
  m_jets.clear();
  m_leptonPairs.clear();
}


inline const std::vector<TL::EDM::Lepton>& TL::EDM::FinalState::leptons() const { return m_leptons; }
inline const std::vector<TL::EDM::Jet>&    TL::EDM::FinalState::jets()    const { return m_jets;    }

inline const std::vector<TL::EDM::LeptonPair>& TL::EDM::FinalState::leptonPairs() const {
  return m_leptonPairs;
}

inline float TL::EDM::FinalState::M() const { return m_M; }

inline size_t TL::EDM::FinalState::leadingLeptonIdx() const { return m_llidx; }
inline size_t TL::EDM::FinalState::leadingJetIdx()    const { return m_ljidx; }

#endif
