#ifndef ROOT_ACDRECON_H
#define ROOT_ACDRECON_H

#include "TObject.h"
#include "digiRootData/AcdId.h"
#include <vector>
#ifdef WIN32
using namespace std;
#endif

/** 
* @class AcdRecon
* @brief Root container for the reconstructed ACD information 
* 
* This class contains:
* -# Total reconstructed energy detected in ACD detector elements.
* -# Minimum DOCA (Distance of Closest Approach) computed using all tracks and
*    ACD detectors.  DOCA is computed using the center of the ACD tiles.
* -# AcdId of the tile associated with the minimum DOCA.
* -# Minimum Active Distance computed using all tracks and ACD detectors.
*    Computed using the edge of ACD tiles.
* -# Tile Count the number of ACD tiles which were above veto threshold.
* -# Collection of minimum DOCA values organized by geometry:  top, side rows
* -# Collection of minimum Active Distance values organized by geometry:  top
*    and side rows.
*
* @author Heather Kelly
*
* $Header$
*/

class AcdRecon : public TObject
{
    
public:
    AcdRecon();
 
    AcdRecon(Double_t e, Int_t count, Double_t gDoca, Double_t doca, Double_t actDist,
            const AcdId &minDocaId, const std::vector<Double_t> &rowDoca,
            const std::vector<Double_t> &rowActDist,
			const std::vector<AcdId> &idCol, const std::vector<Double_t> &energyCol)       
            : m_totEnergy(e),
            m_gammaDoca(gDoca),
            m_doca(doca),
            m_actDist(actDist),
            m_tileCount(count),
            m_rowDocaCol(rowDoca),
            m_rowActDistCol(rowActDist),
            m_minDocaId(minDocaId),
			m_idCol(idCol),
			m_energyCol(energyCol)
        {};
     
    virtual ~AcdRecon();
    
    void initialize(Double_t e, Int_t count, Double_t gDoca, Double_t doca, Double_t actDist,
        const AcdId &minDocaId, const std::vector<Double_t> &rowDoca, 
        const std::vector<Double_t> &rowActDist, const std::vector<AcdId> &idCol,
		const std::vector<Double_t> &energyCol);

    /// overload initialize for interactive root where we cannot use std::vector
    void initialize(Double_t e, Int_t count, Double_t gDoca, Double_t doca, Double_t actDist, const AcdId &minDocaId);
    
    void Clear(Option_t *option="");
    
    void Print(Option_t *option="") const;
    
    inline const Double_t getEnergy() const { return m_totEnergy; };
    inline const Int_t getTileCount() const { return m_tileCount; };
    inline const Double_t getGammaDoca() const { return m_gammaDoca; };
    inline const Double_t getDoca() const { return m_doca; };
    inline const Double_t getActiveDist() const { return m_actDist; };
    inline const AcdId& getMinDocaId() const { return m_minDocaId; };
    inline const std::vector<Double_t>& getRowDocaCol() const { return m_rowDocaCol; };
    inline const Double_t getRowDoca(UInt_t i) const { 
        return ((i < m_rowDocaCol.size()) ? m_rowDocaCol[i] : -1.); };
    inline void addRowDoca(Double_t val) { m_rowDocaCol.push_back(val); };
    inline const std::vector<Double_t>& getRowActDistCol() const { return m_rowActDistCol; };
    inline const Double_t getRowActDist(UInt_t i) const {
        return ( (i < m_rowActDistCol.size()) ? m_rowActDistCol[i] : -1.); };
    inline void addRowActDist(Double_t val) { m_rowActDistCol.push_back(val); };
	inline const std::vector<Double_t>& getEnergyCol() const { return m_energyCol; };
	inline const Double_t getEnergy(UInt_t i) const { 
		return ( (i < m_energyCol.size()) ? m_energyCol[i] : -1.); };
	inline void addEnergy(Double_t e) { m_energyCol.push_back(e); };
	inline const std::vector<AcdId>& getIdCol() const { return m_idCol; };
	inline const AcdId* getId(UInt_t i) const { 
		return ( (i < m_idCol.size()) ? &m_idCol[i] : 0); };
	inline void addId(const AcdId &id) { m_idCol.push_back(id); };
	Double_t getEnergy(const AcdId &id) const;
    
private:
    /// Total energy in MeV deposited in the whole ACD system
    Double_t m_totEnergy;
    /// Distance of Closest Approach for the reconstructed gamma, 
    /// if there is one
    Double_t m_gammaDoca;
    /// Minimum Distance of Closest Approach for all tracks and all ACD tiles
    Double_t m_doca;
    /// New Bill Atwood DOCA calculation using edge of tiles
    Double_t m_actDist;
    /// Total number of ACD tiles above threshold
    Int_t m_tileCount;
    /// Collection of distance of closest approach calculations
    /// for each side row of the ACD
    vector<Double_t> m_rowDocaCol;
    /// Collection of Active Distance calc for each side row of ACD
    vector<Double_t> m_rowActDistCol;

    /// record of the tile with the minimum Distance of Closest Approach
    AcdId m_minDocaId;
    
    // Stores reconstructed energy per ACD digi
	vector<AcdId> m_idCol;
	vector<Double_t> m_energyCol;
    
    ClassDef(AcdRecon,3) // Acd Reconstruction data
};

#endif
