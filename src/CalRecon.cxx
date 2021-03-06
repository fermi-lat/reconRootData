#include "reconRootData/CalRecon.h"
#include <commonRootData/RootDataUtil.h>
#include "Riostream.h"

ClassImp(CalRecon)

CalRecon::CalRecon() 
{
    m_xtalRecCol        = 0;
    m_clusterCol        = 0;
    m_mipTrackCol       = 0;
    m_gcrXtalCol        = 0;
    m_gcrTrack          = 0;
    m_calClusterMap     = 0;
    m_calEventEnergyMap = 0;

}

CalRecon::~CalRecon() 
{
    if (m_clusterCol) 
    {
        m_clusterCol->Delete();
        delete m_clusterCol;
        m_clusterCol = 0;
    }
    
    if (m_xtalRecCol) 
    {
        m_xtalRecCol->Delete();
        delete m_xtalRecCol;
        m_xtalRecCol = 0;
    }
    
    if (m_mipTrackCol) 
    {
        m_mipTrackCol->Delete();
        delete m_mipTrackCol;
        m_mipTrackCol = 0;
    }
    
    if (m_gcrXtalCol) 
    {
        m_gcrXtalCol->Delete();
        delete m_gcrXtalCol;
        m_gcrXtalCol = 0;
    }
      
    if (m_gcrTrack) 
    {
        delete m_gcrTrack;
        m_gcrTrack = 0;
    }

    if (m_calClusterMap)
    {
        m_calClusterMap->Clear();
        delete m_calClusterMap;
        m_calClusterMap = 0;
    }

    if (m_calEventEnergyMap)
    {
        m_calEventEnergyMap->Clear();
        delete m_calEventEnergyMap;
        m_calEventEnergyMap = 0;
    }

}

void CalRecon::initialize() 
{
    if (!m_clusterCol)  m_clusterCol  = new TObjArray();
    if (!m_xtalRecCol)  m_xtalRecCol  = new TObjArray();
    if (!m_mipTrackCol) m_mipTrackCol = new TObjArray();
//    if (!m_gcrXtalCol) m_gcrXtalCol = new TObjArray();
    m_gcrXtalCol = 0;
    m_indGcrXtal = -1;

    if (!m_calClusterMap)     m_calClusterMap     = new TMap();
    if (!m_calEventEnergyMap) m_calEventEnergyMap = new TMap();
}

void CalRecon::Clear(Option_t* /* option */) 
{
    if (m_xtalRecCol)  m_xtalRecCol->Delete();
    if (m_clusterCol)  m_clusterCol->Delete();
    if (m_mipTrackCol) m_mipTrackCol->Delete();
    if (m_gcrXtalCol) m_gcrXtalCol->Clear("C");
    m_indGcrXtal = -1;
    if (m_gcrTrack) m_gcrTrack = 0;
    if (m_calClusterMap) m_calClusterMap->Clear();
    if (m_calEventEnergyMap) m_calEventEnergyMap->Clear();
}

void CalRecon::Print(Option_t *option) const 
{
    TObject::Print(option);
    std::cout
        << " # mipTracks: " << m_mipTrackCol->GetEntries()
        << " # clusters: " << m_clusterCol->GetEntries()
        << " # xtalRecDatas: " << m_xtalRecCol->GetEntries() 
       << " # gcrXtal : " << m_indGcrXtal+1 << std::endl;
}


GcrXtal* CalRecon::addGcrXtal(const CalXtalId& xtalId, Double_t pathLength,
    Double_t closestFaceDist, Int_t crossedFaces, const TVector3& entry,
    const TVector3& exit) {
    if (!m_gcrXtalCol) m_gcrXtalCol = new TClonesArray("GcrXtal", 1);
    ++m_indGcrXtal;
    TClonesArray &localCol = *m_gcrXtalCol;
    new(localCol[m_indGcrXtal]) GcrXtal(xtalId, pathLength, closestFaceDist,
                                       crossedFaces, entry, exit);
    return ((GcrXtal*) (localCol[m_indGcrXtal]));
}

GcrXtal* CalRecon::addGcrXtal() {
    if (!m_gcrXtalCol) m_gcrXtalCol = new TClonesArray("GcrXtal", 1);
    ++m_indGcrXtal;
    TClonesArray &localCol = *m_gcrXtalCol;
    new(localCol[m_indGcrXtal]) GcrXtal();
    return ((GcrXtal*) (localCol[m_indGcrXtal]));
}

//======================================================
// For Unit Tests
//======================================================

void CalRecon::Fake( Int_t ievent, Float_t randNum ) {

    const UInt_t NUM_XTALS = 10;
    const UInt_t NUM_EVENT_ENERGIES = 2 ;
    const UInt_t NUM_CLUSTERS = 20;
    const UInt_t NUM_MIP_TRACKS = 5;

    initialize() ;
    Clear() ;

    UInt_t icluster;
    for (icluster = 0; icluster < NUM_CLUSTERS ; icluster++ ) {
        CalCluster *cluster = new CalCluster();
        cluster->Fake(ievent,icluster,randNum) ;
        addCalCluster(cluster);
    }

    UInt_t ienergy;
    CalCluster* cluster = (CalCluster*)m_clusterCol->At(0);
    getCalEventEnergyMap()->SetOwnerKeyValue(kFALSE, kTRUE);
    TObjArray* energyVecRoot = new TObjArray();
    energyVecRoot->SetOwner(kFALSE);
    getCalEventEnergyMap()->Add(cluster,energyVecRoot);
    for (ienergy = 0; ienergy < NUM_EVENT_ENERGIES ; ienergy++ ) {
        CalEventEnergy * energy = new CalEventEnergy() ;
        energy->Fake(ievent,ienergy,randNum) ;
        energyVecRoot->Add(energy);
    }

    UInt_t ixtal;
    for (ixtal = 0; ixtal < NUM_XTALS ; ixtal++) {
        CalXtalRecData *xtal = new CalXtalRecData();
        xtal->Fake(ievent,ixtal,randNum) ;
        addXtalRecData(xtal);
    }

    unsigned int imip;
    for (imip = 0; imip < NUM_MIP_TRACKS ; imip++) {
        CalMipTrack * mipTrack = new CalMipTrack ;
        mipTrack->Fake(ievent,imip,randNum) ;
        addCalMipTrack(mipTrack);

    }

    const int NUM_GCRXTALS = 3;
    int igcrxtal;
    for (igcrxtal=0; igcrxtal < NUM_GCRXTALS; igcrxtal++) {
        GcrXtal *xtal=addGcrXtal();
        xtal->Fake(ievent,igcrxtal,randNum);
        
        //addGcrXtal(xtal.getXtalId(),xtal.getPathLength(),
                   //xtal.getClosestFaceDist(),xtal.getCrossedFaces(),
                   //xtal.getEntryPoint(), xtal.getExitPoint());
    }

    GcrTrack* track = new GcrTrack();
    track->Fake(ievent, randNum);
    addGcrTrack(track);

}

#define COMPARE_TOBJ_ARRAY_IN_RANGE(T,m) rootdatautil::TObjArrayCompareInRange<T>(m,ref.m)

#define COMPARE_TMAP_IN_RANGE(T,m) rootdatautil::TObjArrayCompareInRange<T>(m(cluster),ref.m(rclus))

Bool_t CalRecon::CompareInRange( CalRecon & ref, const std::string & name ) {

    bool result = true ;

    CalCluster* rclus = (CalCluster*)ref.getCalClusterCol()->At(0);
    CalCluster* cluster   = (CalCluster*)getCalClusterCol()->At(0);
    result = COMPARE_TMAP_IN_RANGE(CalEventEnergy, getEventEnergyVec) && result;
    //result = COMPARE_TOBJ_ARRAY_IN_RANGE(CalEventEnergy,getEventEnergyVec(cluster)) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(CalCluster,getCalClusterCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(CalXtalRecData,getCalXtalRecCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(CalMipTrack,getCalMipTrackCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(GcrXtal,getGcrXtalCol()) && result;

    result = rootdatautil::CompareInRange(*(GcrTrack*)getGcrTrack(),*(GcrTrack*)ref.getGcrTrack(),"GcrTrack") && result;

    if (!result) {
        if ( name == "" ) {
            std::cout<<"Comparison ERROR for "<<ClassName()<<std::endl ;
        }
        else {
            std::cout<<"Comparison ERROR for "<<name<<std::endl ;
        }
    }
    return result ;

}

