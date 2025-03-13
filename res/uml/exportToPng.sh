#!/bin/bash

classUMLDIR="../../doc/uml/class/"
seqUMLDIR="../../doc/uml/sequence/"
useCaseUMLDIR="../../doc/uml/usecase/"

classUMLDiag=("game/tetris_lib/GameClass" 
              "game/tetris_royal_lib/EffectClass"
              "game/tetris_royal_lib/GameEngineClass"
              "game/tetris_royal_lib/GameStateClass"
              "game/tetris_royal_lib/PlayerTetrisClass"
              "game/tetris_royal_lib/PlayerStateClass"
              "game/GameStructureClass"
              "client/ControllerClass"
              "client/InterfaceClass"
              "client/ScreenManagerClass"
              "client/NetworkManagerClass"
              "client/ClientStructureClass"
#              "connexion/ConnexionClass"
              "common/BindingClass"
              "common/coreInGameClass"
              "server/DatabaseClass"
              "server/GameServerClass"
              "server/NetworkClass")
            

seqUMLDiag=("ConnexionSequence" 
            "InscriptionSequence"
            "GameClientSequence"
            "GameServerSequence"
            "GameClientSequence"
            "MatchMakingServerSequence")

useCaseUMLDiag=("connexion/ConnexionUseCase"
                "en-jeu/ClassicUseCase" 
                "en-jeu/DualUseCase"
                "en-jeu/EndlessUseCase" 
                "en-jeu/RoyalUseCase" 
                "matchmaking/MatchMakingUseCase" 
                "menu-principal/MenuPrincipalUseCase" 
                "system-besoins-fonctionnels/SystemBesoinsFonctionnelsUseCase")


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
    for (( i = 0; i<${#classUMLDiag[@]}; i++ )); do
      exportFileClass ${classUMLDiag[$i]}
    done

  elif [ "$dir" = "sequence/" ]; then
    for (( i = 0; i<${#SeqUMLDiag[@]}; i++ )); do
      #exportFileSeq ${SeqUMLDiag[$i]}
      echo "hello"
    done

  elif [ "$dir" = "usecase/" ]; then
    for (( i = 0; i<${#useCaseUMLDiag[@]}; i++ )); do
      #exportFileUseCase ${useCaseUMLDiag[$i]}
      echo "hello2"
    done

  fi

done
