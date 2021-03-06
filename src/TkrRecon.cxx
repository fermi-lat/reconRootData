
#include "reconRootData/TkrRecon.h"
#include <commonRootData/RootDataUtil.h>
#include "Riostream.h"

#include "ReconObjectManager.h"

ClassImp(TkrRecon)

TkrRecon::TkrRecon() {
    m_clusterCol  = 0;
    m_trackCol    = 0;
    m_crTrackCol  = 0;
    m_vertexCol   = 0;
    m_diagnostics = 0;
    m_truncationDataCol = 0;
    m_tkrVecPointCol      = 0;
    m_tkrVecPointsLinkCol = 0;
    m_tkrVecNodesCol      = 0;
    m_tkrFilterParamsCol  = 0;
    m_tkrTreeCol          = 0;
    m_tkrEventParams         = 0;
    m_treeClusterRelationCol = 0;
}

TkrRecon::~TkrRecon() {
    Clear("ALL");
    if (m_clusterCol) delete m_clusterCol;
    m_clusterCol = 0;
    if (m_trackCol) delete m_trackCol;
    m_trackCol = 0;
    if (m_crTrackCol) delete m_crTrackCol;
    m_crTrackCol = 0;
    if (m_vertexCol) delete m_vertexCol;
    m_vertexCol = 0;
    if (m_truncationDataCol) delete m_truncationDataCol;
    m_truncationDataCol = 0;
    if (m_diagnostics) delete m_diagnostics;
    m_diagnostics = 0;
    if (m_tkrVecPointCol)       delete m_tkrVecPointCol;
    m_tkrVecPointCol      = 0;
    if (m_tkrVecPointsLinkCol)  delete m_tkrVecPointsLinkCol;
    m_tkrVecPointsLinkCol = 0;
    if (m_tkrVecNodesCol)       delete m_tkrVecNodesCol;
    m_tkrVecNodesCol      = 0;
    if (m_tkrFilterParamsCol)   delete m_tkrFilterParamsCol;
    m_tkrFilterParamsCol  = 0;
    if (m_tkrTreeCol)           delete m_tkrTreeCol;
    m_tkrTreeCol          = 0;
    if (m_treeClusterRelationCol) delete m_treeClusterRelationCol;
    m_treeClusterRelationCol = 0;
}

void TkrRecon::initialize() {
    if (!m_clusterCol)        m_clusterCol        = new TObjArray();
    if (!m_trackCol)          m_trackCol          = new TObjArray();
    if (!m_crTrackCol)        m_crTrackCol        = new TObjArray();
    if (!m_vertexCol)         m_vertexCol         = new TObjArray();
    if (!m_truncationDataCol) m_truncationDataCol = new TObjArray();
    if (!m_tkrVecPointCol)      m_tkrVecPointCol      = new TObjArray();
    if (!m_tkrVecPointsLinkCol) m_tkrVecPointsLinkCol = new TObjArray();
    if (!m_tkrVecNodesCol)      m_tkrVecNodesCol      = new TObjArray();
    if (!m_tkrFilterParamsCol)  m_tkrFilterParamsCol  = new TObjArray();
    if (!m_tkrTreeCol)          m_tkrTreeCol          = new TObjArray();
    if (!m_treeClusterRelationCol) m_treeClusterRelationCol = new TObjArray();
}

void TkrRecon::Clear(Option_t* option) {
    // HMK Unused? static Int_t limitTruncationData = 100;

    // Tell the RECON object manager to reset its iterators
    ReconObjectManager::getPointer()->Delete(option);

    // Note that we need to delete the TkrEventParams object here
    if (m_tkrEventParams) delete m_tkrEventParams;
    m_tkrEventParams = 0;

    // Also note that the TreeClusterRelation objects are not managed by the Recon object
    if (m_treeClusterRelationCol)
    {
        for(int idx = 0; idx < nTreeClusterRelations(); idx++)
        {
            delete m_treeClusterRelationCol->At(idx);
        }

        m_treeClusterRelationCol->Clear();
    }
}


void TkrRecon::Print(Option_t *option) const {
    TObject::Print(option);
    using namespace std;
    cout << "Number of TkrClusters: " << m_clusterCol->GetEntries() << endl;
    cout << "Number of Tracks: " << m_trackCol->GetEntries() << endl;
    if (m_crTrackCol) 
        cout << "Number of Cosmic-ray Tracks: " << m_crTrackCol->GetEntries() << endl;
    else 
        cout << "No Cosmic-ray Tracks" << std::endl;
    cout << "Number of Vertices: " << m_vertexCol->GetEntries() << endl;
    if(m_truncationDataCol)
      cout << "Number of TruncationData: " << m_truncationDataCol->GetEntries() << endl;
    else
      cout<<"No Truncation collection!"<<endl;
}


//======================================================
// For Unit Tests
//======================================================

void TkrRecon::Fake( Int_t ievent, Float_t randNum ) {
    
    initialize() ;
    
    const UInt_t NUM_CLUSTERS = 20;
    const UInt_t NUM_TRACKS = 15;
    const UInt_t NUM_VERTICES = 11;
    const UInt_t NUM_TRUNCATION = 1;

    UInt_t icluster;
    for ( icluster = 0 ; icluster < NUM_CLUSTERS ; icluster++ ) 
     {
      TkrCluster * cluster = new TkrCluster ;
      cluster->Fake(ievent,icluster,randNum) ;
      addCluster(cluster);
     }

    TkrTrack *track;
    UInt_t itrack;
    for (itrack=0; itrack < NUM_TRACKS; itrack++) 
    {
        track = new TkrTrack() ;
        track->Fake(ievent,itrack,randNum) ;
        addTrack(track);
    }

    UInt_t ivertex;
    TkrVertex *vertex;
    for (ivertex=0; ivertex < NUM_VERTICES; ivertex++) {
        vertex = new TkrVertex();
        vertex->Fake(ievent,ivertex,randNum) ;
        addVertex(vertex);
    }

    UInt_t itrunc;
    TkrTruncationData *trunc;
    for(itrunc=0;itrunc< NUM_TRUNCATION;itrunc++) {
       trunc = new TkrTruncationData();
        trunc->Fake(ievent,itrunc,randNum);
        addTruncationData(trunc);        
    }

    TkrDiagnostics * diag = new TkrDiagnostics ;
    diag->Fake(ievent,ivertex,randNum) ;
    addDiagnostics(diag) ;
}

#define COMPARE_TOBJ_ARRAY_IN_RANGE(T,m) rootdatautil::TObjArrayCompareInRange<T>(m,ref.m)

Bool_t TkrRecon::CompareInRange( TkrRecon & ref, const std::string & name ) {

    bool result = true ;

    result = COMPARE_TOBJ_ARRAY_IN_RANGE(TkrCluster,getClusterCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(TkrTrack,getTrackCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(TkrTrack,getCRTrackCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(TkrVertex,getVertexCol()) && result ;
    result = COMPARE_TOBJ_ARRAY_IN_RANGE(TkrTruncationData,getTruncationDataCol()) && result ;
    result = rootdatautil::CompareInRange(*getDiagnostics(),*ref.getDiagnostics(),"Diagnostics") && result ;

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

