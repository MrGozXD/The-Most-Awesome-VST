# The-Most-Awesome-VST
VST+RaspPi+STM32F7
Projet réalisé par : LALEU Margot, BENGHANEM Ali, TRISTANT Simon, PELOUTIER Yannis

## Développement du plug-in VST pour Renoise

IDE : Visual Studio 2022

Langage : C++

Framework : JUCE
https://docs.juce.com/master/tutorial_synth_using_midi_input.html

Initialisation du projet : Projuce

Après création du code, JUCE va fournir les différents fichiers permettant de build le plug-in au format .vst3. Il y a différentes manière de build : avec XCode sur 
macOs, Visual Studio sur Windows et Makefile sur Linux.


## Fabrication du clavier 

Hardware : STM32F7

IDE : STM32CubeIDE

Langage : C

Nous avons codé une interface s'affichant sur l'écran d'une carte STM32F7 Discovery. Cette interface présente 12 touches, ou boutons, correspondant aux 12 notes d'une octave. Nous avons associé à chaque touche le nom de la note associée et une fonction jouant cette note lorsque l'événement "on a cliqué sur la touche" se produit. Chaque note étant codée par son code MIDI. 
Attention à ce qu'il y ait un "délai" entre l'envoie de la note MIDI avec la fonction SendNoteOn, et l'arrêt de l'envoie de cette même note via la fonction sendNoteOff, sinon la note ne sera pas jouée.
Nous avons ensuite ajouté 2 boutons à notre interfaces, intitulés "+" et "-", dont le but est d'augmenter ou de diminuer l'octave sur laquelle seront jouées les notes suivantes. Pour simplifier, nous avons choisi de limiter le nombre d'octaves à 10, car la 11ème octave ne présente pas de code MIDI pour toutes les notes de l'octave.

## Configuration RaspPi

-Installer Debian/RaspOs sur la carte

-Installer la version correspondante de Renoise sur votre Rasp (pour une Rasp4 de l'école, choisir Renoise - Linux armhf) https://www.renoise.com/download 

-Installer le plug-in .vst3 obtenu après build sur la Rasp

-Brancher la STM32F7 Discovery

-Lancer le plug-in sur Renoise

-Sélectionner la STM32F7 comme MIDI Device In

-Enjoy !

