#ifndef TKRCANDTRACK_H
#define TKRCANDTRACK_H

#include "TObject.h"
#include "TkrCandHit.h"
/** 
 * @class TkrCandTrack
 *
 * @brief Root object representing a pattern recognition candidate track
 *        Includes base summary information about the track
 *        and a vector of objects containing information for each hit plane
 *        This class should exactly duplicate TkrPatCand
 * 
 * Created 15-May-2002
 * 
 * @author Tracy Usher
 *
 */

class TkrCandTrack : public TObject
{
public:
    //! constructors
    TkrCandTrack();

    TkrCandTrack(UInt_t id, UInt_t layer, UInt_t tower, Double_t q, Double_t e, const TVectorD& pos, const TVectorD& dir);

    //! destructor
    virtual ~TkrCandTrack() {m_hits.clear();}

    //! Define initialization method
    void     initialize(UInt_t id, UInt_t layer, UInt_t tower, Double_t q, Double_t e, const TVectorD& pos, const TVectorD& dir);

    //! Allow hits to be added to the list
    void     addHit(const TkrCandHit& hit) {m_hits.push_back(hit);}

    //! Group together the access methods here
    UInt_t        getId()                     {return m_id;        }
    Double_t      getQuality()          const {return m_quality;   }
    Double_t      getEnergy()           const {return m_energy;    }
    UInt_t        getLayer()            const {return m_firstLayer;}
    UInt_t        getTower()            const {return m_itower;    }
    TVectorD      getPosition()         const {return m_position;  }
    TVectorD      getDirection()        const {return m_direction; }
//    TkrParams     getTrackPar()    const;
//    double        getTrackParZ()   const {return m_position.z();}
//    TkrFitMatrix  getTrackCov()    const; 

    //! Provide info to any hit on the track
    UInt_t             getNumHits()           {return m_hits.size();   }
    TkrCandHitIter     getHitIterBegin()      {return m_hits.begin();  }
    TkrCandHitIter     getHitIterEnd()        {return m_hits.end();    }

    ClassDef(TkrCandTrack,1)
private:
    //! Track ID 
    UInt_t     m_id;

    //Base information for this candidate track
    TVectorD   m_position;
    TVectorD   m_direction;
    Double_t   m_energy;
    Double_t   m_quality;
    UInt_t     m_firstLayer;
    UInt_t     m_itower;    

    TkrCandHitVec m_hits;
};
#endif
