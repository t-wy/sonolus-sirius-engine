class SiriusHoldStart: public FlatNote {
	public:
	static constexpr const char* name = "Sirius Hold Start";

	let getSprite() { return Sprites.HoldNoteLeft; }
	let getBucket() { return Buckets.HoldStart; }
    ClipsArray getClips() { return {
    	perfect: Clips.Perfect,
    	great: Clips.Perfect,
    	good: Clips.Good
    }; }
    EffectsArray getEffects() { return {
    	linear: Effects.HoldLinear,
    	circular: Effects.HoldCircular,
    }; }
};
