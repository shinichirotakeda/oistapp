#ifndef OISTAPP_OISTComptonEventTreeIO_H
#define OISTAPP_OISTComptonEventTreeIO_H 1

#include <cstdint>
#include "DetectorHit_sptr.hh"
#include "BasicComptonEvent.hh"

using namespace comptonsoft;

class TTree;

namespace oistapp {

/**
 * 
 * @author Hirokazu Odaka
 * @date 2014-12-02
 * @date 2015-10-10
 */
class OISTComptonEventTreeIO
{
public:
  OISTComptonEventTreeIO();
  virtual ~OISTComptonEventTreeIO();

  virtual void setTree(TTree* tree)
  { cetree_ = tree; }

  virtual void defineBranches();
  virtual void setBranchAddresses();

  void fillEvent(int64_t eventID,
		 const uint64_t exptime,
                 const BasicComptonEvent& event);
  void fillEvent(const BasicComptonEvent& event)
  { fillEvent(-1, 0, event); }
  
  BasicComptonEvent retrieveEvent() const;
  void retrieveEvent(BasicComptonEvent& event) const;

  int64_t getEventID() const { return eventid_; }
  
private:
  TTree* cetree_;

  /*
   * tree contents
   */
  
  uint64_t exptime_ = 0;
  
  uint64_t eventid_ = 0u;
  int16_t num_hits_ = 0;

  int16_t hit1_id_ = 0;
  uint32_t hit1_process_ = 0;
  int16_t hit1_detector_ = 0;
  int16_t hit1_readout_module_ = 0;
  int16_t hit1_section_ = 0;
  int16_t hit1_channel_ = 0;
  int16_t hit1_pixelx_ = 0;
  int16_t hit1_pixely_ = 0;
  float hit1_time_ = 0.0;
  float hit1_posx_ = 0.0;
  float hit1_posy_ = 0.0;
  float hit1_posz_ = 0.0;
  float hit1_energy_ = 0.0;

  int16_t hit2_id_ = 0;
  uint32_t hit2_process_ = 0;
  int16_t hit2_detector_ = 0;
  int16_t hit2_readout_module_ = 0;
  int16_t hit2_section_ = 0;
  int16_t hit2_channel_ = 0;
  int16_t hit2_pixelx_ = 0;
  int16_t hit2_pixely_ = 0;
  float hit2_time_ = 0.0;
  float hit2_posx_ = 0.0;
  float hit2_posy_ = 0.0;
  float hit2_posz_ = 0.0;
  float hit2_energy_ = 0.0;

  uint64_t flags_ = 0ul;

  float costheta_ = 0.0;
  float dtheta_ = 0.0;
  float phi_ = 0.0;

  uint64_t hitpattern_ = 0ul;
  int32_t grade_ = 0;
  float likelihood_ = 1.0;
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTComptonEventTreeIO_H */
