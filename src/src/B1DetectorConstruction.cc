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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 5.*cm;
  G4double world_sizeZ  = 5.*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
  G4LogicalVolume* logicWorld =                    
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Target
  //  
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  G4double target_sizeR = 0.5*7.*mm;
  G4double target_sizeZ  = 0.02*mm;
  G4double target_dPhi = 2.*M_PI*rad;
  G4Tubs* target =    
    new G4Tubs("target", 0, target_sizeR, 0.5* target_sizeZ, 0., target_dPhi); //its size
  G4LogicalVolume* logicTarget =                         
    new G4LogicalVolume(target,            //its solid
                        target_mat,             //its material
                        "Target");         //its nam
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicTarget,                //its logical volume
                    "Target",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Plastic
  //  
  G4Material* shape_mat = nist->FindOrBuildMaterial("G4_CR39");
  G4double shape_sizeXY  = 1.5*cm;
  G4double shape_sizeZ  = 0.1*mm;
  G4Box* solidShape = new G4Box("Shape", 0.5*shape_sizeXY, 0.5*shape_sizeXY, 0.5*shape_sizeZ);
  G4LogicalVolume* logicShape =                         
    new G4LogicalVolume(solidShape,         //its solid
                        shape_mat,          //its material
                        "Shape");           //its name
  for (G4int i = 0; i < 7; i++)
    new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,target_sizeZ*0.5 + (i+0.5)*shape_sizeZ ),         //at (0,0,0)
                    logicShape,                //its logical volume
                    "Shape",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    i,                       //copy number
                    checkOverlaps); 

  

  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
