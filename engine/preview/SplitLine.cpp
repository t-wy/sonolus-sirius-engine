class SplitLine: public Archetype {
    public:

    static constexpr const char* name = "Sirius Split Line";

	defineEntityData(beat);
	defineEntityData(endBeat);
	defineEntityData(split);
	defineEntityData(color);

	SonolusApi preprocess() {
		FUNCBEGIN
		duration = Max(duration.get(), beat);
		return VOID;
	}

	SonolusApi render() {
		FUNCBEGIN
		getSplitLine(color);
		drawPreviewSplitLine(beat - splitLineAnimationStart, beat, 1, split);
		drawPreviewSplitLine(beat, endBeat, 0, split);
		drawPreviewSplitLine(endBeat, endBeat + splitLineAnimationEnd, 2, split);
		return VOID;
	}
};