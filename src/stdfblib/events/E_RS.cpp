/*******************************************************************************
 * Copyright (c) 2006 - 2013 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Martin Melik Merkumians, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "E_RS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_RS_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_RS, g_nStringIdE_RS)

const CStringDictionary::TStringId FORTE_E_RS::scm_anDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_E_RS::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL};
const TForteInt16 FORTE_E_RS::scm_anEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_E_RS::scm_anEventInputNames[] = {g_nStringIdR, g_nStringIdS};
const TDataIOID FORTE_E_RS::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_E_RS::scm_anEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_RS::scm_anEventOutputNames[] = {g_nStringIdEO};
const SFBInterfaceSpec FORTE_E_RS::scm_stFBInterfaceSpec = {
  2, scm_anEventInputNames, nullptr, scm_anEIWithIndexes,
  1, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  0, nullptr, nullptr,
  1, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

FORTE_E_RS::FORTE_E_RS(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
    CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, nullptr),
    var_Q(CIEC_BOOL(0)),
    var_conn_Q(var_Q),
    conn_EO(this, 0),
    conn_Q(this, 0, &var_conn_Q) {
}

void FORTE_E_RS::alg_SET(void) {
  
  var_Q = CIEC_BOOL(true);
}
void FORTE_E_RS::alg_RESET(void) {
  
  var_Q = CIEC_BOOL(false);
}


void FORTE_E_RS::executeEvent(TEventID pa_nEIID){
  do {
    switch(m_nECCState) {
      case scm_nStateSTART:
        if(scm_nEventSID == pa_nEIID) enterStateSET();
        else return; //no transition cleared
        break;
      case scm_nStateSET:
        if(scm_nEventRID == pa_nEIID) enterStateRESET();
        else return; //no transition cleared
        break;
      case scm_nStateRESET:
        if(scm_nEventSID == pa_nEIID) enterStateSET();
        else return; //no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 3.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; // 0 is always the initial state
        return;
    }
    pa_nEIID = cg_nInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while(true);
}

void FORTE_E_RS::readInputData(TEventID pa_nEIID) {
}

void FORTE_E_RS::writeOutputData(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventEOID: {
      RES_DATA_CON_CRITICAL_REGION();
      writeData(0, &var_Q, &conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_RS::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_E_RS::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_E_RS::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_RS::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_E_RS::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_RS::getVarInternal(size_t) {
  return nullptr;
}


void FORTE_E_RS::enterStateSTART(void) {
  m_nECCState = scm_nStateSTART;
}

void FORTE_E_RS::enterStateSET(void) {
  m_nECCState = scm_nStateSET;
  alg_SET();
  sendOutputEvent(scm_nEventEOID);
}

void FORTE_E_RS::enterStateRESET(void) {
  m_nECCState = scm_nStateRESET;
  alg_RESET();
  sendOutputEvent(scm_nEventEOID);
}



