//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1TrackingAction.cc 71007 2013-06-09 16:14:59Z maire $
//
/// \file B1TrackingAction.cc
/// \brief Implementation of the B1TrackingAction class

#include "B1TrackingAction.hh"
#include "G4Event.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1TrackingAction::B1TrackingAction():G4UserTrackingAction()
{
	counterAlpha = 0;
  	counterNeutron = 0;
	counterProton = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1TrackingAction::~B1TrackingAction()
{ ; }

void B1TrackingAction::PreUserTrackingAction(const G4Track* track)
{
	G4String ParticleName = track->GetParticleDefinition()->GetParticleName();
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	if (ParticleName == "alpha"){
		counterAlpha++;
		G4cout<<ParticleName<<" : "<<counterAlpha << " process: "<< track->GetCreatorProcess()->GetProcessName() + " " + track->GetCreatorProcess()->GetProcessTypeName(track->GetCreatorProcess()->GetProcessType()) <<G4endl;
		G4EventManager::GetEventManager()->KeepTheCurrentEvent();
		G4cout<<track->GetKineticEnergy()/keV << " keV" <<G4endl;
		analysisManager->FillH1(0, track->GetKineticEnergy());
	}

	if (ParticleName == "neutron"){
		counterNeutron++;
		G4cout<<ParticleName<<" : "<<counterNeutron<< " process: "<< track->GetCreatorProcess()->GetProcessName() + " " + track->GetCreatorProcess()->GetProcessTypeName(track->GetCreatorProcess()->GetProcessType()) <<G4endl;
		G4EventManager::GetEventManager()->KeepTheCurrentEvent();
		G4cout<<track->GetKineticEnergy()/keV << " keV" <<G4endl;
		analysisManager->FillH1(1, track->GetKineticEnergy());
  	}

	if (ParticleName == "proton"){
		counterNeutron++;
		G4cout<<ParticleName<<" : "<<counterProton<< " process: "<< track->GetCreatorProcess()->GetProcessName() + " " + track->GetCreatorProcess()->GetProcessTypeName(track->GetCreatorProcess()->GetProcessType()) <<G4endl;
		G4EventManager::GetEventManager()->KeepTheCurrentEvent();
		G4cout<<track->GetKineticEnergy()/keV << " keV" <<G4endl;
		analysisManager->FillH1(2, track->GetKineticEnergy());
  	}
	  G4EventManager::GetEventManager()->KeepTheCurrentEvent();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
