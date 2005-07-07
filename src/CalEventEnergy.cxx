
#include <reconRootData/CalEventEnergy.h>
#include <commonRootData/RootDataUtil.h>
#include <iostream>

ClassImp(CalEventEnergy)

void CalEventEnergy::init
 ( const CalParams & params,
   UInt_t statusBits,
   const TObjArray & toolsResults )
 {
  m_params = params ;
  m_statusBits = statusBits ;
  m_toolsResults.Delete() ;
  m_toolsResults.Clear() ;
  TIter toolResultIter(&toolsResults) ;
  CalCorToolResult * toolResult ;
  while ((toolResult=(CalCorToolResult *)toolResultIter.Next()))
   { m_toolsResults.Add(toolResult) ; }  
 }

void CalEventEnergy::Clear( Option_t * )
 {
  m_params.Clear() ;
  m_statusBits = 0 ;
  m_toolsResults.Delete() ;
  m_toolsResults.Clear() ;
 }

CalEventEnergy::CalEventEnergy
 ( const CalParams & params,
   UInt_t statusBits,
   const TObjArray & toolsResults )
 { init(params,statusBits,toolsResults) ; }

// dummy data, just for tests
void CalEventEnergy::Fake( UInt_t rank, Float_t randNum )
 {
  CalParams p ;
  p.Fake(rank,randNum) ;
  TObjArray toolsResults ;
  CalCorToolResult * result ;
  result = new CalCorToolResult ;
  result->Fake(rank*2,randNum) ;
  toolsResults.Add(result) ;
  result = new CalCorToolResult ;
  result->Fake(rank*2+1,randNum) ;
  toolsResults.Add(result) ;
  init(p,1,toolsResults) ;
 }

void CalEventEnergy::Print( Option_t * ) const
 {
  m_params.Print() ;
  m_toolsResults.Print() ;
 }

Bool_t CalEventEnergy::CompareInRange( const CalEventEnergy & c ) const 
 {
  bool result = true ;
  result = result && getParams().CompareInRange(c.getParams()) ;
  result = result && rootdatautil::CompareInRange(getStatusBits(),c.getStatusBits(),"StatusBits") ;
  const TObjArray & res1 = getToolsResults() ;
  const TObjArray & res2 = c.getToolsResults() ;
  result = result && rootdatautil::CompareInRange(res1.GetSize(),res2.GetSize(),"Number of results") ;
  TIter res1Iter(&res1), res2Iter(&res2) ;
  const CalCorToolResult * r1, * r2 ;
  while ( ((r1=(const CalCorToolResult *)res1Iter.Next())!=0) &&
          ((r2=(const CalCorToolResult *)res2Iter.Next())!=0) )
   { result = result && r1->CompareInRange(*r2) ; }
  if (!result)
   { std::cout<<"Comparison ERROR for "<<ClassName()<<std::endl ; }
  return result ;

 }

CalEventEnergy::CalEventEnergy()
 { Clear() ; }

CalEventEnergy::~CalEventEnergy()
 { m_toolsResults.Delete() ; }

