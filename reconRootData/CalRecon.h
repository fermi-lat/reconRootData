#ifndef ROOT_CALRECON_H
#define ROOT_CALRECON_H

#include "TObject.h"
#include "TObjArray.h"

//#include <vector>
//#ifdef WIN32
//using namespace std;
//#endif

#include "CalXtalRecData.h"
#include "CalCluster.h"

/** @class CalRecon
 * @brief Primary Root object containing CAL reconstruction data.
 *
 * Portal through which one gains access to the CAL recon data. 
 * Currently there are 2 lists available:
 * - A collection of reconstructed CAL crystals (CalXtalRecData)
 * - A collection of CAL clusters (CalCluster)
 *
 * $Header$
*/

class CalRecon : public TObject
{

public:

    CalRecon();

    virtual ~CalRecon();

    void initialize();

    void Clear(Option_t *option="");

    void Print(Option_t *option="") const;

    /// provide access to list of CalClusters
    //std::vector<CalCluster> getCalClusterCol() { return m_clusterCol; };
    TObjArray* getCalClusterCol() { return m_clusterCol; };

    /// provide access to the list of CalXtalRecData
    //std::vector<CalXtalRecData> getCalXtalRecCol() { return m_xtalRecCol; };
    TObjArray* getCalXtalRecCol() { return m_xtalRecCol;};

  //  void addCalCluster(CalCluster *cluster) { m_clusterCol->Add(cluster); };
    //void addCalCluster(const CalCluster &cluster) { m_clusterCol.push_back(cluster); };
    void addCalCluster(CalCluster* cluster) { m_clusterCol->Add(cluster); };
    void addXtalRecData(CalXtalRecData *xtal) { m_xtalRecCol->Add(xtal); };

    //void addXtalRecData(const CalXtalRecData& xtal) { m_xtalRecCol.push_back(xtal); };

private:
    /// list of CalXtalRecData
    //std::vector<CalXtalRecData> m_xtalRecCol;
    TObjArray *m_xtalRecCol;

    /// list of CalClusters
    //std::vector<CalCluster> m_clusterCol;
    TObjArray *m_clusterCol;
  
    ClassDef(CalRecon,2)
};

#endif
