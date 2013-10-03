/************************************************************************
 * Copyright(c) 2010, One Unified. All rights reserved.                 *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *
 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/

#pragma once

#include <vector>
#include <string>
#include <map>

#include <OUCommon/Delegate.h>

#include "ChartEntryBase.h"

namespace ou { // One Unified

// ChartDataView contains the CChartEntries and related sub-chart 
//   to be viewed in a master chart viewport 

class ChartDataViewCarrier { // used by ChartViewPort objects to chart data
public:
  //enum enumChartDrawingType { Unknown, Indicator, Volume, Bar, Mark, Segment, Shape, _cntChartDrawingTypes };
  ChartDataViewCarrier( void );
  ChartDataViewCarrier( size_t nChart, ChartEntryBase& entry );
//  ChartDataViewCarrier( ChartDataViewCarrier& carrier );
  ~ChartDataViewCarrier( void );
  size_t GetLogicalChartId( void ) { return m_nLogicalChart; };
  void SetActualChartId( size_t ix ) { m_nActualChart = ix; };
  size_t GetActualChartId( void ) const { return m_nActualChart; };
  ChartEntryBase& GetChartEntry( void ) { return *m_pChartEntry; };
protected:
  size_t m_nLogicalChart;  // as supplied by trading rules
  size_t m_nActualChart;   // as supplied by CChartDataView management
  ChartEntryBase* m_pChartEntry;
private:
};

// nChart:  0, 1 reserved:
//   0: main price chart
//   1: main volume chart

class ChartDataView {
public:

  typedef std::vector<ChartDataViewCarrier>::const_iterator const_iterator;
  typedef std::vector<ChartDataViewCarrier>::iterator iterator;

  ChartDataView( const std::string &sStrategy, const std::string &sName );
  ~ChartDataView(void);

  void Add( size_t nChart, ChartEntryBase& entry );  // could try boost::fusion here?  some crtp stuff?
  iterator begin( void ) { return m_vChartDataViewEntry.begin(); };
  iterator end( void ) { return m_vChartDataViewEntry.end(); };
  const std::string &GetStrategy( void ) const { return m_sStrategy; };
  const std::string &GetName( void ) const { return m_sName; };
  ou::Delegate<ChartDataView*> OnClosing;
  void Close( void ); // call before destruction so can be removed from tree view and view port properly
  size_t GetChartCount( void ) const{ return m_mapCntChartIndexes.size(); };
  void SetChanged(void) { m_bChanged = true; };
  bool GetChanged(void) { bool b = m_bChanged; if ( b ) m_bChanged = false; return b; };

  // can use not_a_date_time for one, the other, or both
  void SetViewPort( boost::posix_time::ptime dtBegin, boost::posix_time::ptime dtEnd );

protected:

private:

  struct structChartMapping {
    size_t ixActualChartId;  // actual chart index
    size_t nCharts;  // number of charts at this index
    explicit structChartMapping( void ) : ixActualChartId( 0 ), nCharts( 0 ) {};
    explicit structChartMapping( const structChartMapping &obj ) 
      : ixActualChartId( obj.ixActualChartId ), nCharts( obj.nCharts ) {};
    structChartMapping &operator=( const structChartMapping &obj ) { 
      ixActualChartId = obj.ixActualChartId; nCharts = obj.nCharts; return *this; };
  };

  typedef std::map<size_t /* carrier nChart */, structChartMapping> mapCntChartIndexes_t;

  typedef std::vector<ChartDataViewCarrier> vChartDataViewEntry_t;

  bool m_bChanged;
  bool m_bClosed;
  std::string m_sStrategy;
  std::string m_sName;

  boost::posix_time::ptime m_dtViewPortBegin;
  boost::posix_time::ptime m_dtViewPortEnd;

  mapCntChartIndexes_t m_mapCntChartIndexes;  // how many of each carrier::m_nchart we have

  vChartDataViewEntry_t m_vChartDataViewEntry;

};

} // namespace ou

// http://www.parashift.com/c++-faq-lite/assignment-operators.html