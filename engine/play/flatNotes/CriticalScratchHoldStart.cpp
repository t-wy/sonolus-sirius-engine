class SiriusCriticalScratchHoldStart: public FlatNote {
	public:
	static constexpr const char* name = "Sirius Critical Scratch Hold Start";

	let getSprite() { return Sprites.CriticalNoteLeft; }
	let getBucket() { return Buckets.ScratchHoldStart; }
    ClipsArray getClips() { return {
    	perfect: Clips.Perfect,
    	great: Clips.Perfect,
    	good: Clips.Good
    }; }
    EffectsArray getEffects() { return {
    	linear: Effects.CriticalLinear,
    	circular: Effects.CriticalCircular,
    }; }
};
