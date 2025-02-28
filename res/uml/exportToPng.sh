#!/bin/bash

classUMLDIR="../../doc/uml/class/"
seqUMLDIR="../../doc/uml/sequence/"
useCaseUMLDIR="../../doc/uml/usecase/"


function exportFileClass()
{
  nameFile=$1
  pathing="$classUMLDIR""$nameFile"".plantuml"
  plantuml $pathing
  mv "$classUMLDIR""$nameFile"".png" ./class/
}

function exportFileSeq()
{
  nameFile=$1
  pathing="$seqUMLDIR""$nameFile"".plantuml"
  plantuml $pathing
  mv "$seqUMLDIR""$nameFile"".png" ./sequence/
}


function exportFileUseCase()
{
  nameFile=$1
  pathing="$useCaseUMLDIR""$nameFile"".plantuml"
  plantuml $pathing
  mv "$useCaseUMLDIR""$nameFile"".png" ./usecase/
}

for dir in */; do 
  if [ "$dir" = "class/" ]; then
   exportFileClass "game/tetris_lib/GameClass"
   exportFileClass "connexion/ConnexionClass"

  elif [ "$dir" = "sequence/" ]; then
    exportFileSeq "connexion/ConnexionSequence"
    exportFileSeq "inscription/InscriptionSequence"

  elif [ "$dir" = "usecase/" ]; then
    exportFileUseCase "connexion/ConnexionUseCase"

    exportFileUseCase "en-jeu/ClassicUseCase"
    exportFileUseCase "en-jeu/DualUseCase"
    exportFileUseCase "en-jeu/EndlessUseCase"
    exportFileUseCase "en-jeu/RoyalUseCase"

    exportFileUseCase "matchmaking/MatchMakingUseCase"
    
    exportFileUseCase "menu-principal/MenuPrincipalUseCase"

    exportFileUseCase "system-besoins-fonctionnels/SystemBesoinsFonctionnelsUseCase"
  fi

done
