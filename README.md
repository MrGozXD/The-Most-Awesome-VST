# The-Most-Awesome-VST
VST+RaspPi+STM32F7

## Développement du plug-in VST pour Renoise

IDE : Visual Studio 2022

Langage : C++

Framework : JUCE
https://docs.juce.com/master/tutorial_synth_using_midi_input.html

Initialisation du projet : Projuce

## Fabrication du clavier 

Hardware : STM32F7

IDE : STM32CubeIDE

Langage : C

BENGHANEM Ali

LALEU Margot

Nous avons codé une interface s'affichant sur l'écran d'une carte STM32F7. Cette interface présente 12 touches, ou bouttons, correspondant aux 12 notes d'une octave. Nous avons associé à chaque touche le nom de la note associée et une fonction jouant cette note lorsque l'événement "on a cliqué sur la touche" se produit. Chaque note étant codée par son code MIDI. 
Nous avons ensuite ajouté 2 bouttons à notre interfaces, intitulés "+" et "-", dont le but est d'augmenter ou de diminuer l'octave sur laquelle seront jouées les notes suivantes. Pour simplifier, nous avons choisi de limiter le nombre d'octaves à 10, car la 11ème octave ne présente pas de code MIDI pour toutes les notes de l'octave.
