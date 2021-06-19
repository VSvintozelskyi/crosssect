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
// $Id: B1RunAction.cc 71007 2013-06-09 16:14:59Z maire $
//
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"

// #include "G4EventManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction():G4UserRunAction()
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{ 
    // delete G4AnalysisManager::Instance();
}

void B1RunAction::UserRunAction(const G4Track* track)
{
}

void B1RunAction::BeginOfRunAction(const G4Run* run){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // analysisManager->SetFileName("../root/test.root");
    analysisManager->SetVerboseLevel(1);
    analysisManager->OpenFile("../root/test.root");
    G4cout<<"Creating histo:"<< G4endl;
    G4cout << analysisManager->CreateH1("AlpKE","Alpha Kinetic energy", 100, 0., 10*MeV) << G4endl;
    G4cout << analysisManager->CreateH1("NeuKE","Neutron Kinetic energy", 100, 0., 10*MeV) << G4endl;
    G4cout << analysisManager->CreateH1("ProtKE","Proton Kinetic energy", 100, 0., 10*MeV) << G4endl;
}

void B1RunAction::EndOfRunAction(const G4Run* run){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // Write and close the output file
    G4cout<<"1 mean: "<< analysisManager->GetH1(0)->mean() << "  rms: "<<analysisManager->GetH1(0)->rms()<<G4endl;
    G4cout<<"2 mean: "<< analysisManager->GetH1(1)->mean() << "  rms: "<<analysisManager->GetH1(1)->rms()<<G4endl;
    analysisManager->Write();
    analysisManager->CloseFile();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
