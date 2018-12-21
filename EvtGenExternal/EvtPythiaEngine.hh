#ifdef EVTGEN_PYTHIA
//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package. If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 2011      University of Warwick, UK
//
// Module: EvtPythiaEngine
//
// Description: Interface to the Pytha 8 external generator
//
// Modification history:
//
//    John Back       April 2011            Module created
//
//------------------------------------------------------------------------

#ifndef EVTPYTHIAENGINE_HH
#define EVTPYTHIAENGINE_HH

#include "EvtGenModels/EvtAbsExternalGen.hh"
#include "EvtGenExternal/EvtPythiaRandom.hh"

#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtVector4R.hh"

#include "Pythia8/Pythia.h"
#include "Pythia8/ParticleData.h"

#include <string>
#include <vector>
#include <map>
#include <memory>

class EvtPythiaEngine : public EvtAbsExternalGen {

public:

  EvtPythiaEngine(std::string xmlDir = "./xmldoc",
		  bool convertPhysCodes = false,
		  bool useEvtGenRandom = true);

  virtual ~EvtPythiaEngine();

  bool doDecay(EvtParticle* theMother) override;

  void initialise() override;

protected:

private:

  void updateParticleLists();
  void updatePhysicsParameters();

  void createPythiaParticle(EvtId& particleId, int PDGCode);
  bool validPDGCode(int PDGCode);
  void updatePythiaDecayTable(EvtId& particleId, int aliasInt, int PDGCode);
  void storeDaughterInfo(EvtParticle* theParticle, int startInt);

  void clearDaughterVectors();
  void clearPythiaModeMap();

  void createDaughterEvtParticles(EvtParticle* theParent);

  int getModeInt(EvtDecayBase* decayModel);

  std::unique_ptr<Pythia8::Pythia> _genericPythiaGen;
  std::unique_ptr<Pythia8::Pythia> _aliasPythiaGen;
  Pythia8::Pythia* _thePythiaGenerator;

  std::vector<int> _daugPDGVector;
  std::vector<EvtVector4R> _daugP4Vector;

  typedef std::map<int, std::vector<int> > PythiaModeMap;
  PythiaModeMap _pythiaModeMap;

  bool _convertPhysCodes, _initialised, _useEvtGenRandom;

  std::unique_ptr<EvtPythiaRandom> _evtgenRandom;

  std::map<int, int> _addedPDGCodes;

};

#endif

#endif
