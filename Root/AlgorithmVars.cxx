/** @file AlgorithmVars.cxx
 *  @brief TL::Algorithm class TTreeReader variables implementation
 *
 *  @author Douglas Davis, <ddavis@cern.ch>
 */

#include <TopLoop/Core/Algorithm.h>
#include <TopLoop/Core/FileManager.h>

TL::StatusCode TL::Algorithm::init_core_vars() {
  if (fileManager() == nullptr) {
    logger()->error("Your algorithm has a null FileManager");
    return TL::StatusCode::FAILURE;
  }

  // this TChain::LoadTree()) call suppresses a warning from
  // TTreeReader about the entries being changed by multiple
  // controllers
  fileManager()->mainChain()->LoadTree(0);
  fileManager()->weightsChain()->LoadTree(0);
  m_reader = std::make_shared<TTreeReader>(fileManager()->mainChain());
  m_weightsReader = std::make_shared<TTreeReader>(fileManager()->weightsChain());

  if (fileManager()->particleLevelChain() != nullptr) {
    fileManager()->particleLevelChain()->LoadTree(0);
    fileManager()->truthChain()->LoadTree(0);
    m_particleLevelReader =
        std::make_shared<TTreeReader>(fileManager()->particleLevelChain());
    m_truthReader = std::make_shared<TTreeReader>(fileManager()->truthChain());
  }

  TL_CHECK(connect_default_branches());

  return TL::StatusCode::SUCCESS;
}

TL::StatusCode TL::Algorithm::connect_default_branches() {
  CONNECT_BRANCH(dsid, Int_t, m_weightsReader);
  if (isMC()) {
    CONNECT_BRANCH(totalEventsWeighted, Float_t, m_weightsReader);
    CONNECT_BRANCH(totalEvents, ULong64_t, m_weightsReader);
    CONNECT_BRANCH(totalEventsWeighted_mc_generator_weights, std::vector<float>,
                   m_weightsReader);
    CONNECT_BRANCH(names_mc_generator_weights, std::vector<std::string>, m_weightsReader);
  }

  CONNECT_BRANCH(PDFinfo_X1, std::vector<float>, m_reader);
  CONNECT_BRANCH(PDFinfo_X2, std::vector<float>, m_reader);
  CONNECT_BRANCH(PDFinfo_PDGID1, std::vector<int>, m_reader);
  CONNECT_BRANCH(PDFinfo_PDGID2, std::vector<int>, m_reader);
  CONNECT_BRANCH(PDFinfo_Q, std::vector<float>, m_reader);
  CONNECT_BRANCH(PDFinfo_XF1, std::vector<float>, m_reader);
  CONNECT_BRANCH(PDFinfo_XF2, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_mc, Float_t, m_reader);
  CONNECT_BRANCH(mc_generator_weights, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_pileup, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_EL_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_EL_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_MU_Trigger_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_MU_Trigger_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_MU_Trigger_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_globalLeptonTriggerSF_MU_Trigger_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_70, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_85, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60, Float_t, m_reader);
  CONNECT_BRANCH(weight_jvt, Float_t, m_reader);
  CONNECT_BRANCH(weight_pileup_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_pileup_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Reco_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Reco_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_ID_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_ID_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Isol_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_EL_SF_Isol_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Trigger_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Trigger_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Trigger_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Trigger_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_STAT_LOWPT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_STAT_LOWPT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_SYST_LOWPT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_ID_SYST_LOWPT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Isol_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Isol_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Isol_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_Isol_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_TTVA_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_TTVA_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_TTVA_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_MU_SF_TTVA_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_jvt_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_jvt_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_B_up, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_C_up, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_Light_up, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_B_down, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_C_down, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_eigenvars_Light_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_extrapolation_up, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_extrapolation_down, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_extrapolation_from_charm_up, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_77_extrapolation_from_charm_down, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_B_up, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_C_up, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_Light_up, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_B_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_C_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_MV2c10_Continuous_eigenvars_Light_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_B_up, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_C_up, std::vector<float>, m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_Light_up, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_B_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_C_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_eigenvars_Light_down, std::vector<float>,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_extrapolation_up, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_extrapolation_down, Float_t, m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_extrapolation_from_charm_up, Float_t,
                 m_reader);
  CONNECT_BRANCH(weight_bTagSF_DL1_HybBEff_60_extrapolation_from_charm_down, Float_t,
                 m_reader);
  CONNECT_BRANCH(eventNumber, ULong64_t, m_reader);
  CONNECT_BRANCH(runNumber, UInt_t, m_reader);
  CONNECT_BRANCH(randomRunNumber, UInt_t, m_reader);
  CONNECT_BRANCH(mcChannelNumber, UInt_t, m_reader);
  CONNECT_BRANCH(mu, Float_t, m_reader);
  CONNECT_BRANCH(backgroundFlags, UInt_t, m_reader);
  CONNECT_BRANCH(hasBadMuon, UInt_t, m_reader);
  CONNECT_BRANCH(el_pt, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_cl_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_phi, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_e, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_charge, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_topoetcone20, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_ptvarcone20, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_isTight, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_CF, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_d0sig, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_delta_z0_sintheta, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_true_type, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_origin, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_originbkg, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_typebkg, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_firstEgMotherTruthType, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_firstEgMotherTruthOrigin, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_isPrompt, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_pt, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_phi, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_e, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_charge, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_topoetcone20, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_ptvarcone30, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_isTight, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_d0sig, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_delta_z0_sintheta, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_true_type, std::vector<int>, m_reader);
  CONNECT_BRANCH(mu_true_origin, std::vector<int>, m_reader);
  CONNECT_BRANCH(mu_true_isPrompt, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_pt, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_phi, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_e, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_mv2c00, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_mv2c10, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_mv2c20, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_passfjvt, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_truthflav, std::vector<int>, m_reader);
  CONNECT_BRANCH(jet_truthPartonLabel, std::vector<int>, m_reader);
  CONNECT_BRANCH(jet_isTrueHS, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_isbtagged_MV2c10_70, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_isbtagged_MV2c10_77, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_isbtagged_MV2c10_85, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_tagWeightBin_MV2c10_Continuous, std::vector<int>, m_reader);
  CONNECT_BRANCH(jet_isbtagged_DL1_HybBEff_60, std::vector<char>, m_reader);
  CONNECT_BRANCH(jet_MV2c10mu, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_MV2c10rnn, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_DL1, std::vector<float>, m_reader);
  CONNECT_BRANCH(met_met, Float_t, m_reader);
  CONNECT_BRANCH(met_phi, Float_t, m_reader);
  CONNECT_BRANCH(all_particle, Int_t, m_reader);
  CONNECT_BRANCH(leptonic_2015, Int_t, m_reader);
  CONNECT_BRANCH(leptonic_2016, Int_t, m_reader);
  CONNECT_BRANCH(leptonic_2017, Int_t, m_reader);
  CONNECT_BRANCH(leptonic_2018, Int_t, m_reader);
  CONNECT_BRANCH(ee_2015, Int_t, m_reader);
  CONNECT_BRANCH(ee_2016, Int_t, m_reader);
  CONNECT_BRANCH(ee_2017, Int_t, m_reader);
  CONNECT_BRANCH(ee_2018, Int_t, m_reader);
  CONNECT_BRANCH(mumu_2015, Int_t, m_reader);
  CONNECT_BRANCH(mumu_2016, Int_t, m_reader);
  CONNECT_BRANCH(mumu_2017, Int_t, m_reader);
  CONNECT_BRANCH(mumu_2018, Int_t, m_reader);
  CONNECT_BRANCH(ejets_2015, Int_t, m_reader);
  CONNECT_BRANCH(ejets_2016, Int_t, m_reader);
  CONNECT_BRANCH(ejets_2017, Int_t, m_reader);
  CONNECT_BRANCH(ejets_2018, Int_t, m_reader);
  CONNECT_BRANCH(mujets_2015, Int_t, m_reader);
  CONNECT_BRANCH(mujets_2016, Int_t, m_reader);
  CONNECT_BRANCH(mujets_2017, Int_t, m_reader);
  CONNECT_BRANCH(mujets_2018, Int_t, m_reader);
  CONNECT_BRANCH(emu_2015, Int_t, m_reader);
  CONNECT_BRANCH(emu_2016, Int_t, m_reader);
  CONNECT_BRANCH(emu_2017, Int_t, m_reader);
  CONNECT_BRANCH(emu_2018, Int_t, m_reader);
  CONNECT_BRANCH(eee_2015, Int_t, m_reader);
  CONNECT_BRANCH(eee_2016, Int_t, m_reader);
  CONNECT_BRANCH(eee_2017, Int_t, m_reader);
  CONNECT_BRANCH(eee_2018, Int_t, m_reader);
  CONNECT_BRANCH(eemu_2015, Int_t, m_reader);
  CONNECT_BRANCH(eemu_2016, Int_t, m_reader);
  CONNECT_BRANCH(eemu_2017, Int_t, m_reader);
  CONNECT_BRANCH(eemu_2018, Int_t, m_reader);
  CONNECT_BRANCH(emumu_2015, Int_t, m_reader);
  CONNECT_BRANCH(emumu_2016, Int_t, m_reader);
  CONNECT_BRANCH(emumu_2017, Int_t, m_reader);
  CONNECT_BRANCH(emumu_2018, Int_t, m_reader);
  CONNECT_BRANCH(mumumu_2015, Int_t, m_reader);
  CONNECT_BRANCH(mumumu_2016, Int_t, m_reader);
  CONNECT_BRANCH(mumumu_2017, Int_t, m_reader);
  CONNECT_BRANCH(mumumu_2018, Int_t, m_reader);
  CONNECT_BRANCH(HLT_e60_lhmedium_nod0, Char_t, m_reader);
  CONNECT_BRANCH(HLT_mu26_ivarmedium, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e26_lhtight_nod0_ivarloose, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e140_lhloose_nod0, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e120_lhloose, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e24_lhmedium_L1EM20VH, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e24_lhmedium_nod0_L1EM18VH, Char_t, m_reader);
  CONNECT_BRANCH(HLT_mu50, Char_t, m_reader);
  CONNECT_BRANCH(HLT_mu24, Char_t, m_reader);
  CONNECT_BRANCH(HLT_e60_lhmedium, Char_t, m_reader);
  CONNECT_BRANCH(HLT_mu20_iloose_L1MU15, Char_t, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e60_lhmedium_nod0, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e120_lhloose, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e24_lhmedium_L1EM20VH, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e60_lhmedium, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e26_lhtight_nod0_ivarloose, std::vector<char>, m_reader);
  CONNECT_BRANCH(el_trigMatch_HLT_e140_lhloose_nod0, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_trigMatch_HLT_mu26_ivarmedium, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_trigMatch_HLT_mu50, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_trigMatch_HLT_mu24, std::vector<char>, m_reader);
  CONNECT_BRANCH(mu_trigMatch_HLT_mu20_iloose_L1MU15, std::vector<char>, m_reader);
  CONNECT_BRANCH(lbn, UInt_t, m_reader);
  CONNECT_BRANCH(Vtxz, Float_t, m_reader);
  CONNECT_BRANCH(npVtx, UInt_t, m_reader);
  CONNECT_BRANCH(el_d0pv, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_z0pv, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_d0sigpv, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_z0sigpv, std::vector<float>, m_reader);

  CONNECT_BRANCH(el_true_pdg, std::vector<int>, m_reader);
  CONNECT_BRANCH(el_true_pt, std::vector<float>, m_reader);
  CONNECT_BRANCH(el_true_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_d0pv, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_z0pv, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_d0sigpv, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_z0sigpv, std::vector<float>, m_reader);

  // for old ntuples these branches were bool
  if (static_cast<std::size_t>(fileManager()->getSgTopNtupVersion()) <
      static_cast<std::size_t>(TL::kSgTopNtup::v28)) {
    CONNECT_BRANCH(el_trigMatch_old, std::vector<bool>, m_reader);
    CONNECT_BRANCH(el_tight_old, std::vector<bool>, m_reader);
    CONNECT_BRANCH(mu_trigMatch_old, std::vector<bool>, m_reader);
    CONNECT_BRANCH(mu_tight_old, std::vector<bool>, m_reader);
  }
  else {
    CONNECT_BRANCH(el_trigMatch, std::vector<char>, m_reader);
    CONNECT_BRANCH(el_tight, std::vector<char>, m_reader);
    CONNECT_BRANCH(mu_trigMatch, std::vector<char>, m_reader);
    CONNECT_BRANCH(mu_tight, std::vector<char>, m_reader);
  }

  CONNECT_BRANCH(mu_true_pdg, std::vector<int>, m_reader);
  CONNECT_BRANCH(mu_true_pt, std::vector<float>, m_reader);
  CONNECT_BRANCH(mu_true_eta, std::vector<float>, m_reader);
  CONNECT_BRANCH(jet_m, std::vector<float>, m_reader);
  CONNECT_BRANCH(met_px, Float_t, m_reader);
  CONNECT_BRANCH(met_py, Float_t, m_reader);
  CONNECT_BRANCH(met_sumet, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Reco_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Reco_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_ID_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_ID_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Isol_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_EL_SF_Isol_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Trigger_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_STAT_LOWPT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_STAT_LOWPT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_SYST_LOWPT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_ID_SYST_LOWPT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Isol_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Isol_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Isol_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_Isol_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_TTVA_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_TTVA_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_TTVA_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_leptonSF_tight_MU_SF_TTVA_SYST_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_EL_SF_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_EL_SF_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_STAT_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_STAT_DOWN, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_SYST_UP, Float_t, m_reader);
  CONNECT_BRANCH(weight_triggerSF_tight_MU_SF_Trigger_SYST_DOWN, Float_t, m_reader);

  if (m_particleLevelReader) {
    CONNECT_PL_BRANCH(weight_mc, Float_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eventNumber, ULong64_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(runNumber, UInt_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(randomRunNumber, UInt_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mcChannelNumber, UInt_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu, Float_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(weight_pileup, Float_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_pt, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_eta, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_phi, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_e, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_charge, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_pt_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_eta_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_phi_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(el_e_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_pt, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_eta, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_phi, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_e, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_charge, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_pt_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_eta_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_phi_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mu_e_bare, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_pt, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_eta, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_phi, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_e, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_nGhosts_bHadron, std::vector<int>, m_particleLevelReader);
    CONNECT_PL_BRANCH(jet_nGhosts_cHadron, std::vector<int>, m_particleLevelReader);
    CONNECT_PL_BRANCH(met_met, Float_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(met_phi, Float_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_X1, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_X2, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_PDGID1, std::vector<int>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_PDGID2, std::vector<int>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_Q, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_XF1, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(PDFinfo_XF2, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(mc_generator_weights, std::vector<float>, m_particleLevelReader);
    CONNECT_PL_BRANCH(all_particle, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(leptonic_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(leptonic_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(leptonic_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(leptonic_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ee_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ee_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ee_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ee_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumu_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumu_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumu_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumu_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ejets_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ejets_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ejets_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(ejets_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mujets_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mujets_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mujets_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mujets_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emu_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emu_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emu_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emu_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eee_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eee_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eee_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eee_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eemu_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eemu_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eemu_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(eemu_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emumu_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emumu_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emumu_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(emumu_2018, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumumu_2015, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumumu_2016, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumumu_2017, Int_t, m_particleLevelReader);
    CONNECT_PL_BRANCH(mumumu_2018, Int_t, m_particleLevelReader);
  }

  if (m_truthReader) {
    CONNECT_TRUTH_BRANCH(weight_mc, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(eventNumber, ULong64_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(runNumber, UInt_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(mu, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(weight_pileup, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(randomRunNumber, UInt_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(mcChannelNumber, UInt_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_tbar_pdgId, Int_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_t_pdgId, Int_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_tbar_pdgId, Int_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_t_pdgId, Int_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_tbar_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_t_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_t_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_tbar_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_tbar_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_tbar_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_t_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_t_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_tbar_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_tbar_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_tbar_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_t_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_t_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_tbar_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_beforeFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_beforeDecay_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_beforeFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_beforeDecay_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_beforeFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_beforeFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_beforeFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_beforeFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_SC_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_t_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_t_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_tbar_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_beforeFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_beforeDecay_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_ttbar_afterFSR_beforeDecay_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_t_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_SC_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_beforeFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_SC_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_afterFSR_SC_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_tbar_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_beforeFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_t_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_beforeFSR_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_SC_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_tbar_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_t_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_t_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_beforeFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_tbar_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay1_from_t_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_SC_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_t_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_SC_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_b_from_tbar_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_tbar_afterFSR_SC_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_t_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_Wdecay2_from_t_phi, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_tbar_m, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_tbar_eta, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_t_beforeFSR_pt, Float_t, m_truthReader);
    CONNECT_TRUTH_BRANCH(MC_W_from_tbar_phi, Float_t, m_truthReader);
  }

  return TL::StatusCode::SUCCESS;
}
