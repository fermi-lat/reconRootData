#ifndef TkrSiCluster_H
#define TkrSiCluster_H

#include "TObject.h"

// ===================================
//          Silicon Cluster
// ===================================

//! Root Tree Object storing a single Silicon Cluster
/*! TKR reconstruction may determine SSD clusters
    This class stores one such cluster.
    A cluster is defined by:
    1.) A layer number
    2.) center strip ID
    3.) number of strips in the cluster 
*/

class TkrSiCluster : public TObject
{

public:
    //! denotes type of Si plane - x or y
    typedef enum {
        X = 0,
        Y
    } TKRAxes;
 
private :
  //! id of the cluster
  UInt_t m_id;   
  //! layer number
  UInt_t m_layer;
  //! denotes whether this is an X or Y plane
  TKRAxes m_xy;             
  
  //! center strip of the cluster
  // HMA Question - what if a cluster is an even # of strips
  // which strip number is provided as the "center" strip?
  UShort_t m_centerStrip; 
  //! number of strips in this cluster
  UShort_t m_numStrips;        
  
  //! strip position
  Float_t m_position; 

  //(HMA Question: z position of the layer???)
  //! z position   
  Float_t m_z;              

public:
    
    //! constructors
    // in this case there are no pointers in the class, so
    // users may utilize either constructor
    TkrSiCluster();
    TkrSiCluster(UInt_t id);

    //! destructor
    virtual ~TkrSiCluster();

    //! resets all member variables to default values
    void Clean();
    // Create isn't necessary since there are no pointers
    // in this class

    //! access the ID # associated with this TkrSiCluster
    UInt_t getId() { return m_id; };
    void setId(UInt_t id) { m_id = id; };

    //! access the layer number
    UInt_t getLayer() { return m_layer; };
    void setLayer(UInt_t layer) { m_layer = layer; };
    
    //! access to the type of layer - is it an X or a Y?
    TKRAxes getXY() { return (m_xy ? Y : X); };
    void setXY(TKRAxes xyVal) { m_xy = xyVal; };

    //! access the Center strip number
    UShort_t getCenterStrip() { return m_centerStrip; };
    void setCenterStrip(UShort_t center) { m_centerStrip = center; };

    //! access number of strips in this cluster
    UShort_t getNumStrips() { return m_numStrips; };
    void setNumStrips(UShort_t num) { m_numStrips = num; };

    //! access the position
    Float_t getPosition() { return m_position; };
    void setPosition(Float_t pos) { m_position = pos; };

    //! access the z position
    Float_t getZPosition() { return m_z; };
    void setZPosition(Float_t z) { m_z = z; };
  
  ClassDef(TkrSiCluster,1) 
};
#endif
