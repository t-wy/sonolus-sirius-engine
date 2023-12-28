using namespace std;

const string Scope = "sirius";

#include"configuration/options.cpp"
#include"configuration/ui.cpp"
#ifdef play
using namespace playData;
#include"skins.cpp"
#include"effects.cpp"
#include"particles.cpp"
// #include"data/buckets.cpp"
#include"data/constants.cpp"
#include"data/types.cpp"
#include"data/utils.cpp"
#include"getSplitLine.cpp"
#include"data/archetypes/Initialization.cpp"
#include"data/archetypes/InputManager.cpp"
#include"data/archetypes/Stage.cpp"
#include"data/archetypes/flatNotes/FlatNote.cpp"
#include"data/archetypes/flatNotes/NormalNote.cpp"
#include"data/archetypes/flatNotes/CriticalNote.cpp"
// #include"data/archetype/CriticalNote.cpp"
// #include"data/archetype/FlickNote.cpp"
// #include"data/archetype/HoldStart.cpp"
// #include"data/archetype/CriticalHoldStart.cpp"
// #include"data/archetype/ScratchHoldStart.cpp"
// #include"data/archetype/CriticalScratchHoldStart.cpp"
// #include"data/archetype/Sound.cpp"
// #include"data/archetype/HoldEighth.cpp"
// #include"data/archetype/HoldEnd.cpp"
// #include"data/archetype/ScratchHoldEnd.cpp"
// #include"data/archetype/SyncLine.cpp"
// #include"data/archetype/SplitLine.cpp"
#elif tutorial
using namespace tutorialData;
#include"skins.cpp"
#include"effects.cpp"
#include"particles.cpp"
#include"tutorialData/instructionTexts.cpp"
#include"tutorialData/instructionIcons.cpp"
#include"tutorialData/constants.cpp"
#include"tutorialData/utils.cpp"
#include"getSplitLine.cpp"
#include"tutorialData/components/Note.cpp"
#include"tutorialData/components/Flick.cpp"
#include"tutorialData/components/Hold.cpp"
#include"tutorialData/components/Scratch.cpp"
#include"tutorialData/components/JumpScratch.cpp"
#include"tutorialData/preprocess.cpp"
#include"tutorialData/navigate.cpp"
#include"tutorialData/update.cpp"
#elif preview
using namespace previewData;
#include"skins.cpp"
#include"previewData/constants.cpp"
#include"previewData/utils.cpp"
#include"getSplitLine.cpp"
#include"previewData/archetype/Initialization.cpp"
#include"previewData/archetype/Stage.cpp"
#include"previewData/archetype/NormalNote.cpp"
#include"previewData/archetype/CriticalNote.cpp"
#include"previewData/archetype/FlickNote.cpp"
#include"previewData/archetype/HoldStart.cpp"
#include"previewData/archetype/HoldEighth.cpp"
#include"previewData/archetype/CriticalHoldStart.cpp"
#include"previewData/archetype/ScratchHoldStart.cpp"
#include"previewData/archetype/CriticalScratchHoldStart.cpp"
#include"previewData/archetype/HoldEnd.cpp"
#include"previewData/archetype/ScratchHoldEnd.cpp"
#include"previewData/archetype/Sound.cpp"
#include"previewData/archetype/SyncLine.cpp"
#include"previewData/archetype/SplitLine.cpp"
#elif watch
using namespace watchData;
#include"skins.cpp"
#include"effects.cpp"
#include"particles.cpp"
#include"watchData/updateSpawn.cpp"
#include"watchData/constants.cpp"
#include"watchData/utils.cpp"
#include"getSplitLine.cpp"
#include"watchData/archetype/Initialization.cpp"
#include"watchData/archetype/Stage.cpp"
#include"watchData/archetype/notes/flatNotes/FlatNote.cpp"
#include"watchData/archetype/notes/flatNotes/NormalNote.cpp"
#include"watchData/archetype/notes/flatNotes/CriticalNote.cpp"
#include"watchData/archetype/notes/flatNotes/FlickNote.cpp"
#include"watchData/archetype/notes/flatNotes/HoldStart.cpp"
#include"watchData/archetype/notes/flatNotes/CriticalHoldStart.cpp"
#include"watchData/archetype/notes/flatNotes/ScratchHoldStart.cpp"
#include"watchData/archetype/notes/flatNotes/CriticalScratchHoldStart.cpp"
#include"watchData/archetype/notes/holdTickNotes/HoldTickNote.cpp"
#include"watchData/archetype/notes/holdTickNotes/HoldEnd.cpp"
#include"watchData/archetype/notes/holdTickNotes/ScratchHoldEnd.cpp"
#include"watchData/archetype/notes/holdTickNotes/HoldEighth.cpp"
#include"watchData/archetype/notes/holdTickNotes/Sound.cpp"
#include"watchData/archetype/SyncLine.cpp"
#include"watchData/archetype/SplitLine.cpp"
#endif
