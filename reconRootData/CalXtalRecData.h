
#ifndef Root_CalXtalRecCol_H
#define Root_CalXtalRecCol_H 1


#include "CalRangeRecData.h"
#include "TObject.h"
#include "TVector3.h"
#include <vector>
#ifndef R__GLOBALSTL
#ifndef WIN32
using std::vector;
#else
using namespace std;
#endif
#endif

#include "commonRootData/idents/CalXtalId.h"


/** @class   CalXtalRecData        
* @brief Reconstructed data for one calorimeter crystal                                
*             
* @author A.Chekhtman
* 
* $Header$
*/

class CalXtalRecData :  public TObject { 
    
public:
    
    
    CalXtalRecData() {};
        
    virtual ~CalXtalRecData() { };
    
    void initialize(CalXtalId::CalTrigMode m, CalXtalId id);

    void Clear(Option_t *option="");
    void Fake( Int_t ievent, UInt_t rank, Float_t randNum ) ; // for tests
    Bool_t CompareInRange( const CalXtalRecData &, const std::string & name = "" ) const ; // for tests
    void Print(Option_t *option="") const;

    /// Retrieve readout mode
    const CalXtalId::CalTrigMode getMode() const { return m_mode; };
    
    /// Retrieve Xtal identifier
    const CalXtalId getPackedId() const { return m_xtalId; };
    
    /// Add a new element to the CalRangeRecData collection
    void addRangeRecData(CalRangeRecData r) { m_recData.push_back(r); } ;
    
    /// Retrieve energy range for selected face and readout
    Char_t getRange(UShort_t readoutIndex, CalXtalId::XtalFace face) const;
    
    /// Retrieve energy for selected face and readout
    Double_t getEnergy(UShort_t readoutIndex, CalXtalId::XtalFace face) const;
    
    
    /// Retrieve average energy of two faces for the best range
    Double_t getEnergy() const;
    
    /// Retrieve the position for the best range
    const TVector3& getPosition() const
    {
        return getRangeRecData(0)->getPosition();
    }
    
    /// Retrieve reconstructed data from both ends of selected readout
    const CalRangeRecData* getRangeRecData(UShort_t readoutIndex) const;
    
    /// Retrieve pulse height from selected range
    Double_t getEnergySelectedRange(CalXtalId::AdcRange range, CalXtalId::XtalFace face) const;
    
    
    
private:
    
    /// Cal readout mode is based on trigger type
    CalXtalId::CalTrigMode m_mode;
    /// Cal ID
    CalXtalId m_xtalId;
    /// ranges and pulse heights
    vector<CalRangeRecData> m_recData;
    
    ClassDef(CalXtalRecData,1)
};

#endif
