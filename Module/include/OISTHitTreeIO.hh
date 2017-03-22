#ifndef OISTAPP_OISTHitTreeIO_H
#define OISTAPP_OISTHitTreeIO_H 1

#include <cstdint>
#include "DetectorHit_sptr.hh"

class TTree;

namespace oistapp {

/**
 * 
 * @author Hirokazu Odaka
 * @date 2014-12-02
 */
class OISTHitTreeIO
{
public:
  OISTHitTreeIO();
  virtual ~OISTHitTreeIO();

  virtual void setTree(TTree* tree)
  { hittree_ = tree; }

  virtual void defineBranches();
  virtual void setBranchAddresses();

  void fillHits(int64_t eventID, uint64_t exptime, const std::vector<comptonsoft::DetectorHit_sptr>& hits);
  void fillHits(const std::vector<comptonsoft::DetectorHit_sptr>& hits)
  { fillHits(-1, 0,hits); }

  int64_t getEventID() const { return eventid_; }
  int64_t getNumberOfHits() const { return num_hits_; }
  uint64_t getExpTime() const {return exptime_;}
  comptonsoft::DetectorHit_sptr retrieveHit() const;
  std::vector<comptonsoft::DetectorHit_sptr> retrieveHits(int64_t& entry,
                                             bool get_first_entry=true);
  
private:
  TTree* hittree_;

  /*
   * tree contents
   */
  int64_t eventid_ = 0;
  int16_t ihit_ = 0;
  int32_t num_hits_ = 0;
  // measured data
  uint64_t exptime_ = 0;
  int64_t time_ = 0;
  int16_t instrument_ = 0;
  int16_t detector_ = -1;
  int16_t det_section_ = -1;
  int16_t readout_module_ = -1;
  int16_t section_ = -1;
  int16_t channel_ = -1;
  int16_t pixelx_ = -1;
  int16_t pixely_ = -1;
  int32_t rawpha_ = 0;
  float pha_ = 0.0;
  float epi_ = 0.0;
  uint64_t flag_data_ = 0ul;
  uint64_t flags_ = 0ul;
  // simulation
  float real_time_ = 0.0;
  int16_t time_group_ = 0;
  float real_posx_ = 0.0;
  float real_posy_ = 0.0;
  float real_posz_ = 0.0;
  float edep_ = 0.0;
  float echarge_ = 0.0;
  uint32_t process_ = 0u;
  // reconstructed
  float energy_ = 0.0;
  float posx_ = 0.0;
  float posy_ = 0.0;
  float posz_ = 0.0;
  float local_posx_ = 0.0;
  float local_posy_ = 0.0;
  float local_posz_ = 0.0;
  int32_t grade_ = 0;
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTHitTreeIO_H */
