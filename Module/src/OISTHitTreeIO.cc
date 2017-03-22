#include "OISTHitTreeIO.hh"
#include "G4SystemOfUnits.hh"
#include "TTree.h"
#include "DetectorHit.hh"

namespace oistapp
{

OISTHitTreeIO::OISTHitTreeIO()
  : hittree_(nullptr)
{
}

OISTHitTreeIO::~OISTHitTreeIO() = default;

void OISTHitTreeIO::defineBranches()
{
  hittree_->Branch("eventid",        &eventid_,        "eventid/L");
  hittree_->Branch("ihit",           &ihit_,           "ihit/S");
  hittree_->Branch("num_hits",       &num_hits_,       "num_hits/I");
  
  // measured data
  hittree_->Branch("exptime",           &exptime_,           "exptime/l");
  hittree_->Branch("time",           &time_,           "time/L");
  hittree_->Branch("instrument",     &instrument_,     "instrument/S");
  hittree_->Branch("detector",       &detector_,       "detector/S");
  hittree_->Branch("det_section",    &det_section_,    "det_section/S");
  hittree_->Branch("readout_module", &readout_module_, "readout_module/S");
  hittree_->Branch("section",        &section_,        "section/S");
  hittree_->Branch("channel",        &channel_,        "channel/S");
  hittree_->Branch("pixelx",         &pixelx_,         "pixelx/S");
  hittree_->Branch("pixely",         &pixely_,         "pixely/S");
  hittree_->Branch("rawpha",         &rawpha_,         "rawpha/I");
  hittree_->Branch("pha",            &pha_,            "pha/F");
  hittree_->Branch("epi",            &epi_,            "epi/F");
  hittree_->Branch("flag_data",      &flag_data_,      "flag_data/l");
  hittree_->Branch("flags",          &flags_,          "flags/l");
  
  // simulation
  hittree_->Branch("real_time",      &real_time_,      "real_time/F");
  hittree_->Branch("time_group",     &time_group_,     "time_group/S");
  hittree_->Branch("real_posx",      &real_posx_,      "real_posx/F");
  hittree_->Branch("real_posy",      &real_posy_,      "real_posy/F");
  hittree_->Branch("real_posz",      &real_posz_,      "real_posz/F");
  hittree_->Branch("edep",           &edep_,           "edep/F");
  hittree_->Branch("echarge",        &echarge_,        "echarge/F");
  hittree_->Branch("process",        &process_,        "process/i");

  // reconstructed
  hittree_->Branch("energy",         &energy_,         "energy/F");
  hittree_->Branch("posx",           &posx_,           "posx/F");
  hittree_->Branch("posy",           &posy_,           "posy/F");
  hittree_->Branch("posz",           &posz_,           "posz/F");
  hittree_->Branch("local_posx",     &local_posx_,     "local_posx/F");
  hittree_->Branch("local_posy",     &local_posy_,     "local_posy/F");
  hittree_->Branch("local_posz",     &local_posz_,     "local_posz/F");
  hittree_->Branch("grade",          &grade_,          "grade/I");
}

void OISTHitTreeIO::setBranchAddresses()
{
  hittree_->SetBranchAddress("eventid",        &eventid_);
  hittree_->SetBranchAddress("ihit",           &ihit_);
  hittree_->SetBranchAddress("num_hits",       &num_hits_);

  // measured data
  hittree_->SetBranchAddress("exptime",           &exptime_);
  hittree_->SetBranchAddress("time",           &time_);
  hittree_->SetBranchAddress("instrument",     &instrument_);
  hittree_->SetBranchAddress("detector",       &detector_);
  hittree_->SetBranchAddress("det_section",    &det_section_);
  hittree_->SetBranchAddress("readout_module", &readout_module_);
  hittree_->SetBranchAddress("section",        &section_);
  hittree_->SetBranchAddress("channel",        &channel_);
  hittree_->SetBranchAddress("pixelx",         &pixelx_);
  hittree_->SetBranchAddress("pixely",         &pixely_);
  hittree_->SetBranchAddress("rawpha",         &rawpha_);
  hittree_->SetBranchAddress("pha",            &pha_);
  hittree_->SetBranchAddress("epi",            &epi_);
  hittree_->SetBranchAddress("flag_data",      &flag_data_);
  hittree_->SetBranchAddress("flags",          &flags_);

  // simulation
  hittree_->SetBranchAddress("real_time",      &real_time_);
  hittree_->SetBranchAddress("time_group",     &time_group_);
  hittree_->SetBranchAddress("real_posx",      &real_posx_);
  hittree_->SetBranchAddress("real_posy",      &real_posy_);
  hittree_->SetBranchAddress("real_posz",      &real_posz_);
  hittree_->SetBranchAddress("edep",           &edep_);
  hittree_->SetBranchAddress("echarge",        &echarge_);
  hittree_->SetBranchAddress("process",        &process_);

  // reconstructed
  hittree_->SetBranchAddress("energy",         &energy_);
  hittree_->SetBranchAddress("posx",           &posx_);
  hittree_->SetBranchAddress("posy",           &posy_);
  hittree_->SetBranchAddress("posz",           &posz_);
  hittree_->SetBranchAddress("local_posx",     &local_posx_);
  hittree_->SetBranchAddress("local_posy",     &local_posy_);
  hittree_->SetBranchAddress("local_posz",     &local_posz_);
  hittree_->SetBranchAddress("grade",          &grade_);
}

void OISTHitTreeIO::fillHits(const int64_t eventID,
			     const uint64_t exptime,
                         const std::vector<comptonsoft::DetectorHit_sptr>& hits)
{
  const int NumHits = hits.size();
  num_hits_ = NumHits;

  for (int i=0; i<NumHits; i++) {
    const comptonsoft::DetectorHit_sptr& hit = hits[i];
    eventid_ = (eventID >= 0) ? eventID : hit->EventID();
    ihit_ = i;

    time_ = hit->Time()/ second;
    exptime_ = exptime;
    instrument_ = hit->InstrumentID();
    detector_ = hit->DetectorID();
    det_section_ = hit->DetectorChannelSection();
    readout_module_ = hit->ReadoutModuleID();
    section_ = hit->ReadoutChannelSection();
    channel_ = hit->ReadoutChannelIndex();
    pixelx_ = hit->PixelX();
    pixely_ = hit->PixelY();
    rawpha_ = hit->RawPHA();
    pha_ = hit->PHA();
    epi_ = hit->EPI() / keV;
    flag_data_ = hit->FlagData();
    flags_ = hit->Flags();
    real_time_ = hit->RealTime() / second;
    time_group_ = hit->TimeGroup();
    real_posx_ = hit->RealPositionX() / cm;
    real_posy_ = hit->RealPositionY() / cm;
    real_posz_ = hit->RealPositionZ() / cm;
    edep_ = hit->EnergyDeposit() / keV;
    echarge_ = hit->EnergyCharge() / keV;
    process_ = hit->Process();
    energy_ = hit->Energy() / keV;
    posx_ = hit->PositionX() / cm;
    posy_ = hit->PositionY() / cm;
    posz_ = hit->PositionZ() / cm;
    local_posx_ = hit->LocalPositionX() / cm;
    local_posy_ = hit->LocalPositionY() / cm;
    local_posz_ = hit->LocalPositionZ() / cm;
    grade_ = hit->Grade();
    
    hittree_->Fill();
  }
}

comptonsoft::DetectorHit_sptr OISTHitTreeIO::retrieveHit() const
{
  comptonsoft::DetectorHit_sptr hit(new comptonsoft::DetectorHit);
  hit->setEventID(eventid_);
  hit->setTime(time_ * second);
  hit->setInstrumentID(instrument_);
  hit->setDetectorChannel(detector_, det_section_, channel_);
  hit->setReadoutChannel(readout_module_, section_, channel_);
  hit->setPixel(pixelx_, pixely_);
  hit->setRawPHA(rawpha_);
  hit->setPHA(pha_);
  hit->setEPI(epi_ * keV);
  hit->setFlagData(flag_data_);
  hit->setFlags(flags_);
  hit->setRealTime(real_time_ * second);
  hit->setTimeGroup(time_group_);
  hit->setRealPosition(real_posx_ * cm, real_posy_ * cm, real_posz_ * cm);
  hit->setEnergyDeposit(edep_ * keV);
  hit->setEnergyCharge(echarge_ * keV);
  hit->setProcess(process_);
  hit->setEnergy(energy_ * keV);
  hit->setPosition(posx_ * cm, posy_ * cm, posz_ * cm);
  hit->setLocalPosition(local_posx_ * cm, local_posy_ * cm, local_posz_ * cm);
  hit->setGrade(grade_);

  return hit;
}

std::vector<comptonsoft::DetectorHit_sptr> OISTHitTreeIO::retrieveHits(int64_t& entry,
                                                      bool get_first_entry)
{
  std::vector<comptonsoft::DetectorHit_sptr> hits;

  if (get_first_entry) {
    hittree_->GetEntry(entry);
  }
  
  const int numHits = getNumberOfHits();
  for (int i=0; i<numHits; i++) {
    if (i!=0) {
      hittree_->GetEntry(entry+i);
    }

    comptonsoft::DetectorHit_sptr hit = retrieveHit();
    hits.push_back(std::move(hit));
  }
  entry += numHits;
  return hits;
}

} /* namespace oistapp */
