#ifndef ROOT_TKRRECON_H
#define ROOT_TKRRECON_H

#include "TObject.h"
#include "TObjArray.h"

#include "TkrCluster.h"
#include "TkrTrack.h"
#include "TkrVertex.h"
#include "TkrDiagnostics.h"
/** 
 * @class TkrRecon
 * @brief Root container for the reconstructed Tracker information 
 * 
 * This class contains:
 * -# Collection of Clusters
 * -# Collection of 
 * -# Collectoin of Reconstructed Tracks
 * -# Collection Vertices
 * 
 * @author Tracy Usher
 *
 * $Header$
 */

class TkrRecon : public TObject
{

public:
    TkrRecon();

    virtual ~TkrRecon();

    void initialize();
    
    static void CleanUp();
    void Clear(Option_t *option="");
    void Fake( Int_t ievent, Float_t randNum ) ; // for tests
    Bool_t CompareInRange( TkrRecon &, const std::string & name = "" ) ; // for tests
    void Print(Option_t *option="") const;

    /// provide access to the list of clusters    
    TObjArray *getClusterCol() { return m_clusterCol; };
    void addCluster(TkrCluster *cluster) { m_clusterCol->Add(cluster); };

    TObjArray *getTrackCol() { return m_trackCol; };
    void addTrack(TObject* track) { m_trackCol->Add(track); };

    TObjArray *getVertexCol() { return m_vertexCol; };
    void addVertex(TkrVertex* vertex) { m_vertexCol->Add(vertex); };

    // Added for macros & interactive access - EAC
    Int_t nCluster() const { return m_clusterCol->GetEntries() ; }    
    Int_t nTrack() const { return m_trackCol->GetEntries() ; }
    Int_t nVertex() const { return m_vertexCol->GetEntries() ; }

    TkrCluster* getCluster(Int_t i) { return i < nCluster() ? dynamic_cast<TkrCluster*>(m_clusterCol->At(i)) : 0; };
    TkrTrack* getTrack(Int_t i) { return i < nTrack() ? dynamic_cast<TkrTrack*>(m_trackCol->At(i)) : 0; };
    TkrVertex* getVertex(Int_t i) { return i < nVertex() ? dynamic_cast<TkrVertex*>(m_vertexCol->At(i)) : 0; };
    

    const TkrDiagnostics* getDiagnostics() { return m_diagnostics;};
    void addDiagnostics(TkrDiagnostics* diagnostics) { m_diagnostics = diagnostics;};

private:
    /// collection of TkrSiCluster
    TObjArray *m_clusterCol;
    /// collection of TkrTrack
    TObjArray *m_trackCol;
    /// collection of TkrVertex
    TObjArray *m_vertexCol;
    /// Diagnostics
    TkrDiagnostics*   m_diagnostics;

    static TkrCluster *keepCluster[10000]; //!
    static TkrTrack *keepTrack[10000]; //!
    static TkrVertex *keepVertex[10000]; //!
    static Int_t indCluster, indTrack, indVertex; //!

    ClassDef(TkrRecon,6)
};

#endif
