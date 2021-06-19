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
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{ 
  // n_particle = 100000;
  

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  // delete particle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  //this function is called at the begining of ecah event
  //
  // for (G4int i = 0; i<n_particle;i++){
    G4PrimaryParticle* primaryParticle = new G4PrimaryParticle(particle);
    primaryParticle->SetMomentum(0,0,15.*MeV);
    primaryParticle->SetMass(particle->GetPDGMass());
    primaryParticle->SetCharge(particle->GetPDGCharge());
    primaryParticle->SetTotalEnergy(15.*MeV);
    G4double rfull = 0.5*cm;
    G4double r = rfull*pow(G4UniformRand(), 0.5);
    G4double phi = G4UniformRand()*2.*M_PI*rad;
    // G4double size = 0.8; 
    G4double x0 = r*cos(phi);//size * envSizeXY * (G4UniformRand()-0.5);
    G4double y0 = r*sin(phi);//size * envSizeXY * (G4UniformRand()-0.5);
    G4double z0 = -1 * cm;
    G4ThreeVector position = G4ThreeVector(x0, y0, z0);  

    G4PrimaryVertex* vertex = new G4PrimaryVertex(position, 0);
    vertex->SetPrimary(primaryParticle);
    anEvent->AddPrimaryVertex(vertex);
  // }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

