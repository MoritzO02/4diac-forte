/*******************************************************************************
 * Copyright (c) 2018 fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Kirill Dorofeev
 *      - initial implementation
 *******************************************************************************/
#include "E_DEMUX_tester.h"

#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_DEMUX_tester_gen.cpp"
#endif

DEFINE_FB_TESTER(E_DEMUX_tester, g_nStringIdE_DEMUX)

E_DEMUX_tester::E_DEMUX_tester(CResource *m_poTestResource) :
    CFBTester(m_poTestResource){

  SETUP_INPUTDATA(&m_oIn_K);
}

void E_DEMUX_tester::executeAllTests(){
  evaluateTestResult(testCase_K0(), "K0");
  evaluateTestResult(testCase_K1(), "K1");
  evaluateTestResult(testCase_K2(), "K2");
  evaluateTestResult(testCase_K3(), "K3");
  evaluateTestResult(testCase_K_GT_3(), "K_GT_3");
}

/***********************************************************************************/

bool E_DEMUX_tester::testCase_K0(){
  /* prepare inputparameters */
  m_oIn_K = 0;

  /* trigger the inputevent */
  triggerEvent(0);

  return checkForSingleOutputEventOccurence(0);
}

bool E_DEMUX_tester::testCase_K1(){
  /* prepare inputparameters */
  m_oIn_K = 1;

  /* trigger the inputevent */
  triggerEvent(0);

  return checkForSingleOutputEventOccurence(1);
}

bool E_DEMUX_tester::testCase_K2(){
  /* prepare inputparameters */
  m_oIn_K = 2;

  /* trigger the inputevent */
  triggerEvent(0);

  return checkForSingleOutputEventOccurence(2);
}

bool E_DEMUX_tester::testCase_K3(){
  /* prepare inputparameters */
  m_oIn_K = 3;

  /* trigger the inputevent */
  triggerEvent(0);

  return checkForSingleOutputEventOccurence(3);
}

bool E_DEMUX_tester::testCase_K_GT_3(){
  /* prepare inputparameters */
  m_oIn_K = 4;

  /* trigger the inputevent */
  triggerEvent(0);

  return !checkForSingleOutputEventOccurence(0)
      && !checkForSingleOutputEventOccurence(1)
      && !checkForSingleOutputEventOccurence(2)
      && !checkForSingleOutputEventOccurence(3);
}
