#ifndef ROOT_TKRRECON_H
#define ROOT_TKRRECON_H

#include "TObject.h"
#include <vector>
#ifdef WIN32
using namespace std;
#endif

#include "TkrCandTrack.h"
#include "TkrSiCluster.h"
//#include "TkrTrack.h"
//#include "TkrVertex.h"
/** 
 * @class TkrRecon
 *
 * @brief Root container for the reconstructed Tracker information 
 *        Reconstructed information includes:
 *           1) Silicon Clusters
 *           2) Pattern Recognized Tracks
 *           3) Reconstructed Tracks
 *           4) Vertices
 * 
 * Created 13-May-2002
 * 
 * @author Tracy Usher
 *
 */

class TkrRecon : public TObject
{

public:
    TkrRecon();

    virtual ~TkrRecon();
    
    void Clear(Option_t *option="");

    void Print(Option_t *option="") const;

    /// provide access to the list of clusters
    vector<TkrSiCluster> getSiClusterCol() { return m_siClusterCol; };
    void addSiCluster(const TkrSiCluster &cluster) { m_siClusterCol.push_back(cluster); };

    /// provide access to the list of pattern recognized tracks
    vector<TkrCandTrack> getTrackCandCol() { return m_trackCandCol; };
    void addTrackCand(const TkrCandTrack &track) { m_trackCandCol.push_back(track);};
    //// provide access to the list of tracks
    //vector<TkrTrack> getTrackCol() { return m_trackCol; };
    //void addTrack(const TkrTrack &track) { m_trackCol.push_back(track); };

    /// provide access to the list of vertices
    //vector<TkrVertex> getVertexCol() { m_vertexCol; };
    //void addVertex(const TkrVertex &vertex) { m_vertexCol.push_back(vertex); };

private:
    //! list of TkrSiClusters
    vector<TkrSiCluster> m_siClusterCol;
    //! list of TkrTrackCands
    vector<TkrCandTrack> m_trackCandCol;

    //! list of TkrTracks
    //vector<TkrTrack> m_trackCol;

    //! list of TkrVertices
    //vector<TkrVertex> m_vertexCol;

    ClassDef(TkrRecon,3)
};

#endif
