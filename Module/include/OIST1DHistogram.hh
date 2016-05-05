#ifndef OISTAPP_OIST1DHistogram_H
#define OISTAPP_OIST1DHistogram_H 1

#include "VCSModule.hh"
#include <string>
#include <vector>
#include <functional>

class TH1;

using namespace comptonsoft;

namespace oistapp {

/**
 * Making histograms.
 * @author Hirokazu Odaka
 * @date 2014-11-30
 */
class OIST1DHistogram : public VCSModule
{
  DEFINE_ANL_MODULE(OIST1DHistogram, 1.0);
public:
  OIST1DHistogram();
  ~OIST1DHistogram() = default;
 
  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

private:
  bool m_ReadoutOrder;
  bool m_GroupingInSection;
  std::string m_HistogramType;
  std::vector<TH1*> m_Histograms;
  int m_NumBins;
  double m_RangeMin;
  double m_RangeMax;
  std::function<double (MultiChannelData*, int)> m_GetterFunc;
};

} /* namespace comptonsoft */

#endif /* OISTAPP_OIST1DHistogram_H */
