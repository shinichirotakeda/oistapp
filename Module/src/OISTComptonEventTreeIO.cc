#include "OISTComptonEventTreeIO.hh"
#include "G4SystemOfUnits.hh"
#include "TTree.h"
#include "BasicComptonEvent.hh"

namespace oistapp
{

OISTComptonEventTreeIO::OISTComptonEventTreeIO()
  : cetree_(nullptr)
{
}

OISTComptonEventTreeIO::~OISTComptonEventTreeIO() = default;

void OISTComptonEventTreeIO::defineBranches()
{

  cetree_->Branch("exptime", &exptime_, "exptime/l");
  
  cetree_->Branch("eventid", &eventid_, "eventid/l");
  cetree_->Branch("num_hits", &num_hits_, "num_hits/S");

  cetree_->Branch("hit1_id", &hit1_id_, "hit1_id/S");
  cetree_->Branch("hit1_process", &hit1_process_, "hit1_process/i");
  cetree_->Branch("hit1_detector", &hit1_detector_, "hit1_detector/S");
  cetree_->Branch("hit1_readout_module", &hit1_readout_module_, "hit1_readout_module/S");
  cetree_->Branch("hit1_section", &hit1_section_, "hit1_section/S");
  cetree_->Branch("hit1_channel", &hit1_channel_, "hit1_channel/S");
  cetree_->Branch("hit1_pixelx", &hit1_pixelx_, "hit1_pixelx/S");
  cetree_->Branch("hit1_pixely", &hit1_pixely_, "hit1_pixely/S");

  cetree_->Branch("hit1_time", &hit1_time_, "hit1_time/F");
  cetree_->Branch("hit1_posx", &hit1_posx_, "hit1_posx/F");
  cetree_->Branch("hit1_posy", &hit1_posy_, "hit1_posy/F");
  cetree_->Branch("hit1_posz", &hit1_posz_, "hit1_posz/F");
  cetree_->Branch("hit1_energy", &hit1_energy_, "hit1_energy/F");
  
  cetree_->Branch("hit2_id", &hit2_id_, "hit2_id/S");
  cetree_->Branch("hit2_process", &hit2_process_, "hit2_process/i");
  cetree_->Branch("hit2_detector", &hit2_detector_, "hit2_detector/S");
  cetree_->Branch("hit2_readout_module", &hit2_readout_module_, "hit2_readout_module/S");
  cetree_->Branch("hit2_section", &hit2_section_, "hit2_section/S");
  cetree_->Branch("hit2_channel", &hit2_channel_, "hit2_channel/S");
  cetree_->Branch("hit2_pixelx", &hit2_pixelx_, "hit2_pixelx/S");
  cetree_->Branch("hit2_pixely", &hit2_pixely_, "hit2_pixely/S");

  cetree_->Branch("hit2_time", &hit2_time_, "hit2_time/F");
  cetree_->Branch("hit2_posx", &hit2_posx_, "hit2_posx/F");
  cetree_->Branch("hit2_posy", &hit2_posy_, "hit2_posy/F");
  cetree_->Branch("hit2_posz", &hit2_posz_, "hit2_posz/F");
  cetree_->Branch("hit2_energy", &hit2_energy_, "hit2_energy/F");

  cetree_->Branch("flags", &flags_, "flags/l");
  cetree_->Branch("costheta", &costheta_, "costheta/F");
  cetree_->Branch("dtheta", &dtheta_, "dtheta_/F");
  cetree_->Branch("phi", &phi_, "phi/F");

  cetree_->Branch("hitpattern", &hitpattern_, "hitpattern/l");
  cetree_->Branch("grade", &grade_, "grade/I");
  cetree_->Branch("likelihood", &likelihood_, "likelihood/F");
}

void OISTComptonEventTreeIO::setBranchAddresses()
{

  cetree_->SetBranchAddress("exptime", &exptime_);
  
  cetree_->SetBranchAddress("eventid", &eventid_);
  cetree_->SetBranchAddress("num_hits", &num_hits_);

  cetree_->SetBranchAddress("hit1_id", &hit1_id_);
  cetree_->SetBranchAddress("hit1_process", &hit1_process_);
  cetree_->SetBranchAddress("hit1_detector", &hit1_detector_);
  cetree_->SetBranchAddress("hit1_readout_module", &hit1_readout_module_);
  cetree_->SetBranchAddress("hit1_section", &hit1_section_);
  cetree_->SetBranchAddress("hit1_channel", &hit1_channel_);
  cetree_->SetBranchAddress("hit1_pixelx", &hit1_pixelx_);
  cetree_->SetBranchAddress("hit1_pixely", &hit1_pixely_);

  cetree_->SetBranchAddress("hit1_time", &hit1_time_);
  cetree_->SetBranchAddress("hit1_posx", &hit1_posx_);
  cetree_->SetBranchAddress("hit1_posy", &hit1_posy_);
  cetree_->SetBranchAddress("hit1_posz", &hit1_posz_);
  cetree_->SetBranchAddress("hit1_energy", &hit1_energy_);
  
  cetree_->SetBranchAddress("hit2_id", &hit2_id_);
  cetree_->SetBranchAddress("hit2_process", &hit2_process_);
  cetree_->SetBranchAddress("hit2_detector", &hit2_detector_);
  cetree_->SetBranchAddress("hit2_readout_module", &hit2_readout_module_);
  cetree_->SetBranchAddress("hit2_section", &hit2_section_);
  cetree_->SetBranchAddress("hit2_channel", &hit2_channel_);
  cetree_->SetBranchAddress("hit2_pixelx", &hit2_pixelx_);
  cetree_->SetBranchAddress("hit2_pixely", &hit2_pixely_);

  cetree_->SetBranchAddress("hit2_time", &hit2_time_);
  cetree_->SetBranchAddress("hit2_posx", &hit2_posx_);
  cetree_->SetBranchAddress("hit2_posy", &hit2_posy_);
  cetree_->SetBranchAddress("hit2_posz", &hit2_posz_);
  cetree_->SetBranchAddress("hit2_energy", &hit2_energy_);

  cetree_->SetBranchAddress("flags", &flags_);
  cetree_->SetBranchAddress("costheta", &costheta_);
  cetree_->SetBranchAddress("dtheta", &dtheta_);
  cetree_->SetBranchAddress("phi", &phi_);

  cetree_->SetBranchAddress("hitpattern", &hitpattern_);
  cetree_->SetBranchAddress("grade", &grade_);
  cetree_->SetBranchAddress("likelihood", &likelihood_);
}

void OISTComptonEventTreeIO::fillEvent(const int64_t eventID,
				       const uint64_t exptime,
                                   const BasicComptonEvent& event)
{
  eventid_ = (eventID >= 0) ? eventID : event.EventID();
  num_hits_ = event.NumberOfHits();
  exptime_ = exptime;
  
  hit1_id_ = event.Hit1ID();
  hit1_process_ = event.Hit1Process();
  hit1_detector_ = event.Hit1DetectorID();
  const ReadoutChannelID hit1ReadoutChannel = event.Hit1ReadoutChannel();
  hit1_readout_module_ = hit1ReadoutChannel.ReadoutModule();
  hit1_section_ = hit1ReadoutChannel.Section();
  hit1_channel_ = hit1ReadoutChannel.Index();
  const PixelID hit1Pixel = event.Hit1Pixel();
  hit1_pixelx_ = hit1Pixel.X();
  hit1_pixely_ = hit1Pixel.Y();

  hit1_time_ = event.Hit1Time() / second;
  const vector3_t hit1Position = event.Hit1Position();
  hit1_posx_ = hit1Position.x() / cm;
  hit1_posy_ = hit1Position.y() / cm;
  hit1_posz_ = hit1Position.z() / cm;
  hit1_energy_ = event.Hit1Energy() / keV;

  hit2_id_ = event.Hit2ID();
  hit2_process_ = event.Hit2Process();
  hit2_detector_ = event.Hit2DetectorID();
  const ReadoutChannelID hit2ReadoutChannel = event.Hit2ReadoutChannel();
  hit2_readout_module_ = hit2ReadoutChannel.ReadoutModule();
  hit2_section_ = hit2ReadoutChannel.Section();
  hit2_channel_ = hit2ReadoutChannel.Index();
  const PixelID hit2Pixel = event.Hit2Pixel();
  hit2_pixelx_ = hit2Pixel.X();
  hit2_pixely_ = hit2Pixel.Y();

  hit2_time_ = event.Hit2Time() / second;
  const vector3_t hit2Position = event.Hit2Position();
  hit2_posx_ = hit2Position.x() / cm;
  hit2_posy_ = hit2Position.y() / cm;
  hit2_posz_ = hit2Position.z() / cm;
  hit2_energy_ = event.Hit2Energy() / keV;

  flags_ = event.Flags();
  costheta_ = event.CosThetaE();
  dtheta_ = event.DeltaTheta();
  phi_ = event.PhiG();
  hitpattern_ = event.HitPattern();
  grade_ = event.Grade();
  likelihood_ = event.Likelihood();
  
  cetree_->Fill();
}

BasicComptonEvent OISTComptonEventTreeIO::retrieveEvent() const
{
  BasicComptonEvent event;
  retrieveEvent(event);
  return event;
}

void OISTComptonEventTreeIO::retrieveEvent(BasicComptonEvent& event) const
{
  event.setEventID(eventid_);
  event.setNumberOfHits(num_hits_);
  
  event.setHit1ID(hit1_id_);
  event.setHit1Process(hit1_process_);
  event.setHit1DetectorChannel(DetectorChannelID(hit1_detector_));
  event.setHit1ReadoutChannel(ReadoutChannelID(hit1_readout_module_,
                                               hit1_section_,
                                               hit1_channel_));
  event.setHit1Pixel(hit1_pixelx_, hit1_pixely_);
  event.setHit1Time(hit1_time_ * second);
  event.setHit1Position(hit1_posx_ * cm, hit1_posy_ * cm, hit1_posz_ * cm);
  event.setHit1Energy(hit1_energy_ * keV);

  event.setHit2ID(hit2_id_);
  event.setHit2Process(hit2_process_);
  event.setHit2DetectorChannel(DetectorChannelID(hit2_detector_));
  event.setHit2ReadoutChannel(ReadoutChannelID(hit2_readout_module_,
                                               hit2_section_,
                                               hit2_channel_));
  event.setHit2Pixel(hit2_pixelx_, hit2_pixely_);
  event.setHit2Time(hit2_time_ * second);
  event.setHit2Position(hit2_posx_ * cm, hit2_posy_ * cm, hit2_posz_ * cm);
  event.setHit2Energy(hit2_energy_ * keV);
  
  event.setFlags(flags_);
  event.setHitPattern(hitpattern_);
  event.setGrade(grade_);
  event.setLikelihood(likelihood_);
}

} /* namespace oistapp */
