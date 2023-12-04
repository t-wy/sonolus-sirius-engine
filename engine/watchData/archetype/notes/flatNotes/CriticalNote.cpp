class SiriusCriticalNote: public SiriusFlatNote {
	public:

	string name = "Sirius Critical Note";

	var getClip() { return Clips.CriticalPerfect; }
	var getLinearEffect() { return Effects.CriticalLinear; }
	var getCircularEffect() { return Effects.CriticalCircular; }

	var updateParallel() {
		return {
			drawNormalNote(Sprites.CriticalNote, lane, enLane, beat)
		};
	}
};
