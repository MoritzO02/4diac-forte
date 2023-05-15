/*******************************************************************************
 * Copyright (c) 2013 ACIN, fortiss GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "F_ACOS.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_ACOS_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_ACOS, g_nStringIdF_ACOS)

const CStringDictionary::TStringId FORTE_F_ACOS::scm_anDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_ACOS::scm_anDataInputTypeIds[] = {g_nStringIdANY_REAL};

const CStringDictionary::TStringId FORTE_F_ACOS::scm_anDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_ACOS::scm_anDataOutputTypeIds[] = {g_nStringIdANY_REAL};

const TDataIOID FORTE_F_ACOS::scm_anEIWith[] = {0, 255};
const TForteInt16 FORTE_F_ACOS::scm_anEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ACOS::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_F_ACOS::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_F_ACOS::scm_anEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ACOS::scm_anEventOutputNames[] = {g_nStringIdCNF};


const SFBInterfaceSpec FORTE_F_ACOS::scm_stFBInterfaceSpec = {
  1, scm_anEventInputNames, scm_anEIWith, scm_anEIWithIndexes,
  1, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  1, scm_anDataInputNames, scm_anDataInputTypeIds,
  1, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

FORTE_F_ACOS::FORTE_F_ACOS(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
    CFunctionBlock( pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId),
    var_IN(CIEC_ANY_REAL_VARIANT()),
    var_OUT(CIEC_ANY_REAL_VARIANT()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_ACOS::executeEvent(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventREQID:
      var_OUT = std::visit([](auto &&paIN) -> CIEC_ANY_REAL_VARIANT {
          return func_ACOS(paIN);
      }, var_IN);
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}

void FORTE_F_ACOS::readInputData(TEventID pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventREQID: {
      RES_DATA_CON_CRITICAL_REGION();
      readData(0, &var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_ACOS::writeOutputData(TEventID pa_nEIID) {
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

CIEC_ANY *FORTE_F_ACOS::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_ACOS::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_ACOS::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_ACOS::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_ACOS::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


