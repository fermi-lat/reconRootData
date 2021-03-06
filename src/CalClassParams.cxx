

//  Implementation file of Root clone for CalClassParams
//  
// Authors:
//
//    Luca Baldini
//    Johan Bregeon
//

#include <reconRootData/CalClassParams.h>
#include <commonRootData/RootDataUtil.h>
#include "Riostream.h"

ClassImp(CalClassParams)

CalClassParams::CalClassParams()
{
  setProducerName("Not set");
  Clear();
}

CalClassParams::CalClassParams
( std::string producerName,
  std::map <std::string, Double_t> probMap )
{
  init
    ( producerName,probMap );
}

void CalClassParams::init(const std::string& producerName, const std::map <std::string, Double_t>& probMap)
{
  m_producerName = producerName;
  m_probMap      = probMap;
}

void CalClassParams::Clear( Option_t * )
{
  m_probMap.clear();
}
  
Double_t CalClassParams::getProb(const std::string &className) const
{
  if (hasClass(className)){
    return m_probMap.find(className)->second;
  }
  else {
    return -1.;
  }
}

Bool_t CalClassParams::hasClass(const std::string &className) const
{
  return m_probMap.count(className);
}

void CalClassParams::Print( Option_t * ) const
{
  std::cout << "Producer name: '" << getProducerName() << "'\n";
  std::map <std::string, double>::const_iterator iter;
  for (iter = m_probMap.begin(); iter != m_probMap.end(); iter++)
    {
      std::cout << "Probability for class '" << (*iter).first << "': " <<
        (*iter).second << "\n";
    }
}

// dummy data, just for tests
void CalClassParams::Fake( Int_t /* ievent */, UInt_t /* rank */, Float_t /* randNum */ )
 {
   std::map <std::string, double> probMap;
   probMap["gam"] = 0.5;
   probMap["had"] = 0.5;
   init("Fake producer", probMap);
 }

Bool_t CalClassParams::CompareInRange( const CalClassParams & cp, const std::string & name ) const
{  
  Bool_t result = true ;

  result = rootdatautil::CompareInRange(getProducerName(),cp.getProducerName(),
                                        "Producer name") && result ;
  std::map <std::string, double>::const_iterator iter;
  
  for (iter = getProbMap().begin(); iter != getProbMap().end(); iter++)
    {
      result = rootdatautil::CompareInRange((*iter).second,cp.getProb((*iter).first),
                                            (*iter).first) && result ;
    }

  if (!result) {
    if ( name == "" ) {
      std::cout<<"Comparison ERROR for CalClassParams"<<std::endl ;
    }
    else {
      std::cout<<"Comparison ERROR for "<<name<<std::endl ;
    }
  }
  
  return result;
}

