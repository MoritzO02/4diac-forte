/*******************************************************************************
 * Copyright (c) 2020 Johannes Kepler University
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "GEN_STRUCT_MUX.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_STRUCT_MUX_gen.cpp"
#endif


DEFINE_GENERIC_FIRMWARE_FB(GEN_STRUCT_MUX, g_nStringIdGEN_STRUCT_MUX);

const CStringDictionary::TStringId GEN_STRUCT_MUX::scm_anEventInputNames[] = { g_nStringIdREQ };
const CStringDictionary::TStringId GEN_STRUCT_MUX::scm_anEventOutputNames[] = { g_nStringIdCNF };

const CStringDictionary::TStringId GEN_STRUCT_MUX::scm_anDataOutputNames[] = { g_nStringIdOUT };

const TForteInt16 GEN_STRUCT_MUX::scm_anEIWithIndexes[] = {0};
const TForteInt16 GEN_STRUCT_MUX::scm_anEOWithIndexes[] = {0};
const TDataIOID GEN_STRUCT_MUX::scm_anEOWith[] = {0, 255};


void GEN_STRUCT_MUX::executeEvent(int paEIID) {
  if(scm_nEventREQID == paEIID) {
    CIEC_ANY *members = OUT().getMembers();
    for (size_t i = 0; i < OUT().getStructSize(); i++){
      members[i].setValue(*getDI(static_cast<unsigned int>(i)));
    }
    sendOutputEvent(scm_nEventCNFID);
  }
}

GEN_STRUCT_MUX::GEN_STRUCT_MUX(const CStringDictionary::TStringId paInstanceNameId, CResource *paSrcRes) :
    CGenFunctionBlock<CFunctionBlock>(paSrcRes, paInstanceNameId){
}

GEN_STRUCT_MUX::~GEN_STRUCT_MUX(){
  if(0!= m_pstInterfaceSpec){
    delete[](m_pstInterfaceSpec->m_anEIWith);
    delete[](m_pstInterfaceSpec->m_aunDINames);
    delete[](m_pstInterfaceSpec->m_aunDIDataTypeNames);
    delete[](m_pstInterfaceSpec->m_aunDODataTypeNames);
  }
}

bool GEN_STRUCT_MUX::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) {
  bool retval = false;
  CStringDictionary::TStringId structTypeNameId = getStructNameId(paConfigString);

  CIEC_ANY *data = CTypeLib::createDataTypeInstance(structTypeNameId, 0);

  if(0 != data){
      if(data->getDataTypeID() == CIEC_ANY::e_STRUCT){
      // we could find the struct
      CIEC_STRUCT *structInstance = static_cast<CIEC_STRUCT *>(data);

      TDataIOID* eiWith = new TDataIOID[structInstance->getStructSize() + 1];
      CStringDictionary::TStringId* diDataTypeNames = new CStringDictionary::TStringId[structInstance->getStructSize()];
      CStringDictionary::TStringId* diNames = new CStringDictionary::TStringId[structInstance->getStructSize()];
      CStringDictionary::TStringId* doDataTypeNames = new CStringDictionary::TStringId[1];

      paInterfaceSpec.m_nNumEIs = 1;
      paInterfaceSpec.m_aunEINames = scm_anEventInputNames;
      paInterfaceSpec.m_anEIWith = eiWith;
      paInterfaceSpec.m_anEIWithIndexes = scm_anEIWithIndexes;
      paInterfaceSpec.m_nNumEOs = 1;
      paInterfaceSpec.m_aunEONames = scm_anEventOutputNames;
      paInterfaceSpec.m_anEOWith = scm_anEOWith;
      paInterfaceSpec.m_anEOWithIndexes = scm_anEOWithIndexes;
      paInterfaceSpec.m_nNumDIs = static_cast<TForteUInt8>(structInstance->getStructSize());
      paInterfaceSpec.m_aunDINames = diNames;
      paInterfaceSpec.m_aunDIDataTypeNames = diDataTypeNames;
      paInterfaceSpec.m_nNumDOs = 1;
      paInterfaceSpec.m_aunDONames = scm_anDataOutputNames;
      paInterfaceSpec.m_aunDODataTypeNames = doDataTypeNames;
      doDataTypeNames[0] = structTypeNameId;

      for (size_t i = 0; i < paInterfaceSpec.m_nNumDIs; i++){
        eiWith[i] = static_cast<TForteUInt8>(i);
        diNames[i] = structInstance->elementNames()[i];
        diDataTypeNames[i] = (&(structInstance->getMembers()[i]))->getTypeNameID();
      }
      eiWith[paInterfaceSpec.m_nNumDIs] = scmWithListDelimiter;
      retval= true;
    } else {
      DEVLOG_DEBUG("GEN_STRUCT_MUX: data type is not a struct: %s\n", CStringDictionary::getInstance().get(structTypeNameId));
    }
    delete data;
  } else {
    DEVLOG_DEBUG("GEN_STRUCT_MUX: Couldn't create struct of type: %s\n", CStringDictionary::getInstance().get(structTypeNameId));
  }
  return retval;
}


CStringDictionary::TStringId  GEN_STRUCT_MUX::getStructNameId(const char *paConfigString){
  const char *acPos = strchr(paConfigString, '_');
  if(0 != acPos){
    acPos++;
    acPos = strchr(acPos, '_');
    if(0 != acPos){
      acPos += 2;  //put the postion one after the seperating number
      return CStringDictionary::getInstance().getId(acPos);
    }
  }
  return CStringDictionary::scm_nInvalidStringId;
}



