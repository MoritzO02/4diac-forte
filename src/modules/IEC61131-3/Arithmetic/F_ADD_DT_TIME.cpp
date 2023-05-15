/*******************************************************************************
 * Copyright (c) 2013 ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "F_ADD_DT_TIME.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_ADD_DT_TIME_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_ADD_DT_TIME, g_nStringIdF_ADD_DT_TIME)

const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anDataInputNames[] = {g_nStringIdIN1, g_nStringIdIN2};

const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anDataInputTypeIds[] = {g_nStringIdDATE_AND_TIME, g_nStringIdTIME};

const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anDataOutputTypeIds[] = {g_nStringIdDATE_AND_TIME};

const TDataIOID FORTE_F_ADD_DT_TIME::scm_anEIWith[] = {0, 1, 255};
const TForteInt16 FORTE_F_ADD_DT_TIME::scm_anEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_F_ADD_DT_TIME::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_F_ADD_DT_TIME::scm_anEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ADD_DT_TIME::scm_anEventOutputNames[] = {g_nStringIdCNF};


const SFBInterfaceSpec FORTE_F_ADD_DT_TIME::scm_stFBInterfaceSpec = {
  1, scm_anEventInputNames, scm_anEIWith, scm_anEIWithIndexes,
  1, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  2, scm_anDataInputNames, scm_anDataInputTypeIds,
  1, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

FORTE_F_ADD_DT_TIME::FORTE_F_ADD_DT_TIME(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
    CFunctionBlock( pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId),
    var_IN1(CIEC_DATE_AND_TIME(0)),
    var_IN2(CIEC_TIME(0)),
    var_OUT(CIEC_DATE_AND_TIME(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_ADD_DT_TIME::executeEvent(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventREQID:
      var_OUT = func_ADD_DT_TIME(var_IN1, var_IN2);
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}

void FORTE_F_ADD_DT_TIME::readInputData(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventREQID: {
      RES_DATA_CON_CRITICAL_REGION();
      readData(0, &var_IN1, conn_IN1);
      readData(1, &var_IN2, conn_IN2);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_ADD_DT_TIME::writeOutputData(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventCNFID: {
      RES_DATA_CON_CRITICAL_REGION();
      writeData(0, &var_OUT, &conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_ADD_DT_TIME::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN1;
    case 1: return &var_IN2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_ADD_DT_TIME::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_ADD_DT_TIME::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_ADD_DT_TIME::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN1;
    case 1: return &conn_IN2;
  }
  return nullptr;
}

CDataConnection *FORTE_F_ADD_DT_TIME::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


